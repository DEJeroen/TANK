#define trigPin 25
#define echoPinFront1 31
#define echoPinFront2 29
#define echoPinLeft 27
#define echoPinRight 33

int motor_left[] = {4, 5};
int motor_right[] = {2, 3};                                                                                                                   //store serial input 

long durationFront1, distanceFront1, distanceFront2, durationFront2;
long durationLeft, distanceLeft, distanceRight, durationRight;

bool mstop, mforward, mbackward, mleft, mright;

void setup() {
  Serial.begin(9600);
  //Serial1.begin(9600);

  mstop, mforward, mbackward, mleft, mright = false;

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               
    pinMode(motor_right[i], OUTPUT);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront1, INPUT);
  pinMode(echoPinFront2, INPUT);
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
  
    durationFront1 = pulseIn(echoPinFront1, HIGH);
    distanceFront1 = (durationFront1 / 2) / 29.1;
    Serial.print(distanceFront1);
    Serial.println(" cm FRONT1");

    delay(120);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    durationFront2 = pulseIn(echoPinFront2, HIGH);
    distanceFront2 = (durationFront2 / 2) / 29.1;
    Serial.print(distanceFront2);
    Serial.println(" cm FRONT2");
    
    delay(120);

    if (distanceFront1 > 15 && distanceFront2 > 15) {                             
      Serial.println("drive_forward");                          //if no object in front of neither front sensor, drive forward
      drive_forward();
    }
    else if (distanceFront1 <= 15 && distanceFront2 > 15) {
      Serial.println("drive_left");                             //if an object is in front of the right sensor, drive left
      drive_left();
    }
    else if (distanceFront2 <= 15 && distanceFront1 > 15) {
      Serial.println("drive_right");                            //if an object is in front of the left sensor, drive right
      drive_right();
    }
    else if (distanceFront1 <= 15 && distanceFront2 <= 15) {
      Serial.println("motor_stop");
      motor_stop();
    }
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durationLeft = pulseIn(echoPinLeft, HIGH);
    distanceLeft = (durationLeft / 2) / 29.1;
    Serial.print(distanceLeft);
    Serial.println(" cm LEFT");
    
    delay(120);
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durationRight = pulseIn(echoPinRight, HIGH);
    distanceRight = (durationRight / 2) / 29.1;
    Serial.print(distanceRight);
    Serial.println(" cm RIGHT");

    delay(120);

    if (mforward == true) {
      if (distanceLeft <= 7) {
        Serial.println("drive_right");
        drive_right_short();
      }
      else if (distanceRight <= 7) {
        Serial.println("drive_left");
        drive_left_short();
      }
    }
    
    if (mstop == true) {
      if (distanceLeft >= 9) {
        Serial.println("drive_left");
        drive_left();                
      } 
      else if (distanceRight >=9 ) {
        Serial.println("drive_right");
        drive_right();               
      }
      else {
        Serial.println("drive_backward");
        drive_backward();
        Serial.println("drive_left");
        drive_left();        
      }
    }    
    Serial.println("");
    delay(50);
}
                                                                                   
void motor_stop() {
  mstop = true;
  mforward = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 0);
  delay(25);
  
}

void drive_backward() {
  mbackward = true;
  mstop = false;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
  delay(500);
}

void drive_forward() {
  mforward = true;
  mstop = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
}

void drive_left() {
  mleft = true;
  mstop = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
  delay(500);
}

void drive_left_short() {
  mleft = true;
  mstop = false;
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 200);

  analogWrite(motor_right[0], 200);
  analogWrite(motor_right[1], 0);
  delay(200);
}

void drive_right() {
  mright = true;
  mstop = false;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
  delay(500);
}

void drive_right_short() {
  mright = true;
  mstop = false;
  analogWrite(motor_left[0], 200);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 200);
  delay(200);
}
