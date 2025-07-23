#pragma once

#include "CameraBehaviour.h"

#include <Transform.h>
#include <Input.h>
#include <UniDxTime.h>

#include "Player.h"


using namespace DirectX;
using namespace UniDx;


void CameraBehaviour::OnEnable()
{
    Quaternion rot = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), 0.3f);
    transform->localRotation = rot;
}


void CameraBehaviour::Update()
{
    transform->position = player->transform->position + Vector3(0, 4, -8);

    const float speed = 1;

    Vector3 pos = transform->localPosition;
    if (Input::GetKey(Keyboard::A))
    {
        pos.x -= speed * Time::deltaTime;
    }
    if (Input::GetKey(Keyboard::D))
    {
        pos.x += speed * Time::deltaTime;
    }
    if (Input::GetKey(Keyboard::W))
    {
        pos.y += speed * Time::deltaTime;
    }
    if (Input::GetKey(Keyboard::S))
    {
        pos.y -= speed * Time::deltaTime;
    }
    if (Input::GetKey(Keyboard::Q))
    {
        pos.z += speed * Time::deltaTime;
    }
    if (Input::GetKey(Keyboard::E))
    {
        pos.z -= speed * Time::deltaTime;
    }
    transform->localPosition = pos;

    const float angleSpeed = 1.0f;
    Quaternion localRot = transform->localRotation;
    Quaternion rot;
    if (Input::GetKey(Keyboard::J))
    {
        rot = Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), -angleSpeed * Time::deltaTime);
    }
    if (Input::GetKey(Keyboard::K))
    {
        rot = Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), angleSpeed * Time::deltaTime);
    }
    transform->localRotation = localRot * rot;
}
