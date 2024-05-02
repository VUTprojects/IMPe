#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SHT31.h>

#define OLED_RESET    -1
Adafruit_SSD1306 display(OLED_RESET);

#define SHT3X_ADDR 0x44
Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  if (!sht31.begin(SHT3X_ADDR)) {
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);

  float temp = sht31.readTemperature();
  float humidity = sht31.readHumidity();

  display.print("Temp: ");
  display.println(temp);
  display.print("Humidity: ");
  display.println(humidity);

  Serial.print("Temp: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  if (temp > 25.0){
    Serial.println("Temperature hot");
  }
  else {
    Serial.println("Temperature normal");
  }

  display.display();
  delay(1000);
}
