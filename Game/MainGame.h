#pragma once
#include <DX3D/All.h>

class MainGame : public dx3d::Game
{
public:
    explicit MainGame(const dx3d::GameDesc& desc);
protected:
    virtual void onCreate();
    virtual void onUpdate(dx3d::f32 deltaTime);

private:
    dx3d::GameObject* m_player{};
    dx3d::f32 m_rot{}, m_scale{};
};