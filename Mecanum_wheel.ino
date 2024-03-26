#include <SoftwareSerial.h>
#include <AccelStepper.h>

SoftwareSerial Bluetooth(A7, 38);

AccelStepper LeftBackWheel(1, 42, 43);
AccelStepper LeftFrontWheel(1, 40, 41);
AccelStepper RightBackWheel(1, 44, 45);
AccelStepper RightFrontWheel(1, 46, 47);

#define led 14

int wheelSpeed = 1500;

int dataIn, m;

int lbw[50], lfw[50], rbw[50], rfw[50];
int index = 0;

void setup() {
  LeftFrontWheel.setMaxSpeed(3000);
  LeftBackWheel.setMaxSpeed(3000);
  RightFrontWheel.setMaxSpeed(3000);
  RightBackWheel.setMaxSpeed(3000);

  Serial.begin(38400);
  Bluetooth.begin(38400);
  Bluetooth.setTimeout(1);
  delay(20);

  pinMode(led, OUTPUT);

}

void loop() {

  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.read();

    if (dataIn == 0) {
      m = 0;
    }
    if (dataIn == 1) {
      m = 1;
    }
    if (dataIn == 2) {
      m = 2;
    }
    if (dataIn == 3) {
      m = 3;
    }
    if (dataIn == 4) {
      m = 4;
    }
    if (dataIn == 5) {
      m = 5;
    }
    if (dataIn == 6) {
      m = 6;
    }
    if (dataIn == 7) {
      m = 7;
    }
    if (dataIn == 8) {
      m = 8;

    }
    if (dataIn == 9) {
      m = 9;
    }
    if (dataIn == 10) {
      m = 10;
    }
    if (dataIn == 11) {
      m = 11;
    }

    if (dataIn == 12) {
      m = 12;
    }
    if (dataIn == 14) {
      m = 14;
    }
    
    if (dataIn >= 16) {
      wheelSpeed = dataIn * 10;
      Serial.println(wheelSpeed);
    }
  }
  if (m == 4) {
    moveSidewaysLeft();
  }
  if (m == 5) {
    moveSidewaysRight();
  }
  if (m == 2) {
    moveForward();
  }
  if (m == 7) {
    moveBackward();
  }
  if (m == 3) {
    moveRightForward();
  }
  if (m == 1) {
    moveLeftForward();
  }
  if (m == 8) {
    moveRightBackward();
  }
  if (m == 6) {
    moveLeftBackward();
  }
  if (m == 9) {
    rotateLeft();
  }
  if (m == 10) {
    rotateRight();
  }

  if (m == 0) {
    stopMoving();
  }
  
  if (m == 12) {
    if (index == 0) {
      LeftBackWheel.setCurrentPosition(0);
      LeftFrontWheel.setCurrentPosition(0);
      RightBackWheel.setCurrentPosition(0);
      RightFrontWheel.setCurrentPosition(0);
    }
    lbw[index] = LeftBackWheel.currentPosition();
    lfw[index] = LeftFrontWheel.currentPosition();
    rbw[index] = RightBackWheel.currentPosition();
    rfw[index] = RightFrontWheel.currentPosition();
    index++;
    m = 0;
  }

  if (m == 14) {
    runSteps();
    if (dataIn != 14) {
      stopMoving();
      memset(lbw, 0, sizeof(lbw));
      memset(lfw, 0, sizeof(lfw));
      memset(rbw, 0, sizeof(rbw));
      memset(rfw, 0, sizeof(rfw));
      index = 0;
    }
  }

  LeftFrontWheel.runSpeed();
  LeftBackWheel.runSpeed();
  RightFrontWheel.runSpeed();
  RightBackWheel.runSpeed();

  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.00) * 3;

  if (voltage < 11) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }

}

void runSteps() {
  for (int i = index - 1; i >= 0; i--) {
    LeftFrontWheel.moveTo(lfw[i]);
    LeftFrontWheel.setSpeed(wheelSpeed);
    LeftBackWheel.moveTo(lbw[i]);
    LeftBackWheel.setSpeed(wheelSpeed);
    RightFrontWheel.moveTo(rfw[i]);
    RightFrontWheel.setSpeed(wheelSpeed);
    RightBackWheel.moveTo(rbw[i]);
    RightBackWheel.setSpeed(wheelSpeed);

    while (LeftBackWheel.currentPosition() != lbw[i] & LeftFrontWheel.currentPosition() != lfw[i] & RightFrontWheel.currentPosition() != rfw[i] & RightBackWheel.currentPosition() != rbw[i]) {
      LeftFrontWheel.runSpeedToPosition();
      LeftBackWheel.runSpeedToPosition();
      RightFrontWheel.runSpeedToPosition();
      RightBackWheel.runSpeedToPosition();

      if (Bluetooth.available() > 0) {
        dataIn = Bluetooth.read();
        if ( dataIn == 15) {
          while (dataIn != 14) {
            if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.read();
              if ( dataIn == 13) {
                stopMoving();
                break;
              }
            }
          }
        }
        if (dataIn >= 16) {
          wheelSpeed = dataIn * 10;
          dataIn = 14;
        }
        if ( dataIn == 13) {
          break;
        }
      }
    }
  }
  
  for (int i = 1; i <= index - 1; i++) {

    LeftFrontWheel.moveTo(lfw[i]);
    LeftFrontWheel.setSpeed(wheelSpeed);
    LeftBackWheel.moveTo(lbw[i]);
    LeftBackWheel.setSpeed(wheelSpeed);
    RightFrontWheel.moveTo(rfw[i]);
    RightFrontWheel.setSpeed(wheelSpeed);
    RightBackWheel.moveTo(rbw[i]);
    RightBackWheel.setSpeed(wheelSpeed);

    while (LeftBackWheel.currentPosition() != lbw[i]& LeftFrontWheel.currentPosition() != lfw[i] & RightFrontWheel.currentPosition() != rfw[i] & RightBackWheel.currentPosition() != rbw[i]) {

      LeftFrontWheel.runSpeedToPosition();
      LeftBackWheel.runSpeedToPosition();
      RightFrontWheel.runSpeedToPosition();
      RightBackWheel.runSpeedToPosition();

      if (Bluetooth.available() > 0) {
        dataIn = Bluetooth.read();
        if ( dataIn == 15) {
          while (dataIn != 14) {
            if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.read();
              if ( dataIn == 13) {
                stopMoving();
                break;
              }
            }
          }
        }
        if (dataIn >= 16) {
          wheelSpeed = dataIn * 10;
          dataIn = 14;
        }
        if ( dataIn == 13) {
          break;
        }
      }
    }
  }
}

void moveForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveSidewaysRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveSidewaysLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void rotateLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void rotateRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveRightForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveRightBackward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftForward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}
