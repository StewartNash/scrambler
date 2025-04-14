#include <Servo.h>
#include <math.h>
#include <SoftwareSerial.h> // HC-12
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

// global variables
int gate; // [1, 2] = [tripod, ripple] 
float step_length; float step_height; 
int ground_distance; int radial_distance; // distance from the body to the tip of the leg
int walk_angle, speed;

int skip; // multiplies speed at the cost of reduced points in the leg path -> jittery movement
float speed_delay; // delay between points in the leg path

float Jx, Jy; int Jbtn; // reciever: Jx, Jy...joystick distance, Jbtn...joystick button

int ground_points; // number of points the leg is on the ground
int points = 100; // number of points of the whole path
int y_zero_offset = 40; // when y = 45 for all legs, the distance from the ground of the robot is ~zero

// movement paths
float leg_path_Z50[] = {-2.5,-7.6,-12.7,-17.8,-22.9,-28,-33.1,-38.2,-43.3,-48.4,-53.5,-58.6,-63.7,-68.8,-73.9,-79,-84.1,-89.2,-94.3,-99.4,-104.5,-109.6,-114.7,-119.8,-124.9,-130,-133.6,-135.8,-136.5,-135.8,-133.6,-130,-123,-115.9,-108.9,-101.9,-94.9,-87.8,-80.8,-73.8,-66.8,-59.7,-52.7,-45.7,-38.6,-31.6,-24.6,-17.6,-10.5,-3.5,3.5,10.5,17.6,24.6,31.6,38.6,45.7,52.7,59.7,66.8,73.8,80.8,87.8,94.9,101.9,108.9,115.9,123,130,133.6,135.8,136.5,135.8,133.6,130,124.9,119.8,114.7,109.6,104.5,99.4,94.3,89.2,84.1,79,73.9,68.8,63.7,58.6,53.5,48.4,43.3,38.2,33.1,28,22.9,17.8,12.7,7.6,2.5};
float leg_path_Y50[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.3,1.3,3,5.3,8.3,12,17.2,22,26.6,30.9,34.9,38.6,42.1,45.2,48.1,50.7,52.9,55,56.7,58.1,59.2,60.1,60.7,61,61,60.7,60.1,59.2,58.1,56.7,55,52.9,50.7,48.1,45.2,42.1,38.6,34.9,30.9,26.6,22,17.2,12,8.3,5.3,3,1.3,0.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float leg_path_Z60[] = {-2.1,-6.4,-10.7,-14.9,-19.2,-23.4,-27.7,-32,-36.2,-40.5,-44.8,-49,-53.3,-57.5,-61.8,-66.1,-70.3,-74.6,-78.9,-83.1,-87.4,-91.6,-95.9,-100.2,-104.4,-108.7,-113,-117.2,-121.5,-125.7,-130,-133.6,-135.8,-136.5,-135.8,-133.6,-130,-120.4,-110.7,-101.1,-91.5,-81.9,-72.2,-62.6,-53,-43.3,-33.7,-24.1,-14.4,-4.8,4.8,14.4,24.1,33.7,43.3,53,62.6,72.2,81.9,91.5,101.1,110.7,120.4,130,133.6,135.8,136.5,135.8,133.6,130,125.7,121.5,117.2,113,108.7,104.4,100.2,95.9,91.6,87.4,83.1,78.9,74.6,70.3,66.1,61.8,57.5,53.3,49,44.8,40.5,36.2,32,27.7,23.4,19.2,14.9,10.7,6.4,2.1};
float leg_path_Y60[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.3,1.3,3,5.3,8.3,12,19,25.4,31.4,36.7,41.6,45.9,49.6,52.9,55.6,57.7,59.3,60.4,60.9,60.9,60.4,59.3,57.7,55.6,52.9,49.6,45.9,41.6,36.7,31.4,25.4,19,12,8.3,5.3,3,1.3,0.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// IK
float pi = 3.14159;
float x, y, z, theta1, theta2, theta3;
// rotate_around_point
float rotated1, rotated2;
//low pass filter
float xn1_Jx = 0;
float xn1_Jy = 0;
float xn1_battery = 50;

float yn1_Jx = 0;
float yn1_Jy = 0;
float yn1_battery = 50;

int filter_counter_Jx = 0;
int filter_counter_Jy = 0;
int filter_counter_battery = 0;

// HC-12 
struct DataPacket { // values to be recieved
  int Jx;
  int Jy;
  int Jbtn;
};

// servos
Servo s1; Servo s2; Servo s3; //right front leg
Servo s4; Servo s5; Servo s6; //right middle leg
Servo s7; Servo s8; Servo s9; //right back leg
Servo s10; Servo s11; Servo s12; //left front leg
Servo s13; Servo s14; Servo s15; //left middle leg
Servo s16; Servo s17; Servo s18; //left back leg

void setup() {
Serial.begin(9600);
HC12.begin(9600); // Serial port to HC12

s1.attach(39); s2.attach(38); s3.attach(37); //right front leg #6
s4.attach(36); s5.attach(35); s6.attach(34); //right middle leg #5
s7.attach(33); s8.attach(32); s9.attach(31); //right back leg #4
s10.attach(22); s11.attach(23); s12.attach(24); //left front leg
s13.attach(25); s14.attach(26); s15.attach(27); //left middle leg
s16.attach(28); s17.attach(29); s18.attach(30); //left back leg 

//STAND UP
float Bx[] = {210,213.1,216,218.7,221.3,223.7,226,228,229.9,231.7,233.3,234.7,235.9,237,237.9,238.7,239.3,239.7,239.9,240};
float By[] = {50,59.5,67.1,72.6,76.1,77.7,77.3,74.8,70.4,64,55.5,45.1,32.7,18.3,1.9,-16.5,-36.9,-59.3,-83.6,-110};

for (int i = 0; i < 20-1; i++) {
x = Bx[i];
y = By[i];
z = 0;
IK(x, y, z, &theta1, &theta2, &theta3);
s1.write(theta1); s2.write(theta2); s3.write(theta3);
s4.write(theta1); s5.write(theta2); s6.write(theta3);
s7.write(theta1); s8.write(theta2); s9.write(theta3);
s10.write(180-theta1); s11.write(180-theta2); s12.write(180-theta3);
s13.write(180-theta1); s14.write(180-theta2); s15.write(180-theta3);
s16.write(180-theta1); s17.write(180-theta2); s18.write(180-theta3);
delay(60);
}
}

void loop() {
//walk settings
  gate = 1; //1-->tripod 2-->ripple
  ground_points = 50; //% of the time the leg is on the ground. Can be 50 or 60
  ground_distance = 90; //distance of robot from the ground
  radial_distance = 250; //distance from joint1 to the tip of the leg
  skip = 1;

for(int i = 0; i < points; i += skip){
  // HC-12
  if (HC12.available() >= sizeof(DataPacket)) { // Check if enough bytes are available
    DataPacket receivedData;                    // Variable to store received data packet
    HC12.readBytes((byte*)&receivedData, sizeof(receivedData)); // Read the data packet

    Jx = receivedData.Jx; Jy = receivedData.Jy; Jbtn = receivedData.Jbtn; // "unpack DataPacket" 
    Jx = (Jx - 512) / 512; // jx € <-1; 1>
    Jy = (Jy - 512) / 512; // jy € <-1; 1>

    //filter joystick x, y data
    float Jx_filtered = low_pass_filter(Jx, xn1_Jx, yn1_Jx, filter_counter_Jx, 0.5 , 0.01);
    float Jy_filtered = low_pass_filter(Jy, xn1_Jy, yn1_Jy, filter_counter_Jy, 0.5 , 0.01);

    //map to circle (trash joystick)
    float x_circle = Jx_filtered*sqrt(1 - Jy_filtered*Jy_filtered/2);
    float y_circle = Jy_filtered*sqrt(1 - Jx_filtered*Jx_filtered/2);

    //final joystick angle and distance
    float distance = sqrt(x_circle * x_circle + y_circle * y_circle);
    int angle = static_cast<int>(atan2(y_circle, x_circle)*180/pi); // €<-180; 180>
    speed = distance*100; // €<0; 100>

  //set walk settings
  speed_delay = (160 - 160*speed/100);
  if(speed < 3){
        step_length = 0.5*speed/100;
        step_height = 2*speed/100;
       } 
       else{
        step_length = 0.5;
        step_height = 2;
       }

  switch(gate){
    case(1): { 
      // tripod gate
      leg_cycle(1, 0, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(2, 50, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(3, 0, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(4, 50, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(5, 0, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(6, 50, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle); break;
    }
    case(2): {
      // ripple gate
      leg_cycle(1, 0, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(6, 17, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(2, 33, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(5, 50, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(3, 67, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle);
      leg_cycle(4, 83, ground_points, ground_distance, radial_distance, step_height, step_length, i, walk_angle); break;
    }
  }
  delay(speed_delay);
}

  //check battery %
  int battery_charge = get_battery_charge();
  int battery_charge_filtered = static_cast<int>(low_pass_filter(battery_charge, xn1_battery, yn1_battery, filter_counter_battery, 0.03, 2)); Serial.print(battery_charge); Serial.print(" "); Serial.println(battery_charge_filtered);
  if (battery_charge_filtered < 20){
    //turn off sequence
      /*float Bx[] = {210,213.1,216,218.7,221.3,223.7,226,228,229.9,231.7,233.3,234.7,235.9,237,237.9,238.7,239.3,239.7,239.9,240};
      float By[] = {50,59.5,67.1,72.6,76.1,77.7,77.3,74.8,70.4,64,55.5,45.1,32.7,18.3,1.9,-16.5,-36.9,-59.3,-83.6,-110};

      for (int i = 20; i >= 0; i--) {
      x = Bx[i];
      y = By[i];
      z = 0;
      IK(x, y, z, &theta1, &theta2, &theta3);
      s1.write(theta1); s2.write(theta2); s3.write(theta3);
      s4.write(theta1); s5.write(theta2); s6.write(theta3);
      s7.write(theta1); s8.write(theta2); s9.write(theta3);
      s10.write(180-theta1); s11.write(180-theta2); s12.write(180-theta3);
      s13.write(180-theta1); s14.write(180-theta2); s15.write(180-theta3);
      s16.write(180-theta1); s17.write(180-theta2); s18.write(180-theta3);
      delay(80);
      }
      delay(100000);*/
  }

}