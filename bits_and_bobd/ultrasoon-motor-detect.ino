// define pins
const int echoPin = 9;
const int trigPin = 10;

// variabelen
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Start de serial communicatie
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // stuur ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // lees echo tijd
  duration = pulseIn(echoPin, HIGH);

  // afstand berekenen
  distance = duration * 0.034 / 2;
  
  // print afstand
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // obstacle detection
  if (distance <= 20) {
    Serial.println("Obstacle detected!");
  }

  delay(300);
}

