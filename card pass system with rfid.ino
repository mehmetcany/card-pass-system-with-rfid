#include <Servo.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>


#include <SPI.h>

#include <LiquidCrystal.h>
 
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define beep_pin 8

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

 Servo sg90;
void setup() 
{
  
  Serial.begin(9600);   // Initiate a serial communication
  sg90.attach(8);
  
  pinMode(beep_pin,OUTPUT);
  digitalWrite(beep_pin,LOW);
  
  lcd.begin(16, 2);
  lcd.setCursor(3, 1);
  lcd.print("Hosgeldiniz!!");
  lcd.setCursor(0, 0);
  lcd.print("Devre hazir");
  delay(1500);
  lcd.clear();  
  
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Karti okutunuz...");
  Serial.println();

}
void loop() 
{
  digitalWrite(beep_pin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Karti okutunuz");
  lcd.setCursor(0, 1);
  lcd.print("Okunuyor......");
  delay(300);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  

  
  if (content.substring(1) == "FF A5 E0 49")

  {
    digitalWrite(beep_pin,HIGH);
    delay(200);
    digitalWrite(beep_pin,LOW);
    delay(100);
    
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    
    lcd.print("BURAK GUMUS");
    lcd.setCursor(0, 1);
    lcd.print("Giris izni");
    Serial.println("Giris izni");
    Serial.println("BURAK GUMUS");
    
    
    delay(1200);    
    sg90.write(45);
    delay(3000);
    sg90.write(0);
    delay(1000);
    
      
  }
  else if(content.substring(1) =="04 9F C6 6A 4C 4D 80")
  {
    digitalWrite(beep_pin,HIGH);
    delay(200);
    digitalWrite(beep_pin,LOW);
    delay(100);
    
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    
    lcd.print("MEHMETCAN YAZICI");
    lcd.setCursor(0, 1);
    lcd.print("Giris izni");
    Serial.println("Giris izni");
    Serial.println("MEHMETCAN YAZICI");
    
    
    
    sg90.write(45);
    delay(3000);
    sg90.write(0);
    delay(1000);
  }
  
 
 else   {
    digitalWrite(beep_pin,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Giris izni yok");
    Serial.println(" Giris izni yok");
    delay(1500);
     }
} 
