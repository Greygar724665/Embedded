int ldr = A0;

void setup() {
	pinMode(A0, INPUT);
	pinMode(13, OUTPUT);
}

void loop() {
	ldr = analogRead(A0);
	if (ldr > 700) {
		digitalWrite(13, 1);
	} else {
		digitalWrite(13, 0);
	}
}
