#include "QueueList.h"
#include <Servo.h>
#include "JacobsLadder.h"

///////////////////////////
///   SETUP VARIABLES   ///
///////////////////////////

const int MODULE_ID = 0;
const int NUM_LADDERS = 5;
const int PINS[NUM_LADDERS] = {2,3,7,5,6};

const char CALIBRATE_START = 's';
const char CALIBRATE_REGISTERED = 'c';

///////////////////////////
///  GLOBAL VARIABLES   ///
///////////////////////////

JacobsLadder* ladders[NUM_LADDERS];

bool moduleCalibrated = false;

long lastUpdated;

// For serial communication
String inputString = ""; //Available input is appended each loop
boolean stringComplete = false; //Indicates the incoming command is complete and available and should be processed


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  lastUpdated = millis();

  for (int i = 0; i < NUM_LADDERS; i++) {
    JacobsLadder* ladder = new JacobsLadder;
    ladder->init(PINS[i], 500, 2500);
    ladders[i] = ladder;
    Serial.print("L");
    Serial.print(i);
    Serial.println(";");
  }
  
  Serial.println("R;");
}

void loop() {
  // TODO: calibrate the module if not calibrated yet
//  if (!moduleCalibrated) {
//    calibrate();
//    moduleCalibrated = true;
//  }


  // TODO: Read input from computer over serial
  if (Serial.available() > 0) {
    byte message[3];
    Serial.readBytesUntil(';', message, 3);
    byte index = message[0];
    MovementType type = (MovementType) message[1];
    byte velocity = message[2];
//    Serial.print(message[0]);
//    Serial.println(';');
    ladders[index]->addMovement(type, velocity);
  }

//  if (Serial.available() > 0) {
//    char c = Serial.read();
//    if (c == 'b') {
//      for (int i = 0; i < NUM_LADDERS; i++) {
//        ladders[i]->addMovement(Buzz, 150);
//      }
//    } else if (c == 'c') {
//      for (int i = 0; i < NUM_LADDERS; i++) {
//        ladders[i]->addMovement(Cascade, 150);
//      }
//    }
//  }
//
//  if (stringComplete) {
//    Serial.println("RECEIVED: " + inputString);
//    // clear the string:
//    inputString = "";
//    stringComplete = false;
//  }



//  if (millis() - lastUpdated > 2000) {
//    for (int i = 0; i < NUM_LADDERS; i++) {
//      ladders[i]->addMovement(Cascade, 150);
//    }
//    lastUpdated = millis();
//  }

  // Update the ladders
  for (int i = 0; i < NUM_LADDERS; i++) {
    JacobsLadder* ladder = ladders[i];
    ladder->updateLadder();
  }
}
//
//void serialEvent() {
//  while (Serial.available()) {
//    // get the new byte:
//    char inChar = (char)Serial.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag
//    // so the main loop can do something about it:
//    if (inChar == ';') {
//      stringComplete = true;
//    }
//  }
//}
//
//
//void calibrate() {
//  for (int i = 0; i < NUM_LADDERS; i++) {
//    JacobsLadder* ladder = ladders[i];
//    byte message[2] = {MODULE_ID, i};
//    Serial.write(message, 2);
//    bool startAllowed = false;
//    while (!startAllowed) {
//      if (Serial.available() > 0) {
//        if (Serial.read() == CALIBRATE_START) {
//          startAllowed = true;
//        }
//      }
//    }
//    bool didCalibrate = false;
//    long lastAdded = millis();
//    while (!didCalibrate) {
//      ladder->updateLadder();
//      if (millis() - lastAdded > 500) {
//        ladder->addMovement(Buzz, 150);
//        lastAdded = millis();
//      }
//      if (Serial.available() > 0) {
//        if (Serial.read() == CALIBRATE_REGISTERED) {
//          didCalibrate = true;
//        }
//      }
//    }
//  }
//}
