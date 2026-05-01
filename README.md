# 🔋 SandVault - Technical Documentation & Firmware

Welcome to the hardware and firmware repository for **SandVault**. 

This repository is dedicated to the Proof of Concept (PoC) physical prototype of SandVault. Its purpose is to physically validate the thermodynamic heat transfer ($Q = mc\Delta T$) from a solid medium (sand) to a liquid loop (water) using an ESP32 for real-time telemetry. This implementation serves as the hardware foundation for our scalable thermal energy storage solution.

---

## 🛠️ 1. Bill of Materials (BOM)

To replicate this physical prototype, you will need the following components:

**Thermal Core & Fluid Dynamics:**
* 2x Nested metal pots (inner and outer shell).
* High-density Rock Wool (for insulation between pots).
* 13 kg of dry sand (thermal storage medium).
* Copper & Silicone tubing (for the internal heat exchanger loop).
* 1x External water container (for the water loop inlet/outlet).
* 1x 12V Water Pump.

**Microcontroller & Telemetry:**
* 1x ESP32 Microcontroller.
* 1x USB-C Data Cable (to flash the ESP32 and read serial data on a computer).
* 2x DS18B20 1-Wire Temperature Sensors.
* 1x 4.7kΩ Resistor (Crucial: acts as a pull-up resistor for the 1-Wire bus).
* 1x Breadboard.
* Assorted Jumper Wires (Male/Male, Male/Female, Female/Female).

**Heating & Power Distribution:**
* 2x 26W Soldering-tip resistors (230V AC - embedded directly in the sand).
* 1x 50W Submerged resistor (12V DC).
* 1x 230V-to-12V Transformer.
* PVC power cables with standard 230V wall plugs.
* Multi-strand electrical cable (FVV type) for custom junctions.
* Electrical insulating tape.

**Control & Safety Architecture:**
* *Note:* The following components were installed in the circuit architecture but were manually bypassed during the final PoC test runs to guarantee data logging amidst relay communication bugs. Any future iteration should actively utilize these:
* 3x Relay Modules (intended for ESP32 automated switching of the pump and heating elements).
* Blade and Glass Fuses + respective fuse holders (mandatory safety measure when operating 230V AC systems near water loops).

---

## 🔌 2. Wiring & Circuit Architecture

Due to the mix of high-voltage and low-voltage components, the system is split into two isolated circuits. 

**Low-Voltage Circuit (Telemetry & Fluid Dynamics):**
* The ESP32 is powered via standard USB-C (5V).
* **Sensors (DS18B20):**
  * `VCC` -> `3.3V`
  * `GND` -> `GND`
  * `DATA` -> `GPIO 5` *(Note: A 4.7kΩ pull-up resistor MUST bridge DATA and 3.3V to stabilize readings).*
* The 12V Water Pump and 12V 50W Resistor are powered directly from the 230V-to-12V Transformer.

**High-Voltage Circuit (Heating):**
* The 2x 26W AC resistors are connected directly to the 230V mains. 
* *Safety Note:* For this hackathon iteration, relays were bypassed. Switching was handled manually to ensure safe operation while logging the thermal rise.

---

## 💻 3. Firmware (`sensor_plotter.ino`)

The provided firmware is designed to capture real-time thermodynamic data and output it in a format readable by the Arduino IDE Serial Plotter.

### How to run it:
1. Clone this repository.
2. Open `sensor_plotter.ino` in the Arduino IDE.
3. Install the required libraries: `OneWire.h` and `DallasTemperature.h`.
4. Connect the ESP32 via USB-C and select the correct COM port and board (e.g., "DOIT ESP32 DEVKIT V1").
5. Upload the code.
6. Open the **Serial Plotter** (Set Baud Rate to `115200`).

### Telemetry Output:
The code initializes the 1-Wire bus on GPIO 5, locates the two DS18B20 sensors (Core Sand Temp and Water Loop Temp), and prints the data dynamically. This allowed us to successfully record the water loop rising from 20°C to 45°C in roughly three minutes, validating the thermodynamic efficiency of the system.
