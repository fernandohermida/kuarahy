//#include <Time.h>

// -------------------------
// Definicion de Pines
// -------------------------
// Digitales
#define Relay_1  11
#define Relay_2  10
#define RELAY_ON 0
#define RELAY_OFF 1
#define PinHumedadOn 8


// Analogicos
int PinSensorLuz = A1;    // LDR
int PinSensorHumedad = A0;//ajdsfhsdoiufhdsiufg

#define TiempoRiegoValv1  1
#define TiempoRiegoValv2  2
#define Tiempo  1 




boolean DeDia = false;
int Luz = 0;  // variable to store the value coming from the LDR sensor
int Humedad = 0; // variable to store the value coming from the Humedad sensor
long startTime; // the value returned from millis when the switch is pressed
long duration; // variable to store the duration
int ResguardoLuz; // Lo utilizo para resguardar el valor de la luz 1 hora antes de activarse el riego
long previousMillis = 0;
int contamanecer = 0;


void setup() {
  
  Serial.begin(9600);
  
  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  pinMode(Relay_1, OUTPUT);
  //LeerSensorLuz();
   
   
}

void loop() {
  
  startTime = millis();     // Leo tiempo transcurrido 
  
  // ----------------------------------------------------------------------------
  // Resguardo el valor de luz una hora antes para saber si es de dia o noche 
  unsigned long currentMillis = millis(); 
  if(currentMillis - previousMillis > 3600000) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis; 
    ResguardoLuz = Luz;
  }
  // ----------------------------------------------------------------------------
  
  
  LeerSensorLuz();  
 
  if (Luz > 250 and Luz < 700)  {
      LeerSensorHumedad();
  
      //if (Humedad  < 700) {
       if (Humedad  < 1000) { 
    
   
            if (ResguardoLuz < Luz ){                // Riego en el amaencer o atardecer   
             //Amanecer
             contamanecer += 1;
              ActivoValvula1();
              delay(5000);
             }
             else {  
               
             //Atardecer
             } 
             
           if (contamanecer % 2 == 0){            // Riego 1 vez al dia, dia de por medio      
              ActivoValvula2();
              delay(5000);
           } 
          
          
       }
       
      Serial.println("Espero que cambie la luz...");
      delay(60000 * 60); 
      
                   
  }
   
   delay(1000); 
}



void ActivoValvula1(){
   Serial.println("Activo Valvula 1"); 
   digitalWrite(Relay_1, RELAY_ON);
   delay (TiempoRiegoValv1 * 60000);
   Serial.println("Desactivo Riego"); 
   digitalWrite(Relay_1, RELAY_OFF); 
} 


void ActivoValvula2(){
   Serial.println("Activo Valvula N° 2"); 
   digitalWrite(Relay_2, RELAY_ON);
   delay (TiempoRiegoValv2 * 60000);
   Serial.println("Desactivo Valvula N° 2"); 
   digitalWrite(Relay_2, RELAY_OFF); 
} 

/*
void SensorLluvia() {                  //  Produces average of 6 readings from the rain sensor (n=number of trials to derive stat):
	rain = 0;                      //  When dry: between 446 and 550 (n=314), When wet: between 1013 and 1023 (n=338)
    for (int j = 1; j < 7; j++) {
        rain += (int)analogRead(RainPIN); 
        delay(25);
    }
    rain = rain / 6;
}*/

void LeerSensorLuz(){  
    Luz = 0;                            // 6 lecturas del sensor de luz 
                                        //  When dry: between 446 and 550 (n=314), When wet: between 1013 and 1023 (n=338)
    for (int j = 1; j < 7; j++) {
        Luz += (int)analogRead(PinSensorLuz); 
        delay(1000);
    }
    Luz = Luz / 6 ;
 Serial.print("Lectura Promedio de Luz : ");
 Serial.println(Luz);
}

void LeerSensorHumedad(){ 
  digitalWrite(PinHumedadOn, HIGH);  
     Humedad = 0;                            // 6 lecturas del sensor de luz 
                                             //  When dry: between 446 and 550 (n=314), When wet: between 1013 and 1023 (n=338)
    for (int j = 1; j < 7; j++) {
        Humedad += (int)analogRead(PinSensorHumedad); 
        delay(1000);
    }
    Humedad = Humedad / 6 ;
 Serial.print("Lectura Promedio de Humedad : ");
 Serial.println(Humedad);
 digitalWrite(PinHumedadOn, LOW);
}

