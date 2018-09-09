#define CATCH_CONFIG_MAIN
#include <Catch/catch2.hpp>

#include <engine/ecs/Component.h>
#include <engine/ecs/ComponentManager.h>
#include <engine/ecs/Entity.h>
#include <engine/ecs/EntityManager.h>

#include <set>

TEST_CASE("Each entity has an unique id.", "[entity]")
{
    using namespace engine;

    std::set<EntityId> uniqueIds;
    EntityManager entityManager;

    SECTION("Each EntityManager creates unique ID's starting from 0.")
    {
        for (int i = 0; i < 1000; ++i) {
            const auto& entity = entityManager.create();
            const bool hasInserted = uniqueIds.insert(entity.id()).second;

            REQUIRE(hasInserted);
        }

        SECTION("Another EntityManager can create duplicate EntityId's")
        {
            EntityManager otherManager;

            const auto& entity = otherManager.create();
            const bool hasInserted = uniqueIds.insert(entity.id()).second;

            REQUIRE_FALSE(hasInserted);
        }
    }
}

TEST_CASE("Each component type has a unique family id", "[component]")
{
    using namespace engine;
    struct FirstComponent : public BaseComponent<FirstComponent> {
    };
    struct SecondComponent : public BaseComponent<SecondComponent> {
    };

    REQUIRE(FirstComponent::familyId() == FirstComponent::familyId());
    REQUIRE(SecondComponent::familyId() == SecondComponent::familyId());
    REQUIRE(FirstComponent::familyId() != SecondComponent::familyId());
}

TEST_CASE("The ComponentManager can create managers for each component, and add them to entities.", "[component]")
{
    using namespace engine;
    struct TestComponent : public BaseComponent<TestComponent> {
        int firstTestValue = 0;
        std::string secondTestValue = "";

        TestComponent(int firstTestValue, std::string secondTestValue)
            : firstTestValue(firstTestValue)
            , secondTestValue(std::move(secondTestValue))
        {
        }
    };
    ComponentManager componentManager;
    EntityManager entityManager;
    auto& entity = entityManager.create();

    SECTION("The ComponentManager throws when user requests an unregistered manager.")
    {
        REQUIRE_THROWS(componentManager.getManager<TestComponent>());
    }

    SECTION("The ComponentManager can register new managers.")
    {
        componentManager.addManager<TestComponent>();
        REQUIRE_NOTHROW(componentManager.getManager<TestComponent>());

        SECTION("The ComponentManager can request a registered manager.")
        {
            const int firstValueToTest = 42;
            const std::string secondValueToTest = "My test string";

            componentManager.add<TestComponent>(entity, firstValueToTest, secondValueToTest);
            auto& testManager = componentManager.getManager<TestComponent>();
            auto& component = testManager.get(entity);

            REQUIRE(component.firstTestValue == firstValueToTest);
            REQUIRE(component.secondTestValue == secondValueToTest);
        }
    }

    SECTION("The ComponentManager can add new components to entities.")
    {
        componentManager.addManager<TestComponent>();
        componentManager.add<TestComponent>(entity, 0, "");
        REQUIRE(entity.hasComponent<TestComponent>());
    }

    SECTION("The ComponentManager properly forwards component constructor to the added component")
    {
        const int firstValueToTest = 42;
        const std::string secondValueToTest = "My test string";

        componentManager.addManager<TestComponent>();
        auto& component = componentManager.add<TestComponent>(entity, firstValueToTest, secondValueToTest);

        REQUIRE(component.firstTestValue == firstValueToTest);
        REQUIRE(component.secondTestValue == secondValueToTest);
    }
}
