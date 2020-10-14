#include <TimerOne.h>

bool output;
void setup() {
pinMode(LED_BUILTIN, OUTPUT);
Timer1.initialize(100000); 
Timer1.attachInterrupt(callback);
output=true;
}

void callback()
{
digitalWrite(LED_BUILTIN, output);
output = !output;
}

void loop() {

}
