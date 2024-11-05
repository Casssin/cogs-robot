int trigRightPin = 10;
int echoRightPin = 11;
int trigFrontPin = 3;
int echoFrontPin = 2;
float alpha = 0.90;

long distRight, distFront; // distance for ultrasonic in cm

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
    int turning = 10;
    if (distFront < 15) {
        stop();
        push(-1);
        turnLeft(turning);
    }
    else if (distRight > 15) {
        stop();
        push(1);
        turnRight(turning);
    }
    else if (distRight < 8) {
      stop();
      push(-1);
      turnLeft(turning);
    }
    else {
        stop();
        push(0);
        forward();
        delay(5);
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
  if (distFront == 0) {
    distFront = old;
  } else {
    distFront = alpha * distFront + (1- alpha) * old;
  }
  
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
  if (distRight == 0) {
    distRight = old;
  } 
  else if (distRight > 30) {
    distRight = old;
  } 
  else {
    distRight = alpha * distRight + (1 - alpha) * old;
  }
  
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
