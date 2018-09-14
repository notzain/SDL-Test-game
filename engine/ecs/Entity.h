#ifndef SDL_GAME_ENTITY_H
#define SDL_GAME_ENTITY_H

#include "Component.h"

#include <bitset>
#include <cassert>
#include <cstdint>
#include <type_traits>

namespace engine {

using EntityId = uint64_t;

class Entity {
    const EntityId m_id;
    std::bitset<32> m_componentSignature;
    std::bitset<32> m_tagSignature;

public:
    explicit Entity(EntityId id);

    EntityId id() const;

    template <typename Component>
    bool hasComponent() const
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        return m_componentSignature[(std::size_t)Component::familyId()];
    }

    template <typename FirstComponent, typename SecondComponent,
        typename... Rest>
    bool hasComponent() const
    {
        return hasComponent<FirstComponent>()
            && hasComponent<SecondComponent, Rest...>();
    }

    template <typename Component>
    void registerComponent()
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        m_componentSignature.set((std::size_t)Component::familyId(), 1);
    }

    template <typename Component>
    void unregisterComponent()
    {
        m_componentSignature.set((std::size_t)Component::familyId(), 0);
    }
};

} // end namespace engine

#endif //SDL_GAME_ENTITY_H
