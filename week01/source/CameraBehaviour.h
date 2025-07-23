#pragma once

#include <UniDx.h>
#include <Behaviour.h>


class Player;

class CameraBehaviour : public UniDx::Behaviour
{
public:
    Player* player;

    virtual void OnEnable() override;
    virtual void Update() override;
};