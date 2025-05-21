// Ultrasonic Sensor Pins
#define trigFront A1
#define echoFront A0

#define trigLeft A3
#define echoLeft A2

#define trigRight 5
#define echoRight 4

// Motor Driver Pins
#define ENA 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENB 11

// Minimum Distance from obstacles
int thresholdDistance = 50;     // Front threshold
int sideThreshold = 20;         // Left/Right side threshold

// Base motor speed
int baseSpeed = 255;

// Function to read distance in cm from HC-SR04
long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long time = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  long distance = time * 0.034 / 2;
  return (distance > 400 || time == 0) ? 400 : distance;
}

// Motor control functions
void moveForward() {
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Turn LEFT: Right motor forward, Left motor stopped
void turnLeft() {
  analogWrite(ENA, baseSpeed);  // Left motor forward
  analogWrite(ENB, 0);          // Right motor stopped
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Turn RIGHT: Left motor forward, Right motor stopped
void turnRight() {
  analogWrite(ENA, 0);          // Left motor stopped
  analogWrite(ENB, baseSpeed);  // Right motor forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
  digitalWrite(IN1, LOW);   // Left motor backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);   // Right motor backward
  digitalWrite(IN4, HIGH);
}

void setup() {
  Serial.begin(9600);

  // Sensor pins
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  pinMode(trigLeft, OUTPUT); pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT); pinMode(echoRight, INPUT);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
}

void loop() {
  long front = readDistance(trigFront, echoFront);
  long left = readDistance(trigLeft, echoLeft);
  long right = readDistance(trigRight, echoRight);

  // Move forward if front is clear or no echo detected
  if (front > thresholdDistance && left > sideThreshold && right > sideThreshold) {
    moveForward();
  } else {
    stopMotors(); // stopped for thinking 
    delay(50);

    // Turn based on side sensor distance
    if (right > sideThreshold && right > left) {
      turnRight();  // right motor forward only
    } else if (left > sideThreshold) {
      turnLeft(); // left motor forward only
    } else {
      // If both sides are blocked, do a hard stop
      stopMotors();
      delay(50);// Thinking
      moveBackward();
      delay(2000);// Moving Backward
      turnRight();
      delay(300);// Turning right to move out of this place where we stucked 
    }

    delay(600);  // turn duration
    stopMotors();
    delay(100);
  }

  delay(100);
}
