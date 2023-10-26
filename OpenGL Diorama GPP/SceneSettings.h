#pragma once

// Include external headers
#include "ExternalHeaders.h"

// Class for scene settings
class SceneSettings
{
public:
    // Public member variables for screen dimensions, time, day/night cycle settings, wireframe mode, fullscreen mode, and exit status
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // Width of the screen in pixels
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // Height of the screen in pixels
    float deltaTime = 0.0f;                          // Time elapsed since the last frame
    float currentTime = 0.0f;                        // Current time in seconds
    float lastTime = 0.0f;                           // Time of the last frame in seconds
    bool isdncycle = true;                           // Flag for whether or not to perform day/night cycle
    bool waitToCycle = false;                        // Flag for whether or not to wait before starting the day/night cycle
    float waitCounter = 0.0f;                        // Time remaining to wait before starting the day/night cycle
    float lengthOfDayNight = 30.0f;                  // Length of the day/night cycle in seconds
    float dnCycleBrightness = 0.5f;                  // Brightness of the scene during the day/night cycle
    float dnCycleSpeed = 0.01f;                      // Speed of the day/night cycle
    bool wireframe = false;                          // Flag for whether or not to render the scene in wireframe mode
    bool fullscreen = true;                          // Flag for whether or not to render the scene in fullscreen mode
    bool exitApp = false;                            // Flag for whether or not to exit the application

    // Methods for updating delta time, performing the day/night cycle, checking if the application should close, toggling wireframe mode, toggling fullscreen mode, and rendering the scene
    void updateDT();
    void DayNightCycle();
    void CheckShouldAppClose(GLFWwindow* window);
    void CheckWireframe();
    void CheckFullScreen(Camera& cam, GLFWwindow* window);
    void SceneRender(Camera& cam, GLFWwindow* window);
};
