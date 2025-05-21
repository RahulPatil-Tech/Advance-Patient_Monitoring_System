#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include <DFRobot_MAX30102.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MLX90614 mlx;
DFRobot_MAX30102 particleSensor;

const char* ssid = "A3";
const char* password = "842481634";

unsigned long channelID = 2404444;
char writeAPIKey[] = "JDAL05J02SQ834MO";

const int pushButton = 4;
int mode = 0;

int32_t SPO2;
int8_t SPO2Valid;
int32_t heartRate;
int8_t heartRateValid;

const int irSensorPin = 2;
const int glucoseThreshold = 500;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  mlx.begin();
  pinMode(pushButton, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(4, 20);
  display.print("Tuning...");
  display.display();
  delay(100);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  while (!particleSensor.begin()) {
    Serial.println("MAX30102 not found");
    delay(1000);
  }

  particleSensor.sensorConfiguration(50, SAMPLEAVG_4, MODE_MULTILED, SAMPLERATE_100, PULSEWIDTH_411, ADCRANGE_16384);

  connectToWiFi();
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
}

void loop() {
  checkButton();

  if (mode == 0) {
    BPMFunction();
  } else if (mode == 1) {
    GlucoseFunction();
  } else if (mode == 2) {
    TemperatureFunction();
  } else if (mode == 3) {
    Spo2();
  }
}

void checkButton() {
  static int lastButtonState = HIGH;
  int buttonState = digitalRead(pushButton);

  if (buttonState == LOW && lastButtonState == HIGH) {
    mode = (mode + 1) % 4;
    display.clearDisplay();
  }

  lastButtonState = buttonState;
}

void sendDataToThingSpeak(const String& data) {
  String serverPath = "/update?api_key=" + String(writeAPIKey) + "&" + data;

  if (client.connect("api.thingspeak.com", 80)) {
    client.print(String("GET ") + serverPath + " HTTP/1.1\r\n" +
                 "Host: api.thingspeak.com\r\n" +
                 "Connection: close\r\n\r\n");

    delay(1000);

    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    Serial.println();
  } else {
    Serial.println("Connection to ThingSpeak failed");
  }

  client.stop();
}

void BPMFunction() {
  particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("BPM: ");
  display.println(heartRate);
  display.setCursor(0, 20);
  display.print("BPM Valid: ");
  display.println(heartRateValid);
  display.display();

  String data = "field1=" + String(heartRate);
  sendDataToThingSpeak(data);

  delay(1000);
  display.clearDisplay();
}

void GlucoseFunction() {
  int sensorValue = analogRead(irSensorPin);
  float glucoseLevel = map(sensorValue, 0, 1023, 70, 200);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.print("IR: ");
  display.println(sensorValue);
  display.setCursor(0, 30);
  display.print("GL: ");
  display.println(glucoseLevel);
  delay(1000);
  display.display();

  String data = "field2=" + String(sensorValue);
  sendDataToThingSpeak(data);

  if (glucoseLevel > glucoseThreshold) {
    Serial.println("High Glucose Level! Take necessary action.");
  }
}

void TemperatureFunction() {
  float temperatureC = mlx.readObjectTempC();

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 50);
  display.print(temperatureC, 1);
  display.drawCircle(92, 35, 3, WHITE);
  display.setCursor(100, 50);
  display.print("C");
  display.display();

  String data = "field3=" + String(temperatureC);
  sendDataToThingSpeak(data);

  delay(1000);
  display.clearDisplay();
}

void Spo2() {
  particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("SpO2: ");
  display.print(SPO2);
  display.println("%");
  display.setCursor(0, 20);
  display.print("Valid: ");
  display.print(SPO2Valid);
  display.display();

  String data = "field4=" + String(SPO2);
  sendDataToThingSpeak(data);

  delay(1000);
  display.clearDisplay();
}
