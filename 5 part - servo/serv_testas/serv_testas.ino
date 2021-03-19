#include <ServoTimer2.h>
#include <L298N.h>
#include <NewPing.h>
//#include <Servo.h>
#include <NewTone.h>

//Varikliu (Pin)
#define ENA 13
#define IN1 8
#define IN2 7
#define ENB 4
#define IN3 5
#define IN4 2

//Utrasonic (pin)
#define TRIGGER_PIN 9
#define ECHO_PIN1 3
#define ECHO_PIN2 6
#define ECHO_PIN3 12
#define MAX_DISTANCE 300

//Ledai ir signalas (pin) ir migtukas // LED, signal, button declaration
#define LED_G A1 //zalio ledo prijungimas;  // green led conection
#define LED_Y A2 // geltono ledo prijungimas; // yellow led conection
#define LED_R A3 // raudono ledo prijungimas; // red led conection
#define tone_pin A0 // piezogarsiakalbio prijungimas; // buzzer conection


NewPing sonar1 (TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE); //ultrasonic1 jutiklio nuskaitymo funkcija // first sensor reading function
NewPing sonar2 (TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE); //ultrasonic2 jutiklio nuskaitymo funkcija // second sensor reading function
NewPing sonar3 (TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE); //ultrasonic3 jutiklio nuskaitymo funkcija // third sensor reading function
L298N driver1(ENA, IN1, IN2); //dc driverio funkcija // first motor function
L298N driver2(ENB, IN3, IN4); //dc driverio funkcija // second motor function
int delsimas = 1500;
int sukimas = 1500;
int greitis = 255; //max 255, min 1 
ServoTimer2 myservo;
int pos = 0;
int tone_frequency = 2000;  // frequency of tone, from low to high about 50-15000 Hz
int short_tone_time = 10;  // time in ms that short tone should play for
int long_tone_time = 1000;  // time in ms that long tone should play for


void setup()
{
  Serial.begin(9600);
  myservo.attach(10);
}

void loop () {
  //kampas -> 750 = 0, 1500 = 90, 2250 = 180 // radius -> 750 = 0deg., 1500 = 90deg., 2250 = 180deg. 
  int dist_cm1= servo_virsus(750);
  int dist_cm2= servo_virsus(1500);
  int dist_cm3= servo_virsus(2250);

  Serial.print("Atstumas1: "); Serial.print(dist_cm1); Serial.print("cm");
  Serial.print("   Atstumas2: "); Serial.print(dist_cm2); Serial.print("cm");
  Serial.print("   Atstumas3: "); Serial.print(dist_cm3); Serial.println("cm");
}

int servo_virsus(int kampas)
{
  //Make servo go to radius degrees
  myservo.write(kampas);
  delay(400);
  int dist_cm=sonar1.ping_cm();
  return dist_cm;
}
