/**************
Developer :-  Milin parekh
Company :-    BUILD MORE
Email:-       2buildmore@gmail.com
site:-        www.instagram.com/build_more/

 if you feel any kind of unknowing ness or doubts during this session then please inform me on my email

************/


#include <NewPing.h>
//#include<Servo.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int P1;    //pwm1 value
int P2;    //pwm2 value

#define E1 3  // pwm Pin for motor 1
#define E2 10  // pwm Pin for motor 2
 
#define I1 8  // Control pin 1 for motor 1
#define I2 7  // Control pin 2 for motor 1
#define I3 6  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
 // int P1=255;
   // int P2=255;
 
// SoftwareSerial my(2,3 );

//int A,s;
char state;
int flag=0; 
void stp();
void fwd();
void left();
void right();
void back();
void rotate();
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
 
void setup() {
  pinMode(5,OUTPUT);
  
   
   Serial.begin(9600);
//    my.begin(9600);
    

/*pinMode(A0,INPUT);     //fr
pinMode(A1,INPUT);     //fl
pinMode(A2,INPUT);     //rl
pinMode(A3,INPUT);     //rr */

    pinMode(E1, OUTPUT);   //  pwm pins
    pinMode(E2, OUTPUT);   // pwm  pins
 
    pinMode(I1, OUTPUT);   
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
    pinMode(A0,INPUT);
    
}
 
void loop()


{
  digitalWrite(5,HIGH);
 
/*fr=digitalRead(A0);
fl=digitalRead(A1);
rl=digitalRead(A2);
rr=digitalRead(A3);


  if(fr == HIGH)
{
digitalWrite(2,HIGH);
     }

  if(fl == HIGH)
{
digitalWrite(4,HIGH);
     }
     if(rl == HIGH)
{
digitalWrite(5,HIGH);
     }
     if(rr == HIGH)
{
digitalWrite(9,HIGH);
     } */
  
  
  
  
  int dis=sonar.ping_cm();   //man comparison class
  
  if(dis > 100)
    {
       P1 = 255;
       P2 = 255;
   }
  else if( 80<dis  && dis<100 )
    {
      P1 = 200 ;
    P2 = 200;
    }
  else if( 60<dis  && dis<80 )
    {
       P1 = 150 ;
     P2 = 150;
    }
  else if( 40<dis && dis<60 )
    {
     P1 = 120;
       P2 = 120;
    }
  else if( dis<40 )
    {
        P1 =50;
        P2 = 50;
    }
     Serial.println(dis);
  
  if(Serial.available() > 0)      // Ckeck for command Recieved
    {    
      state = Serial.read();
      Serial.write(state);  
      flag=0;
    }  
    if (state == 'S')     // Checking Command from User
    {
        stp();
        if(flag == 0){
          Serial.write("Stop");
          flag=1;
       }
    }
    else if (state == 'F')
    {
        fwd();
        if(flag == 0)
        {
          Serial.write("Forward");
          flag=1;
         }
    }
    else if (state == 'B')
    {
        back();
        if(flag == 0)
        {
          Serial.write("Backward");
          flag=1;
        }
    }
    else if (state == 'L')
    {
        left();
        if(flag == 0)
        {
          Serial.write("Left");
          flag=1;
         }
    }
   else if (state == 'R')
  {
        right();
        if(flag == 0)
        {
          Serial.write("Right");
          flag=1;
         }
    }
 /*else if (state=='G')
 {
    rotate();
    if(flag == 0)
    {
       Serial.write("rotate");
       flag=1;
    }
 }*/
    
 
 //loop() ends here
 }
 
 void stp()                              //fumction for stopping the car
 {
   digitalWrite(I1, LOW);
    digitalWrite(I2, LOW);
    digitalWrite(I3, LOW);
    digitalWrite(I4, LOW);
 }
 
void fwd()                                                     //forward
{
    analogWrite(E1,P1); 
    analogWrite(E2,P2); 
 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
 delay(15);
 digitalWrite(I1,LOW);
  digitalWrite(I3,LOW);
    //delay(100);
    
 
    // change direction
 
    //digitalWrite(E1, LOW);
    //digitalWrite(E2, LOW);
 
    //delay(10);
  
}
void back()          // Backward
{
    analogWrite(E1, P1); // Run in half speed
    analogWrite(E2,P2); // Run in full speed
 
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
delay(15);
 digitalWrite(I1, LOW);
    digitalWrite(I4,LOW);
    
    /*delay(100);
    
 
    // change direction
 
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
 
    delay(10);*/
  
}
void left()          //LEFT
{
  analogWrite(E1,P1); // Run in half speed
    analogWrite(E2,P2); // Run in full speed
 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
    delay(15);
   digitalWrite(I1,LOW);
    digitalWrite(I4,LOW);

  /* delay(100);
    
 
    // change direction
 
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
 
    delay(10);*/
}

void right()  //Right
{
    analogWrite(E1, P1); // Run in half speed
    analogWrite(E2,P2); // Run in full speed
 
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
delay(15);
 digitalWrite(I2,LOW);
    digitalWrite(I3,LOW);

  }    
   /*delay(100);
    
 
    
  // change direction
 
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
 
    delay(10);*/

/*void rotate()
{
  analogWrite(E1, P1); // Run in half speed
    analogWrite(E2,P2); // Run in full speed
 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);*/
    
   /*delay(100);
    
 
    // change direction
 
    digitalWrite(E1, LOW);
    digitalWrite(E2, LOW);
 
    delay(10);*/


