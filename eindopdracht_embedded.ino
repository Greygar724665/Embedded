// ULTRASONIC PINS
const uint8_t echoPin = 9;
const uint8_t trigPin = 10;
// MOTOR PINS
const uint8_t motorApin1 = 1;
const uint8_t motorApin2 = 2;
const uint8_t motorBpin1 = 3;
const uint8_t motorBpin2 = 4;
// MOTOR SPEED PINS
const uint8_t motorAen = 5;
const uint8_t motorBen = 6;
// LDR PIN
const uint8_t ldrPin = A0;
// LED PIN
//13

// Variables -- ULTRASONIC SENSOR
int distance = 0;

// Variables -- MOTOR
int motorSpeed = 0;
bool enabled = false;

// Variables -- LDR
int lightValue;

// Helper functions -- ULTRASONIC SENSOR
void setDistance() {
  static int state = 0;
  static unsigned long timer = 0;
  bool newReading;
  static unsigned long echoStart = 0;

  unsigned long now = micros();

  switch (state) {
    case 0: // cooldown between measurements (~60ms)
      if (now - timer >= 60000) {
        digitalWrite(trigPin, LOW);
        timer = now;
        state = 1;
      }
      break;

    case 1: // wait 4us LOW
      if (now - timer >= 4) {
        digitalWrite(trigPin, HIGH);
        timer = now;
        state = 2;
      }
      break;

    case 2: // wait 10us HIGH
      if (now - timer >= 10) {
        digitalWrite(trigPin, LOW);
        timer = now;
        state = 3;
      }
      break;

    case 3: // wait for echo HIGH (timeout 30ms)
      if (digitalRead(echoPin) == HIGH) {
        echoStart = now;
        state = 4;
      } else if (now - timer > 30000) {
        timer = now;
        state = 0; // timeout, restart
      }
      break;

    case 4: // wait for echo LOW (timeout 30ms)
      if (digitalRead(echoPin) == LOW) {
        unsigned long echoTime = now - echoStart;
        if (echoTime > 25000) {
          timer = now;
          state = 0;
          break;
        }
        distance = echoTime * 0.0343 / 2;
        newReading = true;
        timer = now;
        state = 0;
      } else if (now - echoStart > 30000) {
        timer = now;
        state = 0; // timeout, restart
      }
      break;
  }
}

// Helper functions -- MOTOR
void decideSpeed() {
	if (distance > 40) motorSpeed = 255;
	else if (distance > 25) motorSpeed = 128;
	else motorSpeed = 0;
}


void enableMotor(int motor, bool reverse = false) {
  if (motor == 1) {
    if (reverse) {
      digitalWrite(motorApin1, LOW);
      digitalWrite(motorApin2, HIGH);
    } else {
      digitalWrite(motorApin1, HIGH);
      digitalWrite(motorApin2, LOW);
    }
  } else {
    if (reverse) {
      digitalWrite(motorBpin1, LOW);
      digitalWrite(motorBpin2, HIGH);
    } else {
      digitalWrite(motorBpin1, HIGH);
      digitalWrite(motorBpin2, LOW);
    }
  }
}


void setMotorSpeed(int speed, int motorEn) {
  bool reverse = (speed < 0);
  speed = min(abs(speed), 255);
  int motor = (motorEn == motorAen) ? 1 : 2;

  analogWrite(motor, speed);
  enableMotor(motor, reverse);
}

void disableMotor(int motor) {
  if (motor==1) {
    digitalWrite(motorApin1, LOW);
    digitalWrite(motorApin2, LOW);
  } else {
    digitalWrite(motorBpin1, LOW);
    digitalWrite(motorBpin2, LOW);
  }
}

void setLight() {
  int lightVal = analogRead(ldrPin);
  if (lightVal < 50) digitalWrite(13, HIGH);
  else digitalWrite(13, HIGH);

}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  pinMode(motorApin1, OUTPUT);
  pinMode(motorApin2, OUTPUT);
  pinMode(motorBpin1, OUTPUT);
  pinMode(motorBpin2, OUTPUT);
  pinMode(motorAen, OUTPUT);
  pinMode(motorBen, OUTPUT);

  pinMode(ldrPin, INPUT);

  // Initially off
  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, LOW);

  delay(50); // Give sensor time to stabilize
}

void loop() {
  if (enabled) {
    setDistance();
    decideSpeed();
    setLight();
  } else {
    disableMotor(1);
    disableMotor(2);
  }
}
