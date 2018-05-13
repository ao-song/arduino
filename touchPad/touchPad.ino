#define LED 13
#define TOUCH_SENSOR 8
#define RELAY 2

#define TOUCH true
#define NOT_TOUCH false

boolean power_on = false;
boolean state = NOT_TOUCH;



void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(TOUCH_SENSOR, INPUT_PULLUP);
  pinMode(RELAY, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // as relay connected in NC mode, provide power all the time 
  digitalWrite(LED, HIGH);

  if (digitalRead(TOUCH_SENSOR) == HIGH) {   
    if (state == NOT_TOUCH) {
      state = TOUCH;
      if (power_on) {
        power_on = false;
      } else {
        power_on = true;
      }      
    }          
  } else {    
    if (state == TOUCH) {
      state = NOT_TOUCH;    
    }         
  }

  if (power_on) {
    digitalWrite(RELAY, HIGH);
  } else {
    digitalWrite(RELAY, LOW);
  }
}
