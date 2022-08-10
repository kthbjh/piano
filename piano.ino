
const int buzzerPin = A4;
const int hz[11] = {262, 277, 294, 311, 330, 349, 370, 415, 440, 466, 494};

void setup() {
    pinMode(buzzerPin, OUTPUT);
}

void loop() {
    //tone(buzzerPin, 840);
    for(int i = 0; i < 11; i++) {
        tone(buzzerPin, hz[i]);
        delay(500);
    }
    // delay(500);
    noTone(buzzerPin);
    delay(500000);
}

void difficultCho(){
    if 
}