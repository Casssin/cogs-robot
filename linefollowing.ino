const int leftPhotoPin = A5;
const int centerPhotoPin = A4;
const int rightPhotoPin = A3;

int history[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};     // 0 is forward value, 1 is right, -1 is left
void tapeMaze() {
  Serial.print("Left: ");
  Serial.print(analogRead(leftPhotoPin));
  Serial.print(" Center: ");
  Serial.print(analogRead(centerPhotoPin));
  Serial.print(" Right: ");
  Serial.println(analogRead(rightPhotoPin));
  stop();
  bool leftVal = seeWhiteLeft(analogRead(leftPhotoPin));
  bool rightVal = seeWhiteRight(analogRead(rightPhotoPin));
  bool centerVal = seeWhiteCenter(analogRead(centerPhotoPin));
  int turning = 8;
  float forwardBias = 1;

  // Only center sees white, move forward
  if (centerVal && !leftVal && !rightVal) {
    push(0);
    forward();
  } 
  // only right sees white, turn right
  else if(!centerVal && !leftVal && rightVal) {
    push(1);
    turnRight(turning);
  }
  // only left sees white, turn left
  else if(!centerVal && leftVal && !rightVal) {
    push(-1);
    turnLeft(turning);
  }
  // center and left see white, turh left
  else if(centerVal && leftVal && !rightVal) {
    push(-1);
    turnLeft(turning);
  }
  // center and right see white, turh right
  else if(centerVal && !leftVal && rightVal) {
    push(1);
    turnRight(turning);
  }
  // else check history and move based on history
  else {
    int direction = historyProb();
    if (direction == -1) {
      turnLeft(turning);
    } else if(direction == 0) {
      forward();
    } else {
      turnRight(turning);
    }
  }
  delay(10);
}

void push(int value) {
  int temp[sizeof(history)/sizeof(history[0])];
  memcpy(temp, history, sizeof(history)/sizeof(history[0]));
  for(int i = 1; i < sizeof(history)/sizeof(history[0]); i++) {
    history[i] = temp[i - 1];
  }
  history[0] = value;
}

// returns -1 if probabilitically should move left, 0 if should moveForward, 1 if should move Right
int historyProb() {
  int countRight, countLeft, countFor = 0;
  for (int i = 0; i < sizeof(history); i++) {
    if (history[i] == 0) {
      countFor++;
    } else if (history[i] == 1) {
      countRight++;
    } else {
      countLeft++;
    }
  }

  int randomValue = rand() % 10 + 1;
  if (randomValue <= countLeft) {
    return -1;
  } else if (randomValue <= countLeft + countFor) {
    return 0;
  } else {
    return 1;
  }
}

bool seeWhiteCenter(int value) {
  return value >= 30;       // arbitrary value need to test
}

bool seeWhiteLeft(int value) {
  return value >= 55;       // arbitrary value need to test
}

bool seeWhiteRight(int value) {
  return value >= 23;       // arbitrary value need to test
}
