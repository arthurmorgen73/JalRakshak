/*
  JalRakshak - Basic Smart Water Tank Controller
  Board: ESP32 DevKit V1
  Wokwi sensor: HC-SR04 (simulation substitute for JSN-SR04T)

  Tank geometry:
    Calibrated sensor-to-bottom distance = 120 cm
    20% level -> 96 cm measured distance -> pump ON
    95% level -> 6 cm measured distance  -> pump OFF

  Relay assumption:
    Wokwi relay module uses default NPN / active-HIGH input.
*/

#include <Arduino.h>

constexpr uint8_t TRIG_PIN  = 5;
constexpr uint8_t ECHO_PIN  = 18;
constexpr uint8_t RELAY_PIN = 23;
constexpr uint8_t LED_PUMP  = 19; // green = pump ON
constexpr uint8_t LED_STOP  = 21; // red = pump OFF

constexpr float TANK_HEIGHT_CM = 120.0f;
constexpr float LOW_LEVEL_PCT  = 20.0f;
constexpr float HIGH_LEVEL_PCT = 95.0f;

constexpr uint32_t ECHO_TIMEOUT_US = 30000;
constexpr uint8_t SAMPLE_COUNT = 5;
constexpr uint16_t SAMPLE_GAP_MS = 35;

bool pumpOn = false;
bool sensorFault = false;

float readDistanceOnceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  if (duration == 0) return -1.0f;

  return duration / 58.0f;
}

// Small median filter helps reject occasional ultrasonic spikes.
float readFilteredDistanceCm() {
  float samples[SAMPLE_COUNT];
  uint8_t count = 0;

  for (uint8_t i = 0; i < SAMPLE_COUNT; i++) {
    const float d = readDistanceOnceCm();
    if (d >= 2.0f && d <= 400.0f) {
      samples[count++] = d;
    }
    delay(SAMPLE_GAP_MS);
  }

  if (count < 3) return -1.0f;

  // Insertion sort (only five values).
  for (uint8_t i = 1; i < count; i++) {
    float key = samples[i];
    int8_t j = i - 1;
    while (j >= 0 && samples[j] > key) {
      samples[j + 1] = samples[j];
      j--;
    }
    samples[j + 1] = key;
  }

  return samples[count / 2];
}

void setPump(bool turnOn) {
  pumpOn = turnOn;

  // Default Wokwi relay module (transistor: "npn") is active HIGH.
  digitalWrite(RELAY_PIN, pumpOn ? HIGH : LOW);
  digitalWrite(LED_PUMP, pumpOn ? HIGH : LOW);
  digitalWrite(LED_STOP, pumpOn ? LOW : HIGH);

  Serial.print("PUMP: ");
  Serial.println(pumpOn ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PUMP, OUTPUT);
  pinMode(LED_STOP, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  setPump(false);

  Serial.println();
  Serial.println("================================");
  Serial.println(" JalRakshak Smart Water Tank");
  Serial.println(" ESP32 + Ultrasonic + Relay");
  Serial.println(" SMART AUTO mode");
  Serial.println("================================");
}

void loop() {
  const float distanceCm = readFilteredDistanceCm();

  // Fail-safe for missing/invalid sensor readings: stop the pump.
  if (distanceCm < 0.0f || distanceCm > TANK_HEIGHT_CM) {
    sensorFault = true;
    setPump(false);
    Serial.println("FAULT: Invalid/no ultrasonic reading.");
    Serial.println("Pump forced OFF for this reading.");
    delay(1000);
    return;
  }

  sensorFault = false;

  float levelPct =
      ((TANK_HEIGHT_CM - distanceCm) / TANK_HEIGHT_CM) * 100.0f;
  levelPct = constrain(levelPct, 0.0f, 100.0f);

  const float volumeLitres = levelPct * 10.0f; // 100% = 1000 L

  Serial.println("--------------------------------");
  Serial.print("Sensor distance : ");
  Serial.print(distanceCm, 1);
  Serial.println(" cm");

  Serial.print("Water level     : ");
  Serial.print(levelPct, 1);
  Serial.println(" %");

  Serial.print("Water volume    : ");
  Serial.print(volumeLitres, 0);
  Serial.println(" / 1000 L");

  // Two-threshold control provides hysteresis:
  // start at/below 20%, stop at/above 95%.
  if (!pumpOn && levelPct <= LOW_LEVEL_PCT) {
    Serial.println("LOW LEVEL reached: AUTO START");
    setPump(true);
  } else if (pumpOn && levelPct >= HIGH_LEVEL_PCT) {
    Serial.println("HIGH LEVEL reached: AUTO CUT-OFF");
    setPump(false);
  }

  Serial.print("Pump status     : ");
  Serial.println(pumpOn ? "RUNNING" : "STOPPED");

  delay(1000);
}
