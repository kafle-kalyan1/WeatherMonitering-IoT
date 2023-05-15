#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#include <ArduinoJson.h>



LiquidCrystal_I2C lcd(0x3F,16,2);

StaticJsonDocument<200> doc;

//Pin
int pinDHT11 = 2;
int sensorPin = 4;


//Initialisation of Sensor
byte temp = 0;
byte hum = 0;
byte gas = 0;
byte tempF = 0;



void setup() {
  // lcd.init(); 
  lcd.begin();
  lcd.backlight();
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  
}

void loop() {
  int sensorValue = digitalRead(sensorPin);
  
if (sensorValue == LOW) { 
    
    Serial.println("It's raining!");  
  } else {
    Serial.println("It's not raining");
  }
   lcdd();
  //Obtain Temp, Hum and Moisture data
  dht11_sensor();


  // Clear the document and add the sensor data
  doc.clear();
  doc["humidity"] = hum;
  doc["temperature"] = temp;
  doc["co2"] = (gas,DEC);
  doc["tempF"] = tempF;
   if (sensorValue == LOW) {

  doc["rain"] = true;
   }
   else{
     doc["rain"] = false;
   }


  // Serialize JSON document
  String jsonString;
  serializeJson(doc, jsonString);

  // Send JSON message over serial
  Serial.println(jsonString);

  // Wait for a bit before sending the next message

}

void dht11_sensor() {
  SimpleDHT11 dht11(2);
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temp, &hum, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(",");
    Serial.println(SimpleDHTErrDuration(err));
    delay(1000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error DTH");
    delay(3000);
    
    return;
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temprature = ");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    lcd.print(" *C ||  ");
    tempF = (temp * 9/5) + 32;
    lcd.print(tempF);
    lcd.print(" *F");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity = ");
    lcd.print(hum);
    lcd.print(" %");
    delay(3000);

    Serial.print("Temprature(C) = ");
    Serial.println(temp);
    Serial.print("Humidity = ");
    Serial.println(hum);
    Serial.print("Temprature(F) = ");
    Serial.println(tempF);



  }
  gas = analogRead(0);
  Serial.print("co2 = ");
  Serial.println(gas,DEC);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("co2 = ");
  lcd.println(gas,DEC);
  lcd.print("PPM");
  delay(2000);

int sensorValue = digitalRead(sensorPin);
 if (sensorValue == LOW) {
  doc["rain"] = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("It's raining!");
  delay(1500);
  lcd.clear();
   }
   else{
     doc["rain"] = false;
       lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("It's not raining!");
  delay(1500);
  lcd.clear();
   }
   return;




}
  void lcdd(){
 

  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weather Monitor-");
    lcd.setCursor(0,1);
    lcd.print("ing System");
   
    delay(1000);
    lcd.print(".");
    delay(1000);
    lcd.print(".");
    delay(1000);
   lcd.print(".");
   delay(2000);
  
  }

