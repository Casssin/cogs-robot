
const int seeUpperBound = 5;
const int seeLowerBound = 3;
const int sigDiff = 3;
int trigFrontRight = 13;
int echoFrontRight = 12;
int trigFrontLeft = 6;
int echoFrontLeft = 7;
const float alphaNew = 0.75;

long distFrontRight, distFrontLeft;

void setupPaper() {
    pinMode(trigFrontRight, OUTPUT);
    pinMode(echoFrontRight, INPUT);
    pinMode(trigFrontLeft, OUTPUT);
    pinMode(echoFrontLeft, INPUT);
}

void paper() {
    ultrasonicFrontRight();
    ultrasonicFrontLeft();
    int diff = abs(distFrontRight - distFrontLeft);
    bool seePaperRight = distFrontRight <= seeUpperBound;
    bool seePaperLeft = distFrontLeft <= seeUpperBound;
    bool imbalance = diff > sigDiff;
    int turning = 15;
    int frontBias = 3;

    if (!seePaperRight && !seePaperLeft) {
        forward();
        delay(turning * frontBias);
    }
    else if (seePaperRight && seePaperLeft && !imbalance) {
        if (distFrontRight <= seeLowerBound || distFrontLeft <= seeLowerBound) {
            backward();
            delay(turning * frontBias);
        }
        else {
            stop();
        }
    }
    else if (distFrontRight > distFrontLeft && imbalance) {
        turnLeft(turning);
    }
    else if (distFrontRight < distFrontLeft && imbalance) {
        turnRight(turning);
    }
    else {
        forward();
        delay(turning * frontBias);
    }

    stop();
    delay(10);
}

void ultrasonicFrontRight() {
    long durationFront;
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigFrontRight, LOW);
  delayMicroseconds(5);
  digitalWrite(trigFrontRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFrontRight, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 

  pinMode(echoFrontRight, INPUT);
  durationFront = pulseIn(echoFrontRight, HIGH);

  // Convert the time into a distance
  long old = distFrontRight;
  distFrontRight = (durationFront / 2) / 29.1;
    distFrontRight = alphaNew * distFrontRight + (1- alphaNew) * old;
  delay(2);
}

void ultrasonicFrontLeft() {
    long durationLeft;
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigFrontLeft, LOW);
  delayMicroseconds(5);
  digitalWrite(trigFrontLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFrontLeft, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 

  pinMode(echoFrontLeft, INPUT);
  durationLeft = pulseIn(echoFrontLeft, HIGH);

  // Convert the time into a distance
  long old = distFrontLeft;
  distFrontLeft = (durationLeft / 2) / 29.1;
  distFrontLeft = alphaNew * distFrontLeft + (1- alphaNew) * old;
  
//   Serial.print("Front Right: ");
//   Serial.print(distFrontRight);
//   Serial.print(" , Front Left: ");
//   Serial.println(distFrontLeft);
  
  delay(2);
}