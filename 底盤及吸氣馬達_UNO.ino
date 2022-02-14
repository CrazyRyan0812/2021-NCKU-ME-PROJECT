/*主要維護者，E14073190李庭競*/
/*UNO Controller*/
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial BTSerial(10, 11); // RX | TX
void setup() {
    BTSerial.begin(38400);
    Wire.begin(3); //I2C位址與連線設定，這裡設定為3號
    Serial.begin(9600);
}

void loop() {
        char input = BTSerial.read();
        switch(input){
            case 'f':
            Wire.beginTransmission(3); 
            Wire.write("f"); 
            Wire.endTransmission();  
            Serial.print("f \n");
            break;
            case 'b':
            Wire.beginTransmission(3); 
            Wire.write("b"); 
            Wire.endTransmission();  
            Serial.print("b \n");
            break;
            case 'r':
            Wire.beginTransmission(3); 
            Wire.write("r"); 
            Wire.endTransmission();  
            Serial.print("r \n");
            break;
            case 'l':
            Wire.beginTransmission(3); 
            Wire.write("l"); 
            Wire.endTransmission(); 
            Serial.print("l \n"); 
            break;
            case '0':
            Wire.beginTransmission(3); 
            Wire.write("0"); 
            Wire.endTransmission(); 
            Serial.print("0 \n"); 
            break;
            case 'a':
            Wire.beginTransmission(3); 
            Wire.write("a"); 
            Wire.endTransmission(); 
            Serial.print("a \n"); 
            break;
            case 'c':
            Wire.beginTransmission(3); 
            Wire.write("c"); 
            Wire.endTransmission(); 
            Serial.print("c \n"); 
            break;
            case 'd':
            Wire.beginTransmission(3); 
            Wire.write("d"); 
            Wire.endTransmission(); 
            Serial.print("d \n"); 
            break;
            case 'e':
            Wire.beginTransmission(3); 
            Wire.write("e"); 
            Wire.endTransmission(); 
            Serial.print("e \n"); 
            break;
            case 'g':
            Wire.beginTransmission(3); 
            Wire.write("g"); 
            Wire.endTransmission(); 
            Serial.print("g \n"); 
            break;
            case 'h':
            Wire.beginTransmission(3); 
            Wire.write("h"); 
            Wire.endTransmission(); 
            Serial.print("h \n"); 
            break;
            case 'i':
            Wire.beginTransmission(3); 
            Wire.write("i"); 
            Wire.endTransmission(); 
            Serial.print("i \n"); 
            break;
            case 'j':
            Wire.beginTransmission(3); 
            Wire.write("j"); 
            Wire.endTransmission(); 
            Serial.print("j \n"); 
            break;
            
            case 'q':
            Wire.beginTransmission(3); 
            Wire.write("q"); 
            Wire.endTransmission(); 
            Serial.print("q \n"); 
            break;
            case 'w':
            Wire.beginTransmission(3); 
            Wire.write("w"); 
            Wire.endTransmission(); 
            Serial.print("w \n"); 
            break;
            case 'k':
            Wire.beginTransmission(3); 
            Wire.write("k"); 
            Wire.endTransmission(); 
            Serial.print("k \n"); 
            break;
            case 'm':
            Wire.beginTransmission(3); 
            Wire.write("m"); 
            Wire.endTransmission(); 
            Serial.print("m \n"); 
            break;


            
            default:
            break;
        }
}
