#include <Time.h>

#define RELAY_ON 0
#define RELAY_OFF 1

#define Relay_1  10
#define Relay_2  11

#define TiempoDeRiegoSeg 10



int PinSensorLuz = 4;    // select the input pin for the potentiometer

int Luz = 0;  // variable to store the value coming from the sensor
long startTime; // the value returned from millis when the switch is pressed
long duration; // variable to store the duration
int  Seg;
int  Min ;
int  Hora ;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);

}

void loop() {
  // read the value from the sensor:
  time_t t = now();
  
  MostrarReloj();
  Serial.print(",");
  Serial.print(analogRead(PinSensorLuz));
  Serial.println(",");
 // LeerSensorLuz(); 
  delay(5000);
                 
}


/*
void SensorLluvia() {                  //  Produces average of 6 readings from the rain sensor (n=number of trials to derive stat):
	rain = 0;                     //  When dry: between 446 and 550 (n=314), When wet: between 1013 and 1023 (n=338)
    for (int j = 1; j < 7; j++) {
        rain += (int)analogRead(RainPIN); 
        delay(25);
    }
    rain = rain / 6;
}*/
void MostrarReloj(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
}
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void LeerSensorLuz() {  
    Luz = 0;                             // 6 lecturas del sensor de luz 
                                        //  When dry: between 446 and 550 (n=314), When wet: between 1013 and 1023 (n=338)
    for (int j = 1; j < 7; j++) {
        Luz += (int)analogRead(PinSensorLuz); 
        delay(1000);
    }
    Luz = Luz / 6 ;
 // Serial.print("Lectura Promedio de Luz : ");
 Serial.println(Luz);
}

