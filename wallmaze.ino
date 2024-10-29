int trigRightPin = 10;
int echoRightPin = 11;
int trigFrontPin = 3;
int echoFrontPin = 2;

long distRight, distFront; // distance for ultrasonic in cm

void setupMaze() {

  //Define inputs and outputs
  pinMode(trigRightPin, OUTPUT);
  pinMode(echoRightPin, INPUT);
  pinMode(trigFrontPin, OUTPUT);
  pinMode(echoFrontPin, INPUT);
}


void wallMaze() {
    ultrasonic();
    int turning = 30;
    if (distRight > 7) {
        stop();
        turnRight(turning);
    }
    else if (distFront < 10) {
        stop();
        turnLeft(turning);
    }
    else {
        stop();
        forward();
    }
    delay(20);
    stop();
}

void seeWallTurnRight() {
  ultrasonic();
//   if (cm < 40) {
//     stop();
//     delay(300);
//     turnRight();
//     stop();
//     delay(500);
//   } 
//   else {
//     forward();                            
//   }
}

void ultrasonic() {
    long durationFront, durationRight;
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigRightPin, LOW);
  digitalWrite(trigFrontPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigRightPin, HIGH);
  digitalWrite(trigFrontPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRightPin, LOW);
  digitalWrite(trigFrontPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoRightPin, INPUT);
  durationRight = pulseIn(echoRightPin, HIGH);
 

  pinMode(echoFrontPin, INPUT);
  durationFront = pulseIn(echoFrontPin, HIGH);

  // Convert the time into a distance
  distRight = (durationRight / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  distFront = (durationFront / 2) / 29.1;
//   cm = alpha * cm + (1- alpha) * oldCm;
  
  Serial.print("Distance right: ");
  Serial.print(distRight);
  Serial.print(" cm, Distance Front: ");
  Serial.print(distFront);
  Serial.println(" cm");
  
  delay(2);
}

int invertOurValue(int input) {
  return 255 - input;
}
