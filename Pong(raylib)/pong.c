#include "raylib.h"
typedef enum GameScreen{ title, game, credits } GameScreen;

int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Project: Pong");
    GameScreen screen = title;
    int framecounter = 0;
    bool gamepaused = false;
    int move_1 = 0;
    int player1_lives = 3, player2_lives = 3;
    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        //update
        switch(screen){
            case title:
                framecounter++;
                if(IsKeyPressed(KEY_ENTER))
                    screen = game;
                break;
            case game:
                framecounter++;
                if(!gamepaused){
                    
                }
                if (IsKeyPressed(KEY_ENTER))
                    screen = credits;
                break;
            case credits:
                framecounter++;
                if(framecounter == 600 || IsKeyPressed(KEY_ENTER))
                    screen = title;
                break;
            default:
                break;
        }
        //draw
        BeginDrawing();
            ClearBackground(BLACK);
            switch(screen){
                case title:
                    DrawRectangleLines(40,40, screenWidth-80, screenHeight-80, RAYWHITE);
                    DrawText("PONG", (screenWidth/2)-80, (screenHeight/2)-40, 56, RED);
                    DrawText("By Aly", (screenWidth/2)-40, (screenHeight/2)+40, 24, RED);
                    if((framecounter/30)%2 == 0){
                        DrawText("PRESS [ENTER] to START", 280, 320, 18, MAROON);
                    }
                    break;
                case game: 
                    DrawRectangle(40, screenHeight/3 + move_1, 20, screenHeight/5, RAYWHITE);
                    DrawRectangle(screenWidth-60, screenHeight/3 + move_1, 20, screenHeight/5, RAYWHITE);
                    for (int i = 0; i < player1_lives; i++){
                        DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, LIGHTGRAY);
                    }
                    for (int i = player2_lives; i > 0; i--){
                        DrawRectangle(screenWidth - (20 + 40*i), screenHeight - 30, 35, 10, LIGHTGRAY);
                    }
                    break;
                
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}