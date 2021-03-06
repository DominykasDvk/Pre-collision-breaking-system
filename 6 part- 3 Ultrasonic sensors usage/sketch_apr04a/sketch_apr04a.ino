#include <NewPing.h>


#define TRIGGER_PIN 13
#define ECHO_PIN1 10
#define ECHO_PIN2 11
#define ECHO_PIN3 12
#define MAX_DISTANCE 300

NewPing sonar1 (TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE); //ultrasonic1 jutiklio nuskaitymo funkcija
NewPing sonar2 (TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE); //ultrasonic2 jutiklio nuskaitymo funkcija
NewPing sonar3 (TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE); //ultrasonic3 jutiklio nuskaitymo funkcija


void setup()
{
  Serial.begin(9600);
}

void loop (){
  delay (5);
  int dist_cm1=sonar1.ping_cm();
  delay (5);
  int dist_cm2=sonar2.ping_cm();
  delay (5);
  int dist_cm3=sonar3.ping_cm();
  Serial.print("Atstumas1: "); Serial.print(dist_cm1); Serial.print("cm");
  Serial.print("   Atstumas2: "); Serial.print(dist_cm2); Serial.print("cm");
  Serial.print("   Atstumas3: "); Serial.print(dist_cm3); Serial.println("cm");
}
