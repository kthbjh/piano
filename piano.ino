
const int buzzerPin = A4;
int dfcRLED = A5;
int dfcGLED = A6;
int dfcBLED = A7;
const int hz[11] = {262, 277, 294, 311, 330, 349, 370, 415, 440, 466, 494};
const int dfcButton = 5;
const int startButton = 6;
int difficult = 1;

void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(dfcRLED, OUTPUT);
    pinMode(dfcGLED, OUTPUT);
    pinMode(dfcBLED, OUTPUT);

    pinMode(dfcButton, INPUT);
    pinMode(startButton, INPUT);
}

void loop() {
    //tone(buzzerPin, 840);
    for(int i = 0; i < 11; i++) {
        tone(buzzerPin, hz[i]);
        delay(500);
    }
    // delay(500);
    noTone(buzzerPin);
    delay(1000);
}

bool prebutton = false;
void dfcCho() {
    if 
}

int dfcChg() {
    difficult = (difficult + 1) % 3;
    if (difficult == 0) {
        analogWrite(dfcRLED, 0);
        analogWrite(dfcGLED, 255);
    }
    else if (difficult == 1) {
        analogWrite(dfcRLED, 255);
        analogWrite(dfcGLED, 190);
    }
    else {
        analogWrite(dfcRLED, 255);
        analogWrite(dfcGLED, 0);
    }
    analogWrite(dfcBLED, 0);

}