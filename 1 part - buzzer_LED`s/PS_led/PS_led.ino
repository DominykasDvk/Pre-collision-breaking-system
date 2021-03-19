#include <NewPing.h>
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 300
#define LED_G 6
#define LED_Y 5
#define LED_R 4
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  unsigned int dist_cm;
  dist_cm = sonar.ping_cm();
  
 if (dist_cm >= 50)// zalios saplvos degimas, attumas saugus // green light means that distance is safe
{
 digitalWrite (LED_G, HIGH);
 digitalWrite(LED_Y, LOW); 
 digitalWrite(LED_R, LOW); 
 delay(400);
 
}
 if (dist_cm<=40 && dist_cm>=11)// yra tikimybe eismo įvikui // Waring there is posibilty to crash 
{
 digitalWrite (LED_G, LOW);
 digitalWrite(LED_Y, HIGH); 
 digitalWrite(LED_R, LOW); 
 delay(400);
}

 if (dist_cm <= 10)// stabdymas // Breaking
 {
 digitalWrite (LED_G,LOW);
 digitalWrite(LED_Y, LOW); 
 digitalWrite(LED_R, HIGH); 
 delay(400);
}
}
