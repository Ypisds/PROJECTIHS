
#include "raylib.h"
#include <iostream>
#include "Player.h"
#include "ball.h"
#include "math.h"
#include "misc.h"

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

    string p1score;
    string p2score;

    InitAudioDevice();
    Sound bonk = LoadSound("bonk.wav");

    

    int gameState = 0;

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

            handleInputChar(&p1Input, &p2Input);
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
