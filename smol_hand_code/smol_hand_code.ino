#include <Servo.h>

// constants used
#define SENSOR A0   // reads EMG from pin A0
#define SERPIN 9    // uses pin 9 to send PWM signals to servo
#define COUNT 10    // number of counts used for moving average
#define THRESHOLD 150 // threshold of voltage reading from sensor
#define DEG 135       // degree rotation set to motor

Servo myservo;

// variables used
int rawin;
int changing = 0;

void setup() {
  // initialises sensor pin, servo and serial (for testing)
  pinMode(SENSOR, INPUT);
  myservo.attach(SERPIN);
  Serial.begin(9600);
  Serial.print(0);
  Serial.print(" ");
  Serial.print(100);  // To freeze the upper limit
  Serial.print(" ");
}

void loop() {
  
  // calculates the average of 10 readings with 10 ms intervals
  rawin = 0;
  for (int i=0; i<COUNT; i++) {
    rawin += analogRead(SENSOR);
    delay(10);
  }
  rawin = rawin / COUNT;

  Serial.println(rawin);

  // checks the state of the arm and moves it
  if (rawin >= THRESHOLD) {
    if (changing == 0) {
      swappos(myservo);
      changing = 1;
    }
  } else {
    changing = 0;
  }
  
  delay(10);
}

/** changes the state of the machine
 *  
*/
void swappos(Servo s) {
  if (s.read() == 0) {
    s.write(DEG);
  } else {
    s.write(0);
  }
}

