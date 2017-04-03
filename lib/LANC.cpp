/*
   Send a Start/Sop Recording command to the LANC port of a video camera.
   Tested with a Canon XF300 camcorder
   This code requires a simple interface see http://micro.arocholl.com
   Feel free to use this code in any way you want.

   Comprehensive LANC info: www.boehmel.de/lanc.htm

   "LANC" is a registered trademark of SONY.
   CANON calls their LANC compatible port "REMOTE".

   2011, Martin Koch
http://controlyourcamera.blogspot.com/2011/02/arduino-controlled-video-recording-over.html
 */

//Write the 8 bits of byte 0
//"28hex" or “00101000”  tells the camera that there will be a sepcial command to camera in the next byte
//Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
#define SPECIAL_COMMAND() \
  digitalWrite(output_pin_, LOW); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, LOW); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, LOW); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, HIGH); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, LOW); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, HIGH); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, LOW); \
  delayMicroseconds(bit_duration_); \
  digitalWrite(output_pin_, LOW); \
  delayMicroseconds(bit_duration_);

#include <Arduino.h>

int output_pin_;
int input_pin_;

int cmd_repeat_count_;
int bit_duration_ = 104; //Duration of one LANC bit in microseconds. 


void lanc_setup(int output_pin, int input_pin) {
  output_pin_ = output_pin;
  input_pin_ = input_pin;

  pinMode(input_pin_, INPUT); //listens to the LANC line
  pinMode(output_pin_, OUTPUT); //writes to the LANC line
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(output_pin_, LOW); //set LANC line to +5V
  digitalWrite(LED_BUILTIN, LOW);

  // delay(5000); //Wait for camera to power up completly
  bit_duration_ = bit_duration_ - 8; //Writing to the digital port takes about 8 microseconds so only 96 microseconds are left till the end of each bit
}


void lanc_rec() {

  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of byte 0 
    //"18hex" or “00011000”  tells the camera that there will be a normal command to camera in the next byte
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, LOW);  //Write bit 0. 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 1 
    delayMicroseconds(bit_duration_);  
    digitalWrite(output_pin_, LOW);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 3
    delayMicroseconds(bit_duration_);  
    digitalWrite(output_pin_, HIGH);  //Write bit 4
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 5 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 6
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"33hex" or “00110011” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}

void lanc_focus_auto() {

  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    SPECIAL_COMMAND();
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"43hex" or “01000011” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}

void lanc_focus_far() {

  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    SPECIAL_COMMAND();
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"45hex" or “01000101” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}

void lanc_focus_near() {


  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    SPECIAL_COMMAND();
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"47hex" or “01000111” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}


void lanc_iris_inc() {


  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    SPECIAL_COMMAND();
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"53hex" or “01010011” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}

void lanc_iris_dec() {


  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    SPECIAL_COMMAND();
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"55hex" or “01010101” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, LOW);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}

void lanc_iris_auto() {


  cmd_repeat_count_ = 0;

  while (cmd_repeat_count_ < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(input_pin_, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    SPECIAL_COMMAND();
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(input_pin_)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bit_duration_);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"AFhex" or “10101111” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(output_pin_, HIGH);  //Write bit 0 
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 1 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 2
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 3
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 4 
    delayMicroseconds(bit_duration_); 
    digitalWrite(output_pin_, HIGH);  //Write bit 5
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, LOW);  //Write bit 6
    delayMicroseconds(bit_duration_);
    digitalWrite(output_pin_, HIGH);  //Write bit 7
    delayMicroseconds(bit_duration_);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(output_pin_, LOW); 

    cmd_repeat_count_++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmd_repeat_count_ < 5
}
