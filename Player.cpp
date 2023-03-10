#include "Player.h"

void Player::setPosition(float x, float y) {
	this->playerPosition.x = x;
	this->playerPosition.y = y;
}

float Player::getPositionX() {
	return playerPosition.x;
}

float Player::getPositionY() {
	return playerPosition.y;
}

void Player::setSize(float w, float h) {
	this->width = w;
	this->height = h;
}

float Player::getWidth() {
	return width;
}

float Player::getHeight() {
	return height;
}

float Player::getGroundHeight() {
	return this->groundHeight;
}

void Player::setColour(sf::Color colour) {
	this->colour = colour;
}

void Player::setShapeColour(sf::Color colour) {
	rect.setFillColor(colour);
}

void Player::setShape() {
	rect.setSize({ width, height });
	rect.setPosition({ playerPosition.x, playerPosition.y });
	topBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 1.f, playerPosition.y - rect.getGlobalBounds().height / 4 });
	leftBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 - leftBound.getGlobalBounds().width, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	rightBound.setPosition({ playerPosition.x + rect.getGlobalBounds().width / 4, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	bottomBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 5.f, playerPosition.y + rect.getGlobalBounds().height / 2 + 1.f });
}

void Player::setGroundHeight(float height) {
	groundHeight = height;
}

void Player::setVelX() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !cangrapple) {
		playerVelocity.x = -5.f + indirVelX;
		animation.setStartEndPoints(400, 900);
		animation.flipped = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !cangrapple) {
		playerVelocity.x = 5.f + indirVelX;
		animation.setStartEndPoints(400, 900);
		animation.flipped = true;
	}
	else {
		animation.setStartEndPoints(0, 300);
		playerVelocity.x = indirVelX;
	}
}

void Player::setGrappleVelocity(float velx, float vely) {
	playerVelocity.x = velx;
	playerVelocity.y = vely;
}

void Player::jump() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerVelocity.y == 0 && lift == true) {
		playerVelocity.y = -15.f;
		lift = false;
		onLedge = false;
		indirVelX = 0.f;
	}

	if (playerPosition.y > (this->groundHeight)) {
		playerPosition.y = this->groundHeight;
		playerVelocity.y = 0;
		lift = true;
		animation.switchTime = 1.0;
	}

	if (playerPosition.y < (this->groundHeight)) {
		if (playerVelocity.y < 13.f) {
			playerVelocity.y += gravity;
			animation.switchTime = 0.3;
		}
	}
}

void Player::movePlayer() {
	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
	rect.setPosition(playerPosition);
	topBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 1.f, playerPosition.y - rect.getGlobalBounds().height / 4 });
	leftBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 - leftBound.getGlobalBounds().width, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	rightBound.setPosition({ playerPosition.x + rect.getGlobalBounds().width / 4, playerPosition.y - rect.getGlobalBounds().height / 4 + 15.f });
	bottomBound.setPosition({ playerPosition.x - rect.getGlobalBounds().width / 4 + 5.f, playerPosition.y + rect.getGlobalBounds().height / 2 + 1.f });
	hurtBox.setPosition(playerPosition.x + (rect.getGlobalBounds().width / 4), playerPosition.y + (rect.getGlobalBounds().height / 4));
}

void Player::update(sf::RenderWindow& window) {
	jump();
	movePlayer();
	attack();

	if (isBow) {
		animation.coordinates.top = 80;
	} else if (isAxe) {
		animation.coordinates.top = 160;
	} else {
		animation.coordinates.top = 0;
	}

	animation.Animate(rect, animation.switchTime);
	window.draw(rect);
}

sf::FloatRect Player::getBounds() {
	return rect.getGlobalBounds();
}

float Player::getVelY() {
	return playerVelocity.y;
}

sf::RectangleShape Player::getShape() {
	return rect;
}

void Player::setIndirVelX(float vel) {
	indirVelX = vel;
}

void Player::setAnchor(bool anchor) {
	anchored = anchor;
}

bool Player::getAnchor() {
	return this->anchored;
}

void Player::setVelY(float vely) {
	playerVelocity.y = vely;
}

float Player::getVelX() {
	return this->playerVelocity.x;
}

bool Player::getOnLedge() {
	return this->onLedge;
}

void Player::setOnLedge(bool onLedge) {
	this->onLedge = onLedge;
}

void Player::setDistanceBetween(sf::Vector2f targetDistance) {
	distanceBetween.x = targetDistance.x - playerPosition.x;
	distanceBetween.y = targetDistance.y - playerPosition.y;
}

