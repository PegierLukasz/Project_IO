#include "Player.h"

void Player::initFonts()
{
	if (!this->font.loadFromFile("Fonts/OpenSans-Regular.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Player::initText()
{
	this->numberOfWallsText.setCharacterSize(12);
	this->numberOfWallsText.setFillColor(sf::Color::White);
	this->numberOfWallsText.setFont(this->font);
	sf::FloatRect textRect = numberOfWallsText.getLocalBounds();
	numberOfWallsText.setOrigin(textRect.left + textRect.width / 2.0f,
	textRect.top + textRect.height / 2.0f);
}

void Player::initPlayerHealthBar()
{
	this->hpBarBack.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(20.f, 20.f);

	this->hpBarFront.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBarFront.setFillColor(sf::Color(20, 250, 20, 200));
	this->hpBarFront.setPosition(this->hpBarBack.getPosition());
}
void Player::updatePlayerHPBar()
{
	float currentHealth = this->HP / maxHP;

	this->hpBarFront.setSize(sf::Vector2f(60.f * currentHealth, 10.f));

	this->hpBarBack.setPosition(this->playerSprite.getPosition().x - 175.f, this->playerSprite.getPosition().y + 100.f);
	this->hpBarFront.setPosition(this->hpBarBack.getPosition());
}

void Player::initPlayerWallHud()
{
	this->wallIcon.setSize(sf::Vector2f(15.f, 15.f));
	this->wallIcon.setFillColor(sf::Color(20, 250, 20, 200));
	this->wallIcon.setOutlineThickness(1.f);
	this->wallIcon.setOutlineColor(sf::Color::Black);

	this->wallIconBackground.setSize(sf::Vector2f(45.f, 45.f));
	this->wallIconBackground.setFillColor(sf::Color(50, 50, 50, 200));
	this->wallIconBackground.setOutlineThickness(1.f);
	this->wallIconBackground.setOutlineColor(sf::Color::Black);
}

void Player::updatePlayerWallHud()
{
	this->wallIcon.setPosition(this->playerSprite.getPosition().x, this->playerSprite.getPosition().y + 97.f);
	this->wallIconBackground.setPosition(this->playerSprite.getPosition().x - this->wallIcon.getSize().x, this->playerSprite.getPosition().y + 100.f - this->wallIcon.getSize().y/2);
	this->numberOfWallsText.setPosition(this->wallIcon.getPosition().x+offset, this->wallIcon.getPosition().y);

	std::stringstream ss;
	ss << this->numberOfWalls << "\n";
	numberOfWallsText.setString(ss.str());

	this->updateWallOffset();
}

void Player::updateCanPlaceWall()
{
	if (this->numberOfWalls > 0)
		this->canPlaceWall = true;
	else this->canPlaceWall = false;
}

void Player::initVariables()
{
	this->damage = 2.f;
	this->maxHP = 5.f;
	this->HP = maxHP;
	this->movementSpeed = 3.f;
	this->attackDelayMax = 40.f;
	this->attackDelay = this->attackDelayMax;
	this->bulletSize = 1.f;
	this->numberOfWalls = 3;
}
void Player::initTexture()
{
	if (this->playerTexture.loadFromFile("Textures/square.png") == false)
	{
		std::cout << "PLAYER::InitTextureError\n";
	}
}
void Player::initSprite()
{
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.scale(0.050f, 0.050f);
	this->playerSprite.setPosition(1920.f / 2, 1080.f / 2);
}

Player::Player(float x, float y)
{
	this->playerSprite.setPosition(x, y);
	this->initFonts();
	this->initText();
	this->initVariables();
	this->initPlayerHealthBar();
	this->initPlayerWallHud();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->playerSprite.getPosition();
}

const sf::FloatRect& Player::getGlobalBounds() const
{
	return this->playerSprite.getGlobalBounds();
}

const bool Player::canAttack()
{
	if (this->attackDelay >= this->attackDelayMax)
	{
		this->attackDelay = 0.f;
		return true;
	}
	return false;
}

void Player::updateWallOffset()
{
	if (numberOfWalls > 9)
		this->offset = 0.f;
	else
		this->offset = 3.5f;
}

float Player::getPlayerMovementSpeed()
{
	return movementSpeed;
}

float Player::getPlayerDamage()
{
	return damage;
}

float Player::getPlayerHP()
{
	return HP;
}

float Player::getPlayerReloadTime()
{
	return attackDelayMax;
}

float Player::getPlayerBulletSize()
{
	return this->bulletSize;
}

bool Player::getPlaceWallStatus()
{
	if (canPlaceWall) return true;
	else return false;
}


void Player::movePlayer(const float x, const float y)
{
	this->playerSprite.move(movementSpeed * x, movementSpeed * y);
}

//Functions

void Player::setPosition(float pos_x, float pos_y)
{
	this->playerSprite.setPosition(pos_x, pos_y);
}

void Player::update()
{
	//Window collision
	this->updateAttack();
	this->updatePlayerHPBar();
	this->updatePlayerWallHud();
	this->updateCanPlaceWall();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->playerSprite);
	this->renderPlayerHPBar(target);
	this->renderPlayerWallHud(target);
}

void Player::renderPlayerHPBar(sf::RenderTarget* target)
{
	target->draw(this->hpBarBack);
	target->draw(this->hpBarFront);
}

void Player::renderPlayerWallHud(sf::RenderTarget* target)
{
	target->draw(this->wallIconBackground);
	target->draw(this->wallIcon);
	target->draw(this->numberOfWallsText);
}


void Player::updateAttack()
{
	if(this->attackDelay < this->attackDelayMax)
	this->attackDelay += 1.f;
}

void Player::takeDamage(float damage)
{
	this->HP = this->HP - damage;
}

void Player::wallPlaced()
{
	numberOfWalls--;
}

void Player::giveItem(std::string itemType)
{
	if (itemType == "HealingItem")
	{
		this->HP += 3.f;
		if (this->HP > this->maxHP)	this->HP = this->maxHP;
	}
	else if (itemType == "DamagingItem")
	{
		this->damage += 0.5f;
	}
	else if (itemType == "MovementSpeedItem")
	{
		this->movementSpeed += 0.25f;
	}
	else if (itemType == "FasterShootingItem")
	{
		this->attackDelayMax -= 5.f;
		if (this->attackDelayMax <= 5.f)	this->attackDelayMax = 5.f;
	}
	else if (itemType == "BulletSizeItem")
	{
		this->bulletSize += 0.125f;
	}
	else if (itemType == "WallItem")
	{
		this->numberOfWalls += 3;
	}
}

const bool Player::isDead()
{
	if (this->HP <= 0) return true;
	return false;
}