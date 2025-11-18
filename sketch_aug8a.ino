#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// WiFi credentials
const char* ssid = "Rushi";
const char* password = "11111111";

// Weather API info
String openWeatherMapApiKey = "7fb821132959e7acb10d548b5f8547c6";  // Replace with your API key
String city = "Ahmednagar";
String countryCode = "IN";

// Timer settings
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;  // 10 seconds

String jsonBuffer;

void setup() {
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
    delay(500);
    Serial.print(".");
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }
}

void loop() {
  Serial.println(city);
  delay(10000);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.begin(ssid, password);
    delay(5000);
    return;  // skip this loop if not connected
  }

  if ((millis() - lastTime) > timerDelay) {
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&appid=" + openWeatherMapApiKey + "&units=metric";

    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println(jsonBuffer);

    JSONVar myObject = JSON.parse(jsonBuffer);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing failed!");
      return;
    }

    Serial.print("Temperature: ");
    Serial.println(myObject["main"]["temp"]);
    Serial.print("Pressure: ");
    Serial.println(myObject["main"]["pressure"]);
    Serial.print("Humidity: ");
    Serial.println(myObject["main"]["humidity"]);
    Serial.print("Wind Speed: ");
    Serial.println(myObject["wind"]["speed"]);

    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}
