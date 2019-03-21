#include "World.h"
#include "Visualisation.h"
#include "Sound.h"
#include "BackgroundEntity.h"
#include "PlayerEntity.h"
#include "HorseEnemy.h"
#include "MonsterEnemy.h"
#include "BulletEntity.h"
#include <cassert>

World::World()
{
}

World::~World()
{
	//Delete all the pointers when program closes
	delete m_graphics;
	delete m_audio;

	for (auto p : m_entityVector)
		delete p;

	for (auto p : m_backgroundVector)
		delete p;

	for (auto p : m_healthVector)
		delete p;

	for (auto p : m_bombVector)
		delete p;
}

void World::Run()
{
	//Create graphics system and initialise program 
	m_graphics = new Visualisation;
	
	if (!m_graphics->Initialise(1000, 800))
		return;

	if (!LoadLevel())
		return;

	Update();
}

bool World::LoadLevel()
{
	//Load the sound effects
	if (!m_audio->LoadSound("Data\\laser.wav"))
		return false;

	if (!m_audio->LoadSound("Data\\bomb_sound.wav"))
		return false;

	if (!m_audio->LoadSound("Data\\player_hurt.wav"))
		return false;

	if (!m_audio->LoadSound("Data\\enemy_hurt.wav"))
		return false;

	//Load all the sprites
	if (!m_graphics->CreateSprite("Data\\player_sprite.png", "player", 4, 2))
		return false;

	if (!m_graphics->CreateSprite("Data\\background1.tga", "background"))
		return false;

	if (!m_graphics->CreateSprite("Data\\background_clouds.tga", "clouds"))
		return false;

	if (!m_graphics->CreateSprite("Data\\pegasus.png", "enemy_horse", 4, 1))
		return false;

	if (!m_graphics->CreateSprite("Data\\flying_monster.png", "enemy_monster", 6, 3))
		return false;

	if (!m_graphics->CreateSprite("Data\\bullet.png", "bullet"))
		return false;

	if (!m_graphics->CreateSprite("Data\\explosion.png", "bomb", 7, 2))
		return false;

	if (!m_graphics->CreateSprite("Data\\heart.png", "heart"))
		return false;

	//Create all the sprites
	BackgroundEntity *newBackground = new BackgroundEntity("background");
	m_backgroundVector.push_back(newBackground);
	newBackground->SetPosition(Vector2(0.f, 295.f));
	newBackground->SetOffsetSpeed(0.5f);

	BackgroundEntity *newBackgroundScroll = new BackgroundEntity("background");
	m_backgroundVector.push_back(newBackgroundScroll);
	newBackgroundScroll->SetPosition(Vector2(newBackground->GetPosition().posX + newBackgroundScroll->GetBackWidth(), 295.f));
	newBackgroundScroll->SetOffsetSpeed(0.5f);

	BackgroundEntity *newClouds = new BackgroundEntity("clouds");
	m_backgroundVector.push_back(newClouds);
	newClouds->SetPosition(Vector2(0.f, 0.f));
	newClouds->SetOffsetSpeed(0.2f);

	BackgroundEntity *newCloudsScroll = new BackgroundEntity("clouds");
	m_backgroundVector.push_back(newCloudsScroll);
	newCloudsScroll->SetPosition(Vector2(newClouds->GetPosition().posX + newCloudsScroll->GetBackWidth(), 0.f));
	newCloudsScroll->SetOffsetSpeed(0.2f);

	PlayerEntity *newPlayer = new PlayerEntity("player", 4, 2, true);
	m_entityVector.push_back(newPlayer);
	m_shooterVector.push_back(newPlayer);
	newPlayer->SetPosition(Vector2(300.f, 611.f));

	HorseEnemy *newEnemyHorse = new HorseEnemy("enemy_horse", 4, 1, true);
	m_entityVector.push_back(newEnemyHorse);
	m_shooterVector.push_back(newEnemyHorse);
	newEnemyHorse->SetPosition(Vector2(10.f, 200.f));

	MonsterEnemy *newEnemyMonster = new MonsterEnemy("enemy_monster", 6, 3, true);
	m_entityVector.push_back(newEnemyMonster);
	m_shooterVector.push_back(newEnemyMonster);
	m_monsterEntity.push_back(newEnemyMonster);
	newEnemyMonster->SetPosition(Vector2(800.f, 600.f));

	MonsterEnemy *newEnemyMonster1 = new MonsterEnemy("enemy_monster", 6, 3, true);
	m_entityVector.push_back(newEnemyMonster1);
	m_shooterVector.push_back(newEnemyMonster1);
	m_monsterEntity.push_back(newEnemyMonster1);
	newEnemyMonster1->SetPosition(Vector2(100.f, 700.f));

	for (int i = 0; i < 10; i++)
	{
		BackgroundEntity *newHeart = new BackgroundEntity("heart");
		m_healthVector.push_back(newHeart);
		newHeart->SetPosition(Vector2(20.f + (i * 15.f), 30.f));
		newHeart->SetOffsetSpeed(0.f);
	}

	for (int i = 0; i < kNumBullets; i++)
	{
		BulletEntity *newBullet = new BulletEntity("bullet");
		m_bulletsVector.push_back(newBullet);
		m_backgroundVector.push_back(newBullet);
	}
	
	for (int i = 0; i < kNumBombs; i++)
	{
		BulletEntity *newBomb = new BulletEntity("bomb", 7, 2, true, 48, 48);
		m_bombVector.push_back(newBomb);
	}

	return true;
}

