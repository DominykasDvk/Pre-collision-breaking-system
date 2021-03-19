
#include <L298N.h>

//pin definition
#define ENA 13
#define IN1 8
#define IN2 7
#define ENB 4
#define IN3 5
#define IN4 2

L298N driver(ENB, IN3, IN4); //dc driverio funkcija
int delsimas = 1500;
int sukimas = 1500;
int greitis = 100; //max 255, min 1

void setup()
{
  //Serial.begin(9600);
}

void loop (){
      driver.setSpeed(greitis); //nustatom greiti
  driver.forward(); //priekyn
  delay(sukimas);
  driver.stop(); //stabdyti
  delay(delsimas);
  driver.backward(); //atgal
  delay(sukimas);
  driver.stop(); //stabdyti
  delay(delsimas);

}
