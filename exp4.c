const int poten=A3;
int var;

void setup(){
  pinMode(6,OUTPUT);
}

void loop(){
  var =analogRead(poten);
int pwmValue = map(var,0,1023,0,255);
  analogWrite(6,pwmValue);
}