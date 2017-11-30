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


// The code in setup() runs once when the device is powered on or reset. Used for setting up states, modes, etc
void setup() {
    // Tell b to get everything ready to go
    b.begin();
    b.allLedsOff();

    // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("LEDs",ledToggle);
   b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4");
}

int ledToggle(String command) {

    int buzz = 0;
    b.allLedsOff();
    delay(5);
    
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
    delay(5);
    
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
            Particle.publish("allbuttons",NULL, 60, PRIVATE);
            b.rainbow(10);
            delay(100);
            b.allLedsOff();
        }
    }
    else {buttonAll = 0;}

    if(b.buttonOn(1)){
        if(!button1){
            button1 = 1;
            Particle.publish("button1",NULL, 60, PRIVATE);
            b.ledOn(12,50,0,0);
            delay(100);
            b.ledOff(12);
        }
    }
    else {button1 = 0;}

    if(b.buttonOn(2)){
        if(!button2){
            button2 = 1;
            Particle.publish("button2",NULL, 60, PRIVATE);
            b.ledOn(3,0,50,0);
            delay(100);
            b.ledOff(3);
        }
    }
    else {button2 = 0;}

    if(b.buttonOn(3)){
        if(!button3){
            button3 = 1;
            Particle.publish("button3",NULL, 60, PRIVATE);
            b.ledOn(6,0,0,50);
            delay(100);
            b.ledOff(6);
        }
    }
    else {button3 = 0;}

    if(b.buttonOn(4)){
        if(!button4){
            button4 = 1;
            Particle.publish("button4",NULL, 60, PRIVATE);
            b.ledOn(9,30,30,30);
            delay(100);
            b.ledOff(9);
        }
    }
    else {button4 = 0;}
}