int sensorPin=A0;
int sensorValue=0;
int led=9;

void setup(){
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}


void loop(){
 sensorValue=analogRead(sensorPin);
 Serial.println(sensorValue);
  
  
if(sensorValue<100){
  Serial.println("LED light on");
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
}else{
  digitalWrite(led,LOW);
}
  delay(200);
}