
#include <L298N.h>

//pin definition
#define ENA 10
#define IN1 9
#define IN2 7

L298N driver(ENA, IN1, IN2); //dc driverio funkcija
int delsimas = 1000;
int sukimas = 500;
int  ratai_tiesiai_delsima = 20;
int greitis = 255; //max 255, min 1

void setup()
{
  Serial.begin(9600);
}

void loop (){

  driver.setSpeed(greitis); //letas rezimas 10/255
  driver.forward(); //i viena sona
	delay(sukimas);
	driver.stop(); //stabdyti
	delay(delsimas);
	driver.backward(); //atgal
	delay(sukimas);
	driver.stop(); //stabdyti
	delay(delsimas);
	
	//statom ratus tiesiai:
	ratai_tiesiai();

}

void ratai_tiesiai()
{
	driver.forward(); //i viena sona
	delay(sukimas);
	driver.stop(); //stabdyti
	driver.backward(); //atgal
	delay(ratai_tiesiai_delsima);
	driver.stop(); //stabdyti
	
}
