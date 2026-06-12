#include "MainGame.h"
#include "Objects/Player.h"
#include "DX3D/Component/MeshComponent.h"
#include <ThirdParty/stb_image.h>

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)   // ADD THIS
{
}

void MainGame::onCreate()
{
    Game::onCreate();
    auto& world = getWorld();
    auto graphicsDevice = getGraphicsDevice();

    const dx3d::Vertex vertexList[] = { 
        {{-0.5f,-0.5f,-0.5f}, {1,0,0,1}, {0,0}},
        {{-0.5f, 0.5f,-0.5f}, {0,1,0,1}, {0,1}},
        {{ 0.5f, 0.5f,-0.5f}, {0,0,1,1}, {1,1}},
        {{ 0.5f,-0.5f,-0.5f}, {1,0,1,1}, {1,0}},
        {{ 0.5f,-0.5f, 0.5f}, {1,0,1,1}, {0,0}},
        {{ 0.5f, 0.5f, 0.5f}, {0,0,1,1}, {0,1}},
        {{-0.5f, 0.5f, 0.5f}, {0,1,0,1}, {1,1}},
        {{-0.5f,-0.5f, 0.5f}, {1,0,0,1}, {1,0}}
         };

    const dx3d::ui32 indexList[] = {
        0,1,2,  2,3,0, //first and 2nd triangle
        4,5,6,  6,7,4, //back face
        1,6,5,  5,2,1, //top face
        7,0,3,  3,4,7, //bottom face
        3,2,5,  5,4,3, //right face
        7,6,1,  1,0,7 //left face };
        };

    int width, height, channels;
    auto* data = stbi_load("DX3D/Assets/Textures/Gravel043_1K-PNG_Color.png",
        &width, &height, &channels, 4);
    auto texture = graphicsDevice->createTexture({
        data,
        (dx3d::ui32)width,
        (dx3d::ui32)height,
        (dx3d::ui32)(width * 4)
        });
    stbi_image_free(data);

    // Floor slab
    auto floor = world.createGameObject<dx3d::GameObject>();
    auto mesh = floor->createOrGetComponent<dx3d::MeshComponent>(graphicsDevice);
    mesh->setMesh(
        { vertexList, std::size(vertexList), sizeof(dx3d::Vertex) },
        { indexList, std::size(indexList) }
    );
    mesh->setTexture(texture);
    floor->getTransform().setScale({ 6.8f, 0.1f, 6.8f });
    floor->getTransform().setPosition({ 0, -1, 0 });
    //5x5 cube 
    srand((unsigned int)time(NULL));
    for (auto y = -2; y < 3; y++)
    {
        for (auto x = -2; x < 3; x++)
        {
            auto cube = world.createGameObject<dx3d::GameObject>();
            auto meshComp = cube->createOrGetComponent<dx3d::MeshComponent>(graphicsDevice);
            meshComp->setMesh(
                { vertexList, std::size(vertexList), sizeof(dx3d::Vertex) },
                { indexList, std::size(indexList) }
            );
            meshComp->setTexture(texture);
            auto height = (rand() % 120 + 80.0f) / 100.0f;
            auto width = (rand() % 600 + 200.0f) / 1000.0f;
            cube->getTransform().setScale({ width, height, width });
            cube->getTransform().setPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });
        }
    }

    // Player starts slightly behind and above the origin
    auto player = world.createGameObject<Player>();
    player->getTransform().setPosition({ 0, 1, -2 });

    getInputSystem().setCursorLocked(true);
    getInputSystem().setCursorVisible(false);
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
    Game::onUpdate(deltaTime);
    // Player movement is now handled inside Player::onUpdate
   }