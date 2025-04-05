void leg_cycle(int leg, float cycle_offset, int ground_points, float ground_distance, float radial_distance, float y_scale, float z_scale, int i, int walkAngle) {
  //int k = static_cast<int>(i + cycle_offset)%points; 
  int k = static_cast<int>(i + cycle_offset)%points;
  float x,y,z;
  switch(ground_points){
    case (50): {
      x = radial_distance;
      y = y_scale*leg_path_Y50[k]-y_zero_offset - ground_distance;
      z = z_scale*leg_path_Z50[k]; break;
    }
    case (60): {
      x = radial_distance;
      y = y_scale*leg_path_Y60[k]-y_zero_offset - ground_distance;
      z = z_scale*leg_path_Z60[k]; break;
    }
  }

  float angle;
   switch (leg) {
    case (1): {angle = 60+walkAngle; break;}
    case (2): {angle = 0+walkAngle; break;}
    case (3): {angle = -60+walkAngle; break;}
    case (4): {angle = 60-walkAngle; break;}
    case (5): {angle = 0-walkAngle; break;}
    case (6): {angle = -60-walkAngle; break;}
   }
  rotate_around_point(z, x, 0, radial_distance, angle, &rotated1, &rotated2); z=rotated1; x=rotated2;

  IK(x, y, z, &theta1, &theta2, &theta3);

  switch (leg) {
    case (1): {s1.write(theta1); s2.write(theta2); s3.write(theta3); break;}
    case (2): {s4.write(theta1); s5.write(theta2); s6.write(theta3); break;}
    case (3): {s7.write(theta1); s8.write(theta2); s9.write(theta3); break;}
    case (4): {s10.write(180-theta1); s11.write(180-theta2); s12.write(180-theta3); break;}
    case (5): {s13.write(180-theta1); s14.write(180-theta2); s15.write(180-theta3); break;}
    case (6): {s16.write(180-theta1); s17.write(180-theta2); s18.write(180-theta3); break;}
  }
}