#include <ServoTimer2.h>
#include <L298N.h>
#include <NewPing.h>
#include <NewTone.h>

//Varikliu (Pin) // motor conection pins
#define ENA 13
#define IN1 8
#define IN2 7
#define ENB 4
#define IN3 5
#define IN4 2

//Utrasonic (pin) // Ultrasonic sensor conection pins 
#define TRIGGER_PIN 9
#define ECHO_PIN1 3
#define ECHO_PIN2 6
#define ECHO_PIN3 12
#define MAX_DISTANCE 300

//Ledai ir signalas (pin) ir migtukas // LED, buzzer, button conection pins
#define LED_G A1 //zalio ledo prijungimas; // green led conection pin
#define LED_Y A2 // geltono ledo prijungimas; // yellow led conection pin
#define LED_R A3 // raudono ledo prijungimas; // red pin conection pin
#define tone_pin A0 // piezogarsiakalbio prijungimas; // buzzer pin;
#define buttonPin A4 //rezimo jungtuko prijungimas // functional button conetion pin


NewPing sonar1 (TRIGGER_PIN, ECHO_PIN1, MAX_DISTANCE); //ultrasonic1 jutiklio nuskaitymo funkcija // sensor1 pin
NewPing sonar2 (TRIGGER_PIN, ECHO_PIN2, MAX_DISTANCE); //ultrasonic2 jutiklio nuskaitymo funkcija // sensor2 pin
NewPing sonar3 (TRIGGER_PIN, ECHO_PIN3, MAX_DISTANCE); //ultrasonic3 jutiklio nuskaitymo funkcija // sensor3 pin
L298N driver1(ENA, IN1, IN2); //dc valdiklio funkcija // first motor function
L298N driver2(ENB, IN3, IN4); //dc valdiklio funkcija // second motor function
ServoTimer2 myservo; // servo function

int sukimas = 1500; //kiek ms sukti i sona (1500ms=1.5s) // turn to aside (1500ms=1.5s)
int sukimo_greitis = 150; //max 255, min 1
int normalus_greitis = 160; // max 255
int suletintas_greitis = 130; //max 255
int tone_frequency = 2000;  //Signalo daznis 50-15000 Hz //signal frequency 50-15000 Hz
int trumpas_signalas = 10;  //Trumpo signalo trukme ms //short signal time
int buttonState = 0; // migtuko inicializavimas // button initialization
int max_dist = 35; // maximum distance
int min_dist = 25; // minimum distance

void setup()
{
  Serial.begin(9600);
  myservo.attach(10);
  pinMode(buttonPin, INPUT);
}

void loop () {
  //int dist_cm1=sonar1.ping_cm();
  //int dist_cm2=sonar2.ping_cm();
  //int dist_cm3=sonar3.ping_cm();
  //Serial.print("Atstumas1: "); Serial.print(dist_cm1); Serial.print("cm");
  //Serial.print("   Atstumas2: "); Serial.print(dist_cm2); Serial.print("cm");
  //Serial.print("   Atstumas3: "); Serial.print(dist_cm3); Serial.println("cm");

  driver2.setSpeed(sukimo_greitis);//nustatom sukimo greiti //set turning speed
  myservo.write(1500); //nukreipti servo 90 kampu (ziuri tiesiai) ir pasiruosti // set servo to the forward position
  buttonState = digitalRead(buttonPin);//nuskaitom rezimo mygtuka // initialization of function button

  //Servo + Utrasonic rezimas // first state: servo using + one ultrasonic: servo motor turning sensor to directions every 10ms.
  while (buttonState == HIGH)
  {
    int dist_cm2 = servo_virsus(750);
    delay(10);
    int dist_cm1 = servo_virsus(1500);
    delay(10);
    int dist_cm3 = servo_virsus(2250);
    delay(10);
    if (dist_cm1==0)
    {dist_cm1=400;}
    if (dist_cm2==0)
    {dist_cm2=400;}
    if (dist_cm3==0)
    {dist_cm3=400;}
    distancija_rodymas(dist_cm1, dist_cm2, dist_cm3);
    pagrindine_logika(dist_cm1, dist_cm2, dist_cm3);
  }

  //3 Ultrasonic rezimas //second state: three sensors. all sensors steady
  while (buttonState == LOW)
  {
    int dist_cm2 = sonar2.ping_cm();
    delay(10);
    int dist_cm1 = sonar1.ping_cm();
    delay(10);
    int dist_cm3 = sonar3.ping_cm();
    delay(10);
    if (dist_cm1==0)
    {dist_cm1=400;}
    if (dist_cm2==0)
    {dist_cm2=400;}
    if (dist_cm3==0)
    {dist_cm3=400;}
    distancija_rodymas(dist_cm1, dist_cm2, dist_cm3);
    pagrindine_logika(dist_cm1, dist_cm2, dist_cm3);
  }

}

void auto_vairavimas(int puse) // function auto_steering
{
  driver1.setSpeed(normalus_greitis); 
  //jei puse == 0, tai sukam i kaire 
  // if parameter "side" = "puse" equals 0 then car go forward, and turning "driving wheel" to the oposite side of obstacle (in this case left), when there is no obstacle anymore, stearing return to default point.
  if (puse == 0)
  {
    driver2.forward(); //sukti i sona 
    driver1.backward(); //ir vaziuoti i prieki
    delay(sukimas);
    driver2.stop(); //paleisti vairavima
  }
  //jei puse == 1, tai sukam i desine
   // if parameter "side" = "puse" equals 1 then car go forward, and turning "driving wheel" to the oposite side of obstacle(in this case right), when there is no obstacle anymore, stearing return to default point.
  else if (puse == 1)
  {
    driver2.backward(); //sukti i sona
    driver1.backward(); //ir vaziuoti i prieki
    delay(sukimas);
    driver2.stop(); //paleisti vairavima
  }
}

