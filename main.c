int pinStep = 2;
int pinEnable = 6;
int pinDirection = 4;
int waitNs = 0;
bool isMotorEnabled = false;
int speedStart = 1000;
int speedLow = 500;
int speedTarget = 0;


void setup() {
  initApp();
  startupApp();
}

void loop() {
  while (Serial.available() > 0){
    mainSwitchCase(Serial.read());
  }
  if (isMotorEnabled){
    DoMotor();
    DoWait();
  }
}

void mainSwitchCase(int input)
{
  switch (input)
  {
    case 'q':     
      speedTarget -= 100;
      Serial.print("Speed: ");
      Serial.println(speedTarget, DEC);
    break;
    case 'e':     
      speedTarget += 100;
      Serial.print("Speed: ");
      Serial.println(speedTarget, DEC);
    break;
    case 'a':
      enableMotor();
      isMotorEnabled = true;
      speedTarget = speedLow;
      Serial.println("Motor: ON");
    break;
    
    case 'd':
      disableMotor();
      isMotorEnabled = false;
      Serial.println("Motor: OFF");
    break;
    
    case 'w':
      digitalWrite(pinDirection, HIGH);
      Serial.println("Direction: right");
    break;
    case 's':
      digitalWrite(pinDirection, LOW);
      Serial.println("Direction: left");
    break;
    default: break;
  }
}

void DoMotor()
{
  int val = 0;
  val = digitalRead(pinStep);
  if (val == LOW) digitalWrite(pinStep, HIGH);
  else digitalWrite(pinStep, LOW);
}

void DoWait()
{
  if (waitNs > speedTarget){
    waitNs -= 1;
  }
  else if (waitNs < speedTarget){
    waitNs += 1;
  }
  delayMicroseconds(waitNs);
}

void disableMotor(){
  digitalWrite(pinEnable, HIGH);
}
void enableMotor(){
  digitalWrite(pinEnable, LOW);
  waitNs = speedStart;
}
void initApp(){
  pinMode(pinStep, OUTPUT);
  pinMode(pinEnable, OUTPUT);
  pinMode(pinDirection, OUTPUT);
  
  Serial.begin(9600);
}
void startupApp(){
  disableMotor();
  Serial.println("Start Program");
}
