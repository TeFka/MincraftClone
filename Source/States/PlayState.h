#ifndef PLAYSTATE_H_INCLUDED
#define PLAYSTATE_H_INCLUDED

#include "../Player/Player.h"
#include "StateBase.h"

#include "../Util/FPSCounter.h"
#include "../World/Chunk/Chunk.h"
#include "../World/World.h"

/// @brief Active game playing state, not associated with game menus.
class StatePlay : public StateBase {
  public:
    StatePlay(Application &app, const Config &config);

    void handleEvent(int e) override;
    void handleInput(GLFWwindow* window) override;

    void update(float deltaTime) override;

    void render(RenderMaster &renderer) override;

    void onOpen() override;

  private:
    std::array<bool, 100> keyboard_keys;
    Player m_player;
    World m_world;
    
    FPSCounter m_fpsCounter;
};

#endif // PlayState_H_INCLUDED
