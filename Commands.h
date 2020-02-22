class Commands {

  private:
    
  public:
    
    // 3-AXIS CALIBRATION
    void beginCalbiration(){

        if(digitalRead(X_LIM) == HIGH && X_POS == false){  
          SMC.step(true, X_DIR, X_STP, stps);
          Serial.println("MOVING X-AXIS TO THE RIGHT.");
        } else if(digitalRead(X_LIM) == LOW && X_POS == false){
          Serial.println("X_POS TOUCHED");
          X_POS = true;
          delay(3000);
        } else if(digitalRead(X_LIM) == HIGH && X_NEG == false){
          SMC.step(false, X_DIR, X_STP, stps);
          Serial.println("MOVING X-AXIS TO THE LEFT.");
        } else if(digitalRead(X_LIM) == LOW && X_NEG == false){
          Serial.println("X_NEG TOUCHED");
          delay(1000);
          SMC.step(false, X_DIR, X_STP, 0);
          Serial.println("Now stopping motion along X-AXIS.");
          X_NEG = true;
          delay(3000);
        } else if (X_POS == true && X_NEG == true){
          Serial.println("X-AXIS SUCCESSFULLY CALIBRATED.");
          SMC.step(false, X_DIR, X_STP, 0);
          Serial.println("MOTION ALONG X-AXIS STOPPED.");
          delay(5000);
          calibrate = 0;
        }
    }

        

}; 

Commands AGE; 
