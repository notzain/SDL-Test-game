#ifndef SDL_GAME_ENTITYMANAGER_H
#define SDL_GAME_ENTITYMANAGER_H

#include <cassert>
#include <memory>
#include <vector>

#include "Entity.h"

namespace engine {

class EntityManager {
private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    EntityId lastEntityId = 0;

public:
    EntityManager() = default;

    Entity& create();
    void destroy(Entity& entity);

private:
    EntityId makeUniqueEntityId();
};

} // end namespace engine

#endif //SDL_GAME_ENTITYMANAGER_H
