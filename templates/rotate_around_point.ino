void rotate_around_point(float xToRot, float yToRot, float a, float b, float theta, float* rotated1, float* rotated2) {
  *rotated1 = (xToRot-a)*cos(theta*pi/180) -(yToRot-b)*sin(theta*pi/180)+a;
  *rotated2 = (xToRot-a)*sin(theta*pi/180) +(yToRot-b)*cos(theta*pi/180)+b;
}