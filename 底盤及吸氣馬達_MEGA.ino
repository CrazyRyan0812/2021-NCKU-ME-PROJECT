/*主要維護者，E14073190李庭競*/
/*MEGA2560*/
/*以車身的4根叉叉為前為正向*/
/*第一組底盤馬達*//*左後輪*/
#define MOTOT_PIN_RIGHT_A 40
#define MOTOT_PIN_RIGHT_B 41
#define MOTOT_PIN_RIGHT_EN 9
/*第一組底盤馬達*//*右後輪*/
#define MOTOT_PIN_LEFT_A 42
#define MOTOT_PIN_LEFT_B 43
#define MOTOT_PIN_LEFT_EN 10
/*第二組底盤馬達*//*右前輪*/
#define MOTOT_PIN_RIGHT_A_2 30
#define MOTOT_PIN_RIGHT_B_2 31
#define MOTOT_PIN_RIGHT_EN_2 7
/*第二組底盤馬達*//*左前輪*/
#define MOTOT_PIN_LEFT_A_2 34
#define MOTOT_PIN_LEFT_B_2 35
#define MOTOT_PIN_LEFT_EN_2 6
/*第三組，吸氣馬達*/
#define In1 50
#define In2 51
#define In3 52
#define In4 53
#define ENA_3 11
#define ENB_3 5

#include <Wire.h>
#include <Servo.h>

class Motor{
    private:
    int Pin_A, Pin_B, Pin_EN;
    public:
    Motor(int pin_A, int pin_B, int pin_EN){
        Pin_A = pin_A;
        Pin_B = pin_B;
        Pin_EN = pin_EN;
        pinMode(Pin_A, OUTPUT);
        pinMode(Pin_B, OUTPUT);
        pinMode(Pin_EN, OUTPUT);
    }
    void setSpeed(int speed){
        bool dir = speed > 0;
        digitalWrite(Pin_A, dir);
        digitalWrite(Pin_B, !dir);
        speed = abs(speed);
        speed = speed > 250 ? 250 : speed;
        analogWrite(Pin_EN, speed);
    }
};

Motor motorLeftBack(MOTOT_PIN_RIGHT_A, MOTOT_PIN_RIGHT_B, MOTOT_PIN_RIGHT_EN);
Motor motorRightBack( MOTOT_PIN_LEFT_A,  MOTOT_PIN_LEFT_B,  MOTOT_PIN_LEFT_EN);
Motor motorRightFront(MOTOT_PIN_RIGHT_A_2, MOTOT_PIN_RIGHT_B_2, MOTOT_PIN_RIGHT_EN_2);
Motor motorLeftFront( MOTOT_PIN_LEFT_A_2,  MOTOT_PIN_LEFT_B_2,  MOTOT_PIN_LEFT_EN_2);

void setup() {
  Wire.begin(3); //I2C位址與連線設定，這裡設定為3號
  Wire.onReceive(receiveEvent); //當收到I2C訊號時，啟動的動作
  Serial.begin(9600); //Serial輸出鮑率為9600
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENA_3, OUTPUT);
  pinMode(ENB_3, OUTPUT);
}
double power1 = 0, power2 = 0, power3 = 0, power4 = 0;
double value1 = 231, value2 = -243, value3 = -190, value4 = 250; /*控制馬力，需每次用三用電表精調*/
/*左後 右前 左前 右後*/
/*正負跟想像的要相反*/
//自定義的接收後的啟動副程式
void receiveEvent(int numBytes){
    while(Wire.available()){ //判斷Wire.available()有沒有訊號
        char input = Wire.read(); //將傳入的訊號Wire.read()指定給字串input
        Serial.println(input);
        int ststus=1; 
        if(ststus==1){
          switch(input){
            case 'f': //前，滿速
            power1 += value1;
            power3 += value3;
            power2 -= value2;
            power4 += value4;
            Serial.print("f \n");
            break;
            case 'b': //後，滿速
            power1 -= value1;
            power3 -= value3;
            power2 += value2;
            power4 -= value4;
            Serial.print("b \n");
            break;
            case 'r': //右，滿速
            power1 -= value1;
            power3 += value3;
            power2 += value2;
            power4 += value4;
            Serial.print("r \n");
            break;
            case 'l': //左，滿速
            power1 += value1;
            power3 -= value3;
            power2 -= value2;
            power4 -= value4;
            Serial.print("l \n");
            break;
            case 'e': //前，半速
            power1 += value1/2;
            power3 += value3/2;
            power2 -= value2/2;
            power4 += value4/2;
            Serial.print("e \n");
            break;
            case 'g': //後，半速
            power1 -= value1/2;
            power3 -= value3/2;
            power2 += value2/2;
            power4 -= value4/2;
            Serial.print("g \n");
            break;
            case 'h': //右，半速
            power1 -= value1/2;
            power3 += value3/2;
            power2 += value2/2;
            power4 += value4/2;
            Serial.print("h \n");
            break;
            case 'i': //左，半速
            power1 += value1/2;
            power3 -= value3/2;
            power2 -= value2/2;
            power4 -= value4/2;
            Serial.print("i \n");
            break;
            case 'w': //順時針自轉
            power1 -= value1/2;
            power3 -= value3/2;
            power2 -= value2/2;
            power4 += value4/2;
            Serial.print("q \n");
            break;
            case 'q': //順時針自轉
            power1 += value1/2;
            power3 += value3/2;
            power2 += value2/2;
            power4 -= value4/2;
            Serial.print("w \n");
            break;
            
            case '0': //馬達停機
            power1 = 0;
            power2 = 0;
            power3 = 0;
            power4 = 0;
            Serial.print("0 \n");
            break;
            
            case 'a': /*吸氣馬達，吸*/
            digitalWrite(In1, HIGH);
            digitalWrite(In2, LOW);
            digitalWrite(ENA_3, HIGH);
            digitalWrite(In3, LOW);
            digitalWrite(In4, LOW);
            digitalWrite(ENB_3, LOW);
            Serial.print("a \n");
            break;
            case 'c':/*吐氣馬達，吐*/
            digitalWrite(In1, LOW);
            digitalWrite(In2, LOW);
            digitalWrite(ENA_3, LOW);
            digitalWrite(In3, HIGH);
            digitalWrite(In4, LOW);
            digitalWrite(ENB_3, HIGH); 
            Serial.print("c \n");
            break;
            case 'd':/*吸吐氣馬達停止運作*/
            digitalWrite(In1, LOW);
            digitalWrite(In2, LOW);
            digitalWrite(ENA_3, LOW);
            digitalWrite(In3, LOW);
            digitalWrite(In4, LOW);
            digitalWrite(ENB_3, LOW);
            Serial.print("d \n");
            break;
            
            default:
            break;
        }
    }
    else{
        power1 *= 0.99;
        power2 *= 0.99;
        power3 *= 0.99;
        power4 *= 0.99;
        }
    }
    delay(10);
    motorLeftBack.setSpeed((int)power3);
    motorRightBack.setSpeed((int)power4);
    motorLeftFront.setSpeed((int)power1);
    motorRightFront.setSpeed((int)power2);
    
}
