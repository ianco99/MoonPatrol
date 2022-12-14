#include "Player.h"
#include "Enemy.h"
#include "raymath.h"

extern Player* player;
extern bool playing;

int spawnOffset = 10;

Enemy::Enemy(float radius, float damage, float speed)
{
	this->radius = radius;
	this->damage = damage;
	this->speed = speed;

	this->position = { 0,0 };
}

void Enemy::ChangePosition(Vector2 newPosition)
{
	this->position = newPosition;
}

void Enemy::Move()
{
	this->CheckLimits();

	Vector2 newPos;

	newPos = { this->position.x + speed * GetFrameTime(), this->position.y };

	this->position = newPos;

	if (CheckCollision())
	{
		playing = false;
	}
}

void Enemy::DealDamage()
{

}

void Enemy::CheckLimits()
{
	if (this->position.x <= 0)
	{
		this->position.x = GetScreenWidth() + spawnOffset;
	}
}

bool Enemy::CheckCollision()
{
	double distX = static_cast<double>(player->GetPosition().x) - static_cast<double>(this->position.x);
	double distY = static_cast<double>(player->GetPosition().y) - static_cast<double>(this->position.y);

	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= player->GetRadius() + this->radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::Draw()
{
	DrawCircleV(this->position, this->radius, RAYWHITE);
}