#include "raylib.h"
#include <cstdint>
#include <stdlib.h>
#include "AssetManager.h"


static uint16_t fps_limiter = 144;


int main() {

    AssetManager ass;

    const uint16_t screenWidth = 1600;
    const uint16_t screenHeight = 900;
    
    TraceLogLevel(LOG_DEBUG);
    const EnemyDef& ref = ass.Getenemytempref(0);
    TraceLog(LOG_DEBUG, "MAIN DEBUG:: %f",ref.damage);
    
    InitWindow(screenWidth, screenHeight, "Empty Window");
    SetTargetFPS(fps_limiter);

    float frametime = 0;

  
    while(!WindowShouldClose()){
        frametime = GetFrameTime();    
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText(std::to_string(frametime).c_str(),0,32,32,WHITE);
            DrawFPS(0,0);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}