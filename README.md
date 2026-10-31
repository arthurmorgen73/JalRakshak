# 💧 JalRakshak – Smart Water Tank Management System

<p align="center">
  <strong>Save Water. Prevent Overflow. Build a Smarter Future.</strong>
</p>

<p align="center">
  An IoT-based smart water management solution designed to prevent water wastage through automated overhead water tank monitoring and pump control.
</p>

---

## 🌊 About the Project

**JalRakshak (जल रक्षक)** is a smart water tank management system that aims to eliminate water wastage caused by the overflow of overhead water tanks.

The system uses an ultrasonic water-level sensor to monitor the amount of water inside a tank. An ESP32/ESP8266 microcontroller processes the sensor readings and controls the water pump through a relay module.

By automating pump operations, JalRakshak helps conserve water, reduce manual effort, and promote efficient water management.

## 🚨 Problem Statement

Water wastage due to overhead tank overflow is a common problem in residential buildings, apartments, and other establishments.

Traditional water tank systems often require manual monitoring, which can lead to:

- Water wastage due to tank overflow.
- Unnecessary electricity consumption.
- Increased human effort.
- Inefficient water resource management.

## 💡 Proposed Solution

JalRakshak provides an automated solution using IoT technology.

The system continuously monitors the water level and automatically controls the motor pump based on predefined water-level thresholds.

**Key operating thresholds:**

| Water Level | System Action |
|---|---|
| 20% or below | Automatically starts the pump in Smart Mode |
| 50% | Generates a water-level notification |
| 80% | Generates a high-level warning |
| 95% | Automatically stops the pump |

This prevents tank overflow while ensuring water availability.

## ✨ Features

- **Automatic Water-Level Monitoring:** Monitors tank water levels using a waterproof ultrasonic sensor.
- **Smart Pump Control:** Automatically starts and stops the water pump based on water levels.
- **Overflow Prevention:** Stops the pump when the tank reaches 95% capacity.
- **Low Water Detection:** Starts the pump when the water level falls to 20% in Smart Mode.
- **Interactive Dashboard:** Displays water level, tank capacity, pump status, and system notifications.
- **Smart and Manual Modes:** Supports automated and manual pump operation in the prototype.
- **Water Conservation:** Helps reduce unnecessary water wastage.
- **Simulation Support:** Includes an interactive browser-based prototype and a Wokwi project.

## 🛠️ Hardware Requirements

The proposed physical implementation uses the following components:

| Component | Purpose |
|---|---|
| ESP32 / ESP8266 NodeMCU | Main microcontroller |
| JSN-SR04T Ultrasonic Sensor | Non-contact water-level measurement |
| 30A Relay Module | Water pump switching |
| Water Pump / Motor | Pumps water into the tank |
| Power Supply | Supplies power to the controller and peripherals |
| Connecting Wires | Electrical connections |
| Overhead Water Tank | Water storage and monitoring |

## 💻 Software Requirements

- Modern web browser (Chrome, Firefox, Edge, etc.)
- HTML5
- CSS3
- JavaScript
- Wokwi Simulator (for hardware simulation)

## ⚙️ Working Principle

The system operates through the following process:

1. The JSN-SR04T ultrasonic sensor is mounted at the top of the overhead water tank.
2. The sensor measures the distance between itself and the water surface.
3. The ESP32/ESP8266 processes the sensor readings and calculates the water level.
4. When the water level reaches 20% or below, Smart Mode activates the water pump.
5. As the tank fills, the system continuously monitors the water level.
6. At 80%, the system generates a warning notification.
7. When the tank reaches 95%, the controller switches off the pump through the relay.
8. The dashboard displays the current water level and pump status.

### System Architecture

```text
       Overhead Water Tank
                |
                v
      JSN-SR04T Ultrasonic
             Sensor
                |
                v
         ESP32 / ESP8266
          Microcontroller
                |
         +------+------+
         |             |
         v             v
     Relay Module   Dashboard
         |
         v
      Water Pump
         |
         v
    Tank Refilling
```

## 📊 Project Dashboard

The project includes an interactive web-based dashboard that demonstrates the proposed smart water management system.

The dashboard provides:

- Real-time-style water-level visualization.
- Tank capacity monitoring.
- Motor pump ON/OFF controls.
- Smart and Manual operating modes.
- Water consumption simulation.
- System notifications and alerts.
- Water-saving and ROI calculations.

**Note:** The browser dashboard is a simulation. Its displayed readings and automated operations are simulated rather than received from a connected physical sensor.

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/arthurmorgen73/JalRakshak.git
```

### 2. Navigate to the Project Directory

```bash
cd JalRakshak
```

### 3. Run the Web Prototype

Locate the HTML prototype:

```text
JalRakshak Smart Water Tank Prototype.html
```

Open this file in your preferred web browser.

No additional installation or build process is required for the browser-based prototype.

### 4. Explore the Simulation

Use the interactive dashboard to:

- Monitor simulated water levels.
- Start and stop the motor pump.
- Switch between Smart and Manual modes.
- Simulate household water consumption.
- Observe automatic pump control and notifications.

## 🔬 Wokwi Simulation

Explore the project's Wokwi simulation:

[**Open JalRakshak on Wokwi**](https://wokwi.com/projects/479431876603034625)

## 📁 Project Structure

```text
JalRakshak/
│
├── wokwi/
│   └── Hardware simulation files
│
├── JalRakshak Smart Water Tank Prototype.html
│
└── README.md
```

## 🌱 Future Enhancements

Some planned improvements include:

- Integration with a physical ESP32-based hardware system.
- Live water-level monitoring through an IoT dashboard.
- SMS and mobile application notifications.
- Cloud-based water consumption analytics.
- Multiple tank monitoring.
- Historical water usage reports.
- Improved fault detection and pump protection.

## 🌍 Environmental Impact

JalRakshak aims to support sustainable water consumption by minimizing unnecessary water wastage.

The project aligns with:

**United Nations Sustainable Development Goal 6 – Clean Water and Sanitation.**

By reducing tank overflow and promoting responsible water usage, JalRakshak contributes towards a more sustainable future.

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome!

1. Fork this repository.
2. Create a new branch:

   ```bash
   git checkout -b feature/YourFeature
   ```

3. Commit your changes:

   ```bash
   git commit -m "Add: Your Feature"
   ```

4. Push your branch:

   ```bash
   git push origin feature/YourFeature
   ```

5. Open a Pull Request.

## 👨‍💻 Author

**Arthur Morgen**

- GitHub: [@arthurmorgen73](https://github.com/arthurmorgen73)
- Project: [JalRakshak](https://github.com/arthurmorgen73/JalRakshak)

## 📜 License

No license is currently specified for this repository. Please contact the project owner regarding permissions for reuse and distribution.

---

<p align="center">
  💧 <strong>Every Drop Counts. Save Water with JalRakshak!</strong> 💧
</p>

<p align="center">
  Made with ❤️ for a sustainable future.
</p>
