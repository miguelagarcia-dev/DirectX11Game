#pragma once
#include <DX3D/All.h>

class MyObject : public dx3d::GameObject
{
    dx3d_typeid(MyObject)
public:
    explicit MyObject(const dx3d::GameObjectDesc& desc);
    virtual ~MyObject() override;
protected:
    virtual void onCreate();
    virtual void onUpdate(dx3d::f32 deltaTime);
};

