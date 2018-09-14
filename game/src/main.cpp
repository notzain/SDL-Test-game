#include <engine/ecs/Component.h>
#include <engine/ecs/ComponentManager.h>
#include <engine/ecs/EntityManager.h>

#include <ecs/World.h>
#include <iostream>

struct PositionComponent : public engine::BaseComponent<PositionComponent> {
    int x;
    int y;

    PositionComponent(int x, int y)
        : x(x)
        , y(y)
    {
    }
};
struct OtherComponent : public engine::BaseComponent<OtherComponent> {
    OtherComponent(int x, int y)
    {
        (void)x;
        (void)y;
    }
};

template <typename... Components>
bool hasComps(const engine::Entity& entity)
{
    return entity.hasComponent<Components...>();
}

int main(int /*argc*/, char** /*argv*/)
{
    engine::EntityManager entityManager;
    engine::ComponentManager componentManager;

    componentManager.addManager<PositionComponent>();
    componentManager.addManager<OtherComponent>();

    for (int i = 0; i < 20; ++i) {
        auto& entity = entityManager.create();
        componentManager.getManager<PositionComponent>().add(entity, 0, 0);
        if (i % 3 == 0)
            componentManager.getManager<OtherComponent>().add(entity, 0, 0);
    }

    engine::World world(entityManager, componentManager);
    world.forEachEntityWith<PositionComponent, OtherComponent>([](engine::Entity& entity) {
        std::cout << entity.id() << '\n';
    });

    auto& entity = entityManager.create();
    componentManager.add<PositionComponent>(entity, 0, 0);
    componentManager.add<OtherComponent>(entity, 0, 0);
    std::cout << entity.hasComponent<PositionComponent, OtherComponent>();
}
