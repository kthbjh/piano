#include "Polytone.h"

Polytone poly;

int seed = 0;
bool playingGame = false;
const int buzzerPins[3] = {10, 11, 12};
const int buttonPins[8] = {A6, A7, A8, A9, A10, A11, A12, A13};
const int difficultyButton = 5;
const int startGameButton = 6;
const int gameTone[8] = {262, 294, 330, 349, 392, 440, 494, 523};
const int difficultyLed[3] = {A0, A1, A2};
const int correctLeds[3][2] = {
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

enum Difficulty {
    EASY,
    NORMAL,
    HARD
};
Difficulty gameDifficulty = EASY;

void changeDifficulty() {
    gameDifficulty = (Difficulty)((gameDifficulty + 1) % 3);
    if(gameDifficulty == EASY) {
        analogWrite(difficultyLed[0], 0);
        analogWrite(difficultyLed[1], 255);
        analogWrite(difficultyLed[2], 0);
    }
    else if(gameDifficulty == NORMAL) {
        analogWrite(difficultyLed[0], 128);
        analogWrite(difficultyLed[1], 128);
        analogWrite(difficultyLed[2], 0);
    }
    else {
        analogWrite(difficultyLed[0], 255);
        analogWrite(difficultyLed[1], 0);
        analogWrite(difficultyLed[2], 0);
    }
}
int rights[3] = {-1, -1, -1};
void makeRandomArray(int length) {
    int all[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    randomSeed(seed);
    for(int i = 0; i < 8; i++) {
        int a = random(0, 8);
        int b = random(0, 8);
        int temp = all[a];
        all[a] = all[b];
        all[b] = temp;
    }
    for(int i = 0; i < length; i++) {
        rights[i] = all[i];
    }
}
void playRandomTones() {
    Polytone poly;
    poly.setPins(buzzerPins[0], buzzerPins[1], buzzerPins[2]);
    poly.begin();
    for(int i = 0; i <= gameDifficulty; i++) {
        poly.tone(gameTone[rights[i]]);
        Serial.println(rights[i]);
    }
    delay(1000);
    poly.end();
}
void startGame() {
    playingGame = true;
    makeRandomArray(gameDifficulty+1);
    playRandomTones();
}
void answerEntered() {

}
bool isCorrected() {

}
void gameFinished() {

}

void setup() {
    for(int i = 0; i < 8; i++) {
        pinMode(buttonPins[i], INPUT);
    }
    for(int i = 0; i < 3; i++) {
        pinMode(buzzerPins[i], OUTPUT);
    }
    for(int i = 0; i < 6; i++) {
        pinMode(correctLeds[i / 2][i % 2], OUTPUT);
    }
    analogWrite(difficultyLed[1], 255);
    Serial.begin(9600);
}

int pushedBtns[3] = {0, 0, 0};

// void answerCheck() {
//     for (int i=0; i<2; i++) {
//         int pushedBtn = pushedBtns[i];
//         if (pushedBtn == gameTone[i]) {
            
//         }
//     }
// }

bool buttonPushed(int pin) {
    int read = analogRead(pin);
    return read > 1000;
}

void loop() {
    if(playingGame) {

    }
    else {
        if(digitalRead(difficultyButton)) {
            changeDifficulty();
            delay(500);
        }
        if(digitalRead(startGameButton)) {
            startGame();
        }
    }
    seed = (seed+1) % 30000;
}

// void difficultCho(){
//     if 
// }