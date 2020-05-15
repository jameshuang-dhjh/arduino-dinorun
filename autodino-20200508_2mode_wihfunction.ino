#include <Servo.h>
Servo myservo;
int mode = 0; //0: day ; 1: night
float sensorValue = 0.0;
float gateValue = 0.0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  myservo.attach(13);
  myservo.write(115);

  //Detect enviroment light value to set the init gatevalue
  for (int i = 0 ; i < 50 ; i++) {
    gateValue += analogRead(A0);
    delay(100);
  }
  gateValue = (gateValue / 50) - 8.0;
  Serial.println("Init Ok!! Let Dino Run!!");
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);
  Serial.print("In : ");
  Serial.print(sensorValue);
  Serial.print(" Gate : ");
  Serial.print(gateValue);
  Serial.print(" Mode : ");
  Serial.println(mode);

  delay(1);
  if (mode == 0 && (sensorValue < gateValue - 100)) {
    mode = 1; //Night Mode
    dinojump();
    
    delay(400); //延遲0.1秒再開始初始化
    gateValue = sensorValue - 5;
    //Detect enviroment light value to set the init gatevalue
    /*
      for (int i = 0 ; i < 50 ; i++) {
       gateValue += sensorValue;
       delay(1);
      }
      
      gateValue = (gateValue / 100) + 5;

    */
  } else if (mode == 1 && (sensorValue > gateValue + 100)) {
    mode = 0; //Light Mode

    //Detect enviroment light value to set the init gatevalue
    for (int i = 0 ; i < 50 ; i++) {
      gateValue += sensorValue;
      delay(2);
    }
    gateValue = (gateValue / 50) - 5;
  }
  if (mode == 0) {
    //Light Mode
    if (sensorValue < gateValue ) {
      dinojump();
    }
  } else {
    //Night Mode
    if (sensorValue > gateValue ) {
      dinojump();
    }
  }
}
void dinojump() {
  myservo.write(126);
  delay(90);
  myservo.write(115);
  //delay(20);
  Serial.println("Jump!!!!!!!!!!!!");
}

