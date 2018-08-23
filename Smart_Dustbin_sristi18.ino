#include <Stepper.h>
int ledPin = 12;               
int inputPin = 2;               // PIR sensor
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int dir1A = 4;
int dir1B = 5;

const int trigPin = 8;
const int echoPin = 9;
int led =13;
long duration;
int distance;

//32 steps
int pwm1A = 3;
int pwm1B = 6;

 
Stepper stepper1(32,3,4,5,6);

 
void setup() 
{
  pinMode(ledPin, OUTPUT);      
  pinMode(inputPin, INPUT);     
  pinMode(pwm1A, OUTPUT);
  pinMode(pwm1B, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT);// Sets the echoPin as an Input
pinMode(led,OUTPUT);
  
  digitalWrite(pwm1A, HIGH);
  digitalWrite(pwm1B, HIGH);
  
  
  stepper1.setSpeed(600);
  
  Serial.begin(9600);
  Serial.println("Sensor is working!"); 
}
void loop()
{
  val = digitalRead(inputPin);  
  if (val == HIGH) 
  { digitalWrite(ledPin, HIGH); 
    if (pirState == LOW) 
    {// we have just turned on     // print when motion detected
    Serial.print("Motion detected! at ");
    Serial.print(millis()/1000);
    Serial.println(" sec");
        // Turn the stepper 100 steps to open which means 180 degrees
               
        stepper1.step(1300);
        
        // Wait half minunte
        delay(5000);

        // Turn the stepper 100 steps to close which means 180 degrees
     
        stepper1.step(-1300);
        
        // Wait half second
        delay(500);
     
    pirState = HIGH;
    }
  } 
 

  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

if (distance<=10)
{digitalWrite(led,HIGH);
 Serial.println("Dustbin Full");
 delay(1000);
}
else 
{digitalWrite(led,LOW);
Serial.println("USE");
digitalWrite(ledPin, LOW);
    if (pirState == HIGH)
    { // we have just turned of  // print the when motion not detected:
      Serial.print("Motion ended! at ");   
      Serial.print(millis()/1000);
         Serial.println(" sec"); // We only want to print on the output change, not state
      pirState = LOW;
    }
delay(1000);
}

}
