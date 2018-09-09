#ifndef SDL_GAME_COMPONENTMANAGER_H
#define SDL_GAME_COMPONENTMANAGER_H

#include "Component.h"
#include "Entity.h"

#include <cassert>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace engine {

class IComponentManager {
public:
    IComponentManager();
    virtual ~IComponentManager();
};

template <typename Component>
class BaseComponentManager : public IComponentManager {
    using ComponentMap = std::unordered_map<EntityId, std::unique_ptr<Component>>;
    ComponentMap m_components;

public:
    template <typename... ComponentArgs>
    Component& add(Entity& entity, ComponentArgs&&... args)
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        auto component = std::make_unique<Component>(std::forward<ComponentArgs>(args)...);
        auto* ptr = component.get();

        const bool valid = m_components.insert({ entity.id(), std::move(component) }).second;

        entity.registerComponent<Component>();
        return *ptr;
    }

    Component& get(const Entity& entity) const
    {
        return *m_components.at(entity.id()).get();
    }
    Component& get(const EntityId entityId) const
    {
        return *m_components.at(entityId).get();
    }

    ComponentMap& getAll()
    {
        return m_components;
    }
};

class ComponentManager : public IComponentManager {
    using ManagerMap = std::unordered_map<engine::ComponentId, std::unique_ptr<IComponentManager>>;
    ManagerMap m_managers;

public:
    template <typename Component>
    void addManager()
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        m_managers.insert({ Component::familyId(),
            std::make_unique<BaseComponentManager<Component>>() });
    }

    template <typename Component>
    BaseComponentManager<Component>& getManager()
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        auto& manager = m_managers.at(Component::familyId());

        return *reinterpret_cast<BaseComponentManager<Component>*>(manager.get());
    };

    template <typename Component, typename... ComponentArgs>
    Component& add(Entity& entity, ComponentArgs&&... args)
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        return getManager<Component>().add(entity, std::forward<ComponentArgs>(args)...);
    }
};

} // end namespace engine

#endif //SDL_GAME_COMPONENTMANAGER_H
