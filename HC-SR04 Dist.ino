#define TRIG_PIN 4  // Trig pin of HC-SR04 connected to digital pin 10
#define ECHO_PIN 3  // Echo pin of HC-SR04 connected to digital pin 11
#define NUM_SAMPLES 5  // Number of samples to take for noise averaging

void setup() {
  // Set Trig and Echo pins as output and input, respectively
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  long distance = getDistance();  // Get distance to object in cm

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);  // Delay for half a second before taking another reading
}

// Function to get distance to object in cm using noise averaging
long getDistance() {
  long sum = 0;  // Sum of samples

  // Take multiple samples and sum them
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += getDistanceSample();
  }

  // Return average of samples
  return sum / NUM_SAMPLES;
}

// Function to get a single distance sample in cm
long getDistanceSample() {
  digitalWrite(TRIG_PIN, LOW);  // Set Trig pin low
  delayMicroseconds(2);  // Delay for 2 microseconds
  digitalWrite(TRIG_PIN, HIGH);  // Set Trig pin high
  delayMicroseconds(10);  // Delay for 10 microseconds
  digitalWrite(TRIG_PIN, LOW);  // Set Trig pin low

  // Measure the time it takes for the Echo pin to go high (pulse width)
  long pulseWidth = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance to object in cm using pulse width and speed of sound
  long distance = pulseWidth / 58.2;

  return distance;
}
