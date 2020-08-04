class Commands {

  private:

  public:

    // 3-AXIS CALIBRATION
    void beginCalbiration() {

      // Z-AXIS CALIBRATION
      if (axis == 'Z') {

        if (digitalRead(Z_LIM) == HIGH && Z_POS == false) {
          MPC.step(true, Z_DIR, Z_STP, stps);
          Serial.println("MOVING Z-AXIS UPWARD.");
        } else if (digitalRead(Z_LIM) == LOW && Z_POS == false) {
          Serial.println("Z_POS TOUCHED");
          Z_POS = true;
          Serial.println("MOTION ALONG Z-AXIS STOPPED.");
          Serial.println("Z-AXIS SUCCESSFULLY CALIBRATED.");
          delay(3000);
          axis = 'X';
        }

      }

      // X-AXIS CALIBRATION
      else if (axis == 'X') {

        if (digitalRead(X_LIM) == HIGH && X_POS == false) {
          MPC.step(true, X_DIR, X_STP, stps);
          Serial.println("MOVING X-AXIS TO THE RIGHT.");
        } else if (digitalRead(X_LIM) == LOW && X_POS == false) {
          Serial.println("X_POS TOUCHED");
          X_POS = true;
          if (X_POS == true) {
            MPC.step(false, X_DIR, X_STP, stps);    // GO BACK ONE STEP
          }
          delay(1000);
        } else if (digitalRead(X_LIM) == HIGH && X_NEG == false) {
          MPC.step(false, X_DIR, X_STP, stps);
          Serial.println("MOVING X-AXIS TO THE LEFT.");
        } else if (digitalRead(X_LIM) == LOW && X_NEG == false) {
          Serial.println("X_NEG TOUCHED");
          delay(1000);
          Serial.println("Now stopping motion along X-AXIS.");
          X_NEG = true;
          delay(1000);
        } else if (X_POS == true && X_NEG == true) {
          Serial.println("MOTION ALONG X-AXIS STOPPED.");
          Serial.println("X-AXIS SUCCESSFULLY CALIBRATED.");
          delay(3000);
          axis = 'Y';
        }

      }

      // Y-AXIS CALIBRATION
      else if (axis == 'Y') {

        if (digitalRead(Y_LIM) == HIGH && Y_POS == false) {
          MPC.step(true, Y_DIR, Y_STP, stps);
          Serial.println("MOVING Y-AXIS UPWARD.");
        } else if (digitalRead(Y_LIM) == LOW && Y_POS == false) {
          Serial.println("Y_POS TOUCHED");
          Y_POS = true;
          if (Y_POS == true) {
            MPC.step(false, Y_DIR, Y_STP, stps);    // GO BACK ONE STEP
          }
          delay(1000);
        } else if (digitalRead(Y_LIM) == HIGH && Y_NEG == false) {
          MPC.step(false, Y_DIR, Y_STP, stps);
          Serial.println("MOVING Y-AXIS DOWNWARD.");
        } else if (digitalRead(Y_LIM) == LOW && Y_NEG == false) {
          Serial.println("Y_NEG TOUCHED");
          delay(1000);
          Serial.println("Now stopping motion along Y-AXIS.");
          Y_NEG = true;
          delay(1000);
        } else if (Y_POS == true && Y_NEG == true) {
          Serial.println("MOTION ALONG Y-AXIS STOPPED.");
          Serial.println("Y-AXIS SUCCESSFULLY CALIBRATED.");
          delay(3000);

          // CALIBRATION FINISHED
          calibrate = 0;
          seed = 1;
          Serial.println("XYZ ROBOT CALIBRATED SUCCESSFULLY");
          water = 0;

          // RESET LIMIT SWTICH CHECKERS
          X_POS = false;
          X_NEG = false;
          Y_POS = false;
          Y_NEG = false;
          Z_POS = false;
        }
      }
    }


    // SEEDING
    void beginSeedDistribution() {

      mode.check();
      mode.assign();

      // PRINT STARTING COORDINATES
      Serial.println((String)"START \n    --> X : " + X_VAL + (String)" CM , Y : " + Y_VAL +  (String)" CM , Z : " + Z_VAL + (String)" CM");

      // MOVE TO LOCATION OF SEED TRAY
      

      for (int i = 0; i < noOfRows; i++) {
        for (int j = noOfCols; j > 0; j--) {
          for (int k = 0; k < noOfSeeds; k++) {

            // MOVE TO FIRST ROW AND FIRST COLUMN
            MPC.step(true, X_DIR, X_STP, stps * (xStart - X_MIN));
            Serial.println((String)"X MOVED " + (xStart - X_MIN) + (String)" CM.");
            MPC.step(true, Y_DIR, Y_STP, stps * (yWater - Y_MIN));
            Serial.println((String)"Y MOVED " + (yWater - Y_MIN) + (String)" CM.");
            MPC.step(false, Z_DIR, Z_STP, stps * zDepth);
            MPC.stopVacuumPump();
            MPC.step(true, Z_DIR, Z_STP, stps * zDepth);
            MPC.step(true, X_DIR, X_STP, stps * (xStart - X_MIN));
            Serial.println((String)"X MOVED " + (xStart - X_MIN) + (String)" CM.");
            MPC.step(true, Y_DIR, Y_STP, stps * (yWater - Y_MIN));
            Serial.println((String)"Y MOVED " + (yWater - Y_MIN) + (String)" CM.");





            //            while (digitalRead(X_LIM) == HIGH) {                                      // GO TO 1ST X-COORDINATE
            //              MPC.step(true, X_DIR, X_STP, stps);
            //            }
            //            while (digitalRead(Z_LIM) == HIGH) {
            //              MPC.step(false, Z_DIR, Z_STP, stps);
            //            }
            //            MPC.startVacuumPump();
            //            while (digitalRead(Z_LIM) == HIGH) {
            //              MPC.step(true, Z_DIR, Z_STP, stps);
            //            }
            //            if (j == noOfCols) {
            //              MPC.step(false, X_DIR, X_STP, stps * j * xSpace + xStart - X_MIN);
            //            }
            //            else {
            //              MPC.step(false, X_DIR, X_STP, stps * j * xSpace);
            //            }
            //            MPC.step(true, Y_DIR, Y_STP, stps * (ySeed - Y_MIN) * (i + 1) );
            //            while (digitalRead(Z_LIM) == HIGH) {
            //              MPC.step(false, Z_DIR, Z_STP, stps);
            //            }
            //            MPC.stopVacuumPump();
            //            delay(3000);
            //            while (digitalRead(Z_LIM) == HIGH) {
            //              MPC.step(true, Z_DIR, Z_STP, stps);
            //            }


          }
        }
      }

      Serial.println("Seeding process finished.");
      calibrate = 0;
      seed = 0;
      water = 0;

    }

    // WATERING

    //      For visualization:      X - starting point
    //
    //          modePin0 = 0:                   |       modePin = 1;
    //                                          |
    //                <<<<<<<<<<<<<<<^          |             ^>>>>>>>>>>>>>>>>
    //                               ^          |             ^
    //                               ^          |             ^<<<<<<<<<<<<<<<^
    //                               ^          |                             ^
    //          X     >>>>>>>>>>>>>>>^          |       X     >>>>>>>>>>>>>>>>^
    //                                          |

    void beginWateringProcess() {

      mode.check();
      mode.assign();

      // PRINT STARTING COORDINATES
      Serial.println((String)"START \n    --> X : " + X_VAL + (String)" CM , Y : " + Y_VAL +  (String)" CM , Z : " + Z_VAL + (String)" CM");

      // MOVE TO 1ST ROW AND 1ST COLUMN
      MPC.step(true, X_DIR, X_STP, stps * (xStart - X_MIN));
      Serial.println((String)"X MOVED " + (xStart - X_MIN) + (String)" CM.");
      MPC.step(true, Y_DIR, Y_STP, stps * (yWater - Y_MIN));
      Serial.println((String)"Y MOVED " + (yWater - Y_MIN) + (String)" CM.");
      delay(5000);
      MPC.startWaterPump();
      delay(3000);
      MPC.stopWaterPump();

      // TRAVEL TO REMAINING COLUMNS OF 1ST ROW  [L -> R]
      for (int i = 1; i < noOfCols; i++) {
        MPC.step(true, X_DIR, X_STP, stps * xSpace);
        Serial.println((String)"X MOVED " + xSpace + (String)" CM.");
        delay(5000);
        MPC.startWaterPump();
        delay(3000);
        MPC.stopWaterPump();
      }

      // MOVE TO 2ND ROW
      MPC.step(true, Y_DIR, Y_STP, stps * ySpace);
      Serial.println((String)"Y MOVED " + ySpace + (String)" CM.");
      delay(5000);
      MPC.startWaterPump();
      delay(3000);
      MPC.stopWaterPump();

      // TRAVEL TO REMAINING COLUMNS OF 2ND ROW  [L <- R]
      for (int i = 1; i < noOfCols; i++) {
        MPC.step(false, X_DIR, X_STP, stps * xSpace);
        Serial.println((String)"X MOVED " + xSpace + (String)" CM.");
        delay(5000);
        MPC.startWaterPump();
        delay(3000);
        MPC.stopWaterPump();
      }

      // [FOR TESTING IN WATERING] IF MODE 3 OR MODE 4 IS SELECTED, CHANGE ARGUMENT.
      if (digitalRead(modePin1) == 1) {                                                   // READS MODE PIN FROM RPI : if modePin1 = 0; then noOfCols = 2
        // MOVE TO 3RD ROW                                                                                                modePin1 = 1; then noOfCols = 3
        MPC.step(true, Y_DIR, Y_STP, stps * ySpace);
        Serial.println((String)"Y MOVED " + ySpace + (String)" CM.");
        delay(5000);
        MPC.startWaterPump();
        delay(3000);
        MPC.stopWaterPump();

        // TRAVEL TO REMAINING COLUMNS OF 3RD ROW  [L -> R]
        for (int i = 1; i < noOfCols; i++) {
          MPC.step(true, X_DIR, X_STP, stps * xSpace);
          Serial.println((String)"X MOVED " + xSpace + (String)" CM.");
          delay(5000);
          MPC.startWaterPump();
          delay(3000);
          MPC.stopWaterPump();
        }
        
        // MOVE TO 1ST X-COORDINATE (3RD ROW VERSION)
        for (int j = noOfCols; j > 0; j--) {
          MPC.step(false, X_DIR, X_STP, stps * xSpace);
          Serial.println((String)"X MOVED " + xSpace + (String)" CM.");
        }
        // MOVE TO LEFTMOST END ALONG X 
        MPC.step(false, X_DIR, X_STP, stps * (xStart - X_MIN));
        Serial.println((String)"X MOVED " + (xStart - X_MIN) + (String)" CM.");

      } else {
        // MOVE TO LEFTMOST END ALONG X
        MPC.step(false, X_DIR, X_STP, stps * (xStart - X_MIN));
        Serial.println((String)"X MOVED " + (xStart - X_MIN) + (String)" CM.");
      }

      // MOVE BACK TO ORIGIN
      for (int i = 1; i < noOfRows; i++) {
        MPC.step(false, Y_DIR, Y_STP, stps * ySpace);
        Serial.println((String)"Y MOVED " + ySpace + (String)" CM.");
      }

      MPC.step(false, Y_DIR, Y_STP, stps * (yWater - Y_MIN));
      Serial.println((String)"Y MOVED " + (yWater - Y_MIN) + (String)" CM.");

      Serial.println("Watering process finished.");
      calibrate = 0;
      water = 0;
      seed = 0;

    }

};

Commands AGE;
