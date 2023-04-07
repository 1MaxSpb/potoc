#include <iostream>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
int angle;

#include "extras/raygui.h"

#define NUM_PROCESSES    9


static void DrawStyleEditControls(void);  // Draw and process scroll bar style edition controls

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //---------------------------------------------------------------------------------------
    const int screenWidth = 1850;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raygui - GuiScrollPanel()");
    int display = GetCurrentMonitor();
//    SetWindowSize(GetMonitorWidth(display) * 0.8, GetMonitorHeight(display) * 0.8);

    Image imOrigin = LoadImage("photo_5296793118605166275_y.png");   // Loaded in CPU memory (RAM)
    std::cout << imOrigin.width << ' ' << imOrigin.height;


    ImageFormat(&imOrigin,
                PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);         // Format image to RGBA 32bit (required for texture update) <-- ISSUE


    Image imCopy = ImageCopy(imOrigin);


    bool textureReload = false;

//    Rectangle toggleRecs[NUM_PROCESSES] = {0};
    int mouseHoverRec = -1;

//    for (int i = 0; i < NUM_PROCESSES; i++) toggleRecs[i] = (Rectangle) {40.0f, (float) (50 + 32 * i), 150.0f, 30.0f};
    Texture2D texture = LoadTextureFromImage(imCopy);


    bool showContentArea = true;

    SetTargetFPS(60);
    float contrast = 0;
    float brightness = 0;
    float r = 100;
    float g = 100;
    float b = 100;
    float a = 255;
    float save = 0;

    //-----------------------------------------------------------------------
    // ----------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        UpdateTexture(texture, imCopy.data);
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
//        angle = 0.04;
        //----------------------------------------------------------------------------------


//        UnloadImage(imCopy);                // Unload image-copy data
//        imCopy = ImageCopy(imOrigin);     // Restore image-copy from image-origin

        // NOTE: Image processing is a costly CPU process to be done every frame,
        // If image processing is required in a frame-basis, it should be done
        // with a texture and by shaders
        //        ImageColorGrayscale(&imCopy);

        imCopy = ImageCopy(imOrigin);
        ImageColorTint(&imCopy, (Color) {r, g, b, a});
        //     ImageColorInvert(&imCopy);
        ImageColorContrast(&imCopy, contrast);
        ImageColorBrightness(&imCopy, brightness);

        textureReload = false;

        BeginDrawing();

        ClearBackground(WHITE);

        // Draw rectangles

        DrawTexture(texture, screenWidth - texture.width - 60, screenHeight / 2 - texture.height / 2, WHITE);
        r = GuiSliderBar((Rectangle) {590, 410 + 16, 145, 15}, "Red",
                         TextFormat("%i", (int) r),
                         r, 1,
                         255);
        g = GuiSliderBar((Rectangle) {590, 410 + 16 * 2, 145, 15}, "Green",
                         TextFormat("%i", (int) g),
                         g, 1,
                         255);
        b = GuiSliderBar((Rectangle) {590, 410 + 16 * 3, 145, 15}, "Blue",
                         TextFormat("%i", (int) b),
                         b, 1,
                         255);
        a = GuiSliderBar((Rectangle) {590, 410 + 16 * 4, 145, 15}, " Depth",
                         TextFormat("%i", (int) a),
                         a, 1,
                         255);

        contrast = GuiSliderBar((Rectangle) {590, 385, 145, 15}, "Contrast",
                                TextFormat("%i", (int) contrast),
                                contrast, 1,
                                100);
        brightness = GuiSliderBar((Rectangle) {590, 410, 145, 15}, "Brightness",
                                  TextFormat("%i", (int) brightness),
                                  brightness, 1,
                                  5);
//        panelContentRec.hne = GuiSliderBar((Rectangle) {590, 435, 145, 15}, "hne",
//                                           TextFormat("%i", (int) panelContentRec.hne), panelContentRec.hne, 1, 400);
        save = GuiSliderBar((Rectangle) {590, 410 + 16 * 5, 145, 15}, "save",
                         TextFormat("%i", (int) save),
                         a, 0,
                         1);




        //-----------------------------------------------------------------

        EndDrawing();
        if(IsKeyPressed(KEY_SPACE))
        {
            ExportImage(imCopy, "my_file.png");
        }
    }

    UnloadTexture(texture);       // Unload texture from VRAM
    UnloadImage(imOrigin);        // Unload image-origin from RAM
    UnloadImage(imCopy);


    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------



    return 0;
}
