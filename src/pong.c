#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#define PLAYER_LIFES    3

typedef enum GameScreen{ title, instructions, mode, difficulty, colors, game, credits } GameScreen;

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

typedef struct Effect{
    Vector2 position;
    Vector2 size;
    Color top;
    Color bottom;
    int colorindex; // whose color?
    bool isActive;
} Effect;

typedef enum Difficulty{ easy, normal, hard } Difficulty;

int main(){
    const int screenWidth = 1000;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Project: Pong");
    InitAudioDevice();
    // SetWindowState(FLAG_WINDOW_UNDECORATED);
    
    GameScreen screen = title;
    
    Font font[2] = { 0 };
    font[0] = LoadFont("resources/fonts/pixantiqua.png");
    font[1] = LoadFont("resources/fonts/alagard.png");
    
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
    
    player1.position = (Vector2){ 80, screenHeight/3 };
    player1.speed = (Vector2){ 0.0f, 8.0f };
    player1.size = (Vector2){ 20, screenHeight/5 };
    player1.lifes = PLAYER_LIFES;
    
    player2.position = (Vector2){ screenWidth-100, screenHeight/3 };
    player2.speed = (Vector2){ 0.0f, 8.0f };
    player2.size = (Vector2){ 20, screenHeight/5 };
    player2.lifes = PLAYER_LIFES;
    
    ball.radius = 15.0f;
    ball.active = false;
    ball.position = (Vector2){ player1.position.x + player1.size.x + ball.radius, player1.position.y + player1.size.y/2 };
    ball.speed = (Vector2){ 4.0f, 4.0f };
    
    Effect effect;
    effect.position.x = 0;
    effect.size = (Vector2){ screenWidth , 5 };
    effect.isActive = false;
    int effectStarted = 0;
    
    Difficulty diff = easy;
    
    int start = 2;
    int win_flag = 0;
    int isPVP = 0;
    
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
                    screen = mode;
                break;
            case mode:
                if(IsKeyPressed(KEY_DOWN)){
                        isPVP = 1;
                }
                if(IsKeyPressed(KEY_UP)){
                    isPVP = 0;
                }
                if(IsKeyPressed(KEY_ENTER) && isPVP == 0){
                    framecounter = 0;
                    screen = difficulty;
                }
                if(IsKeyPressed(KEY_ENTER) && isPVP == 1){
                    framecounter = 0;
                    screen = colors;
                }
                break;
            case difficulty:
                if(IsKeyPressed(KEY_DOWN)){
                    if(diff != hard){
                        diff++;
                    }
                    else{
                        diff = easy;
                    }
                }
                if(IsKeyPressed(KEY_UP)){
                    if(diff != easy){
                        diff--;
                    }
                    else{
                        diff = hard;
                    }
                }
                if(IsKeyPressed(KEY_ENTER)){
                    framecounter = 0;
                    screen = colors;
                }
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
                    framecounter = 1;
                    screen = game;
                }
                break;
            case game:
                framecounter++;
                
                if(gamepaused){
                    if(IsKeyPressed(KEY_P)){
                        gamepaused = false;
                    }
                }
                else{
                    if(IsKeyPressed(KEY_P)){
                        gamepaused = true;
                    }
                    //player1 move
                    if (IsKeyDown(KEY_S)) player1.position.y += player1.speed.y;
                    if (IsKeyDown(KEY_W)) player1.position.y -= player1.speed.y;
                    if ((player1.position.y) <= 0) player1.position.y = 0;
                    if((player1.position.y + player1.size.y) > screenHeight) player1.position.y = screenHeight - player1.size.y;
                    
                    if(isPVP == 1){
                        //player2 move
                        if (IsKeyDown(KEY_DOWN)) player2.position.y += player2.speed.y;
                        if (IsKeyDown(KEY_UP)) player2.position.y -= player2.speed.y;
                        if ((player2.position.y) <= 0) player2.position.y = 0;
                        if((player2.position.y + player2.size.y) > screenHeight) player2.position.y = screenHeight - player2.size.y;                        
                    }
                    if(isPVP == 0){
                        //bot logic
                        if(ball.speed.x > 0){
                            float predictedY = ball.position.y + ((screenWidth - ball.position.x) / ball.speed.x) * ball.speed.y;
                            
                            if(predictedY < 0)  predictedY = 0;
                            if(predictedY > screenHeight)  predictedY = screenHeight;
                            
                            float reactspeed = 0.5f;
                            float errormargin = 0.0f;
                            
                            switch(diff){
                                case easy:
                                    reactspeed = 0.3f;
                                    errormargin = (rand() % 40) - 20;
                                    break;
                                case normal:
                                    reactspeed = 0.6f;
                                    errormargin = (rand() % 10) - 5;
                                    break;
                                case hard:
                                    reactspeed = 1.0f;
                                    errormargin = 0.0f;
                                    break;
                            }
                            predictedY += errormargin;
                            if( player2.position.y + player2.size.y / 2 < predictedY - 10 ){
                                        player2.position.y += player2.speed.y * reactspeed;
                                    }
                            else{
                                if( player2.position.y + player2.size.y / 2 > predictedY + 10 ){
                                    player2.position.y -= player2.speed.y * reactspeed;
                                }
                            }
                            if (player2.position.y < 0) player2.position.y = 0;
                            if (player2.position.y + player2.size.y > screenHeight) player2.position.y = screenHeight - player2.size.y;
                        }
                    }
                    
                    player1.bounds = (Rectangle){ player1.position.x, player1.position.y, player1.size.x, player1.size.y };
                    player2.bounds = (Rectangle){ player2.position.x, player2.position.y, player2.size.x, player2.size.y };
                    
                    if (ball.active){
                        effectStarted++;
                        if(effectStarted >= 5){
                            effect.isActive = false;
                        }
                        
                        // Collision logic: ball vs screen-limits
                        if ((ball.position.y - ball.radius) <= 0 || (ball.position.y + ball.radius) >= screenHeight){
                            ball.speed.y *= -1;
                            if(ball.position.y - ball.radius <= 0){
                                ball.position.y = ball.radius + 1.0f; // clamp inside
                            }
                            if(ball.position.y + ball.radius >= screenHeight){
                                ball.position.y = screenHeight - ball.radius - 1.0f; // clamp inside
                            }
                            // effect logic
                            if(ball.speed.x > 0) effect.colorindex = p1color_index;
                            if(ball.speed.x < 0) effect.colorindex = p2color_index;
                            if(ball.position.y > screenHeight/2){ // for the bottom screen limit
                                effect.position.y = screenHeight - effect.size.y;
                                effect.bottom = gradient1[effect.colorindex];
                                effect.top = gradient2[effect.colorindex];
                            } else{
                                effect.position.y = 0;
                                effect.bottom = gradient2[effect.colorindex];
                                effect.top = gradient1[effect.colorindex];
                            }
                            effect.isActive = true;
                            effectStarted = 0;
                        }
                        
                        // Collision logic: ball vs players
                        if( (ball.speed.x < 0) && 
                            (ball.position.x - ball.radius <= player1.position.x + player1.size.x) &&
                            (ball.position.x > player1.position.x) &&
                            (ball.position.y + ball.radius >= player1.position.y) &&
                            (ball.position.y - ball.radius <= player1.position.y + player1.size.y) ){
                            ball.speed.x *= -1.03;
                            ball.position.x = player1.position.x + player1.size.x + ball.radius + 1.0f; // clamp inside
                            ball.speed.y = (ball.position.y - (player1.position.y + player1.size.y/2))/player1.size.y * 5.0f;
                        }
                        if( (ball.speed.x > 0) && 
                            (ball.position.x + ball.radius >= player2.position.x) &&
                            (ball.position.x < player2.position.x) &&
                            (ball.position.y + ball.radius >= player2.position.y) &&
                            (ball.position.y - ball.radius <= player2.position.y + player2.size.y) ){
                            ball.speed.x *= -1.03;
                            ball.position.x = player2.position.x - ball.radius - 1.0f; // clamp inside
                            ball.speed.y = (ball.position.y - (player2.position.y + player2.size.y / 2)) / player2.size.y * 5.0f;
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
                            ball.position.x = player1.position.x + player1.size.x + ball.radius + 1.0f;
                            ball.speed = (Vector2){ 0, 0 };
                            ball.active = false;

                            player1.lifes--;
                            start = 1;
                        }
                        
                        if (player1.lifes == 0){
                            screen = credits;
                            win_flag = 2;
                            player1.lifes = 3;
                            player2.lifes = 3;
                            framecounter = 0;
                        }
                        if (player2.lifes == 0){
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
                            if( isPVP == 0 ){
                                if(framecounter % 60 == 0){
                                    ball.active = true;
                                    ball.speed = (Vector2){ -5.0f , 0 };
                                }
                            }
                        }
                    }
                }
                // if (IsKeyPressed(KEY_ENTER))
                //     screen = credits;
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
                    DrawTextEx(font[1], "SPACE to SERVE the BALL", (Vector2){screenWidth / 2 - (MeasureText("SPACE to SERVE the BALL", 24) / 2) , 3*screenHeight/4 }, 24, 2, MAROON);
                    DrawTextEx(font[1], "P to PAUSE the GAME", (Vector2){screenWidth / 2 - (MeasureText("P to PAUSE the GAME", 24) / 2) , 3*screenHeight/4 + 40}, 24, 2, MAROON);
                    break;
                case mode:
                    DrawTextEx( font[0], "Choose Mode", (Vector2){ (screenWidth/3), (screenHeight/5) }, 50, 4, MAROON);
                    
                    DrawTextEx(font[0], "Against Bot", (Vector2){ screenWidth/2-85 , screenHeight/2-40 }, 32, 2, BLUE);
                    if(isPVP == 0){
                        DrawRectangleLinesEx( (Rectangle){screenWidth/2-95 , screenHeight/2-48, MeasureTextEx( font[0], "Against Bot", 36, 2).x , 44}, 3.0f, RAYWHITE);                        
                    }
                    
                    DrawTextEx(font[0], "Player VS Player", (Vector2){ screenWidth/2-120 , screenHeight/2+40 }, 32, 2, BLUE);
                    if(isPVP == 1){
                        DrawRectangleLinesEx( (Rectangle){screenWidth/2-135 , screenHeight/2+32, MeasureTextEx( font[0], "Player VS Player", 36, 2).x , 46}, 3.0f, RAYWHITE);
                    }
                    break;
                case difficulty:
                    DrawTextEx( font[0], "Choose Difficulty", (Vector2){ (screenWidth/2 - MeasureTextEx( font[0], "Choose Difficulty", 50, 4).x/2 ), (screenHeight/5) }, 50, 4, MAROON);
                    
                    DrawTextEx(font[0], "EASY", (Vector2){ screenWidth/2 - MeasureTextEx( font[0], "EASY", 36, 2).x/2 , screenHeight/2-50 }, 36, 2, GREEN);
                    if(diff == easy){
                        DrawRectangleLinesEx( (Rectangle){screenWidth/2 - MeasureTextEx( font[0], "EASY", 36, 2).x/2 - 10 , screenHeight/2-55, MeasureTextEx( font[0], "EASY", 40, 2).x + 10 , 44}, 3.0f, RAYWHITE);                       
                    }
                    
                    DrawTextEx(font[0], "NORMAL", (Vector2){ screenWidth/2 - MeasureTextEx( font[0], "NORMAL", 36, 2).x/2  , screenHeight/2 }, 36, 2, YELLOW);
                    if(diff == normal){
                        DrawRectangleLinesEx( (Rectangle){screenWidth/2 - MeasureTextEx( font[0], "NORMAL", 36, 2).x/2 - 10 , screenHeight/2 -5, MeasureTextEx( font[0], "NORMAL", 40, 2).x + 10 , 44}, 3.0f, RAYWHITE);
                    }
                    
                    DrawTextEx(font[0], "HARD", (Vector2){ screenWidth/2 - MeasureTextEx( font[0], "HARD", 36, 2).x/2 , screenHeight/2+50 }, 36, 2, RED);
                    if(diff == hard){
                        DrawRectangleLinesEx( (Rectangle){screenWidth/2 - MeasureTextEx( font[0], "HARD", 36, 2).x/2 - 10 , screenHeight/2 +45, MeasureTextEx( font[0], "HARD", 40, 2).x + 10 , 44}, 3.0f, RAYWHITE);
                    }
                    
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
                    DrawCircleV(ball.position, ball.radius, RAYWHITE);
                    if(effect.isActive == true){
                        // DrawRectangle(effect.position.x, effect.position.y, effect.size.x, effect.size.y, effect.lastCollided);
                        DrawRectangleGradientV(effect.position.x, effect.position.y, effect.size.x, effect.size.y, effect.top, effect.bottom);
                    }
                    for (int i = 0; i < player1.lifes; i++){
                        DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, LIGHTGRAY);
                    }
                    for (int i = player2.lifes; i > 0; i--){
                        DrawRectangle(screenWidth - (20 + 40*i), screenHeight - 30, 35, 10, LIGHTGRAY);
                    }
                    if(gamepaused && (framecounter / 30) % 2 == 0)
                    {
                        DrawTextEx(font[1], "PAUSED", (Vector2){ (screenWidth/2)-70, (screenHeight/2)-20 }, 40, 4, RAYWHITE);
                    } 
                    break;
                case credits:
                    if((framecounter/30)%2 == 0){
                        DrawTextEx(font[1], "PRESS [ENTER] to go back to TITLE", (Vector2){screenWidth/2-200 , 3*screenHeight/4 + 40}, 24, 2, MAROON);
                    }
                    if(win_flag == 1){
                        Vector2 textSize = MeasureTextEx(font[1], "PLAYER 1 WINS!", 48, 2);
                        DrawTextEx( font[1], "PLAYER 1 WINS!", (Vector2){ screenWidth/2 - textSize.x/2, screenHeight/2 - textSize.y/2 }, 48, 2, color_arr[p1color_index]);
                    }
                    else{
                        if(win_flag == 0)
                            break;
                        Vector2 textSize = MeasureTextEx(font[1], "PLAYER 2 WINS!", 48, 2);
                        DrawTextEx(font[1], "PLAYER 2 WINS!", (Vector2){ screenWidth/2 - textSize.x/2, screenHeight/2 - textSize.y/2 }, 48, 2, color_arr[p2color_index]);
                    }
                    
                    break;
                default: break;
            }
        EndDrawing();
    }
    for(int i = 0; i<2;i++) UnloadFont(font[i]);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}