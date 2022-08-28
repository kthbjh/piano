int difficultyRgb[3] = {A0, A1, A2};
const int selectDifficultyBtn = 5;
const int startGameBtn = 6;
const int buzzers[3] = {A3, A4, A5};
const int isCorrectRgbs[3][2] = {
    {
        22, 23
    },
    {
        24, 25
    },
    {
        26, 27
    }
};
const int hz[] = {
    262, 294, 330, 349, 392, 440, 494, 523
};
const int pianoBtns[] = {
    5, 6, A6, A7, A8, A9, A10, A11, A12, A13
};
bool btnPressed[] = {
    false, false, false, false, false, false, false, false, false, false, false
};

void testDifficultyRgb(int rgb[], int analog = 255) {
    int length = sizeof(rgb);
    for(int i = 0; i < length; i++) {
        analogWrite(rgb[i], analog);
        delay(500);
    }
}

void testCorrectRgb(int pinR, int pinG) {
    digitalWrite(pinR, HIGH);
    delay(300);
    digitalWrite(pinR, LOW);
    digitalWrite(pinG, HIGH);
    delay(300);
    digitalWrite(pinG, LOW);
}

void testBuzzer(int pin) {
    for(int i = 0; i < (sizeof(hz) / sizeof(hz[0])); i++) {
        tone(pin, hz[i]);
        delay(300);
        noTone(pin);
    }
}

void setup() {
    pinMode(selectDifficultyBtn, INPUT);
    pinMode(startGameBtn, INPUT);
    for(int i = 0; i < 3; i++) {
        pinMode(difficultyRgb[i], OUTPUT);
        pinMode(buzzers[i], OUTPUT);
        for(int j = 0; j < 2; j++) {
            pinMode(isCorrectRgbs[i][j], OUTPUT);
        }
    }
    Serial.begin(9600);
    Serial.println("testing difficulty rgb...");
    testDifficultyRgb(difficultyRgb);
    testDifficultyRgb(difficultyRgb, 0);
    Serial.println("testing correct rgbs...");
    for(int i = 0; i < 3; i++) {
        testCorrectRgb(isCorrectRgbs[i][0], isCorrectRgbs[i][1]);
    }
    Serial.println("testing first buzzer...");
    // testBuzzer(buzzers[0]);
    Serial.println("testing second buzzer...");
    // testBuzzer(buzzers[1]);
    Serial.println("testing third buzzer...");
    // testBuzzer(buzzers[2]);

    for(int i = 0; i < 10; i++) {
        pinMode(pianoBtns[i], INPUT);
    }
    Serial.println("testing piano buttons...\nplease press buttons in order");
}

void loop() {
    bool allTrue = true;
    int i = 0;
    for(; i < 2; i++) {
        allTrue = allTrue && btnPressed[i];
        if(digitalRead(pianoBtns[i]) && !btnPressed[i]) {
            char text[100];
            snprintf(text, 100, "Button that connected at %ipin was pressed!", pianoBtns[i]);
            Serial.println(text);
            btnPressed[i] = true;
            break;
        }
        delay(50);
    }
    for(; i < 10; i++) {
        allTrue = allTrue && btnPressed[i];
        if(analogRead(pianoBtns[i]) > 1000 && !btnPressed[i]) {
            char text[100];
            snprintf(text, 100, "Button that connected at %ipin was pressed!", pianoBtns[i]);
            Serial.println(text);
            btnPressed[i] = true;
            break;
        }
        delay(50);
    }
    if(allTrue) {
        Serial.println("All test was ended.");
        delay(10000);
    }
}