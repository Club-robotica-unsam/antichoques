//// dist = distancia / dsitance no se si lo pued cambiar, no se como lo toma la libreria
/// DD=distancia derecha 
/// DI=distancia derecha 
/// TR=doblar derecha
/// TL=dobalr izquierda
/// MD=mirar derecha
/// MI=mirar izquierda
/// MOV_AD= mover adelante
/// MOV_AT= mover atras
/// Parar= frenar
////PREGUNTAR SI LOS TIEMPO DE ESPERA ESTABAN EN MS

////// los delays estaban en "ms", NO?

//// librerias del sensor, servo y motor    ////// no se si se usa, pero estaba dentro de AFM
#include <AFMotor.h>                          //// porque no esta en naranja
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A4                           ///defino pins del ultrasonido  //// es el disparador segun la libreria
#define ECHO_PIN A5                           ///  el eco de retorno o como se llame
#define MAX_DISTANCE 200                      //// la distancia , es en cm, NO?
#define MAX_SPEED 170                         //// la velocidad (ver, el tope era 255 , por lo que vi)
#define MAX_SPEED_OFFSET 20



NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);             
AF_DCMotor motor1(1, MOTOR12_1KHZ);     //////el de la izquierda             //////1 y 3 es el puerto  
AF_DCMotor motor2(2, MOTOR12_1KHZ);     /////el de la derecha           //// el 1kHZ puede ser 2 8 o 64, depende lo que soporte
AF_DCMotor motor3(3, MOTOR12_1KHZ);  
AF_DCMotor motor4(4, MOTOR12_1KHZ);  
Servo myservo;
int distance = 100;
int speedSet = 0;
boolean avanzar=false;                       //////tipo de dato booleano


///////////////////////////////////////////////////////////////////////////////////
void setup() 
  {
  myservo.attach(10);                                   ///////// pin 9 / 8 / 7 o etc
  myservo.write(50);                             //// ver en ue angulo que ve pa delante
  delay(2000);                                         ////es en ms no?
  distance = readPing();
  delay(100);                                           ////es en ms no?
                                                       /////  hacerlo un par de veces, para configurar i ver que esta bien , tal vez(? o no?
                                                      ////// porque el robot es crack y no lo necesita....
}

int MI()
{
    myservo.write(90); //// ver caunto moverlo moverlo
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write( 0 );   ///vuelve a centrarse
    return distance;
    delay(100);
}

///////////////////////////////////////////////////////////////////////////////////
int MD()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

///////////////////////////////////////////////////////////////////////////////////
int readPing()    /////// me olvide que iba a poner jejeje
                       ////// lee la distancia del sensor
{ 
  delay(70);                  ///////// sigo en dudas que unidad usa............. 
  int cm = sonar.ping_cm();    
  if(cm==0)
  {
    cm = 190;               
  }
  return cm;
}

///////////////////////////////////////////////////////////////////////////////////
void Parar() 
    {
      motor1.run(RELEASE); 
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    }

///////////////////////////////////////////////////////////////////////////////////
void TL()                     ////// no saben  lo que tarde en procesar esto de girar  en mi cabeza
    {
      motor1.run(BACKWARD);        ////// si va para el otro lado hay que configurar al reves el  " motor1"
      motor2.run(BACKWARD);    /////// y el " motor2"
      motor3.run(FORWARD);       /////// creo que entre mas tiempo tarde, mas tiempo se queda "girando"
      motor4.run(FORWARD);   
      delay(500);
      motor1.run(FORWARD);     
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    }

///////////////////////////////////////////////////////////////////////////////////
void TR()
      {
       motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
       motor4.run(BACKWARD);     
      delay(200);
      motor1.run(FORWARD);      
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);          
      }

/////////////////////////////////////////////////////////////////////////////////// pensar como crear la funcion MOV_AD
void MOV_AD()     ////// un amigo me dijo lo de tipo booleano
{                   ///// mi amigo hizo casi todo este cod
  if(!avanzar)
  {
    avanzar=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);          
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=1) ////// no se que tan rapido hace que avance
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(10);                                    ///////// esto deberia se mas rapido que lo que tarda en girar?
   }
  }
}


///////////////////////////////////////////////////////////////////////////////////
void MOV_AT() {
    avanzar=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=1) ////// lo mismo de antes
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(10);                                      ///////// esto deberia se mas rapido que lo que tarda en girar?
  }
}  


///////////////////////////////////////////////////////////////////////////////////
void loop() 
{
 int DR = 0;                                   ////defino la distancia //// es en cm, no?
 int DL = 0;                                   //// es en cm, no?
 delay(40);                                           ////es en ms no?

 if (distance <=10)
     {
       Parar();
       delay(200);
       MOV_AT();
       delay(200);
       Parar();
       delay(200);
       DR = MD(); 
       delay(200);
       DL = MI();
       delay(200);

  if(DR>=DL)  //////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHH PUTAS LLAVES
    {
        TR();
         Parar();
     }
     else
     {
        TL();
        Parar();
      }
       }
       else
       {
         MOV_AD();
        }
     distance = readPing();
}   //////ACA, TERMINA EL LOOP , CREO, CREO FIJARSE

///////////////////////////////////////////////////////////////////////////////////





/////// no se si el orden de las funciones se ven afectadas a la hora de ejecutar
