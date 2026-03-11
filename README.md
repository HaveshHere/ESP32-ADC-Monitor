# 🎛️ ESP32 ADC Monitor

Real-time ADC monitoring using a potentiometer displayed as voltage, raw value and percentage on an OLED screen with ESP32.

## 📸 Hardware Setup

![Image](https://github.com/user-attachments/assets/836ae99d-b98b-423d-ad73-40769b61f8fd)

## 🎥 Demo

https://github.com/user-attachments/assets/66e5b931-d15c-4b22-a09c-93f8e11db5ad

## 🛠️ Hardware Requirements

- ESP32 Development Board
- Potentiometer (10k)
- SSD1306 OLED Display (128x64, I2C)
- Breadboard
- Jumper Wires

## 🔌 Wiring Table

### OLED Display (SSD1306)

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

### Potentiometer

| Potentiometer Pin   | ESP32 Pin   |
|---------------------|-------------|
| Left pin (VCC)      | 3.3V        |
| Middle pin (Signal) | GPIO 4 (D4) |
| Right pin (GND)     | GND         |

## 📦 Libraries Required

Install these via Arduino IDE → Library Manager:

- `Adafruit SSD1306`
- `Adafruit GFX Library`

## 💻 Code

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define POT_PIN 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.display();
}

void loop() {
  int raw = analogRead(POT_PIN);             // 0 - 4095
  int percent = map(raw, 0, 4095, 0, 100);  // convert to 0-100%

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 0);
  display.println("Potentiometer");
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  // Percentage number
  display.setTextSize(3);
  display.setCursor(30, 20);
  display.print(percent);
  display.println("%");

  // Progress bar
  display.drawRect(0, 50, 128, 12, SSD1306_WHITE);
  int barWidth = map(percent, 0, 100, 0, 124);
  display.fillRect(2, 52, barWidth, 8, SSD1306_WHITE);

  display.display();

  Serial.print("Raw: "); Serial.print(raw);
  Serial.print("  Percent: "); Serial.println(percent);

  delay(100);
}
```

## 🚦 Getting Started

1. Clone this repository.
2. Open the `.ino` file in Arduino IDE.
3. Install the required libraries via Library Manager.
4. Select your ESP32 board under **Tools → Board → ESP32 Dev Module**.
5. Connect your hardware following the wiring table above.
6. Upload the code and turn the potentiometer knob to see live ADC readings on the OLED.
