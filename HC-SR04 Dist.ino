#define trig 4
#define echo 3

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop(){
  digitalWrite(trig,LOW);
  delay(0.002);
  digitalWrite(trig,HIGH);
  delay(0.01);
  digitalWrite(trig,LOW);
  delay(0.002);

  float duration = pulseIn(echo,HIGH);
  float time = duration / 2;

  // Assuming 20 degrees Celcius
  float distance = 0.0343 * time;
  if (distance >= 4 && distance <= 400)
  {
    Serial.print("The distance is ");
    Serial.print(distance);
    Serial.print("\n");
  }
}