#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::setWorldPos(Vector2 v)
{
    worldPos = v;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, scale * idle.width / 6.f, scale * (float)idle.height};
}

void BaseCharacter::tick(float deltaTime)
{
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;
        if (frame == maxFrame)
            frame = 0;
    }
    if (Vector2Length(velocity) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    Rectangle source{frame * (float)texture.width / 6.f, 0.0, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * (float)texture.width / 6.f, scale * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{0.0, 0.0}, 0.0, WHITE);
}