void World::Update()
{
	//World update
	while (HAPI.Update())
	{
		if (HAPI.GetTime() - m_lastTimeUpdated >= m_kTickRate)
		{
			HAPI.SetShowFPS(true);

			m_graphics->GreyScaleClearScreen();

			for (auto p : m_backgroundVector)
				p->Update();

			for (auto p : m_entityVector)
				p->Update();

			for (auto p : m_bombVector)
			{
				p->Update();
				p->AnimationStateMachine();
			}

			m_lastTimeUpdated = HAPI.GetTime();

			for (auto p : m_entityVector)
			{
				if (p->GetIsAnimated())
					p->AnimationStateMachine();

				//Checks collisions between player and enemies and plays both sounds if hurt
				for (auto enemy : m_entityVector)
				{
					if (p->CheckForCollision(*enemy))
					{
						p->TakeDamage(enemy->GetCollisionCost());
						enemy->TakeDamage(p->GetCollisionCost());

						m_audio->PlaySound("Data\\player_hurt.wav");
						m_audio->PlaySound("Data\\enemy_hurt.wav");
					}
					
				}

				//Checks if bullets collide with any entities
				for (auto bullet : m_bulletsVector)
				{
					if (bullet->GetAlive())
					{
						if (p->CheckForCollision(*bullet))
						{
							p->TakeDamage(bullet->GetCollisionCost());
							bullet->TakeDamage(p->GetCollisionCost());
							bullet->SetAlive(false);

							if (p->GetSide() == ESide::ePlayer)
								m_audio->PlaySound("Data\\player_hurt.wav");
							else if (p->GetSide() == ESide::eEnemy)
								m_audio->PlaySound("Data\\enemy_hurt.wav");
						}
					}
				}

				//Checks collisions for bombs
				for (auto bomb : m_bombVector)
				{
					if (bomb->GetAlive())
					{
						if (p->CheckForCollision(*bomb))
						{
							m_audio->PlaySound("Data\\bomb_sound.wav");
							p->TakeDamage(bomb->GetCollisionCost());
							bomb->TakeDamage(p->GetCollisionCost());

							if (p->GetSide() == ESide::ePlayer)
								m_audio->PlaySound("Data\\player_hurt.wav");
							else if (p->GetSide() == ESide::eEnemy)
								m_audio->PlaySound("Data\\enemy_hurt.wav");
						}

						if (bomb->GetAnimationStatus() == EAnimationStateMachine::eDead)
						{
							if (bomb->PlayExplosionAnimation())
								bomb->SetAlive(false);
						}
					}
				}
			}

			for (auto p : m_shooterVector)
			{
				if (p->GetSide() == ESide::ePlayer)
				{
					if (p->GetAlive())
					{
						//Stores players health and score
						numHearts = p->GetHealth() / 10;

						timeToIncreaseScore++;

						if (timeToIncreaseScore == 8)
						{
							score++;
							timeToIncreaseScore = 0;
						}
					}
					else
					{
						//Game over message if player dies
						//Option to restart game or close program
						HAPI.UserMessage("Your final score is " + std::to_string(score), "Game over!");

						HAPI_UserResponse response;
						HAPI.UserMessage("Would you like to restart?", "Game over!", HAPI_ButtonType::eButtonTypeYesNo, &response);

						if (response == HAPI_UserResponse::eUserResponseYes)
							RestartGame();
						else
							HAPI.Close();
					}
				}

				//Fires bullets if all checks return true
				if (p->GetAllowedToShoot())
				{
					if (p->PlayAttackAnimation())
					{
						if (p->IsFiring())
						{
							Fire(*p);
							m_audio->PlaySound("Data\\laser.wav");
						}
					}
				}

				if (p->GetAllowedToDropBomb())
					DropBomb(*p);

				//Dies if health is 0
				if (p->GetAnimationStatus() == EAnimationStateMachine::eDead)
				{
					if (p->PlayDeathAnimation())
						p->SetAlive(false);
				}
			}
			
			//Respawns dead enemies
			for (auto m : m_monsterEntity)
			{
				if (!m->GetAlive())
					m->Respawn();
			}
		}

		//Renders all the graphics
		for (auto p : m_backgroundVector)
		{
			if (p->GetAlive())
				p->RenderFast(*m_graphics);
		}

		for (int i = 0; i < numHearts; i++)
			m_healthVector[i]->Render(*m_graphics);

		for (auto p : m_entityVector)
		{
			if (p->GetAlive())
				p->Render(*m_graphics);
		}

		for (auto p : m_bombVector)
		{
			if (p->GetAlive())
				p->Render(*m_graphics);
		}

		HAPI.RenderText(750, 30, HAPI_TColour(110, 55, 70), "Score: " + std::to_string(score), 20, eBold);
	}
}

