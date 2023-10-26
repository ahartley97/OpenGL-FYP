#include "SceneRenderer.h"

//A function for creating the transforms for the trees
void SceneRenderer::PopulateTreeTransformVectors()
{
    glm::mat4 Tree_Model = glm::mat4(1.0f);
    Tree_Model = glm::translate(Tree_Model, glm::vec3(-25.0f, 1.0f, -15.0f));
    Tree_Model = glm::scale(Tree_Model, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model = glm::rotate(Tree_Model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model);

    glm::mat4 Tree_Model2 = glm::mat4(1.0f);
    Tree_Model2 = glm::translate(Tree_Model2, glm::vec3(15.0f, 1.0f, 25.0f));
    Tree_Model2 = glm::scale(Tree_Model2, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model2 = glm::rotate(Tree_Model2, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model2);

    glm::mat4 Tree_Model3 = glm::mat4(1.0f);
    Tree_Model3 = glm::translate(Tree_Model3, glm::vec3(-25.0f, 1.0f, 20.0f));
    Tree_Model3 = glm::scale(Tree_Model3, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model3 = glm::rotate(Tree_Model3, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model3);

    glm::mat4 Tree_Model4 = glm::mat4(1.0f);
    Tree_Model4 = glm::translate(Tree_Model4, glm::vec3(50.0f, 1.0f, 50.0f));
    Tree_Model4 = glm::scale(Tree_Model4, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model4 = glm::rotate(Tree_Model4, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model4);

    glm::mat4 Tree_Model5 = glm::mat4(1.0f);
    Tree_Model5 = glm::translate(Tree_Model5, glm::vec3(-50.0f, 1.0f, 50.0f));
    Tree_Model5 = glm::scale(Tree_Model5, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model5 = glm::rotate(Tree_Model5, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model5);

    glm::mat4 Tree_Model6 = glm::mat4(1.0f);
    Tree_Model6 = glm::translate(Tree_Model6, glm::vec3(-2.0f, 1.0f, -45.0f));
    Tree_Model6 = glm::scale(Tree_Model6, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model6 = glm::rotate(Tree_Model6, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model6);

    glm::mat4 Tree_Model7 = glm::mat4(1.0f);
    Tree_Model7 = glm::translate(Tree_Model7, glm::vec3(-42.0f, 1.0f, -50.0f));
    Tree_Model7 = glm::scale(Tree_Model7, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model7 = glm::rotate(Tree_Model7, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model7);

    glm::mat4 Tree_Model8 = glm::mat4(1.0f);
    Tree_Model8 = glm::translate(Tree_Model8, glm::vec3(20.0f, 1.0f, -35.0f));
    Tree_Model8 = glm::scale(Tree_Model8, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model8 = glm::rotate(Tree_Model8, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model8);

    glm::mat4 Tree_Model9 = glm::mat4(1.0f);
    Tree_Model9 = glm::translate(Tree_Model9, glm::vec3(0.0f, 1.0f, 55.0f));
    Tree_Model9 = glm::scale(Tree_Model9, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model9 = glm::rotate(Tree_Model9, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model9);

    glm::mat4 Tree_Model10 = glm::mat4(1.0f);
    Tree_Model10 = glm::translate(Tree_Model10, glm::vec3(50.0f, 1.0f, -54.0f));
    Tree_Model10 = glm::scale(Tree_Model10, glm::vec3(1.0f, 1.0f, 1.0f));
    Tree_Model10 = glm::rotate(Tree_Model10, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    TreePositions.push_back(Tree_Model10);
}

//A function for creating the transforms for the lanterns
void SceneRenderer::PopulateLanternTransformVectors()
{
    glm::mat4 Lantern_Model1 = glm::mat4(1.0f);
    Lantern_Model1 = glm::translate(Lantern_Model1, glm::vec3(20.0f, 3.5f, -55.0f));
    Lantern_Model1 = glm::scale(Lantern_Model1, glm::vec3(0.75f, 0.75f, 0.75f));
    LanternPositions.push_back(Lantern_Model1);

    glm::mat4 Lantern_Model2 = glm::mat4(1.0f);
    Lantern_Model2 = glm::translate(Lantern_Model2, glm::vec3(47.0f, 3.5f, -32.0f));
    Lantern_Model2 = glm::scale(Lantern_Model2, glm::vec3(0.75f, 0.75f, 0.75f));
    LanternPositions.push_back(Lantern_Model2);

    glm::mat4 Lantern_Model3 = glm::mat4(1.0f);
    Lantern_Model3 = glm::translate(Lantern_Model3, glm::vec3(22.0f, 3.5f, 50.0f));
    Lantern_Model3 = glm::scale(Lantern_Model3, glm::vec3(0.75f, 0.75f, 0.75f));
    LanternPositions.push_back(Lantern_Model3);

    glm::mat4 Lantern_Model4 = glm::mat4(1.0f);
    Lantern_Model4 = glm::translate(Lantern_Model4, glm::vec3(-47.0f, 3.5f, -23.0f));
    Lantern_Model4 = glm::scale(Lantern_Model4, glm::vec3(0.75f, 0.75f, 0.75f));
    LanternPositions.push_back(Lantern_Model4);
}

void SceneRenderer::PopulatePositionVectors()
{
    PopulateLanternTransformVectors();
    PopulateTreeTransformVectors();

    //Creating the transform for the tent
    Tent_Model = glm::mat4(1.0f);
    Tent_Model = glm::translate(Tent_Model, glm::vec3(-35.0f, 3.75f, 45.0f));
    Tent_Model = glm::scale(Tent_Model, glm::vec3(scale, scale, scale));
    Tent_Model = glm::rotate(Tent_Model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
