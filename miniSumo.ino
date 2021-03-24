#include <IRremote.h>

int motorLeftReverse = 2;      
int motorLeftForward = 4;

int motorRightForward = 6;     
int motorRightReverse = 8;

int trigFront = 5;             
int echoFront = 7;

int trigBack = 9;              
int echoBack = 3;

const int maxDistance = 30;     //         attack <= maxDistance (cm)   |   search enemy > maxDistance (cm) 
int frontDistance, backDistance;



// ==================== SETUP ==================

void setup() 
{
  pinMode(motorLeftReverse, OUTPUT);
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorRightReverse, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);

  Serial.begin(9600);
}



// =================== LOOP ====================

void loop() {
   frontDistance = frontSensor();
   backDistance = backSensor();
   
   goMotors(frontDistance, backDistance);
}



// ================ FUNCTIONS ==================


int frontSensor()
{
  int duration, distance;
                                            // we read the distance ahead
  digitalWrite(trigFront, LOW); 
  delayMicroseconds(2);  
  
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFront, LOW);

  duration = pulseIn(echoFront, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}


int backSensor()
{ 
  int duration, distance;
                                            // we read the distance from the back
  digitalWrite(trigBack, LOW); 
  delayMicroseconds(2);  
  
  digitalWrite(trigBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigBack, LOW);

  duration = pulseIn(echoBack, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}


void goMotors(int frontDistance, int backDistance)
{
  
//---------------------------------------------------------------------------------------------------------------------
    if (frontDistance < 4) 
        frontDistance = maxDistance + 5;     // Sensors Error (4 is the minimum value that the sensor can really read)
    if (backDistance < 4)
        backDistance = maxDistance + 5;
//---------------------------------------------------------------------------------------------------------------------
        
    if ((frontDistance > maxDistance) && (backDistance > maxDistance))
        searchEnemy();
    
    if (((frontDistance <= maxDistance) && (backDistance <= maxDistance)) && (backDistance < frontDistance))
        goBack();

    if (((frontDistance <= maxDistance) && (backDistance <= maxDistance)) && (backDistance > frontDistance))
        goFront();

    if ((backDistance <= maxDistance) && ((frontDistance > maxDistance) || (backDistance < frontDistance)))
        goBack();
        
    if ((frontDistance <= maxDistance) && ((backDistance > maxDistance) || (backDistance > frontDistance)))
        goFront();

}


void goFront()
{
    digitalWrite(motorLeftForward, HIGH);
    digitalWrite(motorLeftReverse, LOW);
    digitalWrite(motorRightForward, HIGH);
    digitalWrite(motorRightReverse, LOW);  
}


void goBack()
{
    digitalWrite(motorLeftForward, LOW);
    digitalWrite(motorLeftReverse, HIGH);
    digitalWrite(motorRightForward, LOW);
    digitalWrite(motorRightReverse, HIGH);
}


void searchEnemy()
{
    digitalWrite(motorLeftForward, HIGH);
    digitalWrite(motorLeftReverse, LOW);
    digitalWrite(motorRightForward, LOW);
    digitalWrite(motorRightReverse, HIGH);
}
