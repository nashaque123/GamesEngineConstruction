#pragma once
#include "NonShooterEntity.h"
class BackgroundEntity : public NonShooterEntity
{
public:
	BackgroundEntity(std::string spriteName, int numberOfFramesX = 1, int numberOfFramesY = 1, bool isAnimated = false);
	~BackgroundEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::eNeutral; }

	void SetOffsetSpeed(float speed) { m_speed = speed; }
	float GetBackWidth() const { return m_backWidth; }

private:
	float m_speed{ 0 };
	const float m_backWidth{ 1000.f };
};

