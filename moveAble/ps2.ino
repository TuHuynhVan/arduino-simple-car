#include <PS2X_lib.h>

/******************************************************************
   set pins connected to PS2 controller:
     - 1e column: original
     - 2e colmun: Stef?
   replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {

    Serial.begin(57600);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it

    //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    ps2x.config_gamepad(13, 12, 10, 11, false, false);

    if (error == 0) {
        Serial.print("Found Controller, configured successful!");
        Serial.print("pressures: ");
        if (pressures)
            Serial.println("true ");
        else
            Serial.println("false");
        Serial.print("rumble: ");
        if (rumble)
            Serial.println("true)");
        else
            Serial.println("false");
        Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
        Serial.println("holding L1 or R1 will print out the analog stick values.");
        Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
    } else if (error == 1)
        Serial.println(
                "No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if (error == 2)
        Serial.println(
                "Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if (error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

    //  Serial.print(ps2x.Analog(1), HEX);

    type = ps2x.readType();
    switch (type) {
        case 0:
            Serial.print("Unknown Controller type found ");
            break;
        case 1:
            Serial.print("DualShock Controller found ");
            break;
        case 2:
            Serial.print("GuitarHero Controller found ");
            break;
        case 3:
            Serial.print("Wireless Sony DualShock Controller found ");
            break;
    }
}

void loop() {
    /* You must Read Gamepad to get new values and set vibration values
       ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
       if you don't enable the rumble, use ps2x.read_gamepad(); with no values
       You should call this at least once a second
    */
    if (error == 1) //skip loop if no controller found
        return;
    if (type == 2) { //Guitar Hero Controller
    } else { //DualShock Controller
        ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

        // Triangle controller
        if (ps2x.ButtonPressed(PSB_TRIANGLE))              //will be TRUE if button was JUST pressed
            goAhead();
        if (ps2x.ButtonReleased(PSB_TRIANGLE))             //will be TRUE if button was JUST released
            stopMoving();
            
        // Circle controller
        if (ps2x.ButtonPressed(PSB_CIRCLE))              //will be TRUE if button was JUST pressed
            turnLeft();
        if (ps2x.ButtonReleased(PSB_CIRCLE))             //will be TRUE if button was JUST released
            stopMoving();

        // X controller
        if (ps2x.ButtonPressed(PSB_CROSS))              //will be TRUE if button was JUST pressed
            goBack();
        if (ps2x.ButtonReleased(PSB_CROSS))             //will be TRUE if button was JUST released
            stopMoving();

        // Square controller
        if (ps2x.ButtonPressed(PSB_SQUARE))              //will be TRUE if button was JUST pressed
            turnRight();
        if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
            stopMoving();            
    }
    delay(50);
}

void turnLeft() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void turnRight() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void goAhead() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void goBack() {
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
}

void stopMoving() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
