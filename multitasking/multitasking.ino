unsigned long timeone, intervalone, timetwo, intervaltwo;
bool outputone,outputtwo;

void setup() {
  // put your setup code here, to run once:
intervalone=1000;
intervaltwo=700;
timeone=timetwo=millis();
pinMode(LED_BUILTIN,OUTPUT);
outputone = LOW;

Serial.begin(9600);
}



void loop() {

// TASK1
if (millis() > (timeone + intervalone))
  {
    timeone += intervalone;
    outputone = !outputone;
    digitalWrite(LED_BUILTIN,outputone);
    Serial.print("One:");Serial.println(timeone);
  }

// TASK2
if (millis() > (timetwo + intervaltwo))
  {
    timetwo += intervaltwo;
    outputtwo = !outputtwo;
    Serial.print("Two:");Serial.println(timetwo);
  }
  
//Serial.print("Output="); Serial.print(output);
}
