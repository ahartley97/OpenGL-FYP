#include "SceneSettings.h"

//Updates the delta time value
void SceneSettings::updateDT()
{
    currentTime = static_cast<float>(glfwGetTime());
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}

//Preforms the day and night cycle
void SceneSettings::DayNightCycle()
{
    if (isdncycle)
    {
        if (!waitToCycle)
        {
            dnCycleBrightness += dnCycleSpeed * deltaTime;
            if (dnCycleBrightness >= 0.9f || dnCycleBrightness <= 0.03f)
            {
                dnCycleSpeed = dnCycleSpeed * -1;
                waitToCycle = true;
            }

        }
        else if (waitToCycle)
        {
            waitCounter += 1.0f * deltaTime;
            if (waitCounter >= lengthOfDayNight)
            {
                waitCounter = 0.0f;
                waitToCycle = false;
            }
        }
    }
}

//Checks if the app should exit
void SceneSettings::CheckShouldAppClose(GLFWwindow* window)
{
    if (exitApp)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

//Checks if the scene is wireframe
void SceneSettings::CheckWireframe()
{
    if (wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (!wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

//Checks what the screen size is
void SceneSettings::CheckFullScreen(Camera& cam, GLFWwindow* window)
{
    if (fullscreen)
    {
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate);
        cam.updateWindowSize(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height);
        screenHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
        screenWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    }
    else if (!fullscreen)
    {
        glfwSetWindowMonitor(window, nullptr, 100, 100, 800, 600, NULL);
        cam.updateWindowSize(800, 600);
        screenHeight = 600;
        screenWidth = 800;
    }
}

void SceneSettings::SceneRender(Camera& cam, GLFWwindow* window)
{
    updateDT();
    DayNightCycle();
    CheckShouldAppClose(window);
    CheckWireframe();
    CheckFullScreen(cam, window);
}
