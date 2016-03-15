int motor_left[] = {5, 6};
int motor_right[] = {10, 11};
int i;
int leftF, leftB, rightF, rightB; //variables for different motor states

byte byteRead; //store serial input 

void setup() {
  Serial.begin(9600);

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop() {
  
  /*2=50, 4=52, 5=53, 6=54, 8=56*/
       

  if (Serial.available()) {
    byteRead = Serial.read();   
    if (byteRead==56) {
      Serial.println(byteRead);
      delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: leftF, rightF = 255; leftB, rightB = 0; Serial.println("F10");
        break;
        case 40: leftF, rightF = 245; leftB, rightB = 0; Serial.println("F9");
        break;
        case 39: leftF, rightF = 235; leftB, rightB = 0; Serial.println("F8");
        break;
        case 34: leftF, rightF = 225; leftB, rightB = 0; Serial.println("F7");
        break;
        case 233: leftF, rightF = 215; leftB, rightB = 0; Serial.println("F6");
        break;
        case 38: leftF, rightF = 205; leftB, rightB = 0; Serial.println("F5");
        break;
        default: leftF, rightF = 225; leftB, rightB = 0; Serial.println("FDefault");
        break;
      }
      drive_forward();
      Serial.println("Forwards"); 
           
    }
    if (byteRead==50) {
      Serial.println(byteRead);
      delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: leftB, rightB = 255; leftF, rightF = 0; Serial.println("F10");
        break;
        case 40: leftB, rightB = 245; leftF, rightF = 0; Serial.println("F9");
        break;
        case 39: leftB, rightB = 235; leftF, rightF = 0; Serial.println("F8");
        break;
        case 34: leftB, rightB = 225; leftF, rightF = 0; Serial.println("F7");
        break;
        case 233: leftB, rightB = 215; leftF, rightF = 0; Serial.println("F6");
        break;
        case 38: leftB, rightB = 205; leftF, rightF = 0; Serial.println("F5");
        break;
        default: leftB, rightB = 225; leftF, rightF = 0; Serial.println("FDefault");
        break;
      }
      drive_backward();
      Serial.println("Backwards");
      
    }
    if (byteRead==53) {
       motor_stop();
       Serial.println("Stop");
    }
    if (byteRead==52) {
      Serial.println(byteRead);
      delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: rightF = 255; leftF, leftB, rightB = 0; Serial.println("F10");
        break;
        case 40: rightF = 245; leftF, leftB, rightB = 0; Serial.println("F9");
        break;
        case 39: rightF = 235; leftF, leftB, rightB = 0; Serial.println("F8");
        break;
        case 34: rightF = 225; leftF, leftB, rightB = 0; Serial.println("F7");
        break;
        case 233: rightF = 215; leftF, leftB, rightB = 0; Serial.println("F6");
        break;
        case 38: rightF = 205; leftF, leftB, rightB = 0; Serial.println("F5");
        break;
        default: rightF = 225; leftF, leftB, rightB = 0; Serial.println("FDefault");
        break;
      }
      drive_left();
      Serial.println("Left");
    }
    if (byteRead==54) {
      Serial.println(byteRead);
      delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: leftF = 255; rightF, leftB, rightB = 0; Serial.println("F10");
        break;
        case 40: leftF = 245; rightF, leftB, rightB = 0; Serial.println("F9");
        break;
        case 39: leftF = 235; rightF, leftB, rightB = 0; Serial.println("F8");
        break;
        case 34: leftF = 225; rightF, leftB, rightB = 0; Serial.println("F7");
        break;
        case 233: leftF = 215; rightF, leftB, rightB = 0; Serial.println("F6");
        break;
        case 38: leftF = 205; rightF, leftB, rightB = 0; Serial.println("F5");
        break;
        default: leftF = 225; rightF, leftB, rightB = 0; Serial.println("FDefault");
        break;
      }
      drive_right();
      Serial.println("Right");
    }
  }  
}

void motor_stop() {
  analogWrite(motor_left[0], leftF);
  analogWrite(motor_left[1], leftB);

  analogWrite(motor_right[0], rightF);
  analogWrite(motor_right[1], rightB);
  delay(25);
}

void drive_forward() {
    analogWrite(motor_left[0], leftF);
    analogWrite(motor_left[1], leftB);

    analogWrite(motor_right[0], rightF);
    analogWrite(motor_right[1], rightB);
}

void drive_backward() {
  analogWrite(motor_left[0], leftF);
  analogWrite(motor_left[1], leftB);

  analogWrite(motor_right[0], rightF);
  analogWrite(motor_right[1], rightB);
}

void drive_left() {
  analogWrite(motor_left[0], leftF);
  analogWrite(motor_left[1], leftB);

  analogWrite(motor_right[0], rightF);
  analogWrite(motor_right[1], rightB);
}

void drive_right() {
  analogWrite(motor_left[0], leftF);
  analogWrite(motor_left[1], leftB);

  analogWrite(motor_right[0], rightF);
  analogWrite(motor_right[1], rightB);
}

