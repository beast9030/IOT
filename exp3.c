const int led1 = 4; //green LED
const int led2 = 5;  //REd LED
const int echoPin = 2; 
const int trigPin = 3;
const int buzzerPin = 6; // Buzzer pin
const int nThreshold = 30;  //30 cm threshold
long nDuration;
int nDistance;


void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting ultrasonic detector...");
}
void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  nDuration = pulseIn(echoPin, HIGH);
  nDistance = nDuration * (0.034 / 2); // sound of speed 3.4 m/s
  Serial.print(nDistance);
  Serial.println(" cm");
  if(nDistance < nThreshold) {
    tone(buzzerPin, 2000);
    digitalWrite(led2, HIGH);
    delay(400);
    noTone(buzzerPin);
    delay(300);
    digitalWrite(led2, LOW);
  }
  else{
    digitalWrite(led1, HIGH);
    delay(400);
    digitalWrite(led1, LOW);
  }
}