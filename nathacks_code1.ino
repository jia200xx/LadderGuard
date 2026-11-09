
#include <Arduino_LSM9DS1.h>
#include <math.h>

// Arduino board pin connections
const int redLED = 2; // D2
const int greenLED = 3; // D3
const int buzzer = 8; // D8
const int buzzerSwitch = 4; // D4

// Set constant for safe angle ranges
const float minAngle = 65.0;
const float maxAngle = 85.0;

// Set constants for the safe movement range
const float movementThreshold = 0.20;

// Previous acceleration readings
float previousX = 0;
float previousY = 0;
float previousZ = 0;

bool firstReading = true; // Checks if this is the first reading
unsigned long movementAlarmUntil = 0; // Stores the time when the movement warning should stop

void setup() {
  Serial.begin(9600);  // 9600 baud for the serial monitor

  pinMode(redLED, OUTPUT); 
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Switch pin is set as input
  pinMode(buzzerSwitch, INPUT_PULLUP);

  digitalWrite(buzzer, LOW); // Buzzer starts off 

  if (!IMU.begin()) {
    while (1);  // if accelerometer did not initialize, the code will not run
  }
}

void loop() {
  float x, y, z;

  // If the switch is closed (LOW), the buzzer turns on
  bool buzzerEnabled =
    (digitalRead(buzzerSwitch) == LOW);

  // Obtains acceleration readings and calculates the angle of ladder
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z); 

    // Calculate ladder angle
    float angle = atan2(
      abs(x),
      sqrt(y*y + z*z)
    ) * 180.0 / PI;

    Serial.print("Ladder Angle: ");
    Serial.print(angle, 2);
    Serial.println(" degrees");

    // Calculate sudden movement
    float movement = 0;

    // Only calculates movement after first reading since it uses original readings
    if (!firstReading) {
      movement = sqrt(
        pow(x - previousX, 2) +
        pow(y - previousY, 2) +
        pow(z - previousZ, 2)
      );
    }

    previousX = x;
    previousY = y;
    previousZ = z;
    firstReading = false;

    // Movement alarm lasts 1.5 seconds
    if (movement > movementThreshold) {
      movementAlarmUntil = millis() + 1500;
    }

    // Check safety conditions
    bool angleUnsafe =
      (angle < minAngle || angle > maxAngle);

    bool movementUnsafe =
      (millis() < movementAlarmUntil); // Only unsafe if its within the 1.5 seconds alarm deadline

    bool unsafe = angleUnsafe || movementUnsafe;

    // LEDs 
    if (unsafe) {
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
    } else {
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }

    // Buzzer controlled by  switch
    if (buzzerEnabled && unsafe) {
      tone(buzzer, 2048);
    } else {
      noTone(buzzer);
    }

  }

  delay(100);
}
