
// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h> // Driver Library for the LCD Module

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Adjust to (0x27,20,4) for 20x4 LCD

// THIS IS WORKING CODE FOR TEMP / HUMIDITY AND GAS MONITOR
// DESIGNED BY NATHAN PACEY

// ************INSTRUCTIONS FOR USE************
// run the serial monitor and put in which output you want
// PIN 13 is the temperature LED (RED)
// PIN 11 is the humidity LED (BLUE)

// PIN 10 is the gas for 250 PPM
// BOTH PIN 10 and 11 for 400 PPM
// ALL LED's for over 700 PPM

//**********NEW Addition LCD Display**********
//Pin 1 on LCD (VSS) will connect to GND of Arduino
//Pin 16 on LCD (K) will connect to GND of Arduino
//Pin 2 on LCD (VDD) will connect to +5v of Arduino
//Pin 15 on LCD (A) will connect to +5v of Arduino

//First pin of the potentiometer will go to GND of Arduino
//Pin 3 of the LCD display (VO) will connect to the middle pin of the potentiometer

//Pin 4 of the LCD display (RS) will connect to Pin 3 of Arduino
//Pin 5 of the LCD display (RW) will connect to GND of Arduino
//Pin 6 of the LCD display (E) will connect to Pin 4 of Arduino
//Pin 11 of the LCD display (D4) will connect to Pin 5 of Arduino
//Pin 12 of the LCD display (D5) will connect to Pin 6 of Arduino
//Pin 13 of the LCD display (D6) will connect to Pin 7 of Arduino
//Pin 14 of the LCD display (D7) will connect to Pin 8 of Arduino



// Pin Definitions
#define DHT_PIN_DATA	2
#define MQ135_5V_PIN_AOUT	A0

// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);

// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;
int testTime = millis();


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
    
    lcd.clear();            //Menu instructions
    lcd.setCursor(0,0);
    lcd.print("Input (1) or (2)"); //Test Print
    lcd.setCursor(0,1);
    lcd.print("In Menu"); //Test Print

  
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    if (millis()>10000)
    {
      Serial.println("Test Case");
      menuOption = '1';
      //  menuOption = menu();
    }
    
    dht.begin();
    menuOption = menu();
   
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{

    if(menuOption == '1') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
     
    float dhtTempC = dht.readTempC();
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
   
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(" ");
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));
    Serial.print(" ");

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
    delay(200);


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
   
    } //end of temp and humidity
    
    
    if(menuOption == '2')
    {
    sensorValue = analogRead(0);
    //digitalValue = digitalRead(2);
    
    // Disclaimer: The Hazardous Gas  Sensor - MQ-135 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    Serial.print("AirQua=");
    Serial.print(sensorValue, DEC);               // prints the value read
    Serial.println(" PPM");

    //LCD Print
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.print(sensorValue); // LCD Print Gas sensor in PPM
    
    lcd.print("  PPM");
    lcd.setCursor(0,1);
    lcd.print("Gas Sensor");
    
    if (sensorValue > 700) // new condition for an LCD warning display
    {
      
        //LCD update for 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" ");
        lcd.print(sensorValue); 
        lcd.print(" PPM");
        lcd.setCursor(0,1);
        lcd.print(" WARNING!!");
    }
    
    

    
        if (sensorValue > 250) // just out of the normal air quality range
        {
           digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
        }
       else  digitalWrite(10, LOW); 


       if (sensorValue > 400) // this would be slightly problematic air conditions
       {
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        
       }
       else
       {
       digitalWrite(11, LOW);
       digitalWrite(12, LOW);
       
       }

       // Could have CO in the Air
       if (sensorValue > 700) // this would be highly probematic air conditions
       {
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        
       }
       else
       {
       digitalWrite(11, LOW);
       digitalWrite(12, LOW);
       digitalWrite(13, LOW);
       
       }

       delay(500);

    }//menu 2

    
   //Serial.println(millis());
   
  
    // if you want to stop after certain time
    
  
    
}//end of loop



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(2) Hazardous Gas  Sensor - MQ-135"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
      char c = Serial.read();
      
      if (millis()>10000)
    {
      Serial.println("Test Case");
      menuOption = '1';
      //  menuOption = menu();
    }
    
        
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Hazardous Gas  Sensor - MQ-135 - note that this component doesn't have a test code"));
        
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
