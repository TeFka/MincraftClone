#ifndef STATEBASE_H_INCLUDED
#define STATEBASE_H_INCLUDED

#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>

// This base class for all States, used more as a template than a functional class.

class RenderMaster;
class Application;

/// @brief Base state that determines how other states should normally behave.
class StateBase {
  public:
    StateBase(Application &app)
        : m_pApplication(&app)
    {
    }

    virtual ~StateBase() = default;

    virtual void handleEvent(int e) = 0;
    virtual void handleInput(GLFWwindow* window) = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render(RenderMaster &renderer) = 0;

    virtual void onOpen() = 0;

  protected:
    Application *m_pApplication;
};

#endif // STATEBASE_H_INCLUDED
