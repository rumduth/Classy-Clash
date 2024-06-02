#include "Character.h"
#include "raymath.h"
#include <iostream>
#include <string>
using namespace std;

Character::Character(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
{

    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");
    worldPos = {0.0, 0.0};

    rightLeft = 1.f;
    runningTime = 0.f;
    frame = 0;
}
Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.f - scale * (float)idle.width / 6.f * 0.5f,
        static_cast<float>(windowHeight) / 2.f - scale * (float)idle.height / 2.f};
}
void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;
    float rotation{};
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_X))
        velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);

    Vector2 origin;
    Vector2 offset{};

    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};

        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale, weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale, weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED);
}


void Character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.f)
        setAlive(false);
}