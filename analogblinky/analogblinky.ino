void setup() {
  // put your setup code here, to run once:
pinMode(LED_BUILTIN,OUTPUT);
}

int x = 0;

void loop() {

  analogWrite(12,x);
  delay(5);
  x++;
  if (x > 254)
    {
      x = 0;
    }
}
