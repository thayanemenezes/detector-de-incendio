# Fire Detection System with ESP32 and DHT11 Sensor

This project implements a fire detection system using an ESP32 microcontroller, a DHT11 temperature sensor, and a buzzer. The system monitors the temperature and triggers an alarm if it exceeds a predefined threshold. Additionally, it sends an SMS alert through Twilio's API when a fire hazard is detected. The alarm can be manually deactivated using a push button.

---

## Features

- **Temperature Monitoring**: Continuously reads the ambient temperature using the DHT11 sensor.
- **Fire Detection**: Triggers an alarm if the temperature exceeds a preset threshold.
- **SMS Alert**: Sends a notification via Twilio API to a designated phone number when a fire hazard is detected.
- **Manual Alarm Deactivation**: Allows the user to reset the alarm using a physical button.
- **Visual and Audio Alarm**: Activates an LED and buzzer as part of the alert mechanism.

---

## Components Used

- **ESP32**: Microcontroller for processing and communication.
- **DHT11 Sensor**: Measures temperature.
- **Buzzer**: Emits sound when an alarm is triggered.
- **LED**: Lights up during an alarm.
- **Push Button**: Resets the alarm when pressed.
- **Wi-Fi**: Enables connectivity for sending SMS notifications via Twilio.

---

## How It Works

1. **Wi-Fi Connection**: The ESP32 connects to the configured Wi-Fi network during startup.
2. **Temperature Reading**: The DHT11 sensor measures the temperature every second.
3. **Fire Detection**:
   - If the temperature exceeds `20.0°C`, the system:
     - Activates the buzzer and LED.
     - Sends an SMS alert using Twilio.
4. **Manual Reset**: Pressing the push button turns off the alarm and resumes normal monitoring.

---

## Requirements

### Hardware
- ESP32 microcontroller
- DHT11 temperature sensor
- Buzzer
- LED
- Push button
- Resistors and jumper wires

### Software
- Arduino IDE
- [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library)

---

## Setup

1. **Hardware Connections**:
   - Connect the DHT11 sensor to pin `4`.
   - Connect the buzzer to pin `19`.
   - Connect the LED to pin `18`.
   - Connect the push button to pin `2` with a pull-up resistor.
2. **Software Configuration**:
   - Install the necessary libraries in the Arduino IDE.
   - Replace the placeholders `REDE` and `SENHA` with your Wi-Fi credentials.
   - Replace `twilioAccountSid`, `twilioAuthToken`, `twilioPhoneNumber`, and `destinationPhoneNumber` with your Twilio account details and the recipient phone number.
3. **Upload Code**:
   - Upload the code to the ESP32 using the Arduino IDE.

---

## Usage

1. Power up the ESP32.
2. Monitor the serial output to verify the system's status.
3. The system will trigger an alarm and send an SMS alert if the temperature exceeds the threshold.
4. Press the push button to deactivate the alarm.

---

## Code Overview

### Key Sections
- **Wi-Fi Setup**: Establishes connection to the network.
- **Temperature Monitoring**: Reads and processes temperature data.
- **Alarm Trigger**: Activates buzzer and LED, sends SMS.
- **Alarm Reset**: Deactivates alarm and resumes monitoring.

---

## Dependencies

- **WiFi Library**: For Wi-Fi connectivity.
- **HTTPClient Library**: For HTTP requests to Twilio.
- **Adafruit Sensor and DHT Libraries**: For sensor integration.

---

## Future Improvements

- Add support for humidity-based fire detection.
- Enhance alarm thresholds for different environments.
- Implement a web interface for remote monitoring and control.

