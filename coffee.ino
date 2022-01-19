#include <OneWire.h>
#include <DallasTemperature.h>

// Coffee temperature
const int PERFECT_TEMP = 60;
const int MEDIUM_DIFF= 5;
const int LOW_DIFF = 15;

// Pin layput
const int SENSOR_PIN = 10;
const int GREEN_PIN = 6;
const int YELLOW_PIN = 5;
const int RED_PIN = 4;

// Init
OneWire oneWire(SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);

float tempCelsius;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tempSensor.begin();

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tempSensor.requestTemperatures();
  tempCelsius = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(tempCelsius);

  Serial.print(" - Coffee is: ");

  if (tempCelsius == -127) {
    Serial.print("error (temp disconnected) \n");
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(RED_PIN, HIGH);
    delay(1000);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
    delay(1000);
    return;
  }

  if (tempCelsius > PERFECT_TEMP - MEDIUM_DIFF && tempCelsius < PERFECT_TEMP + MEDIUM_DIFF) {
    Serial.print("perfect");
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, LOW);
  } else if (tempCelsius > PERFECT_TEMP - LOW_DIFF && tempCelsius < PERFECT_TEMP + LOW_DIFF) {
    Serial.print("meh");
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
  } else {
    Serial.print("nope");
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
  }

  Serial.print("\n");
  
  delay(500);
}
