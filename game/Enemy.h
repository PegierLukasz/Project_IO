#pragma once

#include "Item.h"



class Enemy
{
private:
	sf::CircleShape enemy;

	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarFront;	

	float HP;
	float maxHP;
	float damage;
	float movementSpeed;
	float attackDelay;
	float attackDelayMax;
	bool isInRange;
	float enemyRange;
	float bulletSize;

	void initEnemyHealthBar();
	void updateEnemyHPBar();
	void initEnemy();

public:
	Enemy(float pos_x, float pos_y);
	~Enemy();

	const sf::Vector2f& getEnemyPos() const;
	const sf::FloatRect getEnemyBounds() const;
	const bool canAttack();
	const bool isDead();

	//accessors
	float getEnemyDamage();
	float getMovementSpeed();
	float getEnemyRange();
	float getEnemyBulletSize();

	const bool checkIfInRange();
	void randMove();
	void moveEnemy(const float x, const float y);
	void setRange();
	void setRangeFalse();
	void render(sf::RenderTarget* target);
	void renderEnemyHPBar(sf::RenderTarget* target);
	void update();
	void updateHealthStatus();
	void updateAttack();
	void takeDamage(float damage);
	void setEnemyPosition(float pos_x, float pos_y);
	void buffEnemies();
	double rollBuff();
};

