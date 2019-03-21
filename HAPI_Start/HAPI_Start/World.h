#pragma once
#include <vector>
#include <HAPI_lib.h>

class Visualisation;
class Sound;
class WorldEntity;
class BulletEntity;
class ShooterEntity;
class MonsterEnemy;
class Sprite;

using namespace HAPISPACE;

class World
{
public:
	World();
	~World();

	void Run();
	void Fire(const ShooterEntity &shooter);
	void DropBomb(const ShooterEntity &shooter);
	void RestartGame();

private:
	const DWORD m_kTickRate{ 20 };
	DWORD m_lastTimeUpdated{ 0 };

	Visualisation *m_graphics{ nullptr };
	Sound *m_audio{ nullptr };

	std::vector<WorldEntity*> m_backgroundVector;
	std::vector<WorldEntity*> m_entityVector;
	std::vector<ShooterEntity*> m_shooterVector;
	std::vector<MonsterEnemy*> m_monsterEntity;
	std::vector<BulletEntity*> m_bulletsVector;
	std::vector<BulletEntity*> m_bombVector;
	std::vector<WorldEntity*> m_healthVector;

	const int kNumBullets{ 20 }, kNumBombs{ 1 };
	int numHearts, score, timeToIncreaseScore;

	bool LoadLevel();
	void Update();
};

