int motor_left[] = {4, 5};
int motor_right[] = {2, 3};
int i;                                                                            //store motor left, right pins
int leftF, leftB, rightF, rightB;                                                 //variables for different motor states

byte byteRead;                                                                    //store serial input 

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  //start serial monitor

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               //set pins as outputpins
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop() {
       

  if (Serial1.available()) {                                                     //check if serial is on
    byteRead = Serial1.read(); 
    Serial.println(byteRead);                 //read serial input  
    
    if (byteRead==70) {                                                           //if button 8 is pressed
      Serial.println(byteRead);                                                   //print input
      /*delay(2000);                                                                //wait for 2 seconds for other inputs
      byteRead = Serial.read();                                                   //read second serial input
      Serial.println(byteRead);                                                   //print second serial input
      switch (byteRead) {                                                         //switchcase to determine the speed of the motors
        case 167: leftF = 255; rightF = 255; leftB = 0; rightB = 0; Serial.println("F10");  //highest speed, button & pressed
        break;
        case 40: leftF = 235; rightF = 235; leftB = 0; rightB = 0; Serial.println("F9");
        break;
        case 39: leftF = 215; rightF = 215; leftB = 0; rightB = 0; Serial.println("F8");
        break;
        case 34: leftF = 195; rightF = 195; leftB = 0; rightB = 0; Serial.println("F7");
        break;
        case 233: leftF = 175; rightF = 175; leftB = 0; rightB = 0; Serial.println("F6");
        break;
        case 38: leftF = 155; rightF = 155; leftB = 0; rightB = 0; Serial.println("F5");    //lowest speed we chose, button & pressed
        break;
        default: leftF = 195; rightF = 195; leftB = 0; rightB = 0; Serial.println("FDefault"); //default speed if nothing is pressed after the first input
        break;
      }*/
      drive_forward();                                                            //call method with given parameters in serial monitor
      Serial.println("Forwards");                                                 //print used method
           
    }
    if (byteRead==66) {                                                           //if button 2 is pressed
      Serial.println(byteRead);
      /*delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: leftB = 255; rightB = 255; leftF = 0; rightF = 0; Serial.println("F10");
        break;
        case 40: leftB = 232; rightB = 235; leftF = 0; rightF = 0; Serial.println("F9");
        break;
        case 39: leftB = 215; rightB = 215; leftF = 0; rightF = 0; Serial.println("F8");
        break;
        case 34: leftB = 195; rightB = 195; leftF = 0; rightF = 0; Serial.println("F7");
        break;
        case 233: leftB = 175; rightB = 175; leftF = 0; rightF = 0; Serial.println("F6");
        break;
        case 38: leftB = 155; rightB = 155; leftF = 0; rightF = 0; Serial.println("F5");
        break;
        default: leftB = 195; rightB = 195; leftF = 0; rightF = 0; Serial.println("FDefault");
        break;
      }*/
      drive_backward();
      Serial.println("Backwards");
      
    }
    if (byteRead==83) {                                                           //if button 5 is pressed
       motor_stop();
       Serial.println("Stop");
    }
    if (byteRead==76) {                                                           //if button 4 is pressed
      Serial.println(byteRead);
      /*delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: rightF = 255; leftB = 255; leftF = 0; rightB = 0; Serial.println("F10");
        break;
        case 40: rightF = 235; leftB = 235; leftF = 0; rightB = 0; Serial.println("F9");
        break;
        case 39: rightF = 215; leftB = 215; leftF = 0; rightB = 0; Serial.println("F8");
        break;
        case 34: rightF = 195; leftB = 195; leftF = 0; rightB = 0; Serial.println("F7");
        break;
        case 233: rightF = 175; leftB = 175; leftF = 0; rightB = 0; Serial.println("F6");
        break;
        case 38: rightF = 155; leftB = 155; leftF = 0; rightB = 0; Serial.println("F5");
        break;
        default: rightF = 195; leftB = 195; leftF = 0; rightB = 0; Serial.println("FDefault");
        break;
      }*/
      drive_left();
      Serial.println("Left");
    }
    if (byteRead==82) {                                                            //if button 6 is pressed
      Serial.println(byteRead);
      /*delay(2000);
      byteRead = Serial.read();
      Serial.println(byteRead);
      switch (byteRead) {
        case 167: leftF = 255; rightB = 255; leftB = 0; rightF = 0; Serial.println("F10");
        break;
        case 40: leftF = 235; rightB = 235; leftB = 0; rightF = 0; Serial.println("F9");
        break;
        case 39: leftF = 215; rightB = 215; leftB = 0; rightF = 0; Serial.println("F8");
        break;
        case 34: leftF = 195; rightB = 195; leftB = 0; rightF = 0; Serial.println("F7");
        break;
        case 233: leftF = 175; rightB = 175; leftB = 0; rightF = 0; Serial.println("F6");
        break;
        case 38: leftF = 155; rightB = 155; leftB = 0; rightF = 0; Serial.println("F5");
        break;
        default: leftF = 195; rightB = 195; leftB = 0; rightF = 0; Serial.println("FDefault");
        break;
      }*/
      drive_right();
      Serial.println("Right");
    }
  }  
}
                                                                                    //functions
void motor_stop() {
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], 0);
  delay(25);
}

void drive_forward() {
    analogWrite(motor_left[0], 200);
    analogWrite(motor_left[1], 0);

    analogWrite(motor_right[0], 200);
    analogWrite(motor_right[1], 0);
}

void drive_backward() {
    analogWrite(motor_left[0], 0);
    analogWrite(motor_left[1], 200);

    analogWrite(motor_right[0], 0);
    analogWrite(motor_right[1], 200);
}

void drive_left() {
    analogWrite(motor_left[0], 0);
    analogWrite(motor_left[1], 200);

    analogWrite(motor_right[0], 200);
    analogWrite(motor_right[1], 0);
}

void drive_right() {
    analogWrite(motor_left[0], 200);
    analogWrite(motor_left[1], 0);

    analogWrite(motor_right[0], 0);
    analogWrite(motor_right[1], 200);
}
