#include <Adafruit_LiquidCrystal.h>  // LiquidCrystal using the Wire library
#include <TinyDHT.h>        // lightweit DHT sensor library
#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket
 
// Uncomment whatever type sensor you are using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22     // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define TEMPTYPE 1        // Use Fahrenheit (0 for celsius)
 
// Trinket GPIO #1 would be better but LED prevents digital talk with DHT sensor
#define DHTPIN 1          // Sensor connected to GPIO #1 (use a
                          //  1K ohm pullup to 5V to make it work!)
DHT dht(DHTPIN, DHTTYPE); // Define Temp Sensor
 
// Connect display via  i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
 
void setup() {  // first line sets a 5V Trinket to 16 MHz operation
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz
  dht.begin();  // Initialize DHT Teperature Sensor
  
  lcd.begin(16, 2);  // set up the LCD's number of rows and columns: 
  lcd.setBacklight(HIGH); // Set backlight (HIGH - on)
}

void loop() {
  int8_t h = dht.readHumidity();
  int16_t t = dht.readTemperature(TEMPTYPE);

  lcd.setCursor(0, 0); 
  if ( t == BAD_TEMP || h == BAD_HUM ) { // if error conditions (see TinyDHT.h)
     lcd.print("Shit's broke");       //   print error message
  } else {
     lcd.print("Humidity: ");            // write to LCD
     lcd.setCursor(10,0); 
     lcd.print(h);
     lcd.setCursor(12, 0); 
     lcd.print(" % ");
     lcd.setCursor(0, 1); 
     lcd.print("Temp:"); 
     lcd.setCursor(7, 1); 
     lcd.print(t);
     lcd.setCursor(10, 1); 
     lcd.print("*F");
  }
  delay(2000);  // (DHT sensor max rate)
}