float battery_lookup[] = {7.41, 7.45, 7.49, 7.53, 7.57, 7.59, 7.63, 7.67, 7.71, 7.75, 7.83, 7.91, 7.97, 8.05, 8.16, 8.22, 8.30, 8.40}; // ~<15, 100> %, 5% increments

// battery_charge [%]
int get_battery_charge() {
  float voltage = analogRead(A0) / 1023.0 * 5.0 * 3.0 * 1.01; //analogRead(1023) ~ 5V, voltageDivider -> *3
  //Serial.println("voltage: "); Serial.print(voltage);
  if (voltage < 7.40){
    return 0;
  }
  else if (voltage > 8.41) {
    return 100;
  }
  int battery_charge = 15;

  for (int i = 0; i < sizeof(battery_lookup) / sizeof(float); i++) {
    if (voltage > battery_lookup[i]) {
      battery_charge += 5;
    } else {
      break;
    }
  }
  
  return battery_charge;
}