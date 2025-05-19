#define BLYNK_TEMPLATE_ID "TMPL39Uso7HJ0"
#define BLYNK_TEMPLATE_NAME "Water Level Monitoring System"
#define BLYNK_AUTH_TOKEN "57Z-LPmFM1hjqWiex6To0aa3IIFE38P7"

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIG D5
#define ECHO D6
#define RELAY D7

#define LED1 D0
#define LED2 D3
#define LED3 D4
#define LED4 D8
#define LED5 D2  // Changed from D8 to D2 to avoid pin conflict

char auth[] = "57Z-LPmFM1hjqWiex6To0aa3IIFE38P7"; // Blynk Auth
char ssid[] = "ECED";  // WiFi SSID
char pass[] = "eced@tiet1";     // WiFi Password

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool manualControl = false;
int manualPumpState = HIGH; // HIGH = OFF


BLYNK_WRITE(V1) {
  int state = param.asInt(); // 1 = ON, 0 = OFF
  manualPumpState = state ? LOW : HIGH; // LOW = ON
  manualControl = true;

  // Also reflect the manual state in the virtual pump display
  Blynk.virtualWrite(V3, state);
}


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // lcd.begin(16, 2);
  // lcd.backlight();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RELAY, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(RELAY, HIGH);  // Pump OFF initially
}

void loop() {
  Blynk.run();

  // Measure distance
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  float distance = duration * 0.034 / 2.0; // cm

  int level = map(20 - distance, 0, 20, 0, 100); // % level
  level = constrain(level, 0, 100);

  // Update LCD
  // lcd.setCursor(0, 0);
  // lcd.print("Water Level:     ");
  // lcd.setCursor(0, 1);
  // lcd.print(level);
  // lcd.print("%       ");
  Serial.print("Water Level: ");
  Serial.print(level);
  Serial.print("%       ");

  // Send level to Blynk
  Blynk.virtualWrite(V0, level);

  // LED status and labels
  // lcd.setCursor(8, 0);
  if (level <= 20) {
    // lcd.print("Very Low ");
    Serial.print("Very Low ");
    Serial.println();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
  } else if (level <= 40) {
    // lcd.print("Low      ");
    Serial.print("Low      ");
    Serial.println();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
  } else if (level <= 60) {
    // lcd.print("Medium   ");
    Serial.print("Medium   ");
    Serial.println();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
  } else if (level <= 80) {
    // lcd.print("High     ");
    Serial.print("High     ");
    Serial.println();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, LOW);
  } else {
    // lcd.print("Full     ");
    Serial.print("Full     ");
    Serial.println();
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
  }

  // Pump Control
  
int pumpVirtualState = 0; // 0 = OFF, 1 = ON

if (manualControl) {
  pumpVirtualState = (manualPumpState == LOW) ? 1 : 0;
} else {
  if (level >= 85) {
    pumpVirtualState = 0; // OFF
  } else if (level < 20) {
    pumpVirtualState = 1; // ON
  } else {
    pumpVirtualState = 0; // OFF
  }

  // AUTO: update the Blynk switch (V1) to match auto state
  Blynk.virtualWrite(V1, pumpVirtualState);
}

  delay(1000);  // 1 sec delay
}