#include <WiFi.h>

// const char *ssid="XFSETUP-B428";
const char *ssid="SoyaHome";
// const char *password="diner5717follow";
const char *password="soya1374";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.println("¥nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("¥nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
