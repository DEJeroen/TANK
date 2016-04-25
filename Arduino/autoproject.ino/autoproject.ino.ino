int motor_left[] = {4, 5};
int motor_right[] = {2, 3};
int i;                                                                            //store motor left, right pins
int leftF, leftB, rightF, rightB;                                                 //variables for different motor states

byte inbyte;      //store serial input 
String serialDataIn;
int data[2];
int counter;
String val;

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
      

  if (Serial.available()) {
        inbyte = Serial.read();

  
        
        if(inbyte >= '0' & inbyte <= '9')
            serialDataIn += inbyte - 48;
        if (inbyte == ',' || inbyte == 'r' ){  // Handle delimiter
            data[counter] = serialDataIn.toInt();
            serialDataIn = ("");
            counter = counter + 1;
        }
        if(inbyte ==  'r' || counter >= 2){  // end of line

          if (data[0] <= 255) {
            analogWrite(motor_left[0], data[0]);
          }
          else {
            analogWrite(motor_left[1], data[1] - 255);
            
          }

          if (data[1] <= 255) {
            analogWrite(motor_right[0], data[0]);
          }
          else {
            analogWrite(motor_right[1], data[1] - 255);
            
          }

            counter = 0;
            
          }

       

Serial.println(data[0]);
Serial.println(data[1]);
}
}

