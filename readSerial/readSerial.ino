#define moistureReadPin 33
#define tempHumReadPin 32
#define DHTTYPE DHT11 // define the sensor type
 
// ---- LIBRARIES
#include <DHT.h>

// ---- DEFINE OBJECT
DHT dht(tempHumReadPin, DHTTYPE); // create a dht object

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int moisture = analogRead(moistureReadPin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  if (isnan(moisture)) {
    Serial.println(F("Failed to read from Moisture sensor!"));
    delay(500);
    return;
  } else if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensro!"));
    delay(500);
    return;
  }
  delay(1000);
  dumpMeasuredValue(moisture, humidity, temperature);
}

void dumpMeasuredValue(int m, float h, float t) {
  Serial.print(F("Moisture Level: "));
  Serial.println(m);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  return;
}

