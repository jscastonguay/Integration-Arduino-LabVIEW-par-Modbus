///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)

Connection_state connectionState = NO_WIFI;
WiFiServer wifiServer(502);
WiFiClient client;
unsigned long timeRef;


Connection_status Connection_getStatus() {
  return connectionStatus;
}


WiFiClient Connection_getWiFiClient() {
  return client; 
}


void Connection_setup() {
  WiFi.begin(ssid, pass);
  timeRef = millis();
}


void Connection_loop() {

  unsigned long now = millis();

  switch (connectionStatus) {

    case NO_WIFI:
      if (now - timeRef >= 10000) {
        timeRef = now;

        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        if (WiFi.begin(ssid, pass) == WL_CONNECTED) {
          printWifiStatus();
          wifiServer.begin();
          connectionStatus = CONNECTING_CLIENT;
        }
      }
      break;

    case CONNECTING_CLIENT:
      client = wifiServer.available();
      if (client) {
        Serial.println("new client");
        connectionStatus = NEW_CLIENT_CONNECTED;
      }
      break;

    case NEW_CLIENT_CONNECTED:
      connectionStatus = CONNECTING_CLIENT;
      break;

    case CONNECTING_CLIENT:
      if (!client.connected()) {
        Serial.println("client disconnected");
        connectionStatus = CONNECTING_CLIENT;
      }
      break;
  }
}


void printWifiStatus() {

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
