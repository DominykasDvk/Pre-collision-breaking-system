#include <NewPing.h>
#include <L298N.h>

//pin definition
#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 300

#define ENA 10
#define IN1 9
#define IN2 7

L298N driver(ENA, IN1, IN2); //dc driverio funkcija // motor driver initialization function
NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //ultrasonic jutiklio nuskaitymo funkcija // Utrasonic sensor initialization function


void setup()
{
  Serial.begin(9600);
}

void loop (){
  delay (50);
  Serial.print("Atstumas: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  int dist_cm=sonar.ping_cm();
  
  if (dist_cm >= 50)
  {
    driver.setSpeed(255); //turbo rezimas // full throttle
    driver.forward(); //priekyn // forward
    delay(50); //priekyn 50ms 
  }
  else if (dist_cm < 50 && dist_cm >= 11)
  {
    driver.setSpeed(100); //vezlio rezimas // medium speed
    driver.forward(); //priekyn //forward
    delay(50); //priekyn 50ms 
  }
  else if (dist_cm < 10)
  {
    driver.stop(); //stabdyti // break
    delay(2000); //palaukti 2s // wait 2s
  }
}
