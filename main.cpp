
#include "raylib.h"
#include <iostream>
#include "Player.h"
#include "ball.h"
#include "math.h"
#include "misc.h"
#include "Skill.h"

#define DEFAULT_BALL_SPEED 8

using namespace std;

//oiiiiiii

struct playerInput{
    Rectangle inputRec;
    bool isActive;
    string text;
};

void controlGameInputActivation(playerInput *inputP1, playerInput *inputP2);

bool isMouseInsideRec(Rectangle rec);

void handleInputChar(playerInput *inputP1, playerInput *inputP2);

void skillInputCheck(playerInput *skill);

void backToMenu(playerInput *skill);

void p1skillshandler(playerInput *p1s1, playerInput *p1s2, playerInput *p1s3, Skill *sp1, int parameter);

int gameState = 0;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1366;
    const int screenHeight = 768;

    int updateFlag = 0;


   Rectangle upperWall;
   upperWall.x = 0;
   upperWall.y = 0;
   upperWall.width = screenWidth;
   upperWall.height = 5;

   Rectangle bottomWall;
   bottomWall.x = 0;
   bottomWall.y = screenHeight-5;
   bottomWall.width = screenWidth;
   bottomWall.height = 5;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // TODO: Load resources / Initialize variables at this point

    Rectangle rec;
    rec.height = screenHeight/8;
    rec.width = 20;
    rec.x = 5;
    rec.y = screenHeight/2 - rec.height/2;

    Player p1("jorge", LEFT_SIDE);
    Player p2("cuca", RIGHT_SIDE);
    Vector2 ballInitPosition;
    ballInitPosition.x = screenWidth/2;
    ballInitPosition.y = screenHeight/2;
    Ball ball(15, ballInitPosition, DEFAULT_BALL_SPEED,0);

    string insertP1Name = "Insert player 1's name";
    string insertP2Name = "Insert player 2's name";
    string play = "play";
    Rectangle P1NameRec;
    P1NameRec.x = 600;
    P1NameRec.y = 200;
    P1NameRec.width = 500;
    P1NameRec.height = 40;
    Rectangle P2NameRec;
    P2NameRec.x = 600;
    P2NameRec.y = 500;
    P2NameRec.width = 500;
    P2NameRec.height = 40;

    playerInput p1Input;
    p1Input.inputRec = P1NameRec;
    p1Input.isActive = false;
    p1Input.text = "";

    playerInput p2Input;
    p2Input.inputRec = P2NameRec;
    p2Input.isActive = false;
    p2Input.text = "";

    Rectangle playRec;
    playRec.x = 575;
    playRec.y = 350;
    playRec.width = 150;
    playRec.height = 50;

    Rectangle SkillRec;
    SkillRec.x = screenWidth/2 - screenWidth/16;
    SkillRec.y = screenHeight - screenHeight/8;
    SkillRec.width = 100;
    SkillRec.height = 50;


    playerInput skillInput;
    skillInput.inputRec = SkillRec;
    skillInput.isActive = false;
    skillInput.text = "Skills";

    // skills selecting:
    

    Rectangle P1S1;
    P1S1.x = 100;
    P1S1.y = 200;
    P1S1.width = 100;
    P1S1.height = 100;

    playerInput P1S1Input;
    P1S1Input.inputRec = P1S1;
    P1S1Input.isActive = false;
    P1S1Input.text = "S1";

    Rectangle P1S2;
    P1S2.x = 230;
    P1S2.y = 200;
    P1S2.width = 100;
    P1S2.height = 100;

    playerInput P1S2Input;
    P1S2Input.inputRec = P1S2;
    P1S2Input.isActive = false;
    P1S2Input.text = "S2";

    Rectangle P1S3;
    P1S3.x = 360;
    P1S3.y = 200;
    P1S3.width = 100;
    P1S3.height = 100;

    playerInput P1S3Input;
    P1S3Input.inputRec = P1S3;
    P1S3Input.isActive = false;
    P1S3Input.text = "S3";

    // P2 SKILLS:

    Rectangle P2S1;
    P2S1.x = screenWidth/2 +100;
    P2S1.y = 200;
    P2S1.width = 100;
    P2S1.height = 100;

    playerInput P2S1Input;
    P2S1Input.inputRec = P2S1;
    P2S1Input.isActive = false;
    P2S1Input.text = "S1";

    Rectangle P2S2;
    P2S2.x = screenWidth/2 +230;
    P2S2.y = 200;
    P2S2.width = 100;
    P2S2.height = 100;

    playerInput P2S2Input;
    P2S2Input.inputRec = P2S2;
    P2S2Input.isActive = false;
    P2S2Input.text = "S2";

    Rectangle P2S3;
    P2S3.x = screenWidth/2 +360;
    P2S3.y = 200;
    P2S3.width = 100;
    P2S3.height = 100;

    playerInput P2S3Input;
    P2S3Input.inputRec = P2S3;
    P2S3Input.isActive = false;
    P2S3Input.text = "S3";



    

    

    string p1score;
    string p2score;

    string p1wins = "P1 Wins!";
    string p2wins = "P2 Wins!";


    InitAudioDevice();
    Sound bonk = LoadSound("bonk.wav");
    Sound gemidao = LoadSound("gemidao.wav");

    Skill sp1(1, &p1, &p2, &ball, gemidao);
    Skill sp2(1, &p2, &p1, &ball, gemidao);

    string p1timer = "0.0";
    string p2timer = "0.0";
    string skillpronta = "Skill Pronta!";
    

    

    Texture2D sport = LoadTexture("sport.png");
    cout << IsTextureReady(sport);

    SetTargetFPS(60);
    

    SetMasterVolume(70);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        switch (gameState)
        {
        case 0:
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(insertP1Name.data(), 250 ,200 ,30, BLUE);
            DrawRectangleLinesEx(P1NameRec, 2, BLACK);
            DrawText(insertP2Name.data(), 245, 500, 30, RED);
            DrawRectangleLinesEx(P2NameRec, 2, BLACK);
            DrawRectangleLinesEx(SkillRec, 2, BLACK);
            DrawText(skillInput.text.data(), 610, 684, 30, GREEN);
            controlGameInputActivation(&p1Input, &p2Input);
            
            if(p1Input.isActive){
                DrawRectangleLinesEx(P1NameRec, 2, RED);
            }
            else{
                DrawRectangleLinesEx(P1NameRec, 2, BLACK);
            }
            if(p2Input.isActive){
                DrawRectangleLinesEx(P2NameRec, 2, RED);
            }
            else{
                DrawRectangleLinesEx(P2NameRec, 2, BLACK);
            }

            if(skillInput.isActive) {
                DrawRectangleLinesEx(SkillRec, 2, RED);
            }
            else DrawRectangleLinesEx(SkillRec, 2, BLACK);

            handleInputChar(&p1Input, &p2Input);
            skillInputCheck(&skillInput);
            DrawText(p1Input.text.data(), 610, 205, 30, BLUE);
            DrawText(p2Input.text.data(), 610, 505, 30, RED);

            DrawRectangleLinesEx(playRec, 2, BLACK);
            DrawText(play.data(), 620, 360, 30, BLACK);
            if(isMouseInsideRec(playRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && p1Input.text.size() > 0 && p2Input.text.size() > 0){
                gameState = 1;
            }
            EndDrawing();
            break;
        
        case 1:
            BeginDrawing();
            

            
            ClearBackground(RAYWHITE);

            DrawTexture(sport, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 125, RAYWHITE);
            DrawRectangleRec(p1.rec, p1.recColor);
            DrawRectangleRec(p2.rec, p2.recColor);
            DrawCircleV(ball.position, ball.radius, GREEN);
            ball.updateBallSpeed(upperWall, bottomWall, p1.rec, p2.rec, bonk);
            ball.updateBallPosition();
            Player::inputHandler(&p1, &p2);;
            updateScore(&p1, &p2, &ball, &updateFlag);

            // score> int to string and show score
            p1score = to_string(p1.score);
            p2score = to_string(p2.score);

            DrawText(p1score.data(), 100, 50, 30, BLUE);
            DrawText(p2score.data(), SCREEN_WIDTH - 100, 50, 30, RED);


            resetBall(&p1, &p2, &ball, &updateFlag, DEFAULT_BALL_SPEED);

            if(p1.score >= 6 || p2.score >= 6) {
                Player::resetWin(&p1, &p2);
                resetBall(&p1,&p2,&ball,&updateFlag,DEFAULT_BALL_SPEED);
                p1Input.text.clear();
                p2Input.text.clear();
                p1Input.isActive = false;
                p2Input.isActive = false;

                gameState = 0;

            }

            if(IsKeyPressed(KEY_LEFT_SHIFT) && sp1.isActive == false && sp1.timeremaining <=0) {
                sp1.isActive = true;
                sp1.timeremaining = sp1.cd;
            }
            if(IsKeyPressed(KEY_RIGHT_SHIFT) && sp2.isActive == false && sp2.timeremaining <=0) {
                sp2.isActive = true;
                sp2.timeremaining = sp2.cd;
            }
            sp1.updateSkill();
            sp2.updateSkill();

            p1timer = to_string(sp1.timeremaining/60.0f);
            p2timer = to_string(sp2.timeremaining/60.0f);

            for(int i = 0; i < 4; i++) {
                p1timer.pop_back();
                p2timer.pop_back();
            }
            
            DrawText(p1timer.data(), 100, screenHeight -100, 30, BLACK);
            DrawText(p2timer.data(), 1000, screenHeight - 100, 30, BLACK);

            


            EndDrawing();
            break;
        
        case 2:
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Back to menu:
            DrawRectangleLinesEx(SkillRec, 2, BLACK);
            DrawText(skillInput.text.data(), 610, 684, 30, GREEN);

            if(skillInput.isActive) {
                DrawRectangleLinesEx(SkillRec, 2, RED);
            }
            else DrawRectangleLinesEx(SkillRec, 2, BLACK);

            backToMenu(&skillInput);

            // skills player 1:
            p1skillshandler(&P1S1Input, &P1S2Input, &P1S3Input, &sp1, 1);
            p1skillshandler(&P2S1Input, &P2S2Input, &P2S3Input, &sp2, 2);

            
            

            EndDrawing();
        
        default:
            break;
        }

        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    CloseAudioDevice();
    return 0;
}

