/*主要維護者，E14074188鄭博文*/
#include <Stepper.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

// 呼叫伺服驅動程式函數，預設I2C位址為 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define FREQUENCY 50
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)
int angle;
int earBopen=40;
int earBclose=90;
int earCopen=100;
int earCclose=50;
int earC=100;
int earB=40;

void setup() {
  BTSerial.begin(38400);
  pinMode(7, OUTPUT);  //   direction  second_arm
  pinMode(6, OUTPUT); //  step (PWM)  second_arm
  pinMode(8, OUTPUT);  //CW+   direction 
  pinMode(9, OUTPUT); //CLK+  step  PWM
    //  digitalWrite(8, LOW);//主臂(行星齒輪LOW往後  HIGH往前 4800step/rev)
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // This is the maximum PWM frequency
  pwm.setPWM(1, 0, angleToPulse(120) ); //C，120升起來  ear 歸位(上)
  pwm.setPWM(2, 0, angleToPulse(30) ); //B，75升起來   ear 歸位(上)     抓C 閉40 開100
  angle = 75;
  pwm.setPWM(0, 0, angleToPulse(angle) );
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}

void loop() {  
  char input = BTSerial.read();
  
  int counterclockwise,stoppoint,clockwise;
  counterclockwise=250;
  stoppoint=320;
  clockwise=360;
 
  switch(input){
    case 'x':
    Serial.print("w \n");
      digitalWrite(8, LOW);
      analogWrite(9, 127);//(pin,0~255) 255會以digital輸出
    break;
    case 's':
      Serial.print("s \n");
      analogWrite(9, 0);
    break;
    case 'w':
      Serial.print("x \n");
        digitalWrite(8, HIGH);
        analogWrite(9, 127);
    break;
    case 'e':
      Serial.print("e \n");
        digitalWrite(7, LOW);
        analogWrite(6, 127);
    break;
    case 'd':
      Serial.print("d \n");
        analogWrite(6, 0);
    break;
    case 'c':
      Serial.print("c \n");
        digitalWrite(7, HIGH);
        analogWrite(6, 127);
    break;
    case 'u':
      Serial.print("u \n");
      digitalWrite(7,LOW);
      analogWrite(6,127);
    
      digitalWrite(8,HIGH);
      analogWrite(9,127);
    break;
    case 'j':
      Serial.print("j \n");
      digitalWrite(7,HIGH);
      analogWrite(6,127);
      digitalWrite(8,LOW);
      analogWrite(9,127);
    break;


    //fork  'r':  'v': 'f':
    case 'r':  //fork up
     Serial.print("r \n");
        angle=101;
        pwm.setPWM(0, 0, angleToPulse(angle));
           
    break;
    case 'f':  //fork mid
      Serial.print("f \n");
      angle=85;
      pwm.setPWM(0, 0, angleToPulse(85));
           
    break;
    case 'v':   //fork down
      Serial.print("v \n");
       angle=61;
       pwm.setPWM(0, 0, angleToPulse(angle) );           
    break;
    

    
    //ear 't'up  'b'down
    case 't':
      Serial.print("t \n");
      pwm.setPWM(1, 0, angleToPulse(earBopen) ); //earB，40
      pwm.setPWM(2, 0, angleToPulse(earCopen) ); //earC，100開
      //pwm.setPWM(1, 0, angleToPulse(120) ); //earC，120升起來
      //pwm.setPWM(2, 0, angleToPulse(75) ); //earB，75升起來
    break;
    case 'b':
      Serial.print("b \n");
      
      pwm.setPWM(2, 0, angleToPulse(100) ); 
      pwm.setPWM(1, 0, angleToPulse(40) );
      delay(100);
      pwm.setPWM(1, 0, angleToPulse(50) );
      pwm.setPWM(2, 0, angleToPulse(90) );
      delay(100);
      pwm.setPWM(1, 0, angleToPulse(60) );
      pwm.setPWM(2, 0, angleToPulse(80) );
      delay(100);
      pwm.setPWM(1, 0, angleToPulse(70) );
      pwm.setPWM(2, 0, angleToPulse(70) );
      delay(100);
      pwm.setPWM(1, 0, angleToPulse(80) );
      pwm.setPWM(2, 0, angleToPulse(60) );
      delay(100);
      pwm.setPWM(1, 0, angleToPulse(earBclose) ); //earB，90閉
      pwm.setPWM(2, 0, angleToPulse(earCclose) );//earC，50閉
      //pwm.setPWM(1, 0, angleToPulse(50) ); //earC，50壓下去
      //pwm.setPWM(2, 0, angleToPulse(140) ); //earB，140壓下去
    break;

    /*case 'y':
      Serial.print("y \n");
      pwm.setPWM(3, 0, angleToPulse(40) ); //C，40壓下去
     
    break;
    case 'h':
      Serial.print("h \n");
      pwm.setPWM(3, 0, angleToPulse(85) ); //C，85升
      
    break;
    */

    
    default:   
    break;
  }

}
