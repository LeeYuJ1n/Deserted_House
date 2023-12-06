#include "Framework.h"

BulletManager::BulletManager()
{
    bullets.resize(30);

    for (Bullet*& bullet : bullets)
        bullet = new Bullet();
}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)
        delete bullet;
}

void BulletManager::Update()
{
    for (Bullet* bullet : bullets)
        bullet->Update();
}

void BulletManager::Render()
{
    for (Bullet* bullet : bullets)
        bullet->Render();
}

void BulletManager::Fire(Vector2 pos, Vector2 direction)
{
    for (Bullet* bullet : bullets)
    {
        if (!bullet->Active())
        {
            bullet->Fire(pos, direction);
            return;
        }
    }
}
