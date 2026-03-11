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
  display.drawRect(0, 50, 128, 12, SSD1306_WHITE);        // border
  int barWidth = map(percent, 0, 100, 0, 124);
  display.fillRect(2, 52, barWidth, 8, SSD1306_WHITE);    // fill

  display.display();

  Serial.print("Raw: "); Serial.print(raw);
  Serial.print("  Percent: "); Serial.println(percent);

  delay(100);
}