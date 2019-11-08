// #include <joystick.h>
#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/Float64.h>
// #include <Servo.h>
#include <VarSpeedServo.h>

// speed, 1 - 255 slower to faster
#define SPEED 60
               // Servo servo_1_1, servo_2_2, servo_3_1, servo_4_1, claw;
               VarSpeedServo servo_1_1,
    servo_2_2, servo_3_1, servo_4_1, claw;
float servo_position[5] = {0, 0, 0, 0, 0};
bool moving = false;

void attachServos(){
  servo_1_1.attach(3); 
  servo_2_2.attach(5); 
  servo_3_1.attach(6); 
  servo_4_1.attach(9);
  claw.attach(10);
}

void neutralPosition(){
  servo_1_1.write(90); 
  servo_2_2.write(100); 
  servo_3_1.write(10);
  servo_4_1.write(90);
  claw.write(45);
}

float radiansToDegrees(float& radian){
 return (radian/3.1415)*180; 
}

void callback1(const std_msgs::Float64 &msg){
  servo_position[0] = msg.data;
}

void callback2(const std_msgs::Float64 &msg){
  servo_position[1] = msg.data;
}

void callback3(const std_msgs::Float64 &msg){
  servo_position[2] = msg.data;
}

void callback4(const std_msgs::Float64 &msg){
  servo_position[3] = msg.data;
}
void callback5(const std_msgs::Float64 &msg){
  servo_position[4] = msg.data;
}

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Float64> sub1("servo_1_1_position", callback1);
ros::Subscriber<std_msgs::Float64> sub2("servo_2_2_position", callback2);
ros::Subscriber<std_msgs::Float64> sub3("servo_3_1_position", callback3);
ros::Subscriber<std_msgs::Float64> sub4("servo_4_1_position", callback4);
ros::Subscriber<std_msgs::Float64> sub5("claw_position", callback5);
//ros::Subscriber<std_msgs::Float64> sub5("arm_velocity", velocityCallback);


void subscribeToAll(){
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
}

void escrever(VarSpeedServo servo, float valor){
  if(valor<0)valor=0;
  if(valor>180)valor=180;
  servo.write(valor,SPEED,true);
}

    void moveArm()
{
  if (!moving)
  {
    for (int i = 0; i < 4; i++)
    {
      if (true)
      {
        escrever(servo_1_1, 30 + radiansToDegrees(servo_position[0]));
        delay(30);
        escrever(servo_2_2, 90 + 10.31 - radiansToDegrees(servo_position[1]));
        delay(40);
        escrever(servo_3_1, 90 - 17.18 + radiansToDegrees(servo_position[2]));
        delay(40);
        escrever(servo_4_1, 18.9 + radiansToDegrees(servo_position[3]));
        delay(40);
        escrever(claw,radiansToDegrees(servo_position[4]));
      }
    }
  }
}

void setup(){
  // rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200
  nh.getHardware()->setBaud(115200);  
  nh.initNode();
  subscribeToAll();
  attachServos();
  neutralPosition();

  Serial.print("Finished setting up \n");
  delay(1000);
}

void loop(){
  //chatter.publish(&str_msg);
  nh.spinOnce();
  delay(1);
  moveArm();
}


