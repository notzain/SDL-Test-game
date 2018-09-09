set(ECS_SRC
    ecs/Entity.h ecs/Entity.cpp
    ecs/EntityManager.h ecs/EntityManager.cpp
    ecs/Component.h ecs/Component.cpp
    ecs/ComponentManager.h ecs/ComponentManager.cpp
)

add_library(engine ${ECS_SRC})

