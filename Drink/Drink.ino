int ledG = 9;
int ledR = 10;
int button1 = 8;
int button2 = 12;
int motor = 2; //both pump and solenoid valve
int temp = A0;
int photo = A1;

int thresh = analogRead(photo); //global threshhold reading for photoresistor
int button1State = 0;
int button2State = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initilize pins as inputs and outputs
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(motor, OUTPUT);
  digitalWrite(motor,LOW);
  pinMode(temp, INPUT);
  pinMode(photo, INPUT);
  Serial.begin(9600);//initilize serial monitor
 int button1State = digitalRead(button1);
int button2State = digitalRead(button2);
}

// the loop function runs over and over again forever
void loop() {
  start(); //checks buttons and operates pump/solenoid valve
  sensor(); // checks sensors for temperature, photoresistor 
  }
  


void start(){
  //makes sure everything is ready to operate
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
 int thresh = analogRead(photo);
 digitalWrite(ledG, HIGH);
 digitalWrite(ledR, LOW);
 digitalWrite(motor,LOW);
 Serial.println("READY TO SERVE");
  
   if(button1State == HIGH){  // buttoon 1 is a momentary button that only operates the pump aslong as the button is held
  digitalWrite(ledG, LOW);
  digitalWrite(ledR,HIGH);
  digitalWrite(motor,HIGH);
  delay(10);
 }
 if(button2State == HIGH)  // button for automated pouring
{
  while(thresh < 200){ //runs pump while there is a beam connection between laser pointer and photoresistor
    digitalWrite(ledR,HIGH);
    digitalWrite(ledG,LOW);
    digitalWrite(motor,HIGH);
    thresh = analogRead(photo);
    stopbutton(); // press anybutton to stop the motor while automation is running
    if(button1State == HIGH){
      digitalWrite(motor,LOW);
    }
    if (button2State == HIGH){
      digitalWrite(motor,LOW);
    }
  }
 }
}
 
 
 void sensor(){ // ready sensor values to serial monitor
  int thresh = analogRead(photo);
  int reading = analogRead(temp);
  float voltage = reading * 5.0;
   voltage /= 1024.0; 
 float temperatureC = (voltage - 0.5) * 100 ;  
 Serial.print(temperatureC); 
 Serial.println(" degrees C");
 Serial.println(thresh);
 delay(100);
 }

int automatic(){
  int thresh = analogRead(photo);
  if (thresh > 500){
  digitalWrite(ledG, HIGH);
  digitalWrite(ledR,LOW);
  digitalWrite(motor,LOW);
  }
  return thresh;
} 

void stopbutton() // stops operation while automation is running
{
int button1State = digitalRead(button1);
int button2State = digitalRead(button2);
if (button1State == HIGH){
  digitalWrite(motor,LOW);
}
if (button2State == HIGH){
  digitalWrite(motor,LOW);
}
}