//Function to fire a bullet
void World::Fire(const ShooterEntity &shooter)
{
	for (auto p : m_bulletsVector)
	{
		if (!p->GetAlive())
		{
			p->SetAlive(true);
			p->SetAnimationStatus(EAnimationStateMachine::eAlive);
			p->SetSide(shooter.GetSide());

			if (p->GetSide() == ESide::ePlayer)
				p->SetPosition(shooter.GetPosition().posX + 60.f, shooter.GetPosition().posY + 22.f);
			else if (p->GetSide() == ESide::eEnemy)
				p->SetPosition(shooter.GetPosition().posX + 2.f, shooter.GetPosition().posY + 33.f);
			
			return;
		}
	}
}

//Function for horse to drop bomb
void World::DropBomb(const ShooterEntity &shooter)
{
	for (auto p : m_bombVector)
	{
		if (!p->GetAlive())
		{
			p->SetAlive(true);
			p->SetAnimationStatus(EAnimationStateMachine::eAlive);
			p->SetSide(ESide::eBomb);
			p->SetPosition(shooter.GetPosition().posX + 30.f, shooter.GetPosition().posY + 64.f);
			return;
		}
	}
}

void World::RestartGame()
{
	for (auto p : m_shooterVector)
		p->Respawn();

	for (auto p : m_bulletsVector)
		p->SetAlive(false);

	for (auto p : m_bombVector)
		p->SetAlive(false);

	score = 0;
	timeToIncreaseScore = 0;
}