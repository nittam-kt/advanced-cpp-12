// CreateDefaultScene.cpp
// デフォルトのシーンを生成します

#include <numbers>

#include <UniDx.h>
#include <Scene.h>
#include <Component.h>
#include <Camera.h>
#include <PrimitiveRenderer.h>
#include <GltfModel.h>
#include <Rigidbody.h>
#include <Random.h>
#include <Collider.h>
#include <Light.h>

#include "CameraBehaviour.h"
#include "Player.h"

using namespace std;
using namespace UniDx;


unique_ptr<Scene> CreateDefaultScene()
{
    // -- プレイヤー --
    auto player = make_unique<GameObject>(L"プレイヤー",
        make_unique<GltfModel>(),
        make_unique<Player>(),
        make_unique<Rigidbody>(),
        make_unique<SphereCollider>()
        );
    auto model = player->GetComponent<GltfModel>(true);
    model->load<VertexPNT>(L"Resource/ModularCharacterPBR.glb");

    player->transform->position = player->transform->position + Vector3(0,1,0);
    player->transform->localRotation = Quaternion::CreateFromYawPitchRoll(XM_PI, 0, 0);

    // マテリアルをシェーダーを読み込んで初期化
    auto material = make_shared<Material>();
    material->shader.compile<VertexPNT>(L"Resource/AlbedoShade.hlsl");

    // テクスチャを読み込んでマテリアルに追加
    auto t = make_unique<Texture>();
    t->load(L"Resource/Albedo.png");
    material->addTexture(move(t));

    model->addMaterial(material);

    // キューブレンダラを作ってサイズを調整
    auto rb = make_unique<Rigidbody>();
    rb->gravityScale = 0;
    rb->mass = numeric_limits<float>::infinity();
    auto floor = make_unique<GameObject>(L"床",
        CubeRenderer::create<VertexPNT>(L"Resource/AlbedoShade.hlsl", L"Resource/brick-1.png"),
        move(rb),
        make_unique<AABBCollider>());
    floor->transform->localPosition = Vector3(0.0f, -0.5f, 0.0f);
    floor->transform->localScale = Vector3(5, 1, 5);

    // -- カメラ --
    auto cameraBehaviour = make_unique<CameraBehaviour>();
    cameraBehaviour->player = player->GetComponent<Player>(true);

    // -- ライト --
    auto light = make_unique<GameObject>(L"ライト",
        make_unique<Light>());
    light->transform->localRotation = Quaternion::CreateFromYawPitchRoll(0.2f, 0.9f, 0);

    // シーンを作って戻す
    return make_unique<Scene>(

        make_unique<GameObject>(L"オブジェクトルート",
            move(player),
            move(floor)
        ),

        move(light),

        make_unique<GameObject>(L"カメラルート",
            make_unique<Camera>(),
            move(cameraBehaviour)
        )
    );
}
