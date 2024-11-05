/**
 * H-bridge module HG7881CP/HG7881CP example code
 * http://diyprojects.eu/how-to-use-h-bridge-hg7881-with-external-power-supply-and-arduino
 * Extended by Paul Bucci for COGS 300
 */

/**
 * Create variables to be used to run motor A
 */
int pos = 0;
int maxDist = 1000;
int minDist = 0;
int output = 0;
int error = 0;
int range = 277; // How far the ultrasonic is able to detectv
int setpoint = 30; // 5 centimeter is the set point
 
int motorAPin_A = 8; //Arduino digital 8 is connected to HG7881's A-1A terminal
int motorAPin_B = 9; //Arduino digital 9 is connected to HG7881's A-1B terminal

int motorBPin_A = 4; //Arduino digital 4 is connected to HG7881's B-1A terminal
int motorBPin_B = 5; //Arduino digital 5 is connected to HG7881's B-1B terminal

int speed = 150;    // speed of bot
int backSpeed = 255 - speed;
int turningSpeed = 100;


const double degreeToMS = 3.6;

void setup(){
  /**
   * When program starts set Arduino pinmode for 8 and 9 digital to be OUTPUT
   * so we can use analogWrite to output values from 0 to 255 (0-5V) (PWM) 
   */
  pinMode(motorAPin_A, OUTPUT); // A direction
  pinMode(motorAPin_B, OUTPUT); // A speed
  
  pinMode(motorBPin_A, OUTPUT); // B direction
  pinMode(motorBPin_B, OUTPUT); // B speed

  //Serial Port begin
  Serial.begin (9600);
  setupMaze();


}

void loop() {
  wallMaze();
}



void forward() {
  digitalWrite(motorAPin_A, LOW);
  analogWrite(motorAPin_B, speed);

  // Motor B backward
  digitalWrite(motorBPin_A, LOW);
  analogWrite(motorBPin_B, speed);
}

void backward() {
  digitalWrite(motorAPin_A, HIGH);
  analogWrite(motorAPin_B, backSpeed);

  // Motor B backward
  digitalWrite(motorBPin_A, HIGH);
  analogWrite(motorBPin_B, backSpeed);
}

void stop() {
  digitalWrite(motorAPin_A, LOW);
  analogWrite(motorAPin_B, 0);

  // Motor B backward
  digitalWrite(motorBPin_A, LOW);
  analogWrite(motorBPin_B, 0); 
}

void turnLeft(int degrees) {
  // Motor A forward
  digitalWrite(motorAPin_A, HIGH);
  analogWrite(motorAPin_B, turningSpeed);

  // Motor B backward
  digitalWrite(motorBPin_A, LOW);
  analogWrite(motorBPin_B, 255-turningSpeed);
  delay(degrees * degreeToMS);
}

void turnRight(int degrees) {
  // Motor A backward
  digitalWrite(motorAPin_A, LOW);
  analogWrite(motorAPin_B, 255-turningSpeed);

  // Motor B forward
  digitalWrite(motorBPin_A, HIGH);
  analogWrite(motorBPin_B, turningSpeed);
  delay(degrees * degreeToMS);
}




// void PID() {
//   error = setpoint - cm;
//   int oldOutput = output;
//   if (error > 500) {
//     output = 100;
//   }
//   else {
//     output = error * 100 / range;
//   }
//   output = alpha * output + (1- alpha) * oldOutput;
// }