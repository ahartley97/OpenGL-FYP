#define _USE_MATH_DEFINES
#include "ExternalHeaders.h"
#include "SceneSettings.h"
#include "SceneRenderer.h"
#include "Model.h"

int main()
{
    //------------Initial Set-up

    SceneSettings sceneConfig;
    SceneRenderer sceneRend;

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window and make the window's context current
    GLFWwindow* window = glfwCreateWindow(sceneConfig.screenWidth, sceneConfig.screenHeight, "OpenGL Diorama GPP - Andrew Hartley", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);
    
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // Handle initialization failure
        return -1;
    }
    
    //Lock the mouse cursor into the window
    glViewport(0, 0, sceneConfig.screenWidth, sceneConfig.screenHeight);

    //Defining the light positions for the lanturns
    glm::vec4 lightColor = glm::vec4(0.851f, 0.694, 0.141, 1.0f);
    glm::vec3 lightPos1 = glm::vec3(20.0f, 7.0f, -55.0f);
    glm::vec3 lightPos2 = glm::vec3(47.0f, 7.0f, -32.0f);
    glm::vec3 lightPos3 = glm::vec3(22.0f, 7.0f, 50.0f);
    glm::vec3 lightPos4 = glm::vec3(-47.0f, 7.0f, -23.0f);

    //Creating the Camera
    Camera cam(sceneConfig.screenWidth, sceneConfig.screenHeight, glm::vec3(0.0f, 50.0f, 0.0f));

    //Created the ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //----------Creating Meshes:

    //Creating the Tent model
    Shader tentShader("model.vert", "model.frag");
    Model Tent("Assets/Tent/FANTASY_HOUSEP.obj");
    glUniform4f(glGetUniformLocation(tentShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    int location_tentBrightness = glGetUniformLocation(tentShader.ID, "brightness");

    //Creating Trees
    Shader treeShader("model.vert", "model.frag");
    Model Tree("Assets/Tree/Tree1/Col_1_tree_6.obj");
    glUniform4f(glGetUniformLocation(treeShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    int location_treeBrightness = glGetUniformLocation(treeShader.ID, "brightness");

    //Creating Lanturns
    Shader lanternShader("lantern.vert", "lantern.frag");
    glUniform4f(glGetUniformLocation(lanternShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    Model Lantern("Assets/Lantern/objLamp.obj");
    int location_lanternBrightness = glGetUniformLocation(lanternShader.ID, "brightness");

    //This Creates and fills the vectors which hold all of the model vectors
    sceneRend.PopulatePositionVectors();

    //--------------------Creating the Terrain
    Shader TshaderProgram("default.vert", "default.frag");
    Terrain terrain;
    GLuint Tvao;

    //This loads the heighmap from an image and uses that too populate the posititons vector
    terrain.loadHeightmap();
    terrain.populateVectors();

    //Creating and assigning the VBO and EBO
    GLuint TerCoordsvbo;
    glGenBuffers(1, &TerCoordsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, TerCoordsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * terrain.GrassCoords.size(), terrain.GrassCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint TerColorsvbo;
    glGenBuffers(1, &TerColorsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, TerColorsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * terrain.GrassColors.size(), terrain.GrassColors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint TerTexcoordsvbo;
    glGenBuffers(1, &TerTexcoordsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, TerTexcoordsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * terrain.GrassTexCoords.size(), terrain.GrassTexCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint Ternormalsvbo;
    glGenBuffers(1, &Ternormalsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, Ternormalsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * terrain.GrassNormals.size(), terrain.GrassNormals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint Tebo;
    glGenBuffers(1, &Tebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Tebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * terrain.GrassIndices.size(), terrain.GrassIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &Tvao);
    glBindVertexArray(Tvao);

    glBindBuffer(GL_ARRAY_BUFFER, TerCoordsvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, TerColorsvbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, TerTexcoordsvbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, Ternormalsvbo);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Tebo);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //This creates two differernt textures, one for the diffuse and one for the specular
    TextureClass grassTex("grass.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    grassTex.texUnit(TshaderProgram, "tex0", 0);
    TextureClass grassSpec("grass_spec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    grassSpec.texUnit(TshaderProgram, "tex1", 1);
    
    //This activates the shader and assigns the model position, light colour and brightness
    TshaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(TshaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(terrain.terrainModel));
    glUniform4f(glGetUniformLocation(TshaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    int location_terrainBrightness = glGetUniformLocation(TshaderProgram.ID, "brightness");
    //-------------------Finished Creating the terrain

    //----------------------Creating the Water

    //Initialising the shaders for the water
    Shader WshaderProgram("water.vert", "water.frag");
    Water water;
    GLuint Wvao;

    //Allocating space for the relection and refraction buffers
    int reflectionFrameBuffer;
    int reflectionTexture;
    int reflectionDepthBuffer;
    int refractionFrameBuffer;
    int refractionTexture;
    int refractionDepthTexture;
    
    //Loading the DuDv map as a texture
    TextureClass dudvTexture("waterDUDV.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    dudvTexture.texUnit(WshaderProgram, "dudvMap", 2);

    //This function fills the verts with coordinates and texure coordinates
    water.populateVerts();
        
    //Set the VBO and EBO for the water
    GLuint WatCoordsvbo;
    glGenBuffers(1, &WatCoordsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, WatCoordsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * water.WaterCoords.size(), water.WaterCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint WatColorsvbo;
    glGenBuffers(1, &WatColorsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, WatColorsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * water.WaterColors.size(), water.WaterColors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint WatTexcoordsvbo;
    glGenBuffers(1, &WatTexcoordsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, WatTexcoordsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * water.WaterTexCoords.size(), water.WaterTexCoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint WatNormalsvbo;
    glGenBuffers(1, &WatNormalsvbo);
    glBindBuffer(GL_ARRAY_BUFFER, WatNormalsvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * water.WaterNormals.size(), water.WaterNormals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint Webo;
    glGenBuffers(1, &Webo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Webo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * water.WaterIndices.size(), water.WaterIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Bind to the VAO
    glGenVertexArrays(1, &Wvao);
    glBindVertexArray(Wvao);

    glBindBuffer(GL_ARRAY_BUFFER, WatCoordsvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, WatColorsvbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, WatTexcoordsvbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, WatNormalsvbo);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Webo);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //-------------Reflection Frame Buffer----------------
    GLuint reflframeBuffer;
    glGenFramebuffers(1, &reflframeBuffer);
    //generate name for frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, reflframeBuffer);
    //create the framebuffer
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    //indicate that we will always render to color attachment 
    reflectionFrameBuffer = reflframeBuffer;

    GLuint refltexture;
    glGenTextures(1, &refltexture);
    glBindTexture(GL_TEXTURE_2D, refltexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, water.REFLECTION_WIDTH, water.REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refltexture, 0);
    reflectionTexture = refltexture;

    GLuint refldepthBuffer;
    glGenRenderbuffers(1, &refldepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, refldepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, water.REFLECTION_WIDTH, water.REFLECTION_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, refldepthBuffer);
    reflectionDepthBuffer = refldepthBuffer;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, sceneConfig.screenWidth, sceneConfig.screenHeight);

    //-------------Refraction Frame Buffer----------------

    GLuint refrframeBuffer;
    glGenFramebuffers(1, &refrframeBuffer);
    //generate name for frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, refrframeBuffer);
    //create the framebuffer
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    //indicate that we will always render to color attachment 
    refractionFrameBuffer = refrframeBuffer;

    GLuint refrtexture;
    glGenTextures(1, &refrtexture);
    glBindTexture(GL_TEXTURE_2D, refrtexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, water.REFRACTION_WIDTH, water.REFRACTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refrtexture, 0);
    refractionTexture = refrtexture;

    GLuint refrdepthBuffer;
    glGenRenderbuffers(1, &refrdepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, refrdepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, water.REFRACTION_WIDTH, water.REFRACTION_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, refrdepthBuffer);
    refractionDepthTexture = refrdepthBuffer;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, sceneConfig.screenWidth, sceneConfig.screenHeight);

    //Activate the shader for the water and add the model vector and light colour to the shader
    WshaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(WshaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(water.waterModel));
    glUniform4f(glGetUniformLocation(WshaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    //Get the location of the shader variables that effect the water reflection
    water.location_reflectionTexture = glGetUniformLocation(WshaderProgram.ID, "reflectionTexture");
    water.location_refractionTexture = glGetUniformLocation(WshaderProgram.ID, "refractionTexture");
    water.location_dudvMap = glGetUniformLocation(WshaderProgram.ID, "dudvMap");
    water.location_moveFactor = glGetUniformLocation(WshaderProgram.ID, "moveFactor");

    //-------------Finished Creating the water

    //-----------------Creating the Skybox

    //Defining the verts for the skybox
    GLfloat skyboxVerts[] =
    {
        -10.0f,  10.0f, -10.0f,
        -10.0f, -10.0f, -10.0f,
         10.0f, -10.0f, -10.0f,
         10.0f, -10.0f, -10.0f,
         10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,

        -10.0f, -10.0f,  10.0f,
        -10.0f, -10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f,  10.0f,
        -10.0f, -10.0f,  10.0f,

         10.0f, -10.0f, -10.0f,
         10.0f, -10.0f,  10.0f,
         10.0f,  10.0f,  10.0f,
         10.0f,  10.0f,  10.0f,
         10.0f,  10.0f, -10.0f,
         10.0f, -10.0f, -10.0f,

        -10.0f, -10.0f,  10.0f,
        -10.0f,  10.0f,  10.0f,
         10.0f,  10.0f,  10.0f,
         10.0f,  10.0f,  10.0f,
         10.0f, -10.0f,  10.0f,
        -10.0f, -10.0f,  10.0f,

        -10.0f,  10.0f, -10.0f,
         10.0f,  10.0f, -10.0f,
         10.0f,  10.0f,  10.0f,
         10.0f,  10.0f,  10.0f,
        -10.0f,  10.0f,  10.0f,
        -10.0f,  10.0f, -10.0f,

        -10.0f, -10.0f, -10.0f,
        -10.0f, -10.0f,  10.0f,
         10.0f, -10.0f, -10.0f,
         10.0f, -10.0f, -10.0f,
        -10.0f, -10.0f,  10.0f,
         10.0f, -10.0f,  10.0f
    };

    //Create an instance of the skybox class
    Skybox skybox;
    skybox.Initialise();

    //Load day skybox texture from files
    unsigned char* skyboxTextures[6];
    int width, height, nrChannels;
    for (int i = 0; i < 6; i++) {
        unsigned char* data = stbi_load(skybox.skyboxTexnames[i].c_str(), &width, &height, &nrChannels, 0);
        skyboxTextures[i] = data;
    }

    //Load night skybox texture from files
    unsigned char* NightSkyboxTextures[6];
    int Nwidth, Nheight, NnrChannels;
    for (int i = 0; i < 6; i++) {
        unsigned char* data = stbi_load(skybox.NightSkyboxTexNames[i].c_str(), &Nwidth, &Nheight, &NnrChannels, 0);
        NightSkyboxTextures[i] = data;
    }

    //Set up for the Day skybox
    GLuint skyboxTexture;
    // Apply skybox textures
    glGenTextures(1, &skyboxTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    for (int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[i]);
    }
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //Set up for the night skybox
    GLuint NightSkyboxTexture;
    // Apply skybox textures
    glGenTextures(1, &NightSkyboxTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, NightSkyboxTexture);
    for (int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, Nwidth, Nheight, 0, GL_RGB, GL_UNSIGNED_BYTE, NightSkyboxTextures[i]);
    }
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //Creating a shader program & Binding the VAO, VBO and EBO
    Shader SKYshaderProgram("Skybox.vert", "Skybox.frag");
    VAO SVAO;
    SVAO.Bind();
    VBO SVBO(skyboxVerts, sizeof(skyboxVerts));
    SVAO.LinkAttrib(SVBO, 0, 3, GL_FLOAT, 0 * sizeof(float), (void*)0);
    SVAO.Unbind();
    SVBO.Unbind();
    
    //Gettign the location of variables effecting the shader
    int location_SkyBrightness = glGetUniformLocation(SKYshaderProgram.ID, "brightness");
    int locationSkybox_Day = glGetUniformLocation(SKYshaderProgram.ID, "skybox");
    int locationSkybox_Night = glGetUniformLocation(SKYshaderProgram.ID, "nightSkybox");

    //------------Finished Creating the Skybox

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Clearing The Screen and Debugging
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Setting the ImGui for that frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Preform Checks and update D/N cylce
        sceneConfig.SceneRender(cam, window);

        //Controlling the Camera
        cam.Inputs(window, sceneConfig.deltaTime);
        cam.updateMatrix(45.0f, 0.1f, 1000.0f);

        ////Drawing The Skybox for the main scene
        glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        SKYshaderProgram.Activate();
        cam.SKYMatrix(SKYshaderProgram, "combined");
        SVAO.Bind();
        glUniform1i(locationSkybox_Day, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        glUniform1i(locationSkybox_Night, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, NightSkyboxTexture);
        glDrawArrays(GL_TRIANGLES, 0, 72);
        SVAO.Unbind();
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

        //Reflection Render----------------------------------
        glEnable(GL_CLIP_DISTANCE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
        glViewport(0, 0, water.REFLECTION_WIDTH, water.REFLECTION_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Drawing The Skybox for the reflection
        glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        SKYshaderProgram.Activate();
        cam.SKYMatrix(SKYshaderProgram, "combined");
        glUniform1f(location_SkyBrightness, sceneConfig.dnCycleBrightness);
        glUniform1i(locationSkybox_Day, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        glUniform1i(locationSkybox_Night, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, NightSkyboxTexture);
        SVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 72);
        SVAO.Unbind();
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

        //Drawing the tent for the reflection
        tentShader.Activate();
        cam.Matrix(tentShader, "camMatrix");
        Tent.Draw(tentShader);

        //Drawing the trees for the reflection
        treeShader.Activate();
        cam.Matrix(treeShader, "camMatrix");
        for (int i = 0; i < sceneRend.TreePositions.size(); i++)
        {
            glUniformMatrix4fv(glGetUniformLocation(treeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sceneRend.TreePositions[i]));
            Tree.Draw(treeShader);
        }

        //Drawing the Terrain for the Reflection Render
        TshaderProgram.Activate();
        cam.Matrix(TshaderProgram, "camMatrix");
        grassTex.Bind();
        grassSpec.Bind();
        glBindVertexArray(Tvao);
        for (int strip = 0; strip < terrain.numStrips; strip++)
        {
            glDrawElements(GL_TRIANGLE_STRIP, terrain.numTrisPerStrip + 2, GL_UNSIGNED_INT, (void*)(sizeof(unsigned) * (terrain.numTrisPerStrip + 2) * strip));
        }
        grassTex.Unbind();
        grassSpec.Unbind();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, sceneConfig.screenWidth, sceneConfig.screenHeight);
        glDisable(GL_CLIP_DISTANCE0);
        //End of Reflection Render---------------------
       
        //Refraction Render----------------------------------
        glEnable(GL_CLIP_DISTANCE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);
        glViewport(0, 0, water.REFRACTION_WIDTH, water.REFRACTION_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Drawing the tent fot the refraction render
        tentShader.Activate();
        cam.Matrix(tentShader, "camMatrix");
        Tent.Draw(tentShader);

        //Drawing the trees for the refraction render
        treeShader.Activate();
        cam.Matrix(treeShader, "camMatrix");
        for (int i = 0; i < sceneRend.TreePositions.size(); i++)
        {
            glUniformMatrix4fv(glGetUniformLocation(treeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sceneRend.TreePositions[i]));
            Tree.Draw(treeShader);
        }

        //Drawing The Terrain For the refraction Texture
        TshaderProgram.Activate();
        cam.Matrix(TshaderProgram, "camMatrix");
        grassTex.Bind();
        grassSpec.Bind();
        glBindVertexArray(Tvao);
        for (int strip = 0; strip < terrain.numStrips; strip++)
        {
            glDrawElements(GL_TRIANGLE_STRIP, terrain.numTrisPerStrip + 2, GL_UNSIGNED_INT, (void*)(sizeof(unsigned) * (terrain.numTrisPerStrip + 2) * strip));
        }
        grassTex.Unbind();
        grassSpec.Unbind();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, sceneConfig.screenWidth, sceneConfig.screenHeight);
        glDisable(GL_CLIP_DISTANCE1);
        //End of Refraction Render---------------------

        //Drawing Water For the main window
        water.moveFactor += water.Wave_Speed * sceneConfig.deltaTime;
        if (water.moveFactor >= 1.0)
        {
            water.moveFactor -= 1;
        }    
        WshaderProgram.Activate();        
        cam.Matrix(WshaderProgram, "camMatrix");
        glBindVertexArray(Wvao);
        glUniform1i(water.location_reflectionTexture, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, reflectionTexture);
        glUniform1i(water.location_refractionTexture, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, refractionTexture);
        glUniform1i(water.location_dudvMap, 2);
        dudvTexture.BindSlot2();
        glUniform1f(water.location_moveFactor, water.moveFactor);
        glDrawElements(GL_TRIANGLES, sizeof(water.WaterIndices), GL_UNSIGNED_INT, 0);

        //Drawing The Terrain For the main window
        TshaderProgram.Activate();
        glUniform3f(glGetUniformLocation(TshaderProgram.ID, "lightPos1"), lightPos1.x, lightPos1.y, lightPos1.z);
        glUniform3f(glGetUniformLocation(TshaderProgram.ID, "lightPos2"), lightPos2.x, lightPos2.y, lightPos2.z);
        glUniform3f(glGetUniformLocation(TshaderProgram.ID, "lightPos3"), lightPos3.x, lightPos3.y, lightPos3.z);
        glUniform3f(glGetUniformLocation(TshaderProgram.ID, "lightPos4"), lightPos4.x, lightPos4.y, lightPos4.z);
        cam.Matrix(TshaderProgram, "camMatrix");
        glUniform1f(location_terrainBrightness, sceneConfig.dnCycleBrightness);
        grassTex.Bind();
        grassSpec.Bind();
        glBindVertexArray(Tvao);
        for (int strip = 0; strip < terrain.numStrips; strip++)
        {
            glDrawElements(GL_TRIANGLE_STRIP, terrain.numTrisPerStrip + 2, GL_UNSIGNED_INT, (void*)(sizeof(unsigned) * (terrain.numTrisPerStrip + 2) * strip));
        }
        grassTex.Unbind();
        grassSpec.Unbind();

        //Drawing the tent for the main window 
        tentShader.Activate();
        cam.Matrix(tentShader, "camMatrix");
        glUniform1f(location_tentBrightness, sceneConfig.dnCycleBrightness);
        glUniform3f(glGetUniformLocation(tentShader.ID, "lightPos"), lightPos1.x, lightPos1.y, lightPos1.z);
        glUniformMatrix4fv(glGetUniformLocation(tentShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sceneRend.Tent_Model));
        Tent.Draw(tentShader);

        //Drawing the trees for the main window
        treeShader.Activate();
        cam.Matrix(treeShader, "camMatrix");
        for (int i = 0; i < sceneRend.TreePositions.size(); i++)
        {
            glUniform1f(location_treeBrightness, sceneConfig.dnCycleBrightness);
            glUniform3f(glGetUniformLocation(treeShader.ID, "lightPos"), lightPos1.x, lightPos1.y, lightPos1.z);
            glUniformMatrix4fv(glGetUniformLocation(treeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sceneRend.TreePositions[i]));
            Tree.Draw(treeShader);
        }

        //Drawing the lanterns for the main window
        lanternShader.Activate();
        cam.Matrix(lanternShader, "camMatrix");
        for (int i = 0; i < sceneRend.LanternPositions.size(); i++)
        {
            glUniform1f(location_lanternBrightness, sceneConfig.dnCycleBrightness);
            glUniform3f(glGetUniformLocation(lanternShader.ID, "lightPos"), lightPos1.x, lightPos1.y, lightPos1.z);
            glUniformMatrix4fv(glGetUniformLocation(lanternShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sceneRend.LanternPositions[i]));
            Lantern.Draw(lanternShader);
        }
        
        //Configuring the ImGui Menu
        ImGui::Begin("Menu:");
        ImGui::Text("Cosmetic Settings:");
        ImGui::Checkbox("Wireframe", &sceneConfig.wireframe);
        ImGui::Checkbox("Day and Night Cycle", &sceneConfig.isdncycle);
        ImGui::SliderFloat("Time of day", &sceneConfig.dnCycleBrightness, 0.03f, 0.9f);
        ImGui::Text("System Settings:");
        ImGui::Checkbox("Fullscreen", &sceneConfig.fullscreen);
        ImGui::Checkbox("Exit", &sceneConfig.exitApp);
        ImGui::Text("Credits:");
        ImGui::Text("By Andrew Hartley (W9075817)");
        ImGui::End();
        //Render the ImGui menu
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    //Cleaning Textures To avoid memory leaks
    grassTex.Delete();
    grassSpec.Delete();
    dudvTexture.Delete();
    glDeleteTextures(1, &skyboxTexture);
    glDeleteTextures(1, &NightSkyboxTexture);
    
    //Cleaning VAO's and VBO's To avoid memory leaks
    SVAO.Delete();
    SVBO.Delete();

    glDeleteVertexArrays(1, &Wvao);
    glDeleteBuffers(1, &WatCoordsvbo);
    glDeleteBuffers(1, &WatColorsvbo);
    glDeleteBuffers(1, &WatTexcoordsvbo);
    glDeleteBuffers(1, &WatNormalsvbo);

    glDeleteVertexArrays(1, &Tvao);
    glDeleteBuffers(1, &TerCoordsvbo);
    glDeleteBuffers(1, &TerColorsvbo);
    glDeleteBuffers(1, &TerTexcoordsvbo);
    glDeleteBuffers(1, &Ternormalsvbo);

    //Cleaning Shaders To avoid memory leaks
    lanternShader.Delete();
    treeShader.Delete();
    tentShader.Delete();
    TshaderProgram.Delete();
    SKYshaderProgram.Delete();
    WshaderProgram.Delete();
    
    //Cleaning ImGui to avoid memory leaks
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}