#define SDL_MAIN_USE_CALLBACKS

#define CLAY_IMPLEMENTATION
#include <clay/clay.h>

#include <clay/renderers/clay_renderer_raylib.c>


void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

void DebugTreeDebugger() {

}

int main(void) {
    Clay_Raylib_Initialize(1024, 768, "Introducing Clay Demo", FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT); // Extra parameters to this function are new since the video was published

    Font fonts[1];
    fonts[0] = LoadFontEx("resources/Roboto-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();

    Clay_Arena clayMemoryTop = Clay_CreateArenaWithCapacityAndMemory(clayRequiredMemory, new char[clayRequiredMemory]);
    Clay_Context *clayContextTop = Clay_Initialize(clayMemoryTop, Clay_Dimensions{
       .width = (float)GetScreenWidth(),
       .height = (float)GetScreenHeight() / 2
    }, Clay_ErrorHandler{ HandleClayErrors }); // This final argument is new since the video was published
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    Clay_Arena clayMemoryBottom = Clay_CreateArenaWithCapacityAndMemory(clayRequiredMemory, malloc(clayRequiredMemory));
    Clay_Context *clayContextBottom = Clay_Initialize(clayMemoryBottom, Clay_Dimensions{
            .width = (float)GetScreenWidth(),
            .height = (float)GetScreenHeight() / 2
    }, Clay_ErrorHandler{ HandleClayErrors }); // This final argument is new since the video was published
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        Clay_SetDebugModeEnabled(true);
        // Run once per frame
        Clay_SetLayoutDimensions(Clay_Dimensions{
                .width = (float)GetScreenWidth(),
                .height = (float)GetScreenHeight() / 2
        });
        Vector2 mousePosition = GetMousePosition();
        Vector2 scrollDelta = GetMouseWheelMoveV();
        Clay_SetPointerState(
                Clay_Vector2{ mousePosition.x, mousePosition.y },
                IsMouseButtonDown(0)
        );
        Clay_UpdateScrollContainers(
                true,
                Clay_Vector2{ scrollDelta.x, scrollDelta.y },
                GetFrameTime()
        );

        //Clay_Raylib_Render(commands, fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
}