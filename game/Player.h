#pragma once

#include "Bullet.h"

class Player
{
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	bool canPlaceWall;

	sf::Font font;
	sf::Text numberOfWallsText;
	void initFonts();
	void initText();

	int numberOfWalls;
	float offset;

	float damage;
	float HP;
	float maxHP;
	float attackDelay;
	float attackDelayMax;
	float movementSpeed;
	float bulletSize;

	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarFront;
	sf::RectangleShape wallIcon;
	sf::RectangleShape wallIconBackground;

	void initPlayerHealthBar();
	void updatePlayerHPBar();

	void initPlayerWallHud();
	void updatePlayerWallHud();
	void updateCanPlaceWall();
	void updateWallOffset();

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect& getGlobalBounds() const;
	const bool canAttack();

	//Accessors
	float getPlayerMovementSpeed();
	float getPlayerDamage();
	float getPlayerHP();
	float getPlayerReloadTime();
	float getPlayerBulletSize();
	bool getPlaceWallStatus();

	//Functions
	void movePlayer(const float x, const float y);
	void setPosition(float pos_x, float pos_y);
	void update();
	void render(sf::RenderTarget* target);
	void renderPlayerHPBar(sf::RenderTarget* target);
	void renderPlayerWallHud(sf::RenderTarget* target);
	void updateAttack();
	void takeDamage(float damage);
	void wallPlaced();

	void giveItem(std::string itemType);

	const bool isDead();
};
