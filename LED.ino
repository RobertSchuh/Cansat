void set_LED(byte red, byte green, byte blue) {
  analogWrite(R_PIN, red);
  analogWrite(G_PIN, green);
  analogWrite(B_PIN, blue);
}
