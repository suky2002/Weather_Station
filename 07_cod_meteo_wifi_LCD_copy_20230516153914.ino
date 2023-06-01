const char* ssid = "Amiion"; // aici se scrie numele SSID al routerului WiFi de acasa
const char* password = "Octombrie@"; // aici este parola pentru conectarea la router
// includem librariile pentru WiFi
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
// aici sunt librariile din exercitiile anterioare pentru senzor si display
#include <Wire.h> // senzorul BME 280 si ecranul LCD functioneaza ambele pe protocolul I2c
#include <Adafruit_BME280.h> // includem libraria pentru senzorul BME280
#include <LiquidCrystal_I2C.h>// aceasta este libraria pentru ecranul LCD; pe chipurile ESP8266 da un warning, dar functioneaza corect
LiquidCrystal_I2C lcd(0x27,20,4);  // setam LCD-ul la adresa 0x27 si 20 de coloane cu 4 linii
Adafruit_BME280 bme280; 
String serverName = "http://192.168.1.139/database.php"; // aici se defineste serverul catre care trimitem datele; cheia este introdusa automat.
void setup(){lcd.init();                     
  lcd.backlight();
  Serial.begin(9600);
  while (! Serial);
  Serial.println (); // scriem o linie goala
  bool status; 
  status = bme280.begin(0x76);  
  if (!status) {
    Serial.println("Nu s-au putut citi datele de la senzorul BME280!");
    while (1);  }
  WiFi.begin(ssid, password); // ne conectam la WiFi
  while (WiFi.status() != WL_CONNECTED) { delay(5000);
    Serial.println("Conectare la WiFi..");
  lcd.setCursor(0,0);  lcd.print("                    ");
  lcd.setCursor(0,0);  lcd.print("Conectare la WiFi..");
  lcd.setCursor(0,1);  lcd.print("                    ");
  lcd.setCursor(0,2);  lcd.print("                    ");
  lcd.setCursor(0,3);  lcd.print("                    "); }
  Serial.println(WiFi.localIP());   // afisam adresa IP locala
  lcd.setCursor(0,3);  lcd.print("                    ");
  lcd.setCursor(0,3);  lcd.print(WiFi.localIP()); }
char text[13]; 
void loop(){
  lcd.setCursor(0,0);   lcd.print("                    ");
  lcd.setCursor(0,1);   lcd.print("                    ");
  lcd.setCursor(0,2);   lcd.print("                    ");
  lcd.setCursor(0,3);   lcd.print("                    ");
  lcd.setCursor(0,2);   lcd.print("Adresa IP: ");
  lcd.setCursor(0,3);   lcd.print("                    ");
  lcd.setCursor(0,3);   lcd.print(WiFi.localIP());
  delay(10000);
  lcd.setCursor(0,0);  lcd.print("                    ");
  lcd.setCursor(0,1);  lcd.print("                    ");
  lcd.setCursor(0,2);  lcd.print("                    ");
  lcd.setCursor(0,3);  lcd.print("                    ");
  lcd.setCursor(0, 0);  lcd.print("Temp =");
  lcd.setCursor(0, 1);  lcd.print("Humi =");
  lcd.setCursor(0, 2);  lcd.print("Pres =");
  lcd.setCursor(0, 3);  lcd.print("Alt  =");
  // citim temperatura, umiditatea, presiunea si altitudinea din libraria senzorului
  float temperature = bme280.readTemperature();  // se citeste temperatura
  float humidity    = bme280.readHumidity();     // se citeste umiditatea
  float pressure    = bme280.readPressure();     // se citeste presiunea
  float altitude_   = bme280.readAltitude(1013.25); // se citeste altitudinea care poate fi calibrata
    // 0: afisam temperatura
  sprintf(text, "%d.%02u%cC  ", (int)temperature, (int)(temperature * 100)%100, 223);
  lcd.setCursor(7, 0);  lcd.print(text);
  // 1: afisam  umiditatea
  sprintf(text, "%d.%02u %%  ", (int)humidity, (int)(humidity * 100)%100);
  lcd.setCursor(7, 1);  lcd.print(text);
  // 2: afisam presiunea
  sprintf(text, "%u.%02u hPa ", (int)(pressure / 100), (int)((uint32_t)pressure % 100));
  lcd.setCursor(7, 2);  lcd.print(text); 
  // 3: afisam altitudinea
  sprintf(text, "%u.%02u m ", (int)(altitude_), (int)((uint32_t)altitude_ % 100));
  lcd.setCursor(7, 3);  lcd.print(text); 
  // scriem si pe consola seriala
  Serial.print("Temperatura = "); Serial.print(temperature);    Serial.println(" °C");
  Serial.print("Umiditate  = ");  Serial.print(humidity);       Serial.println(" %");
  Serial.print("Presiune   = ");  Serial.print(pressure / 100); Serial.println(" hPa");
  Serial.print("Alt. Estim.= ");  Serial.print(altitude_);      Serial.println(" m");    
  Serial.println();  // scriem o linie goala
  delay(10000);       // asteptam 10 secunde
  if(WiFi.status()== WL_CONNECTED){   //verificam conexiunea WiFi
    HTTPClient http;
    // trimitem datele catre server
    WiFiClient client;
    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "&temperature=" + String(bme280.readTemperature())
                           + "&humidity=" + String(bme280.readHumidity()) + "&pressure=" + String(bme280.readPressure()/100.0F) + "&altitude=" + (bme280.readAltitude(1013.25));
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
  lcd.setCursor(0,0);  lcd.print("                    ");
  lcd.setCursor(0,0);  lcd.print("httpRequestData: ");
  lcd.setCursor(0,1);  lcd.print("                    ");
  lcd.setCursor(0,1);  lcd.print(httpRequestData);
  int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) { Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
  lcd.setCursor(0,2);  lcd.print("                    ");
  lcd.setCursor(0,2);  lcd.print("HTTP Response code: ");
  lcd.setCursor(0,3);  lcd.print("                    ");
  lcd.setCursor(0,3);  lcd.print(httpResponseCode); }
    else { Serial.print("Error code: ");
      Serial.println(httpResponseCode);
  lcd.setCursor(0,2);  lcd.print("                    "); 
  lcd.setCursor(0,2);  lcd.print("Error code: ");
  lcd.setCursor(0,3);  lcd.print("                    ");
  lcd.setCursor(0,3);  lcd.print(httpResponseCode);  }
    http.end(); }  // incheiem tramsmisia 
  else { Serial.println("WiFi deconectat");
  lcd.setCursor(0,0);  lcd.print("                    ");
  lcd.setCursor(0,0);  lcd.print("WiFi deconectat"); }
  delay(10000); }