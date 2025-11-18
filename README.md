# ESP32-Weather-Monitor-OpenWeatherMap
Real-time weather monitoring using ESP32 and OpenWeatherMap API.

This project demonstrates how to connect an ESP32 to WiFi and fetch real-time weather information from the OpenWeatherMap REST API.
The ESP32 makes an HTTP GET request every 10 seconds, retrieves JSON weather data, parses it using the Arduino_JSON library, and prints the values on the Serial Monitor.

Features
ESP32 WiFi connectivity
HTTP GET request to OpenWeatherMap
JSON data parsing (temperature, humidity, pressure, wind speed)
Automatic reconnection to WiFi
Configurable city, API key, and update interval
Clean, readable code with error handling

Technologies Used
ESP32
Arduino IDE
OpenWeatherMap API
HTTPClient
JSON Parsing (Arduino_JSON)

How It Works
ESP32 connects to WiFi using the provided SSID and password.
Every 10 seconds, it sends a GET request to the OpenWeatherMap API.
Server response is parsed into JSON format.
Weather parameters are extracted and printed.
Auto-reconnects if WiFi drops.

Applications
IoT Weather Stations
Smart Home Automation
Environmental Monitoring
Educational IoT Projects
