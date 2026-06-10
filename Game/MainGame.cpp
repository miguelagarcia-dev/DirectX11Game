#include "MainGame.h"
#include "Objects/MyObjects.h"

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate()
{
    Game::onCreate();
    auto& world = getWorld();

    auto object = world.createGameObject<dx3d::GameObject>();
    auto myObject = world.createGameObject<MyObject>();
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
    Game::onUpdate(deltaTime);
}