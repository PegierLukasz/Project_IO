#include "Enemy.h"

void Enemy::initEnemy()
{
	this->damage = 1.f;
	this->movementSpeed = 2.5f;
	this->maxHP = 6.f;
	this->HP = maxHP;
	this->isInRange = false;
	this->bulletSize = 1.f;
	this->enemy.setRadius(10.f);
	this->enemy.setFillColor(sf::Color::Blue);
	this->enemy.setOutlineThickness(1.f);
	this->enemy.setOutlineColor(sf::Color::Black);
	this->initEnemyHealthBar();

	this->enemyRange = 100.f;

	this->attackDelayMax = 60.f;
	this->attackDelay = this->attackDelayMax;
}

void Enemy::initEnemyHealthBar()
{
	this->hpBarBack.setSize(sf::Vector2f(15.f, 3.f));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(this->enemy.getPosition());

	this->hpBarFront.setSize(sf::Vector2f(15.f, 3.f));
	this->hpBarFront.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarFront.setPosition(this->hpBarBack.getPosition());
}

void Enemy::updateEnemyHPBar()
{
	float currentHealth = this->HP / maxHP;

	this->hpBarFront.setSize(sf::Vector2f(15.f*currentHealth, 3.f));

	this->hpBarBack.setPosition(this->enemy.getPosition().x + this->enemy.getGlobalBounds().width / 8, this->enemy.getPosition().y + this->enemy.getGlobalBounds().height);
	this->hpBarFront.setPosition(this->hpBarBack.getPosition());
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initEnemy();
	this->enemy.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::Vector2f& Enemy::getEnemyPos() const
{
	return this->enemy.getPosition();
}

const sf::FloatRect Enemy::getEnemyBounds() const
{
	return this->enemy.getGlobalBounds();
}

const bool Enemy::canAttack()
{
	if (this->attackDelay >= this->attackDelayMax)
	{
		this->attackDelay = 0.f;
		return true;
	}
	return false;
}

const bool Enemy::isDead()
{
	if (this->HP <= 0) return true;
	return false;
}


float Enemy::getEnemyDamage()
{
	return damage;
}

float Enemy::getMovementSpeed()
{
	return movementSpeed;
}

float Enemy::getEnemyRange()
{
	return enemyRange;
}

float Enemy::getEnemyBulletSize()
{
	return this->bulletSize;
}

const bool Enemy::checkIfInRange()
{
	if (this->isInRange) return true;
	return false;
}

void Enemy::randMove()
{
	int randNum;
	if (this->isInRange)
	{
		srand(time(NULL));
		randNum = rand() % (8 - 1 + 1) + 1;
		if (randNum == 1) this->enemy.move(1.f, 0.f);
		if (randNum == 2) this->enemy.move(-1.f, 0.f);
		if (randNum == 3) this->enemy.move(0.f, 1.f);
		if (randNum == 4) this->enemy.move(0.f, -1.f);
		if (randNum == 5) this->enemy.move(1.f, 1.f);
		if (randNum == 6) this->enemy.move(-1.f, -1.f);
		if (randNum == 7) this->enemy.move(1.f, -1.f);
		if (randNum == 8) this->enemy.move(-1.f, 1.f);
	}
}

void Enemy::moveEnemy(const float x, const float y)
{
	this->enemy.move(movementSpeed * x, movementSpeed * y);
}

void Enemy::setRange()
{
	this->isInRange = true;
}

void Enemy::setRangeFalse()
{
	this->isInRange = false;
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->enemy);
	this->renderEnemyHPBar(target);
}

void Enemy::renderEnemyHPBar(sf::RenderTarget* target)
{
	target->draw(this->hpBarBack);
	target->draw(this->hpBarFront);
}

void Enemy::update()
{
	this->updateAttack();
	this->randMove();
	this->updateHealthStatus();
	this->updateEnemyHPBar();
}

void Enemy::updateHealthStatus()
{
	float currentHealth = this->HP / maxHP;
	if (currentHealth > 0.75)
	{
		this->enemy.setOutlineColor(sf::Color::Green);
	}
	if (currentHealth <= 0.75)
	{
		this->enemy.setOutlineColor(sf::Color::Yellow);
	}
	if (currentHealth <= 0.50)
	{
		this->enemy.setOutlineColor(sf::Color::Color(252, 186, 3, 255)); //ORANGE
	}
	if (currentHealth <= 0.25)
	{
		this->enemy.setOutlineColor(sf::Color::Red);
	}
}

void Enemy::updateAttack()
{
	if (this->attackDelay < this->attackDelayMax)
		this->attackDelay += 1.f;

	if (this->attackDelayMax <= 5.f)
		this->attackDelayMax = 5.f;
}

void Enemy::takeDamage(float damage)
{
	this->HP = this->HP - damage;
}

void Enemy::setEnemyPosition(float pos_x, float pos_y)
{
	this->enemy.setPosition(pos_x, pos_y);
}

void Enemy::buffEnemies()
{
	int number = this->rollBuff();
	std::cout << "Buff wylosowany :" << number << std::endl;

	if (number == 1)
	{
		this->maxHP += 2.f;
		this->HP = maxHP;
	}
	if (number == 2)
	{
		this->enemyRange += 10.f;
	}
	if (number == 3)
	{
		this->attackDelayMax -= 5.f;
		this->attackDelay = this->attackDelayMax;
	}
	if (number == 4)
	{
		this->damage += 0.25f;
	}
	if (number == 5)
	{
		this->bulletSize += 0.25f;
	}
}

double Enemy::rollBuff()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> randNum(0.f, 5.f); // 1 to 5

	double randNumber = randNum(mt);
	randNumber = ceil(randNumber);


	return randNumber;
}

