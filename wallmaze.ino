int trigRightPin = 10;
int echoRightPin = 11;
int trigFrontPin = 13;
int echoFrontPin = 12;
int trigLeftPin = 3;
int echoLeftPin = 2;
float alpha = 0.75;
int histRight[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int histLeft[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

long distRight, distFront, distLeft; // distance for ultrasonic in cm

void setupMaze() {

  //Define inputs and outputs
  pinMode(trigRightPin, OUTPUT);
  pinMode(echoRightPin, INPUT);
  pinMode(trigFrontPin, OUTPUT);
  pinMode(echoFrontPin, INPUT);
}


void wallMaze() {
    ultrasonicFront();
    ultrasonicRight();
    ultrasonicLeft();
    int turning = 10;
    bool seeRight = distRight < 15;
    bool seeLeft = distLeft < 15;
    bool seeFront = distFront < 15;
    if (distRight < 8) {
      turnLeft(turning);
      push(1);
    }
    else if (distLeft < 8) {
      turnRight(turning);
      push(-1);
    }
    else if (distFront < 3) {
      backward();
      delay(turning * 2);
    }
    else if (!seeRight && !seeLeft && !seeFront) {
      turnRight(turning);
      push(1);
    }
    else if (!seeFront && !seeRight && seeLeft) {
      turnRight(turning);
      push(1);
    }
    else if (!seeFront && seeRight && !seeLeft) {
      forward();
      delay(turning * 2);
    }
    else if(!seeFront && seeRight && seeLeft) {
      forward();
      delay(turning * 2);
    }
    else {
      int dir = historyProb();
      if (dir == 1) {
        turnRight(turning);
      }
      else if(dir == 0) {
        forward();
        delay(turning);
      }
      else {
        turnLeft(turning);
      }
    }
    delay(20);
    stop();
}



void ultrasonicFront() {
    long durationFront;
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigFrontPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigFrontPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFrontPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 

  pinMode(echoFrontPin, INPUT);
  durationFront = pulseIn(echoFrontPin, HIGH);

  // Convert the time into a distance
  long old = distFront;
  distFront = (durationFront / 2) / 29.1;
    distFront = alpha * distFront + (1- alpha) * old;
  delay(2);
}

void ultrasonicLeft() {
    long durationLeft;
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigLeftPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigLeftPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeftPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 

  pinMode(echoLeftPin, INPUT);
  durationLeft = pulseIn(echoLeftPin, HIGH);

  // Convert the time into a distance
  long old = distLeft;
  distLeft = (durationLeft / 2) / 29.1;
  distLeft = alpha * distLeft + (1- alpha) * old;
  
  
  delay(2);
}


void ultrasonicRight() {
  long durationRight;
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigRightPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigRightPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigRightPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 

  pinMode(echoRightPin, INPUT);
  durationRight = pulseIn(echoRightPin, HIGH);

  // Convert the time into a distance
  long old = distRight;
  distRight = (durationRight / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  if (distRight > 30) {
    distRight = old;
  } 
  else {
    distRight = alpha * distRight + (1 - alpha) * old;
  }
  
  Serial.print("Distance right: ");
  Serial.print(distRight);
  Serial.print(" cm, Distance Front: ");
  Serial.print(distFront);
  Serial.print(" cm, Distance Left: ");
  Serial.print(distLeft);
  Serial.println(" cm");
  
  delay(2);
}

int invertOurValue(int input) {
  return 255 - input;
}
