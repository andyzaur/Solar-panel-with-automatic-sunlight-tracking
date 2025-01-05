#include <Servo.h>

Servo servoHorizontal;  
Servo servoVertical

int photoresistorPins[4] = {A0, A1, A2, A3}; // A0: Top Left, A1: Bottom Left, A2: Top Right, A3: Bottom Right
int servoHorizontalPin = 9; // Pin controlling horizontal movement
int servoVerticalPin = 10;  // Pin controlling vertical movement

int horizontalPosition = 90
int verticalPosition = 90;    
int tolerance = 10;           // Tolerance for the difference in light values
int stepSize = 2

void setup() {
  Serial.begin(9600);  // Initialize serial communication

  servoHorizontal.attach(servoHorizontalPin);
  servoVertical.attach(servoVerticalPin);

  // Set initial positions
  servoHorizontal.write(horizontalPosition);
  servoVertical.write(verticalPosition);

  for (int i = 0; i < 4; i++) {
    pinMode(photoresistorPins[i], INPUT);
  }

  Serial.print("Initial Horizontal Position: ");
  Serial.println(horizontalPosition);
  Serial.print("Initial Vertical Position: ");
  Serial.println(verticalPosition);
}

void loop() {
  // Read the values from the photoresistors
  int topleft = analogRead(photoresistorPins[0]);
  int bottomleft = analogRead(photoresistorPins[2]);
  int topright = analogRead(photoresistorPins[1]);
  int bottomright = analogRead(photoresistorPins[3]);

  // Print the values to the Serial Monitor
  Serial.print("Top Left (A0): ");
  Serial.println(topleft);
  Serial.print("Bottom Left (A1): ");
  Serial.println(bottomleft);
  Serial.print("Top Right (A2): ");
  Serial.println(topright);
  Serial.print("Bottom Right (A3): ");
  Serial.println(bottomright);

  int averageLeft = (topleft + bottomleft) / 2;
  int averageRight = (topright + bottomright) / 2;
  int averageTop = (topleft + topright) / 2;
  int averageBottom = (bottomleft + bottomright) / 2;

  if (averageLeft > averageRight + tolerance) {
    // Move right
    horizontalPosition = constrain(horizontalPosition + stepSize, 0, 180);
  } else if (averageRight > averageLeft + tolerance) {
    // Move left
    horizontalPosition = constrain(horizontalPosition - stepSize, 0, 180);
  }

  if (averageTop > averageBottom + tolerance) {
    // Move down
    verticalPosition = constrain(verticalPosition - stepSize, 0, 180);
  } else if (averageBottom > averageTop + tolerance) {
    // Move up
    verticalPosition = constrain(verticalPosition + stepSize, 0, 180);
  }

  servoHorizontal.write(horizontalPosition);
  servoVertical.write(verticalPosition);

  Serial.print("Horizontal Position: ");
  Serial.println(horizontalPosition);
  Serial.print("Vertical Position: ");
  Serial.println(verticalPosition);

  delay(10
}
