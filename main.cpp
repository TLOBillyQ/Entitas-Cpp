// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: MIT License
// MIT License web page: https://opensource.org/licenses/MIT

#include "EntitasPP/SystemContainer.hpp"
#include "EntitasPP/Matcher.hpp"
#include "EntitasPP/Pool.hpp"
#include <iostream>
#include <string>

#include "EntitasPP/ReactiveSystem.hpp"

using namespace EntitasPP;

class Test1 : public IComponent
{
public:
    void Reset()
    {
    }
};

class Test2 : public IComponent
{
public:
    void Reset()
    {
    }
};

class Test3 : public IComponent
{
public:
    void Reset()
    {
    }
};

class Test4 : public IComponent
{
public:
    void Reset()
    {
    }
};

class Test5 : public IComponent
{
public:
    void Reset()
    {
    }
};

class CountAllTest1Sys
    : public IExecuteSystem
      , public ISetPoolSystem
{
public:
    void SetPool(Pool* pool)
    {
        mPool = pool;
    }

    void Execute()
    {
        const auto count = mPool->GetGroup(Matcher_AllOf(Test1))->Count();
        std::cout << "Test1 Count = " << count << std::endl;
    }

private:
    Pool* mPool;
};

class TestReactiveSys
    : public IReactiveSystem
      , public ISetPoolSystem
    // , public IClearReactiveSystem
    // , public IEnsureComponents
{
public:
    TestReactiveSys()
    {
        trigger = Matcher_AllOf(Test1).OnEntityRemoved();
        // ensureComponents = Matcher_AllOf(Test1);
    }

    void SetPool(Pool* pool) override
    {
        mPool = pool;
    }

    void Execute(std::vector<EntityPtr> entities) override
    {
        for (auto entity : entities)
        {
            mPool->CreateEntity()->Add<Test1>();
            mPool->CreateEntity()->Add<Test1>();
            mPool->CreateEntity()->Add<Test1>();

            std::cout << "Reactive Loop" << std::endl;
        }
    }

private:
    Pool* mPool;
};

class TestMultiReactiveSystem
    : public IMultiReactiveSystem
      , public ISetPoolSystem
{
public:
    TestMultiReactiveSystem()
    {
        triggers.emplace_back(Matcher_AnyOf(Test2), GroupEventType::OnEntityAddedOrRemoved);
        triggers.emplace_back(Matcher_AnyOf(Test3), GroupEventType::OnEntityAddedOrRemoved);
    }

    void SetPool(Pool* pool)
    {
        mPool = pool;
    }

    void Execute(std::vector<EntityPtr> entities)
    {
        std::cout << "Multi Exe" << std::endl;

        for (auto entity : entities)
        {
            std::cout << "Multi Loop" << std::endl;
        }
    }

private:
    Pool* mPool;
};

class RemoveTest1Sys
    : public IInitializeSystem
      , public ISetPoolSystem
      , public IExecuteSystem
{
public:
    void Initialize() override
    {
        auto entities = pool->GetGroup(Matcher_AllOf(Test1))->GetEntities();
        entities.front()->Remove<Test1>();

        std::cout << "RemoveTest1Sys" << std::endl;
    }

    void SetPool(Pool* pool) override
    {
        this->pool = pool;
    }

    void Execute() override
    {
    }

private:
    Pool* pool = nullptr;
};

class CreateEntitySys
    : public ISetPoolSystem, public IInitializeSystem, public IExecuteSystem
{
public:
    void Initialize()
    {
        pool->CreateEntity()->Add<Test1>();
        pool->CreateEntity()->Add<Test1>();
        pool->CreateEntity()->Add<Test1>();

        pool->CreateEntity()->Add<Test2>();
        pool->CreateEntity()->Add<Test3>();

        std::cout << "CreateEntitySys Init!" << std::endl;
    }

    void SetPool(Pool* pool)
    {
        this->pool = pool;
    }

    void Execute()
    {
        pool->GetGroup(Matcher_AllOf(Test1))->GetEntities().front()->Remove<Test1>();

        std::cout << "CreateEntitySys Execute!" << std::endl;
    }

private:
    Pool* pool;
};

class DemoComponent : public IComponent
{
public:
    void Reset(const std::string& name1, const std::string& name2)
    {
        std::cout << "Created new entity: " << name1 << "," << name2 << std::endl;
    }
};

class DemoSystem : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem
{
public:
    void SetPool(Pool* pool)
    {
        mPool = pool;
    }

    void Initialize()
    {
        mPool->CreateEntity()->Add<DemoComponent>("foo", "bar")->Add<Test1>();
        std::cout << "DemoSystem initialized" << std::endl;
        std::cout << "Broken" << std::endl;
    }

    void Execute()
    {
        mPool->CreateEntity()->Add<DemoComponent>("foo", "bar")->Add<Test1>();

        auto entitiesCount = mPool->GetGroup(Matcher_AllOf2(DemoComponent, Test1))->Count();
        std::cout << "There are " << entitiesCount << " entities with the component 'DemoComponent'" << std::endl;

        std::cout << "DemoSystem executed" << std::endl;
    }

private:
    Pool* mPool;
};

class Feature: public IInitializeSystem, public IExecuteSystem
{
public:
    void Initialize() override
    {
        for (const auto& c : containers)
        {
            c->Initialize();
        }
    }
    void Execute() override
    {
        for (auto& c : containers)
        {
            c->Execute();
        }
    }
    std::vector<std::shared_ptr<SystemContainer>> containers;
};

class GameController : public IInitializeSystem, public IExecuteSystem
{
public:
    void Initialize() override
    {
        for (auto& f : features)
        {
            f.Initialize();
        }
    }
    void Execute() override
    {
        for (auto& f : features)
        {
            f.Execute();
        }
    }
    std::vector<Feature> features;
};

class IWriteFile
{
public:
    void IWrite(){};
};

int main(const int argc, const char* argv[])
{
    const auto input = std::make_shared<Pool>();
    const auto logic = std::make_shared<Pool>();
    const auto view = std::make_shared<Pool>();

    const auto container1 = std::make_shared<SystemContainer>();
    container1->Add(logic->CreateSystem<DemoSystem>());
    container1->Add(logic->CreateSystem<TestMultiReactiveSystem>());
    auto input_f = Feature();
    input_f.containers.emplace_back(container1);

    const auto container2 = std::make_shared<SystemContainer>();
    container2->Add(logic->CreateSystem<CreateEntitySys>());
    container2->Add(logic->CreateSystem<RemoveTest1Sys>());
    container2->Add(logic->CreateSystem<TestReactiveSys>());
    container2->Add(logic->CreateSystem<CountAllTest1Sys>());
    auto logic_f = Feature();
    logic_f.containers.emplace_back(container2);
    Feature view_f;

    auto gameController = GameController();
    gameController.features.emplace_back(input_f);
    gameController.features.emplace_back(logic_f);
    gameController.features.emplace_back(view_f);

    gameController.Initialize();
    for (unsigned int i = 0; i < 3; ++i)
    {
        std::cout << std::endl;
        std::cout << "Frame: " << i + 1 << std::endl;

        gameController.Execute();
    }

    return 0;
}
