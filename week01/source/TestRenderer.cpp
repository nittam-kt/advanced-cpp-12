#pragma once

#include "TestRenderer.h"

#include <Texture.h>
#include <D3DManager.h>


using namespace DirectX;
using namespace UniDx;



Vector3 position[4] = {
    {-0.5,-0.5,0},
    {-0.5,0.5,0},
    {0.5,-0.5,0},
    {0.5,0.5,0},
};

Vector2 uv[4] = {
    {0,1},
    {0,0},
    {1,1},
    {1,0},
};


void TestRenderer::OnEnable()
{
    Renderer::OnEnable();

    // �}�e���A����ǉ�
    materials.push_back(std::make_unique<Material>());

    // �}�e���A�����V�F�[�_�[��ǂݍ���ŏ�����
    materials.back()->shader.compile<VertexPT>(L"Resource/Albedo.hlsl");

    // �e�N�X�`����ǂݍ���Ń}�e���A���ɒǉ�
    std::unique_ptr<Texture> t = std::make_unique<Texture>();
    t->load(L"Resource/floor.png");
    materials.back()->addTexture(std::move(t));

    // ���b�V���̏�����
    auto submesh = std::make_unique<SubMesh>();
    submesh->positions = position;
    submesh->uv = uv;
    submesh->topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    submesh->createBuffer<VertexPT>();

    mesh.submesh.push_back(std::move(submesh));
}


