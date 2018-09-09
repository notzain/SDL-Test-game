#include "EntityManager.h"

#include <utility>

namespace engine {

Entity& EntityManager::create()
{
    auto entity = std::make_unique<Entity>(makeUniqueEntityId());
    auto* entityPtr = entity.get();

    m_entities.push_back(std::move(entity));

    return *entityPtr;
}

void EntityManager::destroy(Entity& entity)
{
    //FIXME: Implement function
    (void)entity;
}

EntityId EntityManager::makeUniqueEntityId()
{
    return lastEntityId++;
}

} // end engine
