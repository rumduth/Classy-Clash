#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
class BaseCharacter
{
public:
    BaseCharacter();
    void setWorldPos(Vector2 v);
    Vector2 getWorldPos() { return worldPos; }
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) {alive = isAlive;}

protected:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 worldPos;
    float rightLeft;
    float runningTime;
    int frame;
    const int maxFrame = 6;
    const float updateTime = 1.f / 12.f;
    float speed = 4.f;
    const float scale = 4.f;
    Vector2 velocity{};
private:
    bool alive{true};
};

#endif
