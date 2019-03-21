#pragma once
#include <string>
#include "Vector2.h"
#include "EAnimationStateMachine.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;

enum class ESide
{
	ePlayer,
	eEnemy,
	eNeutral,
	eBomb
};

class Visualisation;

class WorldEntity
{
public:
	WorldEntity(std::string spriteName, int numberOfFramesX, int numberOfFramesY, bool isAnimated, int frameWidth, int frameHeight);
	virtual ~WorldEntity();

	virtual void Update() = 0;
	virtual ESide GetSide() const = 0;

	void Render(Visualisation &graphics );
	void RenderFast(Visualisation &graphics);

	void AnimationStateMachine();
	
	void SetPosition(Vector2 newPos) { m_position = newPos; }
	void SetPosition(float newX, float newY) { m_position.posX = newX; m_position.posY = newY; }
	void SetAlive(bool alive) { m_alive = alive; }
	void SetAnimationStatus(EAnimationStateMachine animation) { m_animationStatus = animation; }

	Vector2 GetPosition() const { return m_position; }
	bool GetAlive() const { return m_alive; }
	int GetHealth() const { return m_health; }
	bool GetIsAnimated() const { return m_isAnimated; }
	EAnimationStateMachine GetAnimationStatus() const { return m_animationStatus; }
	int GetCollisionCost() const { return m_collisionCost; }
	int GetFrameWidth() const { return m_frameWidth; }
	int GetFrameHeight() const { return m_frameHeight; }

	bool CheckForCollision(const WorldEntity &other);
	void TakeDamage(int damage);

protected:
	Vector2 m_position;
	std::string m_spriteName;
	int m_frameWidth, m_frameHeight, m_noOfFramesX, m_noOfFramesY, m_frameNumber{ 0 };
	EAnimationStateMachine m_animationStatus{ EAnimationStateMachine::eAlive };

	void RunAnimation();
	void DeathAnimation();
	void AttackAnimation();

	int m_health{ 100 }, m_collisionCost;
	bool m_alive{ true };

	DWORD m_lastTimeAnimated{ 0 }, m_animationTime{ 150 };
	bool m_isAnimated{ false };

	const float m_speed{ 3.2f }, m_diagonalSpeed{ (float)sqrt((m_speed * m_speed) * 2) / 2 };
};