#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "Maths/glm.h"
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

/* Vestigial class that was going to be used for player movement. */

// WIP
class Controller {
    glm::vec3 translateInput();
    glm::ivec2 mouseInput();
};

#endif // CONTROLLER_H_INCLUDED
