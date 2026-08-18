# DX3D — DirectX 11 Renderer

A DirectX 11 rendering engine built from scratch in C++ as a learning project.
Not a game engine. Not production ready. Built to understand how renderers actually work.

## What it does

- Win32 window + DXGI swap chain (double buffering)
- Deferred device context — GPU commands recorded then submitted in batch
- Runtime HLSL compilation via D3DCompile
- Shader reflection (D3DReflect) — input layout auto-generated from VS bytecode
- Vertex, index, and constant buffers
- Row-major 4x4 matrix math (translate, scale, rotate, ortho, perspective)
- Texture loading via stb_image → ID3D11Texture2D + SRV
- Lambert diffuse lighting (vertex normals, directional light)
- Component-based scene graph (World, GameObject, TransformComponent, MeshComponent, CameraComponent)
- Perspective camera with FOV, near/far planes
- Keyboard + mouse input, cursor lock (WASD + mouse look)

## Stack

- C++20
- DirectX 11 / DXGI
- HLSL (shader model 5.0)
- WRL ComPtr
- stb_image
- Win32

## Structure

DX3D/Include/     — public engine headers
DX3D/Source/      — engine implementation
DX3D/Assets/      — shaders, textures
Game/             — user-space (MainGame, Player)

## Current state

The renderer can display a textured, lit scene with a moveable camera.
Lighting is Lambert diffuse only — no ambient term, no shadow maps yet.
Normals are in world space and not corrected for non-uniform scale.

## What's next

- Normal matrix for correct lighting under non-uniform scale
- Ambient light term
- Specular highlights
- Shadow maps
- Frustum culling