sf::Vector2f Player::getDistanceBetween() {
	return this->distanceBetween;
}

float Player::getInversedDistance() {
	distance = sqrt((distanceBetween.x * distanceBetween.x) + (distanceBetween.y * distanceBetween.y));
	inverseDistance = 1.f / distance;
	return inverseDistance;
}

void Player::anchor(Platform platform) {
	setIndirVelX(0.f);

	if (getOnLedge()) {
		setGroundHeight(platform.getPositionY() - rect.getGlobalBounds().height / 2 + 1.f);
	}
	else {
		setIndirVelX(0.f);
	}
}

//grapple physics. need to take a snapshot of the hypotenuse and then pass into method. A seperate method might be needed
void Player::grapple(sf::Sprite grapplePoint, float direction) {

	setDistanceBetween(grapplePoint.getPosition());
	distance = sqrt((distanceBetween.x * distanceBetween.x) + (distanceBetween.y * distanceBetween.y));
	inverseDistance = 1.f / distance;

	float normalisedDistanceX = distanceBetween.x * inverseDistance;
	float normalisedDistanceY = distanceBetween.y * inverseDistance;
	float dropoff;

	if (rect.getGlobalBounds().intersects(grapplePoint.getGlobalBounds()) && grappletopoint == true) {
		grappletopoint = false;
		dropoff = normalisedDistanceX;
		setVelY(10.f * normalisedDistanceY);
	}

	if (dropoff < 0) {
		dropoff = dropoff * -1;
	}

	if (grappletopoint) {
		setIndirVelX(normalisedDistanceX * 10.f);
		setVelY(normalisedDistanceY * 10.f);
	}

	if (grappletopoint == false && cangrapple == true) {
		setIndirVelX(10.f * direction * dropoff);
	}

	if (getPositionY() >= getGroundHeight() - 1.f) {
		cangrapple = false;
		setIndirVelX(0.f);
	}

	setPosition((playerPosition.x + playerVelocity.x), (playerPosition.y + playerVelocity.y));
}

void Player::shoot(std::vector<Platform> ledges, sf::RenderWindow& window) {

	if (shot) {

		if (animation.flipped) {
			bullet.setPosition((playerPosition.x + rect.getGlobalBounds().width / 4), playerPosition.y);
		}
		else {
			bullet.setPosition((playerPosition.x - rect.getGlobalBounds().width / 4), playerPosition.y);
		}

		bullet.setSize({ 4.f, 4.f });
		bullet.setFillColor(sf::Color::White);

		bulletdistancex = sf::Mouse::getPosition(window).x - (bullet.getPosition().x);
		bulletdistancey = sf::Mouse::getPosition(window).y - (bullet.getPosition().y);

		float distance = sqrt((bulletdistancex * bulletdistancex) + (bulletdistancey * bulletdistancey));
		bulletInverseDistance = 1.f / distance;

		float normalisedDistanceX = bulletdistancex * bulletInverseDistance;
		float normalisedDistanceY = bulletdistancey * bulletInverseDistance;

		bulletVelocityX = normalisedDistanceX * 10.f;
		bulletVelocityY = normalisedDistanceY * 10.f;

		shot = false;
	}

	bullet.move({ bulletVelocityX, bulletVelocityY });

	for (int i = 0; i < ledges.size(); i++) {

		if (bullet.getGlobalBounds().intersects(ledges[i].getBounds())) {
			bullet.setFillColor(sf::Color::Transparent);
			break;
		}
	}

	if (bullet.getPosition().x > SCREENWIDTH ||
		bullet.getPosition().x < 0.f ||
		bullet.getPosition().y < 0.f) {
		bullet.setFillColor(sf::Color::Transparent);
	}
}

void Player::checkBounds(std::vector<Platform> platforms) {

	for (int i = 0; i < platforms.size(); i++) {

		if (bottomBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			setOnLedge(true);
			anchor(platforms[i]);
			break;
		}
		else {
			setOnLedge(false);
			setGroundHeight(SCREENHEIGHT);
		}
	}

	for (int i = 0; i < platforms.size(); i++) {

		if (rightBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			if (getVelX() > 0.f) {
				playerVelocity.x = 0.f;
				break;
			}
		}
	}

	for (int i = 0; i < platforms.size(); i++) {

		if (leftBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			if (getVelX() < 0.f) {
				playerVelocity.x = 0.f;
				break;
			}
		}
	}

	for (int i = 0; i < platforms.size(); i++) {

		if (topBound.getGlobalBounds().intersects(platforms[i].getBounds())) {
			if (getVelY() < 0.f) {
				playerVelocity.y = 0.f;
				break;
			}
		}
	}
}

