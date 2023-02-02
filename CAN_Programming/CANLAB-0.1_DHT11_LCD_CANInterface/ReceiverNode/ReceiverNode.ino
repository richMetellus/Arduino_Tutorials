// adapted from source: https://how2electronics.com/interfacing-mcp2515-can-bus-module-with-arduino/
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
                                  // since my lcd is the Sunfounder I2c LCD2004
 
struct can_frame canMsg;
 
MCP2515 mcp2515(10);                 // SPI CS Pin 10
 
 
void setup()
{
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();                       //Begins SPI communication
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.setCursor(0, 0);
  lcd.print("CANBUS TUTORIAL");
  // delay(1000);
  lcd.clear();
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}
 
 
void loop()
{
  // Serial.println("Start of Reading CAN message");

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    int x = canMsg.data[0];
    int y = canMsg.data[1];
    Serial.println((String)" Received HumidtyValue:" + x + ", Temp:" + y);

    lcd.setCursor(0, 0);         //Display Temp & Humidity value received at 16x2 LCD
    lcd.print("Humidity: ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print("Temperature: ");
    lcd.print(y);
    delay(1000);                // LCD refresh rate every 1 sec
    lcd.clear();
  }
}