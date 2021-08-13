// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h> // Driver Library for the LCD Module

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Adjust to (0x27,20,4) for 20x4 LCD

// OFFLINE WITH PLOTTING
// THIS IS WORKING CODE FOR TEMP / HUMIDITY AND GAS MONITOR
// DESIGNED BY NATHAN PACEY

// ************INSTRUCTIONS FOR USE************
// run the serial monitor and put in which output you want
// PIN 13 is the temperature LED (RED)
// PIN 11 is the humidity LED (BLUE)

// PIN 10 is the gas for 250 PPM
// BOTH PIN 10 and 11 for 400 PPM
// ALL LED's for over 700 PPM

// Pin Definitions
#define DHT_PIN_DATA  2
#define MQ135_5V_PIN_AOUT A0

// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);

// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;
int timeFlip = 1;  // used to flip the lcd screen without using a delay
unsigned long testTime = millis();
uint16_t period = 2000;

int sensorValue;
int digitalValue;

  

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    Serial.begin(9600);
    
    pinMode(10, OUTPUT); // set ups LED1
    pinMode(13, OUTPUT); // set ups LED2
    pinMode(11, OUTPUT); // set ups LED3
    //pinMode(3, INPUT);
    
   // Initiate the LCD and turn on the backlight
    lcd.init();          // Initiate the LCD module
    lcd.backlight();     // Turn on the backlight
    
    lcd.setCursor(0,0);         //Welcome message
    lcd.print("Welcome to the");
    lcd.setCursor(0,1);
    lcd.print("Basement Monitor");
    delay(2000);
  
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    
    
    dht.begin();
  //  menuOption = menu();
   testTime = millis();
}//void setup();


void LCD_Display1(float dhtHumidity, float dhtTempC, int sensorValue)
{
   //Print on LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity ");
    lcd.print(dhtHumidity); //Print Humidity
    lcd.print(" %");
    lcd.setCursor(0,1);
    lcd.print("Temp ");
    lcd.print(dhtTempC); //Print Temp
    lcd.print(" C");
}


void LCD_Display2(float dhtHumidity, float dhtTempC, int sensorValue)
{ 
     //Print on LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.print(sensorValue); // LCD Print Gas sensor in PPM
    lcd.print("  PPM");
    lcd.setCursor(0,1);
    lcd.print("Gas Sensor");
}


// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{

    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    // sensor value is gas reading in PPM
    float dhtTempC = dht.readTempC();
    
    float dhtHumidity = dht.readHumidity();
    sensorValue = analogRead(0);   
    
    // Prints in plotting format
    Serial.print("Humidity_in_%:");
    Serial.print(dhtHumidity);
    Serial.print(',');
    Serial.print("Temp_in_C:");
    Serial.print(dhtTempC);
    Serial.print(',');
    Serial.print("Air_Quality_in_PPM:");
    Serial.print(sensorValue);
    Serial.print(',');
    Serial.print("TimeFlip:");
    Serial.print(timeFlip);
    //Serial.print(',');
    //Serial.print("Time:");
    //Serial.print(millis());
    Serial.println();

    if(millis()>= testTime+period){
      if(timeFlip){
        LCD_Display1(dhtHumidity, dhtTempC, sensorValue);
        timeFlip = 0;
      }
      else if(!timeFlip){
        LCD_Display2(dhtHumidity, dhtTempC, sensorValue);
        timeFlip = 1;
      }
      testTime = millis();
    }
  
    //Built in LED goes of if temp is above 23 [C]
      if (dhtTempC > 20)
     {
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
     else  digitalWrite(13, LOW); 


    //Built in LED goes of if Humidity is above 40 [%]
    //BLUE LED
     if (dhtHumidity > 40)
      {
        digitalWrite(11, HIGH); 
     }
     else  digitalWrite(11, LOW); 

    
    
      if (sensorValue > 500) // just out of the normal air quality range
      {
         digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
      }
     else  digitalWrite(10, LOW); 
    
    
}//end of loop
