#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

LiquidCrystal_I2C lcd(0x27, 16, 2); 
// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
  lcd.init();
  lcd.noBacklight();
}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);

  // lcd.clear();
  lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print("temperature"); 
  lcd.setCursor(0, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(temperatureC);

  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  if(temperatureC > 24){
    lcd.backlight();
  }
  else{
    lcd.noBacklight();
  }
  
  delay(5000);
}