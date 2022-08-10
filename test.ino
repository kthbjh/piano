int difficultyRgb[3] = {A5, A6, A7};
const int selectDifficultyBtn = 5;
const int startGameBtn = 6;
const int buzzers[3] = {A1, A2, A3};
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

void testRgb(int rgb[], int analog = 255) {
    int length = sizeof(rgb);
    for(int i = 0; i < length; i++) {
        analogWrite(rgb[i], analog);
        delay(500);
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
    testRgb(difficultyRgb);
    testRgb(difficultyRgb, 0);
    Serial.println("testing correcting rgb...");
    
}
void loop() {

}