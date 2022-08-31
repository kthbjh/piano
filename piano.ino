int difficult = 0;
bool gamingTF = false;
int dfcLED[3] = {A0, A1, A2}; // RGB
int buzzerPin[3] = {A3, A4, A5}; 
const int sclBtn[8] = {
    A6, A7, A8, A9, A10, A11, A12, A13
}; 
const int dfcButton = 5;
const int startButton = 6;
const int answerLED[6] = {22, 23, 24, 25, 26, 27};

int hz[8] = {
    262, 294, 330, 349, 392, 440, 494, 523
};// C,   D,   E,   F,   G,   A,   B,   HC
bool settingButtonPushed[2] = {
    false, false
};
bool pianoButtonPushed[8] = {
    false, false, false, false, false, false, false, false
};



void setup() {
    Serial.begin(9600);
    pinMode(buzzerPin[0], OUTPUT);
    pinMode(buzzerPin[1], OUTPUT);
    pinMode(buzzerPin[2], OUTPUT);
    pinMode(dfcLED[0], OUTPUT);
    pinMode(dfcLED[1], OUTPUT);
    pinMode(dfcLED[2], OUTPUT);
    for (int i=0; i<6; i++){
        pinMode(answerLED[i], OUTPUT);
    }

    pinMode(dfcButton, INPUT);
    pinMode(startButton, INPUT);
    for (int i=0;i<8;i++){
        pinMode(sclBtn[i], INPUT);
    }
    analogWrite(dfcLED[0], 0);
    analogWrite(dfcLED[1], 255);
}

// void btnpushcheck() {
//     for (int i = 0; i < 8; i++){
//         if (analogRead(sclBtn[i]) > 1000) {
//             buttonPush[i] = true;
//             return;
//         }
//     }
// }


// void dfcChoice() {
//     if (){
//     }
// }

void dfcChange() {
    difficult = (difficult + 1) % 3;
    if (difficult == 0) {
        analogWrite(dfcLED[0], 0);
        analogWrite(dfcLED[1], 255);
    }
    else if (difficult == 1) {
        analogWrite(dfcLED[0], 255);
        analogWrite(dfcLED[1], 230);
    }
    else {
        analogWrite(dfcLED[0], 255);
        analogWrite(dfcLED[1], 0);
    }
    analogWrite(dfcLED[2], 0);

}

int gameTone[3] = {-1, -1, -1};
void dfcCheck() {
    if (digitalRead(startButton) == true) {
        gameStart();
    }
}

void randomArray(int length,int equalmore,int less) {
    //배열(랜덤으로 얻을 수 있는 값이 다 들어있는), 그 배열을 섞어, 그 배열의 0번~n번까지만
    for (int i = 0 ; i<length ; i++) {
        gameTone[i] = random(equalmore, less);
    }
}
void gameStart() {
    char text[100];
    Serial.println(difficult);
    if (difficult == 0) {
        randomArray(1, 0, 8);
        tone(buzzerPin[0], hz[gameTone[0]], 1500);
        Serial.println("EASY");
        snprintf(text, 100, "hz is %i", hz[gameTone[0]]);
    }
    else if (difficult == 1) {
        randomArray(2, 0, 8);
        for (int i = 0; i<2 ; i++){
            tone(buzzerPin[i], hz[gameTone[i]]);
        }
        delay(1000);
        for (int i = 0; i<2 ; i++){
            noTone(buzzerPin[i]);
        }
        Serial.println("NORMAL");
        snprintf(text, 100, "hz are %i and %i", hz[gameTone[0]], hz[gameTone[1]]);
    }
    else {
        randomArray(3, 0, 8);
        for (int i = 0; i<3 ; i++){
            tone(buzzerPin[i], hz[gameTone[i]], 1500);
        }
        Serial.println("DIFFICULT");
        snprintf(text, 100, "hz are %i %i and %i", hz[gameTone[0]], hz[gameTone[1]], hz[gameTone[2]]);
    }
    Serial.println(text);
    gamingTF = true;
}

int pushedBtns[3] = {0, 0, 0};
// void checkPushed() {
//     for (int i = 0 ; i < 8 ; i++) {
//         if (analogRead(scl_btn[i]) > 1000) {
//             pushedBtns[i] = scl_btn[i];
//         }
//     }
// }

void answerCheck() {
    for (int i=0; i<2; i++) {
        int pushedBtn = pushedBtns[i];
        if (pushedBtn == gameTone[i]) {
            
        }
    }
}
void loop() {
    if(!gamingTF) {
        if(digitalRead(dfcButton) && !settingButtonPushed[0]) {
            dfcChange();
            settingButtonPushed[0] = true;
        }
        else settingButtonPushed[0] = false;
        if(digitalRead(startButton) && !settingButtonPushed[1]) {
            gameStart();
            settingButtonPushed[1] = true;
        }
        else settingButtonPushed[1] = false;
    }
    delay(100);

    // btnpushcheck();
    // if (!gamingTF) {
    //     dfcChoice();
    //     dfcCheck();
    //     return;
    // }
    // else {

    // }

    // delay(1000);
}
