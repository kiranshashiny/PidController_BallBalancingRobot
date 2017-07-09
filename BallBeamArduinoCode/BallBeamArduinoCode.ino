
/* The code is available on the net on http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
Some modifications may be needed, like experimenting how the servo motor positions itself.
The accuracy of the Ultrasonic distance finder etc.
*/
#include<Servo.h>
#include<PID_v1.h>


const int servoPin = 8;                                               //Servo Pin
 
float Kp = 2.5;                                                    //Initial Proportional Gain
float Ki = 0;                                                      //Initial Integral Gain
float Kd = 1.1;                                                    //Intitial Derivative Gain
double Setpoint, Input, Output, ServoOutput;                                       


PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);           //Initialize PID object, which is in the class PID.
                                                                                                                                        
Servo myServo;                                                     
void setup() {

  Serial.begin(9600);                                                //Begin Serial 
  myServo.attach(servoPin);                                          //Attach Servo

  Input = readPosition();                                            //Calls function readPosition() and sets the balls
                                                                     //  position as the input to the PID algorithm
  myPID.SetMode(AUTOMATIC);                                          //Set PID object myPID to AUTOMATIC 
  myPID.SetOutputLimits(-80,80);                                     //Set Output limits to -80 and 80 degrees. 
}

void loop()
{ 
  Setpoint = 2;
  Input = readPosition();                                            
 
  myPID.Compute();                                                   //computes Output in range of -80 to 80 degrees
  
  ServoOutput=102+Output ; // 102 degrees is my horizontal 

  Serial.print("Setpoint = ");
  Serial.print (Setpoint);
  
  Serial.print("  Input = ");
  Serial.print (Input);

  Serial.print ( "  Output = " );
  Serial.print ( Output );

  Serial.print ( "  ServoOutput = ");
  Serial.println ( ServoOutput );
  myServo.write(ServoOutput);                                        //Writes value of Output to servo 
}
      

float readPosition() {
  delay(40);                                                            //Don't set too low or echos will run into eachother.       

  const int pingPin = 10;

  long duration, cm;
  unsigned long now = millis();
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);


  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = duration/(29*2);
  
  if(cm > 30)     // 30 cm is the maximum position for the ball
  {cm=30;}
  
  //  Serial.println(cm);
  
  return cm;                                          //Returns distance value.
}
