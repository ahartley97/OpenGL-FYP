#pragma once

//Windows Headers:
#include <math.h>
#include <cmath>
#include <vector>
#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <cerrno>

//ImGui Headers:
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//OpenGL Headers:
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

//Misc Headers:
#include <SOIL2/SOIL2.h>

//Class Headers:
#include "Texture.h"
#include "Camera.h"
#include "Terrain.h"
#include "Water.h"
#include "Skybox.h"
#include "shaderClass.h"
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"

//Assimp Headers:
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>

