#include "PlayerDigEvent.h"

#include "../../Item/Material.h"
#include "../../Player/Player.h"
#include "../World.h"

PlayerDigEvent::PlayerDigEvent(const int buttonId, const glm::vec3 &location, Player &player)
    : m_buttonPress(buttonId)
    , m_digSpot(location)
    , m_pPlayer(&player)
{
}

void PlayerDigEvent::handle(World &world)
{
    auto chunkLocation = World::getChunkXZ(static_cast<int>(m_digSpot.x),
                                           static_cast<int>(m_digSpot.z));

    if (world.getChunkManager().chunkLoadedAt(chunkLocation.x,
                                              chunkLocation.z)) {
        dig(world);
    }
}

void PlayerDigEvent::dig(World &world)
{
    int x = static_cast<int>(m_digSpot.x);
    int y = static_cast<int>(m_digSpot.y);
    int z = static_cast<int>(m_digSpot.z);
    if(glfwGetKey(m_pPlayer->getWindow(), GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
        auto block = world.getBlock(x, y, z);
        const auto &material = Material::toMaterial((BlockId)block.id);
        m_pPlayer->addItem(material);
        /*
                    auto r = 1;
                    for (int y = -r; y < r; y++)
                    for (int x = -r; x < r;x++)
                    for (int z = -r; z < r; z++)
                    {
                        int newX = m_digSpot.x + x;
                        int newY = m_digSpot.y + y;
                        int newZ = m_digSpot.z + z;
                        world.updateChunk   (newX, newY, newZ);
                        world.setBlock      (newX, newY, newZ, 0);
        
        world.updateChunk(x, y, z);
        world.setBlock(x, y, z, 0);
        }*/
    }
    else if(glfwGetKey(m_pPlayer->getWindow(), GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS)
    {
        auto& stack = m_pPlayer->getHeldItems();
        auto& material = stack.getMaterial();

        if (material.id == Material::ID::Nothing) {
            return;
        }
        else {
            stack.remove();
            world.updateChunk(x, y, z);
            world.setBlock(x, y, z, material.toBlockID());
        }
    }

}
