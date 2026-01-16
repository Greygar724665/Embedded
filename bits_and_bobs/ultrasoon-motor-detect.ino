// define pins
const int echoPin = 9;
const int trigPin = 10;

// variables
int distance = 0;

void getDistance() {
  static int state = 0;
  static unsigned long timer = 0;
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

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  delay(50); // Give sensor time to stabilize
}

void loop() {
  getDistance();
  Serial.print(distance);
}
