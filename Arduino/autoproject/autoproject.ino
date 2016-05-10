int motor_left[] = {4, 5};
int motor_right[] = {2, 3};
int i;                                                                            //store motor left, right pins
int leftF, leftB, rightF, rightB;                                                 //variables for different motor states

byte inbyte;      //store serial input 
String serialDataIn;
int data[2];
int driveSpeed[4];
int currentSpeed[4];
int speedChanged;
int counter;
String val;

void setup() {
  Serial.begin(9600);     //USB Serial
  Serial1.begin(9600);  //Connection with Megalania (Android app)
  Serial2.begin(9600);  //Connection with other car

  int i;
  for (i = 0; i < 2; i++) {
    pinMode(motor_left[i], OUTPUT);                                               //set pins as outputpins
    pinMode(motor_right[i], OUTPUT);
  }
}

void loop() {
      

  if (Serial1.available()) {
        inbyte = Serial1.read();

        //Reset (Here for when TANK is waiting for the input for the second motor)
 if(inbyte ==  'r'){
          counter = 0;
          }  
        if(inbyte >= '0' & inbyte <= '9')
            serialDataIn += inbyte - 48;
        if (inbyte == ','){  // Handle delimiter
            data[counter] = serialDataIn.toInt();
            counter = counter + 1;
            Serial.println(counter);
            serialDataIn = ("");
            
        }
        if(counter >= 2){  // end of line

          if (data[0] <= 255) {

            driveSpeed[0] = data[0];
            driveSpeed[1] = 0;
            Serial.println(data[0] + data[1] + "forwardLeft");
            
            


          }
          else {
            driveSpeed[0] = 0;
            driveSpeed[1] = data[0] - 255;
            Serial.println(data[0] + data[1] + "backwardsLeft");
            
            
          }

          if (data[1] <= 255) {
            driveSpeed[2] = data[1];
            driveSpeed[3] = 0;
            Serial.println(data[3] + data[4] + "forwardRight");

           
            
          }
          else {
            driveSpeed[2] = 0;
            driveSpeed[3] = data[1] - 255;
            Serial.println(data[2] + data[3] + "backwardsRight");
            
            
          }
          //Reset wich motor is waiting for data
          counter = 0;

          //Set motor to driveSpeed
          analogWrite(motor_left[0], driveSpeed[0]);
          analogWrite(motor_left[1], driveSpeed[1]); 
          analogWrite(motor_right[0], driveSpeed[2]);  
          analogWrite(motor_right[1], driveSpeed[3]);

          //Set Antwerp car to new speed

          if (driveSpeed[0] == 0 && driveSpeed[1] == 0  && driveSpeed[2] == 0 && driveSpeed[3]  )  {
    //stop the car
    Serial.println("stop");
    Serial2.write("0");
  }
  else if  (driveSpeed[0] > 200 && driveSpeed[2] == 200 )  {
    //drive car forward
    Serial.println("forward");
    Serial2.write("1");
  }

  else if  (driveSpeed[0] > 200 && driveSpeed[3] == 200)  {
    //turn left fast
     Serial2.write("3");
  }

  else if  (driveSpeed[1] > 200 && driveSpeed[2] == 200)  {
    //turn right fast
    Serial.println("fast right");
    Serial2.write("5");
  }
  else if  (driveSpeed[3] > 200 && driveSpeed[4] == 200 )  {
    //drive car backwards
    Serial.println("backwards");
    Serial2.write("6");
  }
          
          

       


        }
  }



 
}

 

