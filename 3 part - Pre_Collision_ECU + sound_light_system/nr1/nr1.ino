#include <NewPing.h>
#include <L298N.h>
#include <NewTone.h>

//pin definition
#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 300
#define LED_G 5 //zalio ledo prijungimas; 
#define LED_Y 4 // geltono ledo prijungimas; 
#define LED_R 3 // raudono ledo prijungimas; 
#define tone_pin 2 // piezogarsiakalbio prijungimas;
#define ENA 10
#define IN1 9
#define IN2 7

L298N driver(ENA, IN1, IN2); //dc driverio funkcija
NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //ultrasonic jutiklio nuskaitymo funkcija
int tone_frequency = 2000;  // frequency of tone, from low to high about 50-15000 Hz
int short_tone_time = 50;  // time in ms that short tone should play for
int long_tone_time = 1000;  // time in ms that long tone should play for

void setup()
{
  Serial.begin(9600);
}

void loop (){
  int dist_cm=sonar.ping_cm();
  Serial.print("Atstumas: ");
  Serial.print(dist_cm);
  Serial.println("cm");
  
  if (dist_cm >= 50)
  {
    driver.setSpeed(255); //turbo rezimas
    driver.forward(); //priekyn

    digitalWrite (LED_G, HIGH);
    digitalWrite(LED_Y, LOW); 
    digitalWrite(LED_R, LOW);
  
  delay(100); //priekyn 100ms
  }
  else if (dist_cm < 50 && dist_cm >= 20)
  {
    // signalas
    NewTone(tone_pin, tone_frequency); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
    delay(short_tone_time); // Wait short time so you can hear it.
    noNewTone(tone_pin); // Turn off the tone.
       
    driver.setSpeed(100); //vezlio rezimas
    driver.forward(); //priekyn
       
    digitalWrite (LED_G, LOW);
    digitalWrite(LED_Y, HIGH); 
    digitalWrite(LED_R, LOW);
  
    delay(100); //priekyn 100ms
  }
  else 
  {
    //staigus signalas
    NewTone(tone_pin, tone_frequency); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
      
  driver.stop(); //stabdyti
  
   digitalWrite (LED_G,LOW);
   digitalWrite(LED_Y, LOW); 
   digitalWrite(LED_R, HIGH);
   
   delay(long_tone_time); // Wait long 1 s so you can hear it.
   noNewTone(tone_pin); // Turn off the tone.
  }
}
