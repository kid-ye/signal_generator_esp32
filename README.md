# ESP32 Signal Generator

The problem with current signal generators is that they are very expensive, not portable, and restricted to lab hours only.

We wanted to solve this problem with a minimal amount of capital spent while creating the best product for hobbyists and students.

## Features

- **Waveforms**: Sine, Square/Rectangle, Triangle, and Sawtooth waves
- **Wide Frequency Range**:
  - Sine: 16Hz - 500kHz
  - Square/Rectangle: 1Hz - 40MHz
  - Triangle/Sawtooth: 153Hz - 150kHz
- **Adjustable Parameters**:
  - Frequency with fine-tuning
  - Pulse width / Duty cycle (0-100%)
  - Amplitude (0-3.3V)
  - Resolution bit depth (1-12 bits for square wave)
- **Web Interface**: Control the signal generator remotely via WiFi
- **OLED Display**: Real-time FFT spectrum analysis
- **Touch Controls**: Use GPIO touch pins for frequency/pulse width adjustments
- **Physical Buttons**: Optional hardware button support
- **Potentiometer Support**: Control frequency or pulse width with a pot

## Hardware Requirements

- ESP32 Development Board (DevKit, NodeMCU, etc.)
- 128x64 I2C OLED Display (SSD1306) - Optional
- Potentiometer (optional)
- Physical buttons (optional)

## Pin Configuration

| Function            | GPIO Pin         |
| ------------------- | ---------------- |
| Waveform Generation | 25 or 26         |
| Potentiometer       | 34               |
| OLED SDA            | 21 (default I2C) |
| OLED SCL            | 22 (default I2C) |

## Dependencies

Install these libraries via Arduino Library Manager:

- **Adafruit SSD1306** - OLED display driver
- **Adafruit GFX Library** - Graphics library for display
- **arduinoFFT** - FFT analysis for spectrum display

## Installation

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support:
   - Go to File → Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
   - Go to Tools → Board → Boards Manager, search for "ESP32" and install
3. Install required libraries (see Dependencies above)
4. Open `code/sketch.ino` in Arduino IDE
5. Configure your WiFi credentials in the sketch:
   ```cpp
   const char *ssid = "YourWiFiName";
   const char *password = "YourPassword";
   ```
6. Select your ESP32 board and port
7. Upload!

## Usage

### Serial Commands

Connect via Serial Monitor (115200 baud) and use these commands:

| Command    | Description                                   |
| ---------- | --------------------------------------------- |
| `s`        | Switch to Sine wave                           |
| `r`        | Switch to Rectangle/Square wave               |
| `t`        | Switch to Triangle wave                       |
| `w`        | Switch to Sawtooth wave                       |
| `f<value>` | Set frequency (e.g., `f1000`, `f2.5k`, `f1m`) |
| `p<value>` | Set pulse width 0-100% (e.g., `p50`)          |
| `b<value>` | Set resolution bits 1-12 (e.g., `b6`)         |
| `a<value>` | Set amplitude 0-3.3V (e.g., `a2.5`)           |
| `save<n>`  | Save preset (e.g., `save1`)                   |
| `load<n>`  | Load preset (e.g., `load1`)                   |
| `e`        | Toggle extended information                   |
| `info`     | Show current settings                         |

### Web Interface

1. Connect to the ESP32's WiFi (AP mode) or your local network
2. Open the IP address shown in Serial Monitor
3. Use the web interface to control all parameters

## Configuration

Key settings can be modified at the top of `sketch.ino`:

```cpp
// Initial waveform settings
char mode = 'r';           // r=Rectangle, s=Sine, t=Triangle, w=Sawtooth
float_t frequency = 1000;  // Starting frequency in Hz
uint8_t pulse = 50;        // Duty cycle percentage

// WiFi settings
const char *ssid = "YourSSID";
const char *password = "YourPassword";

// OLED Display
bool useOLED = true;       // Enable/disable OLED

// Touch pins
uint8_t touchUPPin = 33;
uint8_t touchDOWNPin = 32;
```

## Project Structure

```
├── code/
│   ├── sketch.ino          # Main Arduino sketch
│   ├── WebPage.h           # Web interface HTML/CSS/JS
│   ├── Console.h           # Web console functionality
│   ├── nvs_increase.csv    # NVS partition configuration
│   └── ESP32 Signal Generator_files/
│       └── pageScript.bundle.js
├── documentation/
│   └── *.pdf               # Project documentation
└── images/                 # Project images
```

## License

This project is open source. Feel free to use and modify as needed.
