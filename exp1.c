int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int ledPin4 = 5;
int ledPin5 = 6;
int wait = 250;
void setup()
{
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  
}

void loop()
{
  digitalWrite(ledPin1, HIGH);
  delay(wait);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  delay(wait); 
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, HIGH);
  delay(wait);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, HIGH);
  delay(wait);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, HIGH);
  delay(wait);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin4, HIGH);
  delay(wait);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin3, HIGH);
  delay(wait);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin2, HIGH);
  delay(wait);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, HIGH);
  delay(wait);
   digitalWrite(ledPin2, LOW); 
}