bool isMouseInsideRec(Rectangle rec){
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    if(mouseX <= rec.x + rec.width && mouseX >= rec.x && mouseY <= rec.y + rec.height && mouseY > rec.y){
        return true;
    }
    else{
        return false;
    }
}

void controlGameInputActivation(playerInput *inputP1, playerInput *inputP2){
    if(isMouseInsideRec(inputP1->inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        inputP1->isActive = true;
        inputP2->isActive = false;
    }
    if(isMouseInsideRec(inputP2->inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        inputP2->isActive = true;
        inputP1->isActive = false;
    }
}

void handleInputChar(playerInput *inputP1, playerInput *inputP2){
    char pressed;
    if(inputP1->isActive){
        if(IsKeyPressed(KEY_BACKSPACE) && inputP1->text.size()>0){
            inputP1->text.pop_back();
        }
        else if(IsKeyPressed(KEY_ENTER)){
            inputP1->isActive = false;
        }
        else{
            pressed = GetKeyPressed();
            if(pressed >= 65 && pressed <= 122){
                inputP1->text.push_back(pressed);
            }
        }


    }
    else if(inputP2->isActive){
        if(IsKeyPressed(KEY_BACKSPACE) && inputP2->text.size()>0){
            inputP2->text.pop_back();
        }
        else if(IsKeyPressed(KEY_ENTER)){
            inputP2->isActive = false;
        }
        else{
            pressed = GetKeyPressed();
            if(pressed >= 65 && pressed <= 122){
                inputP2->text.push_back(pressed);
            }
        }
    }
}

    void skillInputCheck(playerInput *skill) {
        if(isMouseInsideRec(skill-> inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            skill -> isActive = true;
            skill -> text = "Menu";
            gameState = 2;
        } else if(isMouseInsideRec(skill-> inputRec)) skill -> isActive = true;
        else skill -> isActive = false;
    }

    void backToMenu(playerInput *skill) {
        if(isMouseInsideRec(skill-> inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            skill -> isActive = true;
            skill -> text = "Skills";
            gameState = 0;
        } else if(isMouseInsideRec(skill-> inputRec)) skill -> isActive = true;
        else skill -> isActive = false;
    }

    void p1skillshandler(playerInput *p1s1, playerInput *p1s2, playerInput *p1s3, Skill *sp1, int parameter) {
        DrawRectangleLinesEx(p1s1 -> inputRec, 2, BLACK);
        DrawRectangleLinesEx(p1s2 -> inputRec, 2, BLACK);
        DrawRectangleLinesEx(p1s3 -> inputRec, 2, BLACK);
        string ms1 = "S1: Increases player's speed";
        string ms2 = "S2: Changes ball direction";
        string ms3 = "S3: Changes enemy's controls";
        

        Color test;
        if(parameter == 1) {
            test = BLUE;
            DrawText(p1s1 ->text.data(), 110, 225, 60, BLUE);
            DrawText(p1s2 ->text.data(), 240, 225, 60, BLUE);
            DrawText(p1s3 ->text.data(), 370, 225, 60, BLUE);
        }
        else {
            test = RED;
            DrawText(p1s1 ->text.data(), 683 + 110, 225, 60, RED);
            DrawText(p1s2 ->text.data(), 683 + 240, 225, 60, RED);
            DrawText(p1s3 ->text.data(), 683 + 370, 225, 60, RED);
        }

        // changing skills && checking mouse
        if(p1s1->isActive) {
            DrawRectangleLinesEx(p1s1 -> inputRec, 2, test);
        } else DrawRectangleLinesEx(p1s1 -> inputRec, 2, BLACK);
        if(p1s2->isActive) {
            DrawRectangleLinesEx(p1s2 -> inputRec, 2, test);
        } else DrawRectangleLinesEx(p1s2 -> inputRec, 2, BLACK);
        if(p1s3->isActive) {
            DrawRectangleLinesEx(p1s3 -> inputRec, 2, test);
        } else DrawRectangleLinesEx(p1s3 -> inputRec, 2, BLACK);

        if(isMouseInsideRec(p1s1->inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            p1s1->isActive = true;
            p1s2->isActive = false;
            p1s3->isActive = false;
            sp1->id = 1;
            sp1->skill_time = 180;
            sp1->cd = 15*60;
            sp1->timeremaining = 0;
            
            
        }
        if(isMouseInsideRec(p1s2->inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            p1s1->isActive = false;
            p1s2->isActive = true;
            p1s3->isActive = false;
            sp1->id = 2;
            sp1->skill_time = 0;
            sp1->cd = 15*60;
            sp1->timeremaining = 0;
            
        }
        if(isMouseInsideRec(p1s3->inputRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            p1s1->isActive = false;
            p1s2->isActive = false;
            p1s3->isActive = true;
            sp1->id = 3;
            sp1->skill_time = 180;
            sp1->cd = 15*60;
            sp1->timeremaining = 0;
            
        }

        if(p1s1 -> isActive) {
            if(parameter == 1) DrawText(ms1.data(), 100, 650, 30, BLACK);
            else DrawText(ms1.data(), 783, 650, 30, BLACK);
        }
        if(p1s2 -> isActive) {
            if(parameter == 1) DrawText(ms2.data(), 100, 650, 30, BLACK);
            else DrawText(ms2.data(), 783, 650, 30, BLACK);
        }
        if(p1s3 -> isActive) {
            if(parameter == 1) DrawText(ms3.data(), 100, 650, 30, BLACK);
            else DrawText(ms3.data(), 783, 650, 30, BLACK);
        }
    }
