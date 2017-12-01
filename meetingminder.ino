// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

InternetButton b = InternetButton();
uint8_t button1 = 0;
uint8_t button2 = 0;
uint8_t button3 = 0;
uint8_t button4 = 0;
uint8_t buttonAll = 0;
int gaugeCount = 0;
int buzzer = D0;

int attempts = 0;
// String last_command = "rgrgrgrgrgr";
String carpTime = "bbbbbbbbbbb";
String meetingTime = "ggggggggggg";
bool checker = false;

// The code in setup() runs once when the device is powered on or reset. Used for setting up states, modes, etc
void setup() {
    // Tell b to get everything ready to go
    b.begin();
    b.allLedsOff();
    b.rainbow(10);

    // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("LEDs",ledToggle);
   
   Particle.function("CarpTransit",carpTransit);
   
   b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4");
}

int carpTransit(String command) {

    b.allLedsOff();
    delay(5);
    
    Particle.publish("carpTransit",command, 60, PRIVATE);
    carpTime = command;

    return command.length();
}

int ledToggle(String command) {

    int buzz = 0;
    
    meetingTime = command;
    
    // if checker: {
        
        
    // }
    
    meetingTime = command;
    b.allLedsOff();
    delay(3);
    
    Particle.publish("ledToggle",command, 60, PRIVATE);

    for (int n=0; n<11; n++) {

        if (sizeof(command)<=n) {
            b.ledOn(1, 255,0, 0);
            b.ledOn(11, 255,0, 0);
            break;
        }

        char c = command.charAt(n);

        switch (c) {
            
            case 'R':
                b.ledOn(n+1, 255, 0, 0); delay(5);
                buzz++; 
                break;

            case 'r':
                b.ledOn(n+1, 10, 0, 0); delay(5);
                break;

            case 'G':
                b.ledOn(n+1, 0, 255, 0); delay(5);
                break;

            case 'g':
                b.ledOn(n+1, 0, 110, 0); delay(5);
                break;

            case 'Y':
                b.ledOn(n+1, 255, 255, 0); delay(5);
                break;

            case 'y':
                b.ledOn(n+1, 10, 10, 0); delay(5);
                break;

            case 'O':
                b.ledOn(n+1, 255, 128, 0); delay(5);
                break;

            case 'o':
                b.ledOn(n+1, 20, 10, 0); delay(5);
                break;

            case 'B':
                b.ledOn(n+1, 0, 0, 128); delay(5);
                break;

            case 'b':
                b.ledOn(n+1, 0, 0, 10); delay(5);
                break;

            default:
                b.ledOn(n+1, 1, 1, 1); delay(5);
                break;
        }
    }
    delay(3);
    
    if (buzz>9) {
        /*
        playSong takes a string in the format
        "NOTE,TYPE,NOTE,TYPE..."
        Types are note types that define duration so
        8 is a 1/8th note and 4 is a 1/4 note
        */

        //Play Sad Trombone
        b.playSong("Bb3,3,A3,3,Ab3,3,G3,2\n");

    } else if (buzz> 6) {
        // playNote just plays a single note, and takes
        // a note name as a string and a note type as an int
        // Note types define duration like in scored music, so
        // 8 is a 1/8th note and 4 is a 1/4 note

        //The buzz sound gets longer as you get closer
        b.playNote("G3",10-buzz);
    }

    digitalWrite(buzzer, LOW);


    return command.length();
}

/* loop(), in contrast to setup(), runs all the time. Over and over again.
Remember this particularly if there are things you DON'T want to run a lot. Like Particle.publish() */
void loop() {

    //Is everything OK
    if (Particle.connected()) {
        attempts = 0;
    }
    else {
        attempts++;
        delay(1000);

        if (attempts>10) {
            ledToggle("bgzzzrzzzgb");
        }

    }

    if(b.allButtonsOn()){
        if(!buttonAll){
            buttonAll = 1;
            Particle.publish("allbuttons","All buttons pushed", 60, PRIVATE);
            b.rainbow(10);
            delay(100);
            b.allLedsOff();
            ledToggle(meetingTime);
        }
    }
    else {buttonAll = 0;}

    if(b.buttonOn(1)){
        if(!button1){
            button1 = 1;
            Particle.publish("button1",carpTime, 60, PRIVATE);
            checker = true;
            ledToggle(carpTime);
            delay(3000);
            b.allLedsOff();
            ledToggle(meetingTime);
        }
    }
    else {button1 = 0;}

    if(b.buttonOn(2)){
        if(!button2){
            button2 = 1;
            Particle.publish("button2","Button 2 was pushed", 60, PRIVATE);
            b.ledOn(3,0,50,0);
            delay(100);
            b.ledOff(3);
            ledToggle(meetingTime);
        }
    }
    else {button2 = 0;}

    if(b.buttonOn(3)){
        if(!button3){
            button3 = 1;
            Particle.publish("book_it", "{\"startTime\":\"8:30PM\", \"endTime\":\"9:30PM\"}", 60, PRIVATE);
            ledToggle(meetingTime);
        }
    }
    else {button3 = 0;}

    if(b.buttonOn(4)){
        if(!button4){
            button4 = 1;
            Particle.publish("button4","Button 4 was pushed", 60, PRIVATE);
            b.ledOn(9,30,30,30);
            delay(100);
            b.ledOff(9);
            ledToggle(meetingTime);
        }
    }
    else {button4 = 0;}
}