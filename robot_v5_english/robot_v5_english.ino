#include <Wire.h>
#include <NXShield.h>
#include<NXTTouch.h>
#include <NXTUS.h>
NXShield nxshield;
NXTTouch touch1;
NXTUS sonar1;
NXTUS sonar2;
int input = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                 //connexion bitrate
  Serial.print("Initializing the devices...");
  nxshield.init(SH_HardwareI2C);                      //initialized Nxhsield
  Serial.print("press go to continue");
  nxshield.waitForButtonPress(BTN_GO);
  touch1.init(&nxshield, SH_BAS1);                    //initialized the contact sensor
  sonar1.init(&nxshield, SH_BAS2);                    //initialized ultrasound sensor n°1
  sonar2.init(&nxshield, SH_BBS1);                    //initialized ultrasound sensor n°2



}
bool lastTouch, touchPressed;

void loop() {
  char aa[80];
  char str[256];
  int bb_us;                                              //initialized ultrasound sensor's variable
  int bb_usg;

  bb_us = sonar1.getDist();                              //increment the sonar's variables with the distance received from the sensors
  sprintf (str, "sonar1: Obstacle at: %d cm", bb_us );
  delay(200);
  Serial.println(str);

  bb_usg = sonar2.getDist();                            //same that the other sensor
  sprintf (str, "sonar2: Obstacle at: %d cm", bb_usg);
  delay(200);
  Serial.println(str);


  input = Serial.read();                                //create the variable who match the values sent by the appilcation 
  if (input == '1') {                                   //autonomous mode (nonfunctional)


    if (bb_us - 4 > 15 and bb_usg - 4 > 15) { //do -4 to get the value in centimeters
      //if they are no obstacles
      nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        int (100));
      nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        int (100));

      nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        int(100));
      nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        int(100));

    }

    if (bb_us - 4 < 15 and bb_usg - 4 > 15) { //if the obstacle is on the left

      //turn right

      nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        int(100));
      nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        int(100));

      nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        int(100));
      nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        int(100));

    }
    if (bb_usg - 4 < 15) { //if the obstalce is on the right

      //turn left
      nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        int(100));
      nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        int(100));

      nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        int(100));
      nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        int(100));
    }
    if (bb_us - 4 < 15 and bb_usg - 4 < 15) { //if the obstacle is in front of 
        //move back
      nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        int (100));
      nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        int (100));

      nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        int(100));
      nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        int(100));
      delay(1000);


    }


    if (input == '9') { //correspond at the stop 
      nxshield.bank_a.motorReset();
      nxshield.bank_b.motorReset();
    }

  }



  //manuel mode
  if (input == '2') { //forward
    nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      int(100));

    nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Forward,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Forward,
                                      int(100));

  }

  if (input == '3') { //backward
    nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Forward,
                                      int(100));
    nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Forward,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      int(100));
  }

  if (input == '4') { //turn left
    nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Forward,
                                      int(100));
    nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Forward,
                                      int(100));


  }

  if (input == '5') { //turn right
    nxshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      int(100));
    nxshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Forward,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                      SH_Direction_Forward,
                                      int(100));
    nxshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      int(100));

  }

  if (input == '9') { //correspond at the stop
    nxshield.bank_a.motorReset();
    nxshield.bank_b.motorReset();
  }
}
