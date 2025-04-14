float L1 = 68.25;
float L2 = 110;
float L3 = 214.44;
void IK(float x, float y, float z, float* theta1, float* theta2, float* theta3) {
  //calculate angles
  *theta1 = (atan(z/x))*180/pi+90;
  float rx = sqrt(x*x+z*z)-L1;
  float fi2 = atan(y/rx); 
  float r = sqrt(y*y+rx*rx); 
  float fi1 = -acos((L2*L2+r*r-L3*L3)/(2*L2*r));
  *theta2 = (fi2-fi1)*180/pi;
  float fi3 = acos((-L2*L2-L3*L3+r*r)/(-2*L2*L3));
  *theta3 = (pi-fi3)*180/pi;
}