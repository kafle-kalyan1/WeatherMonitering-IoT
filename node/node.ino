#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>

#define BAUD_RATE 115200

// Wifi credentials
const char* ssid = "";
const char* password = "";

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

// Firebase project API Key
#define API_KEY "AIzaSyByl7HRpdf2y1v7ce4fp4_72_v87uGkW44"

// RTDB URLefine the RTDB URL
#define DATABASE_URL "https://wms-iic-iot-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

StaticJsonDocument<200> doc;

//Initialisation of Sensor
int temp = 0;
int hum = 0;
int co2 = 0;
int tempF = 0;
bool rain = false;


void setup() {
  Serial.begin(BAUD_RATE);
  connectWifi();
  connectFirebase();
}

void loop() {
  connectArduino();
  pushToFirebase();
  delay(5000);
}

void connectWifi() {
  //Connect to the wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void connectArduino() {
  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming JSON message
    String jsonString = Serial.readString();

    // Deserialize JSON document
    deserializeJson(doc, jsonString);

    // Extract the sensor data
    hum = doc["humidity"];
    temp = doc["temperature"];
    co2 = doc["co2"];
    tempF = doc["tempF"];
    rain = doc["rain"]


    // Print the sensor data to the serial monitor
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.print("co2: ");
    Serial.println(co2);

  } else {
    Serial.println("Arduino not connected yet!");
  }
}

void connectFirebase() {
  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  // Sign up
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void pushToFirebase() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    // Write humidity data on the database path green-house/int
    if (Firebase.RTDB.setInt(&fbdo, "Weather/Humidity", hum)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.setInt(&fbdo, "Weather/Temperature", temp)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.setInt(&fbdo, "Weather/gas", co2)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.setInt(&fbdo, "Weather/tempF", tempF)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }if (Firebase.RTDB.setInt(&fbdo, "Weather/rain", rain)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


  }
}
