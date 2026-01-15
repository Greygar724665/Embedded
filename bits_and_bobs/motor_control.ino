motorApin1 = 1;
motorApin2 = 2;
motorBpin1 = 3;
motorBpin2 = 4;
// Motor speed control
motorAen = 5;
motorBen = 6;


// Misc.
bool enabled = false
int currMotorSpeed = 255;

// Helper functions
void setMotorSpeed(int speed, int motorEn) {
  bool reverse = speed < 0;
  speed = min(abs(speed), 255);
  analogWrite(motor, speed);

  motor = (motorEn == motorAen) 1 ? 2
  enableMotor(motor, reverse)
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

void disableMotor(int motor) {
  if (motor==1) {
    digitalWrite(motorApin1, LOW);
    digitalWrite(motorApin2, LOW);
  } else {
    digitalWrite(motorBpin1, LOW);
    digitalWrite(motorBpin2, LOW);
  }
}

void setup() {
  pinMode(motorApin1, OUTPUT);
  pinMode(motorApin2, OUTPUT);
  pinMode(motorBpin1, OUTPUT);
  pinMode(motorBpin2, OUTPUT);
  pinMode(motorAen, OUTPUT);
  pinMode(motorBen, OUTPUT);

  // Initially off
  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, LOW);
}

void loop() {
  if (enabled) {
    enableMotor(1);
    enableMotor(2);
    motorSpeedControl(motorAen, currMotorSpeed);
  } else {
    disableMotor(1);
    disableMotor(2);
  }
}