void Player::setTexture() {
	texture.loadFromFile(animation.fileName);
}

void Player::setRope(sf::Sprite grapplePoint) {
	rope[0].position = sf::Vector2f(playerPosition);
	rope[0].color = sf::Color::Red;
	rope[1].position = sf::Vector2f(grapplePoint.getPosition().x, grapplePoint.getPosition().y);
	rope[1].color = sf::Color::Red;
	rope[2].position = sf::Vector2f(grapplePoint.getPosition().x, grapplePoint.getPosition().y + 2.f);
	rope[2].color = sf::Color::Red;
	rope[3].position = sf::Vector2f(playerPosition.x, playerPosition.y + 2.f);
	rope[3].color = sf::Color::Red;
	rope[4].position = sf::Vector2f(playerPosition.x, playerPosition.y);
	rope[4].color = sf::Color::Red;
}

void Player::drawRope(sf::RenderWindow& window) {
	window.draw(rope, 5, sf::LineStrip);
}

bool Player::isLeftOf(float currentPositionX, float targetPositionX) {
	if (currentPositionX < targetPositionX) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::checkGrapplePath(std::vector<Platform> ledges, sf::Sprite grapplePoint) {
	bool pathClear;

	if (!isLeftOf(playerPosition.x, grapplePoint.getPosition().x)) {
		distanceBetween.x = playerPosition.x - grapplePoint.getPosition().x;
		distanceBetween.y = grapplePoint.getPosition().y - playerPosition.y;
	}
	else {
		distanceBetween.x = grapplePoint.getPosition().x - playerPosition.x;
		distanceBetween.y = playerPosition.y - grapplePoint.getPosition().y;
	}

	distance = sqrt((distanceBetween.x * distanceBetween.x) + (distanceBetween.y * distanceBetween.y));
	float tandistance = distanceBetween.y / distanceBetween.x;
	sf::RectangleShape path;
	path.setSize({ distance, 2.f });
	path.setPosition(rect.getPosition());

	long angle = atan(tandistance) * (180 / 3.14);

	if (!isLeftOf(playerPosition.x, grapplePoint.getPosition().x)) {
		angle = (360.f - angle) + 180.f;
	}

	if (isLeftOf(playerPosition.x, grapplePoint.getPosition().x)) {
		angle = 360.f - angle;
	}

	path.setRotation(angle);
	sf::FloatRect bounds = path.getGlobalBounds();
	angle = 0.f;

	for (int i = 0; i < ledges.size(); i++) {
		if (bounds.intersects(ledges[i].getBounds())) {
			pathClear = false;
			break;
		}
		else {
			pathClear = true;
		}
	}
	return pathClear;
}

void Player::checkDoor(Level& level) {
	if (level.leverPulled && rect.getGlobalBounds().intersects(level.door.getGlobalBounds())) {

		if (level.levelTwoComplete && level.levelOneComplete) {
			level.levelThreeComplete = true;;
		}
		else if (level.levelOneComplete) {
			level.levelTwoComplete = true;
		}
		else {
			level.levelOneComplete = true;
		}
		level.levelSwitch = true;
	}
}

void Player::setHealthBarPosition(float x, float y) {
	this->healthBarX = x;
	this->healthBarY = y;
}

float Player::getHealthBarPositionX() {
	return healthBarX;
}

float Player::getHealthBarPositionY()
{
	return healthBarY;
}

float Player::getDecreaseHealth()
{
	return decreaseHealth;
}

sf::Vector2f Player::getPlayerHealth() {
	return playerHealth;
}

void Player::setPlayerHealth()
{
	playerHealth.x -= decreaseHealth;

	if (playerHealth.x < 0) {
		playerHealth.x = 0;
	}
	if (playerHealth.x == 0) {
		animation.setStartEndPoints(1400, 1500);
		setPosition(2000, 1000);
		healthBar.setFillColor(sf::Color::Transparent);
	}
}

void Player::setHealthBarShape() {
	healthBar = sf::RectangleShape(playerHealth);
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setPosition(healthBarX, healthBarY);
	healthBar.setScale(2.f, 1.f);

}

void Player::attack() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !cangrapple) {
		animation.attack = true;
	}
	if (animation.attack == true) {
		animation.setStartEndPoints(1000, 1300);
		animation.switchTime = 0.7;

		if (animation.coordinates.left >= animation.endPoint) {
			animation.attack = false;
			animation.setStartEndPoints(0, 300);
			animation.switchTime = 1;
		}
	}
}