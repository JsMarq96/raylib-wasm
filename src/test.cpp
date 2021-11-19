/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>

#include <stdio.h>

//#define PLATFORM_WEB
#include <emscripten/emscripten.h>
//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int EMSCRIPTEN_KEEPALIVE main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // NOTE: screenWidth/screenHeight should match VR device aspect ratio
    InitWindow(screenWidth, screenHeight, "raylib [core] example - vr simulator");

    RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 2.0f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FIRST_PERSON);         // Set first person camera mode

    SetTargetFPS(90);
    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
 extern "C" void EMSCRIPTEN_KEEPALIVE UpdateDrawFrame(float position_x,
                                                      float position_y,
                                                      float position_z) {
    Camera camera = { 0 };
    camera.position = (Vector3){ position_x, position_y, position_z };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FIRST_PERSON);         // Set first person camera mode

    // VR device parameters definition
    VrDeviceInfo device = {
        // Oculus Rift CV1 parameters for simulator
        .hResolution = 2160,                 // Horizontal resolution in pixels
        .vResolution = 1200,                 // Vertical resolution in pixels
        .hScreenSize = 0.133793f,            // Horizontal size in meters
        .vScreenSize = 0.0669f,              // Vertical size in meters
        .vScreenCenter = 0.04678f,           // Screen center in meters
        .eyeToScreenDistance = 0.041f,       // Distance between eye and display in meters
        .lensSeparationDistance = 0.07f,     // Lens separation distance in meters
        .interpupillaryDistance = 0.07f,     // IPD (distance between pupils) in meters
    };

    // Load VR stereo config for VR device parameteres (Oculus Rift CV1 parameters)
    VrStereoConfig config = LoadVrStereoConfig(device);

    BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginVrStereoMode(config);
                BeginMode3D(camera);

                DrawCube({0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, RED);
                   // DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                    DrawGrid(40, 1.0f);

                EndMode3D();
            EndVrStereoMode();
    EndDrawing();
    //----------------------------------------------------------------------------------
}


extern "C" void EMSCRIPTEN_KEEPALIVE init_draw_instance() {
    printf("Test");
    //InitWindow(800, 450, "raylib [core] example - basic window");
}

void close_draw_instance() {
    printf("Close");
    CloseWindow();
}
