#include <engine/ecs/Component.h>
#include <engine/ecs/ComponentManager.h>
#include <engine/ecs/EntityManager.h>

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

int main(int argc, char** argv)
{
    engine::EntityManager entityManager;
    engine::ComponentManager componentManager;

    auto& entity = entityManager.create();
    componentManager.addManager<PositionComponent>();
    componentManager.add<PositionComponent>(entity, 0, 0);
}