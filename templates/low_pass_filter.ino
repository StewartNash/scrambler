float low_pass_filter(float xn, float &xn1_prev, float &yn1_prev, int filterCounter, float fCutOff, float dT) {
  float omegaT = 6.28 * fCutOff * dT;
  float a = (2 - omegaT) / (2 + omegaT);
  float b = omegaT / (2 + omegaT);
  float yn = a * yn1_prev + b * xn + b * xn1_prev;
  xn1_prev = xn;
  yn1_prev = yn;
  filterCounter = filterCounter + 1;
  return yn;
}