#define trigPin 25
#define echoPinFront 31
#define echoPinBack 29
#define echoPinLeft 27
#define echoPinRight 33

int motor_left[] = {4, 5};
int motor_right[] = {2, 3};                                                                                                                   //store serial input 

long durationFront, distanceFront, distanceBack, durationBack;
long durationLeft, distanceLeft, distanceRight, durationRight;

int mstop, mforward, mbackward, mleft, mright;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  mstop, mforward, mbackward, mleft, mright = 0;

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               
    pinMode(motor_right[i], OUTPUT);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinBack, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);
}

void loop() {
  /*if (Serial1.available()) {
    byteRead = Serial1.read();
    Serial.println(byteRead);

    if (byteRead==70) {
    }
  }*/
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    durationFront = pulseIn(echoPinFront, HIGH);
    distanceFront = (durationFront/2) / 29.1;
    Serial.print(distanceFront);
    Serial.println(" cm FRONT");
    
    if (distanceFront > 15) {                             
      Serial.println("drive_forward");
    } else {
      Serial.println("motor_stop");
      motor_stop();
    }

    delay(200);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    durationBack = pulseIn(echoPinBack, HIGH);
    distanceBack = (durationBack/2) / 29.1;
    Serial.print(distanceBack);
    Serial.println(" cm BACK");    

    delay(200);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durationLeft = pulseIn(echoPinLeft, HIGH);
    distanceLeft = (durationLeft/2) / 29.1;
    Serial.print(distanceLeft);
    Serial.println(" cm LEFT");

    if (mstop == 1) {
      if (distanceLeft > 15) {
        Serial.println("drive_left");
        //drive_left();                             //drive LEFT when there is room on the left side 
        //delay(1100);                              //keep turning for 1.1s, can change based on the angle that we want
        //drive_forward();                          //drive forward on this route
      } 
      else if (distanceRight > 15) {
        Serial.println("drive_right");
        //drive_right();                            //drive RIGHT when there is room on the right side
        //delay(1100);                              //keep turning for 1.1s, can change based on the angle that we want
        //drive_forward();                          //drive forward on this route
      }
      else {
        Serial.println("drive_backward");
        //drive_backward();                         //when there is no room on either side we drive backward
        //delay(1500);                              //keep driving backward for 1.5s, can change as we wish
        //drive_left();                             //when finished driving backward we have to turn 90 degrees
        //delay(1100);                              //keep turning for 1.1s, can change based on the angle that we want
      }
    }

    delay(200);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durationRight = pulseIn(echoPinRight, HIGH);
    distanceRight = (durationRight/2) / 29.1;
    Serial.print(distanceRight);
    Serial.println(" cm RIGHT");
    Serial.println("");
    
    

    delay(500);
}
                                                                                   
void motor_stop() {
  mstop = 1;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 0);
  delay(25);
  
}

void drive_backward() {
  mbackward = 1;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
}

void drive_forward() {
  mforward = 1;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}

void drive_left() {
  mleft = 1;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
}

void drive_right() {
  mright = 1;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}
