#include <ServoTimer2.h>
#include <L298N.h>
#include <NewPing.h>
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

//Ledai ir signalas (pin) ir migtukas
#define LED_G A1 //zalio ledo prijungimas; 
#define LED_Y A2 // geltono ledo prijungimas; 
#define LED_R A3 // raudono ledo prijungimas; 
#define tone_pin A0 // piezogarsiakalbio prijungimas;
#define buttonPin A4;     // the number of the pushbutton pin

NewPing sonar1 (TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE); //ultrasonic1 jutiklio nuskaitymo funkcija
NewPing sonar2 (TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE); //ultrasonic2 jutiklio nuskaitymo funkcija
NewPing sonar3 (TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE); //ultrasonic3 jutiklio nuskaitymo funkcija
L298N driver1(ENA, IN1, IN2); //dc driverio funkcija
L298N driver2(ENB, IN3, IN4); //dc driverio funkcija
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

void loop (){
  //int dist_cm1=sonar1.ping_cm();
  //int dist_cm2=sonar2.ping_cm();
  //int dist_cm3=sonar3.ping_cm();
  //Serial.print("Atstumas1: "); Serial.print(dist_cm1); Serial.print("cm");
  //Serial.print("   Atstumas2: "); Serial.print(dist_cm2); Serial.print("cm");
  //Serial.print("   Atstumas3: "); Serial.print(dist_cm3); Serial.println("cm");

  buttonState = digitalRead(buttonPin);

  while (buttonState == HIGH)
  {
    //darom servo+ultra
    
  }

    while (buttonState == LOW)
  {
    //darom 3 ultra
    
  }

 if (dist_cm1 >= 50, dist_cm2 >= 50, dist_cm3 >= 50 )
  {
    driver1.setSpeed(255); //turbo rezimas
    driver1.forward(); //priekyn

    led_zalia();
 
  delay(100); //priekyn 100ms
  }
   else if (dist_cm1 < 50 && dist_cm1 >= 25, dist_cm2 < 50 && dist_cm2 >= 25, dist_cm3 < 50 && dist_cm3 >= 25)
  {
    // signalas
    NewTone(tone_pin, tone_frequency); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
    delay(short_tone_time); // Wait short time so you can hear it.
    noNewTone(tone_pin); // Turn off the tone.
       
    driver1.setSpeed(100); //vezlio rezimas
    driver1.forward(); //priekyn
       
     led_geltona();
     
    delay(100); //priekyn 100ms
  }
  else 
  {
    //staigus signalas
    NewTone(tone_pin, tone_frequency); // Play the frequency (125 Hz to 15 kHz sweep in 10 Hz steps).
      
    driver1.setSpeed(100); //vezlio rezimas
    driver1.forward(); //priekyn
    auto_vairavimas();
  
    led_raudona();;
   
   delay(long_tone_time); // Wait long 1 s so you can hear it.
   noNewTone(tone_pin); // Turn off the tone.
  }
}

 void auto_vairavimas()
{
  driver2.setSpeed(greitis); //letas rezimas 10/255
  driver2.forward(); //priekyn
  delay(sukimas);
  driver2.stop(); //stabdyti
  delay(delsimas);
  driver2.backward(); //atgal
  delay(sukimas);
  driver2.stop(); //stabdyti
  delay(delsimas);
}
 void servo_virsus()
{
   //Make servo go to 0 degrees 
   myservo.write(1000); 
   // Make servo go to 90 degrees 
   myservo.write(1500); 
   delay(500); 
   // Make servo go to 180 degrees 
   myservo.write(2000); 
   delay(500); 
   // Make servo go to 90 degrees 
   myservo.write(1500); 
   delay(500);
   myservo.write(1000); 
}  

 void led_zalia()
{
    digitalWrite (LED_G, HIGH);
    digitalWrite(LED_Y, LOW); 
    digitalWrite(LED_R, LOW);
} 

 void led_geltona()
{
    digitalWrite (LED_G, LOW);
    digitalWrite(LED_Y, HIGH); 
    digitalWrite(LED_R, LOW);
} 

 void led_raudona()
{
    digitalWrite (LED_G, LOW);
    digitalWrite(LED_Y, LOW); 
    digitalWrite(LED_R, HIGH);
} 

int servo_virsus(int kampas)
{
  //kampas -> 750 = 0, 1500 = 90, 2250 = 180
  //naudoti: int dist_cm1= servo_virsus(750);
  //Sita funkcija pasuka servo i tam tikra kamp, nuskaito distancija naudojant ultrasonic jutikli ir sita distanciaj grazina atgal
  myservo.write(kampas);
  delay(400);
  int dist_cm=sonar1.ping_cm();
  return dist_cm;
}
