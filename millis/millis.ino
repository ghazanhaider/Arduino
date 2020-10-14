unsigned long timeone, intervalone, cpucounter, ticker;
bool outputone;

void setup() {
intervalone=2;
timeone=millis();
pinMode(LED_BUILTIN,OUTPUT);
outputone = LOW;
cpucounter=ticker=0;
Serial.begin(115200);
}



void loop() {

cpucounter++;

// TASK1
if (millis() > (timeone + intervalone))
  {
    timeone += intervalone;
    outputone = !outputone;
    digitalWrite(LED_BUILTIN,outputone);
    Serial.print("Timeout:");Serial.print(timeone);Serial.print("\tIdle:");Serial.println(cpucounter - ticker);
    ticker = cpucounter;
  }

}
