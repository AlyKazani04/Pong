#include <raylib.h>

#define PLAYER_LIFES    3

typedef enum GameScreen{ title, instructions, colors, game, credits } GameScreen;

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lifes;
} Player;

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
} Ball;


int main(){
    const int screenWidth = 1000;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Project: Pong");
    
    GameScreen screen = title;
    
    Font font[2] = { 0 };
    font[0] = LoadFont("C:/raylib/raylib/examples/text/resources/fonts/pixantiqua.png");
    font[1] = LoadFont("C:/raylib/raylib/examples/text/resources/fonts/alagard.png");
    
    Color color_arr[5] = {RED, YELLOW, GREEN, BLUE, VIOLET};
    int p1color_index = 0;
    int p2color_index = 3;
    Color gradient1[5] = {
        (Color){ 230, 41, 55, 210 }, // red
        (Color){ 253, 249, 0, 210 }, // yellow
        (Color){ 0, 228, 48, 210 }, // green
        (Color){ 0, 121, 241, 210 }, // blue
        (Color){ 135, 60, 190, 210 } // violet
    };
    Color gradient2[5] = {
        (Color){ 190, 33, 55, 55 }, // maroon
        (Color){ 253, 249, 0, 55 }, // yellowlucent
        (Color){ 0, 228, 48, 55 }, // greenlucent 
        (Color){ 0, 121, 241, 55 }, //bluelucent
        (Color){ 135, 60, 190, 55 } // violetlucent
    };
    
    int framecounter = 0;
    bool gamepaused = false;
    
    Player player1 = { 0 };
    Player player2 = { 0 };
    Ball ball = { 0 };
    
    player1.position = (Vector2){ 40, screenHeight/3 };
    player1.speed = (Vector2){ 0.0f, 10.0f };
    player1.size = (Vector2){ 20, screenHeight/5 };
    player1.lifes = PLAYER_LIFES;
    
    player2.position = (Vector2){ screenWidth-60, screenHeight/3 };
    player2.speed = (Vector2){ 0.0f, 10.0f };
    player2.size = (Vector2){ 20, screenHeight/5 };
    player2.lifes = PLAYER_LIFES;
    
    ball.radius = 10.0f;
    ball.active = false;
    ball.position = (Vector2){ player1.position.x + player1.size.x + ball.radius, player1.position.y + player1.size.y/2 };
    ball.speed = (Vector2){ 4.0f, 4.0f };
    
    int start = 1;
    int win_flag = 0;
    
    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        //update
        switch(screen){
            case title:
                framecounter++;
                if(IsKeyPressed(KEY_ENTER)){
                    framecounter = 0;
                    screen = instructions;
                }
                break;
            case instructions:
                framecounter++;
                if(IsKeyPressed(KEY_ENTER) || framecounter == 180)
                    screen = colors;
                break;
            case colors:
                framecounter++;
                if(IsKeyPressed(KEY_UP)){
                    if(p1color_index != 0){
                        p1color_index--;
                    }
                    else{
                        p1color_index = 4;
                    }
                }
                if(IsKeyPressed(KEY_DOWN)){
                    if(p1color_index != 4){
                        p1color_index++;
                    }
                    else{
                        p1color_index = 0;
                    }
                }
                if(IsKeyPressed(KEY_LEFT)){
                    if(p2color_index != 0){
                        p2color_index--;
                    }
                    else{
                        p2color_index = 4;
                    }
                }
                if(IsKeyPressed(KEY_RIGHT)){
                    if(p2color_index != 4){
                        p2color_index++;
                    }
                    else{
                        p2color_index = 0;
                    }
                }
                if(IsKeyPressed(KEY_ENTER)){
                    screen = game;
                }
                break;
            case game:
                framecounter++;
                if(!gamepaused){
                    
                    //player1 move
                    if (IsKeyDown(KEY_S)) player1.position.y += player1.speed.y;
                    if (IsKeyDown(KEY_W)) player1.position.y -= player1.speed.y;
                    if ((player1.position.y) <= 0) player1.position.y = 0;
                    if((player1.position.y + player1.size.y) > screenHeight) player1.position.y = screenHeight - player1.size.y;
                    
                    //player2 move
                    if (IsKeyDown(KEY_DOWN)) player2.position.y += player2.speed.y;
                    if (IsKeyDown(KEY_UP)) player2.position.y -= player2.speed.y;
                    if ((player2.position.y) <= 0) player2.position.y = 0;
                    if((player2.position.y + player2.size.y) > screenHeight) player2.position.y = screenHeight - player2.size.y;
                    
                    player1.bounds = (Rectangle){ player1.position.x, player1.position.y, player1.size.x, player1.size.y };
                    player2.bounds = (Rectangle){ player2.position.x, player2.position.y, player2.size.x, player2.size.y };
                    
                    if (ball.active){
                        
                        // Collision logic: ball vs screen-limits
                        if ((ball.position.y - ball.radius) <= 0 || (ball.position.y + ball.radius) >= screenHeight)
                            ball.speed.y *= -1;
                        
                        // Collision logic: ball vs player
                        if (CheckCollisionCircleRec( ball.position, ball.radius, player1.bounds)){
                            ball.speed.x *= -1.03;
                            ball.speed.y = (ball.position.y - (player1.position.y + player1.size.y/2))/player1.size.y*5.0f;
                        }
                        if (CheckCollisionCircleRec( ball.position, ball.radius, player2.bounds)){
                            ball.speed.x *= -1.03;
                            ball.speed.y = (ball.position.y - (player2.position.y + player2.size.y/2))/player2.size.y*5.0f;
                        }
                        // Ball movement logic
                        ball.position.x += ball.speed.x;
                        ball.position.y += ball.speed.y;
                        
                        if ((ball.position.x - ball.radius) >= screenWidth){
                            ball.position.y = player2.position.y + player2.size.y/2;
                            ball.position.x = player2.position.x - ball.radius - 1.0f;
                            ball.speed = (Vector2){ 0, 0 };
                            ball.active = false;

                            player2.lifes--;
                            start = 2;
                        }
                        
                        if ((ball.position.x + ball.radius) < 0){
                            ball.position.y = player1.position.y + player1.size.y/2;
                            ball.position.x = player1.position.x + ball.radius + 1.0f;
                            ball.speed = (Vector2){ 0, 0 };
                            ball.active = false;

                            player1.lifes--;
                            start = 1;
                        }
                        
                        if (player1.lifes < 0){
                            screen = credits;
                            win_flag = 2;
                            player1.lifes = 3;
                            player2.lifes = 3;
                            framecounter = 0;
                        }
                        if (player2.lifes < 0){
                            screen = credits;
                            win_flag = 1;
                            player1.lifes = 3;
                            player2.lifes = 3;
                            framecounter = 0;
                        }
                    }
                    else{
                        // Reset ball position
                        if(start == 1){
                            ball.position.x = player1.position.x + player1.size.x + ball.radius;
                            ball.position.y = player1.position.y + player1.size.y/2;
                            
                            if (IsKeyPressed(KEY_SPACE)){
                                // Activate ball logic
                                ball.active = true;
                                ball.speed = (Vector2){ 5.0f , 0 };
                            }
                        }
                        if(start == 2){
                            ball.position.x = player2.position.x - ball.radius;
                            ball.position.y = player2.position.y + player2.size.y/2;
                            
                            if (IsKeyPressed(KEY_SPACE)){
                                // Activate ball logic
                                ball.active = true;
                                ball.speed = (Vector2){ -5.0f , 0 };
                            }
                        }
                    }
                }
                if (IsKeyPressed(KEY_ENTER))
                    screen = credits;
                break;
            case credits:
                framecounter++;
                if(IsKeyPressed(KEY_ENTER))
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
                    DrawTextEx(font[0], "PONG", (Vector2){(screenWidth/2)-75, (screenHeight/2)-70 }, 60, 4, RED);
                    DrawTextEx(font[0], "By Aly", (Vector2){(screenWidth/2)-60, (screenHeight/2)+20}, 34, 4, RED);
                    if((framecounter/30)%2 == 0){

                        DrawTextEx(font[0], "PRESS [ENTER] to START", (Vector2){screenWidth/2-120 , 3*screenHeight/4}, 20, 2, MAROON);
                    }
                    break;
                case instructions:
                    DrawTextEx( font[0], "Instructions", (Vector2){ (screenWidth/3)+10, (screenHeight/5) }, 50, 4, GREEN);
                    DrawTextEx(font[1], "Player 1", (Vector2){ (screenWidth/4-70), (screenHeight/3+30) }, 28, 2, RED);
                    DrawTextEx(font[1], "W = UP", (Vector2){ (screenWidth/4-70), (screenHeight/2+30) }, 28, 2, RED);
                    DrawTextEx(font[1], "S = DOWN", (Vector2){ (screenWidth/4-70), (screenHeight/2+60) }, 28, 2, RED);
                    DrawTextEx(font[1], "Player 2", (Vector2){ (3*screenWidth/4-70), (screenHeight/3+30) }, 28, 2, BLUE);
                    DrawTextEx(font[1], "UP Arrow Key = UP", (Vector2){ (3*screenWidth/4-140), (screenHeight/2+30) }, 28, 2, BLUE);
                    DrawTextEx(font[1], "DOWN Arrow Key = DOWN", (Vector2){ (3*screenWidth/4-180), (screenHeight/2+60) }, 28, 2, BLUE);
                    break;
                case colors:
                    DrawRectangleGradientH(0, 0, 30, screenHeight, gradient1[p1color_index], gradient2[p1color_index]);
                    DrawRectangleGradientH(screenWidth-30, 0, 30, screenHeight, gradient2[p2color_index], gradient1[p2color_index]);
                    
                    DrawTextEx(font[0], "Choose Color for Player 1", (Vector2){screenHeight/2 - 170, screenHeight/2 - 140}, 26, 3, color_arr[p1color_index]);
                    
                    
                    DrawLineEx((Vector2){screenWidth/2-200, screenHeight/2+80}, (Vector2){screenWidth/2-200, screenHeight/2}, 4.0f, color_arr[p1color_index]);
                    DrawLineEx((Vector2){screenWidth/2-200, screenHeight/2}, (Vector2){screenWidth/2-220, screenHeight/2+20}, 4.0f, color_arr[p1color_index]);
                    DrawLineEx((Vector2){screenWidth/2-200, screenHeight/2}, (Vector2){screenWidth/2-180, screenHeight/2+20}, 4.0f, color_arr[p1color_index]);
                    DrawLineEx((Vector2){screenWidth/2-200, screenHeight/2+80}, (Vector2){screenWidth/2-220, screenHeight/2+60}, 4.0f, color_arr[p1color_index]);
                    DrawLineEx((Vector2){screenWidth/2-200, screenHeight/2+80}, (Vector2){screenWidth/2-180, screenHeight/2+60}, 4.0f, color_arr[p1color_index]);
                    
                    DrawTextEx(font[0], "Choose Color for Player 2", (Vector2){screenHeight/2 + 260, screenHeight/2 - 140}, 26, 3, color_arr[p2color_index]);
                    
                    DrawLineEx((Vector2){screenWidth/2+190, screenHeight/2+30}, (Vector2){screenWidth/2+270, screenHeight/2+30}, 4.0f, color_arr[p2color_index]);
                    DrawLineEx((Vector2){screenWidth/2+190, screenHeight/2+30}, (Vector2){screenWidth/2+210, screenHeight/2+50}, 4.0f, color_arr[p2color_index]);
                    DrawLineEx((Vector2){screenWidth/2+190, screenHeight/2+30}, (Vector2){screenWidth/2+210, screenHeight/2+10}, 4.0f, color_arr[p2color_index]);
                    DrawLineEx((Vector2){screenWidth/2+270, screenHeight/2+30}, (Vector2){screenWidth/2+250, screenHeight/2+50}, 4.0f, color_arr[p2color_index]);
                    DrawLineEx((Vector2){screenWidth/2+270, screenHeight/2+30}, (Vector2){screenWidth/2+250, screenHeight/2+10}, 4.0f, color_arr[p2color_index]);
                    
                    if((framecounter/30)%2 == 0){
                        DrawTextEx(font[1], "PRESS [ENTER] to CONTINUE", (Vector2){screenWidth/2-150 , 3*screenHeight/4}, 24, 2, RAYWHITE);
                    }
                    break;
                case game:
                    DrawRectangleGradientH(0, 0, 30, screenHeight, gradient1[p1color_index], gradient2[p1color_index]);
                    DrawRectangleGradientH(screenWidth-30, 0, 30, screenHeight, gradient2[p2color_index], gradient1[p2color_index]);
                    for(int i = 0; i < 30; i++){
                        DrawRectangle(screenWidth/2-10, 5 + i*25, 5, 15, RAYWHITE);
                    }
                    DrawRectangleRounded(player1.bounds, 5.0f, 10, color_arr[p1color_index]);
                    DrawRectangleRounded(player2.bounds, 5.0f, 10, color_arr[p2color_index]);
                    DrawCircleV(ball.position, ball.radius, MAROON);
                    for (int i = 0; i < player1.lifes; i++){
                        DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, LIGHTGRAY);
                    }
                    for (int i = player2.lifes; i > 0; i--){
                        DrawRectangle(screenWidth - (20 + 40*i), screenHeight - 30, 35, 10, LIGHTGRAY);
                    } 
                    break;
                case credits:
                    DrawTextEx( font[0], "CREDITS", (Vector2){ (screenWidth/2)-85, (screenHeight/2)-50 }, 40, 4, RAYWHITE);
                    DrawTextEx(font[1], "Designer, Producer, Editor and Director", (Vector2){ (screenWidth/3)-100, (screenHeight/1.5) }, 28, 2, RED);
                    DrawTextEx(font[0], "ALY", (Vector2){ (screenWidth/2)-40, (screenHeight/2)+30 } , 32, 4, RED);
                    if(win_flag == 1){
                        DrawTextEx( font[1], "PLAYER 1 WINS!", (Vector2){ (screenWidth/2)-130, (screenHeight/4)-20 }, 36, 2, color_arr[p1color_index]);
                    }
                    else{
                        if(win_flag == 0)
                            break;
                        DrawTextEx(font[1], "PLAYER 2 WINS!", (Vector2){ (screenWidth/2)-130, (screenHeight/4)-20 }, 36, 2, color_arr[p2color_index]);
                    }
                    break;
                default: break;
            }
        EndDrawing();
    }
    for(int i = 0; i<2;i++) UnloadFont(font[i]);
    CloseWindow();
    return 0;
}