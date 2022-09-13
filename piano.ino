#include "Polytone.h"

Polytone poly;

int seed = 0;
bool playingGame = false;
const int buzzerPins[3] = {9, 10, 11};
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
int order = 1;

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
int rights[3] = {9999, 9999, 9999};
int userInput[3] = {9999, 9999, 9999};
int* arrSort(int arr[]) {
    int temp;
    for (int i = 0; i < 3; i++) {
        for(int j = i+1; j <3; j++) {
            if(arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return arr;
}
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
    Serial.print("Difficulty: ");
    Serial.println(gameDifficulty);
    makeRandomArray(gameDifficulty+1);
    playRandomTones();
}
bool isCorrected(int answer) {
    for (int i = 0; i < 3; i++) {
        if(answer == rights[i]) return true;
    }
    return false;
}
void playAnswer() {
    int* sortedUserInput = arrSort(userInput);
    int* sortedRights = arrSort(rights);
    Serial.println(order);
    // Serial.println("playanswer");
    Serial.println("Rights");
    for(int i = 0; i < 3; i++) {
        Serial.println(sortedRights[i]);
    }
    Serial.println("answered");
    for(int i = 0; i < 3; i++) {
        Serial.println(sortedUserInput[i]);
    }
    for(int i = 0; i < gameDifficulty+1; i++) {
        poly.setPins(buzzerPins[i]);
        poly.begin();
        poly.tone(gameTone[sortedRights[i]]);
        delay(500);
        poly.end();
    }
    delay(1500);
    for(int i = 0; i < order; i++) {
        poly.setPins(buzzerPins[i]);
        poly.begin();
        poly.tone(gameTone[sortedUserInput[i]]);
        delay(500);
        poly.end();
    }
}
void finish() {
    digitalWrite(difficultyLed[0], 0);
    digitalWrite(difficultyLed[1], 0);
    digitalWrite(difficultyLed[2], 0);
    gameDifficulty = HARD;
    changeDifficulty();
    playingGame = false;
    for(int i = 0; i < 3; i++) {
        userInput[i] = 9999;
        rights[i] = 9999;
        digitalWrite(correctLeds[i][0], LOW);
        digitalWrite(correctLeds[i][1], LOW);
    }
    order=1;
}
void gameWon() {
    for(int i = 0; i< 3; i++) {
        digitalWrite(correctLeds[0][1], HIGH);
        digitalWrite(correctLeds[1][1], HIGH);
        digitalWrite(correctLeds[2][1], HIGH);
        delay(500);
        digitalWrite(correctLeds[0][1], LOW);
        digitalWrite(correctLeds[1][1], LOW);
        digitalWrite(correctLeds[2][1], LOW);
        delay(500);
    }
    playAnswer();
    finish();
}
void gameLosed() {
    digitalWrite(correctLeds[0][1], LOW);
    digitalWrite(correctLeds[1][1], LOW);
    for(int i = 0; i< 3; i++) {
        digitalWrite(correctLeds[0][0], HIGH);
        digitalWrite(correctLeds[1][0], HIGH);
        digitalWrite(correctLeds[2][0], HIGH);
        delay(500);
        digitalWrite(correctLeds[0][0], LOW);
        digitalWrite(correctLeds[1][0], LOW);
        digitalWrite(correctLeds[2][0], LOW);
        delay(500);
    }
    playAnswer();
    finish();
}
void answerEntered(int answer) {
    userInput[order-1] = answer;
    if(isCorrected(answer)) {
        Serial.println("correct");
        if(order-1 == gameDifficulty) {
            gameWon();
        }
        else {
            digitalWrite(correctLeds[order-1][1], HIGH);
            //해당 작업들
            order++;
        }
    }
    else {
        Serial.println("failed");
        digitalWrite(correctLeds[answer-1][0], HIGH);
        delay(500);
        gameLosed();
    }
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

bool buttonPushed(int pin) {
    int read = analogRead(pin);
    return read > 1000;
}
bool inputedBefore(int answer) {
    for(int i = 0; i < 3; i++) {
        if (userInput[i] == answer) return true;
    }
    return false;
}
void loop() {
    
    if(playingGame) {
        // Serial.println("playing");
        for(int i = 0; i < 8; i++) {
            if (buttonPushed(buttonPins[i])) {
                if(inputedBefore(i)) return;
                Serial.println("button pushed");
                answerEntered(i);
                delay(500);
                break;
            }
        }
    }
    else {
        if(digitalRead(difficultyButton)) {
            changeDifficulty();
            delay(500);
        }
        if(digitalRead(startGameButton)) {
            startGame();
        }
        seed = (seed+1) % 30000;
    }
}
