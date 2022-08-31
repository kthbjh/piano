#include "Polytone.h"

Polytone poly;

const int buzzerPin[3] = {10, 11, 12};
const int hz[8] = {262, 294, 330, 349, 392, 440, 494, 523};

enum Difficulty {
    EASY,
    NORMAL,
    HARD
}
// Difficulty gameDifficulty = EASY;

void changeDifficulty() {
    gameDifficulty = gameDifficulty + 1;
    
}
void startGame() {

}
void makeRandomTones() {

}
void playRandomTones() {

}
void answerEntered() {

}
bool isCorrected() {

}
void gameFinished() {

}

void setup() {
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
    
}

// void difficultCho(){
//     if 
// }