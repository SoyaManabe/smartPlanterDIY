// ----- LIBRARIES
#include <WiFi.h>
#include <dht11.h>

// ----- DEFINE PINS
#define moistureReadPin 33
#define dht11Pin 32
#define GET_ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

// ----- CONSTANTS (will not change)
const char* ssid="SoyaHome2.4";
const char* password="soya0922";
const char* host = "10.0.0.249"; // IP address of PC

// ----- VARIABLES (will change)

// ---- DEFINE OBJECT
//DHT dht(tempHumReadPin, DHTTYPE); // create a dht object
dht11 DHT11;
WiFiServer server(80); // create a wifi server object

// ---- TYPE UNION
typedef union {
  int val;
  byte binary[2];
} u;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.disconnect();
  delay(1000);
  bool done = true;
  WiFi.begin(ssid, password);
  while (done) {
    Serial.print("WiFi connecting");
    auto last = millis();
    while (WiFi.status() != WL_CONNECTED && last + 5000 > millis()) {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        done = false;
    } else {
        Serial.println("retry");
        WiFi.disconnect();
        WiFi.reconnect();
    }
  }

  Serial.println("¥nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop() {
  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 6342; // port num of PC side
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  int moisture = analogRead(moistureReadPin);
  delay(40);
  int chk = DHT11.read(dht11Pin);
  //int humidity = dht.readHumidity();
  //delay(40);
  //int temperature = dht.readTemperature();
  delay(40);


  if (isnan(moisture)) {
    Serial.println(F("Failed to read from Moisture sensor!"));
    delay(100);
    return;
  } else if (isnan(DHT11.humidity) || isnan(DHT11.temperature)) {
    Serial.println(F("Failed to read from DHT sensro!"));
    delay(100);
    return;
  }

  dumpMeasuredValue(moisture, DHT11.humidity, DHT11.temperature);
  
  u uMoisture, uHumidity, uTemperature;
  byte binary[6];

  uMoisture.val = moisture;
  uHumidity.val = DHT11.humidity;
  uTemperature.val = DHT11.temperature;

  binary[0] = uMoisture.binary[0];
  binary[1] = uMoisture.binary[1];
  binary[2] = uHumidity.binary[0];
  binary[3] = uHumidity.binary[1];
  binary[4] = uTemperature.binary[0];
  binary[5] = uTemperature.binary[1];
  
  client.write(binary, 6);
  //client.write(uMoisture.binary, 2);
  //delay(500);

  //client.println(datas));
  //client.print(msg);
  //client.print(datas[0]);

  Serial.println("send data...");
  Serial.println("closing connection");
  
  delay(1000);
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