void led_zalia()// fumction to call green light
{
  digitalWrite (LED_G, HIGH);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, LOW);
}

void led_geltona() // fuction to call yelow light
{
  digitalWrite (LED_G, LOW);
  digitalWrite(LED_Y, HIGH);
  digitalWrite(LED_R, LOW);
}

void led_raudona() // function to call red 
{
  digitalWrite (LED_G, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, HIGH);
}

int servo_virsus(int kampas) // function of servo motor moving, initialization of servo and ultrasonic sensor using, system started to work. 
{
  //kampas -> 750 = 0, 1500 = 90, 2250 = 180
  //naudoti: int dist_cm1= servo_virsus(750);
  //Make servo go to kampas degrees
  myservo.write(kampas);
  delay(400);
  int dist_cm = sonar1.ping_cm();
  return dist_cm;
}

void trumpas_garso_signalas() // short sound signal function: plays signal in high frequency for short time.
{
  NewTone(tone_pin, tone_frequency); //Groti signala tone_frequency dazniu
  delay(trumpas_signalas); //Groti signala trumpas_signalas trukme ms
  noNewTone(tone_pin); //Isjungti signala
}

void pagrindine_logika (int dist1, int dist2, int dist3)// main logics function: 
{
  //Jei distancija visur daugiau nei 50cm, vaziuoti greitai tiesiai // if distance around object more than 50cm, go forward all speed. (LED green)
  if (dist1 >= max_dist && dist2 >= max_dist && dist3 >= max_dist )
  {
    led_zalia();
    driver1.setSpeed(normalus_greitis); //turbo rezimas // full throttle;
    driver1.backward(); //priekyn // forward;
    delay(500); //priekyn 500ms // a half of second.
  }
  //Jei distancija kazkur maziau nei 50 bet daugiau nei 25, pristabdyti ir vaziuoti tiesiai // If distance around object less than 50cm, and more than 25cm, drives 50% slower than full throttle.
  else if (dist1 < max_dist && dist1 >= min_dist)
  {
    //isijungia geltona sviesa, trumpas signalas, vaziuoja i prieki letai // warning buzzer signal, goes forward slower (LED yellow).
    led_geltona();
    trumpas_garso_signalas();
    driver1.setSpeed(suletintas_greitis); //vezlio rezimas //slow 
    driver1.backward(); //priekyn // forward
    delay(500); //priekyn 500ms 
  }
  //Jei distancija priekije maziau nei 25, stoti // If distance in front less than 25cm, break. 
  else if (dist1 < min_dist)
  {
    //isijungia raudona sviesa, ilgas signalas, sustoti // Turns on red led, long buzzer signal, breaking.  
    led_raudona();
    NewTone(tone_pin, tone_frequency); //Groti signala // play signal
    driver1.stop(); //sustoti vaziavima // break for 2 seconds.
    delay(2000); //palaukti 2s
    noNewTone(tone_pin); //Isjungti signala // turn off signal.
  }
  //Jei distancija abejose sonose maziau nei 25, bet priekyje daugiau nei 25, vaziuoti greitai tiesiai 
  // If distance in both sides less than 25cm. but in front is more than 25cm, it goes to front, to prevent side collision.
  else if (dist1 > min_dist && dist2 < min_dist && dist3 < min_dist)
  {
    //isijungia raudona sviesa, ilgas signalas, vaziuoti greitai tiesiai // turns on red light, long buzzer signal, go foward fast.
    led_raudona();
    NewTone(tone_pin, tone_frequency); //Groti signala 
    driver1.setSpeed(normalus_greitis); //turbo rezimas 
    driver1.backward(); //priekyn
    delay(500); //priekyn 500ms
    noNewTone(tone_pin); //Isjungti signala //turn off buzzer
  }
  //Jei distancija vienam sone maziau nei 35, sukti i priesinga sona 
  //If distance in one side less than 35cm, turn to other side.
  else if (dist2 < min_dist)
  {
    //isijungia raudona sviesa, ilgas signalas, sukti i priesinga puse nuo objekto
    led_raudona();
    NewTone(tone_pin, tone_frequency); //Groti signala
    auto_vairavimas(0);//Sukam i kaire
    noNewTone(tone_pin); //Isjungti signala
  }
  //Jei distancija vienam sone maziau nei 35, sukti i priesinga sona
  //If distance in one side less than 35cm, turn to side where is no obstacle.
  else if (dist3 < min_dist)
  {
    //isijungia raudona sviesa, ilgas signalas, sukti i priesinga puse nuo objekto
    led_raudona();
    NewTone(tone_pin, tone_frequency); //Groti signala
    auto_vairavimas(1);//Sukam i desine
    noNewTone(tone_pin); //Isjungti signala
  }
}

void distancija_rodymas (int dist1, int dist2, int dist3)// function shows distance of sensors mesure in serial monitor of arduino IDE. 
{
  Serial.print("Atstumas1: "); Serial.print(dist1); Serial.print("cm");
  Serial.print("   Atstumas2: "); Serial.print(dist2); Serial.print("cm");
  Serial.print("   Atstumas3: "); Serial.print(dist3); Serial.println("cm");
}
