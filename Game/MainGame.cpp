#include "MainGame.h"
#include "Objects/MyObjects.h"

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate()
{
    Game::onCreate();
    auto& world = getWorld();

    for (auto x = 0; x < 3; x++)
    {
        for (auto y = 0; y < 3; y++)
        {
            auto object = world.createGameObject<dx3d::GameObject>();
            object->createOrGetComponent<dx3d::CubeComponent>();
            object->getTransform().setPosition({ (dx3d::f32)-1 + x, (dx3d::f32)-1 + y, 0 });
            m_objects[y * 3 + x] = object;
        }
    }
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
    Game::onUpdate(deltaTime);

    m_rot += deltaTime * 0.707f;
    m_scale = std::abs(std::sin(m_rot));

    for (auto i = 0; i < 9; i++)
    {
        m_objects[i]->getTransform().setRotation({ m_rot * i, m_rot, m_rot * i });
        m_objects[i]->getTransform().setScale({ m_scale, m_scale, m_scale });
    }
}