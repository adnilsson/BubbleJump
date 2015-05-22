#include "Player.h"
#include "preproceccors.h"
#include "BubbleList.h"



Player::Player(LPDIRECT3DDEVICE9 d3d)
	: offset(PLAYER_SPRITE_WIDTH / 2), radius(PLAYER_RADIUS), Sprite(d3d, PLAYER_TEXTURE),
	sinking(new SpriteRect(96, 128, 0, 32)), swimming(new SpriteRect(0, 32, 0, 32)){

	D3DXVECTOR3 zero(offset, offset, 0.0f);
	center = zero;

	x = WINDOW_WIDTH / 2;
	y = static_cast<FLOAT>(WINDOW_HEIGHT * 0.7857);  //700 * 0,7857 = 550 

	setPosition();

	if (SetRect(&spritePart, 0, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT) == 0){
		MessageBox(NULL,
			(LPCWSTR)L"SetRect failed in player constructor.",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
		return;
	}

	velocity = new Velocity(1.0f);
	xVelocity = new Velocity(0.0f, X_TOP_SPEED);
	atMaxHeight = false;

	score = 0;
	counter = PLAYER_ANIMATION_CONSTANT;
	hasCollided = false;
	animateForward = true;
}


Player::~Player(void) {
	if (velocity != nullptr) delete velocity;
	if (xVelocity != nullptr) delete xVelocity;
	if (sinking != nullptr) delete sinking;
	if (swimming != nullptr) delete swimming;
}

HRESULT Player::drawPlayer(LPD3DXSPRITE sprite){
	if (!isSinking()){
		if (counter == 0){
			adjustSwimFrame();
			counter += PLAYER_ANIMATION_CONSTANT;
		}
		else counter--;
	}

	if (!setSpriteRect()){
		MessageBox(NULL,
			(LPCWSTR)L"SetRect setSpriteRect failed (player.cpp).",
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK);
	}
	return drawSpritePart(sprite, spritePart);
}

void Player::checkHeight(){

	Vector *v = velocity->getVector();

	if (v->size < 0 && v->direction
		|| v->size > 0 && !v->direction) velocity->flipVelocity();


	//player should be moved
	if (y <= WINDOW_HEIGHT - MAX_PLAYER_HEIGHT
		&& v->direction){

		atMaxHeight = false;
	}
	//bubbles should be moved
	else if (y <= WINDOW_HEIGHT - MAX_PLAYER_HEIGHT
		&& !v->direction)  {

		atMaxHeight = true;
	}
}


void Player::adjustSwimFrame(){
	if (animateForward){
		swimming->xLeft += PLAYER_SPRITE_WIDTH;
		swimming->xRight += PLAYER_SPRITE_WIDTH;
		if ((swimming->xLeft) % (2 * PLAYER_SPRITE_WIDTH) == 0){
			animateForward = false;
		}
		
	}
	else{
		swimming->xLeft -= PLAYER_SPRITE_WIDTH;
		swimming->xRight -= PLAYER_SPRITE_WIDTH;
		if (swimming->xLeft == 0){
			animateForward = true;
		}
	}
}


/*Adjusts the spritePart to display the correct frame/part of the 
sprite animation*/
BOOL Player::setSpriteRect(){
	if (isSinking()){
		return SetRect(&spritePart, sinking->xLeft, sinking->yTop,
			sinking->xRight, sinking->yBottom);
	}
	
	return SetRect(&spritePart, swimming->xLeft, swimming->yTop,
			       swimming->xRight, swimming->yBottom);
}

//return true if the player was moved
bool Player::moveY(){
	checkHeight();

	if(!atMaxHeight){
		y = y + velocity->getSpeed();
		setPosition();
		return true;
	}

	return false;
}

void Player::resetX(bool leftKey){
	xVelocity->resetSpeed(leftKey);
}


void Player::moveX(){
	
	//check if player is out of bounds
	if(x + xVelocity->getSpeed() <= radius ||
		x + xVelocity->getSpeed() >= WINDOW_WIDTH - radius){ 
			return; //do nothing 
	}
	
	x += xVelocity->getSpeed(); //Increase position
	setPosition();
}


void Player::accelerate(){
	Vector *yV = velocity->getVector();
	Vector *xV = xVelocity->getVector();

	yV->size += static_cast<FLOAT>(Y_ACCEL);


	//Safe to accelerate without changing direction
	if(xV->size > 0.02){
		xV->size -= static_cast<FLOAT>(X_ACCEL);
	}
	else if(xV->size < -0.02f){
		xV->size += static_cast<FLOAT>(X_ACCEL);
	}
	else xV->size = 0.0f; //set to zero if speed is close to zero


}

//Groups the numerical value of the player's score into triplets
//i.e. 10000000 will be formated to "10,000,000"
//TODO: Remove, place as static function in parser instead
std::string Player::getFormatedScore(){
	std::string formated = bigIntegerToString(score);

	for(unsigned int i = 3; i < formated.length(); i+=4){
		formated.insert(formated.end()-i,',');
	}
	return formated;
}

std::string Player::scoreToString() const{
	return bigIntegerToString(score);
}

void Player::setCollision(bool collision){
	hasCollided = collision;
}

void Player::incScore(){
	score += Bubble::getPointValue();
}

void Player::doubleScore(){
	score *= 2;
}


bool Player::MaxHeight() const{
	return atMaxHeight;
}


//Getters
FLOAT Player::getOffset() const{
	return offset;
}

FLOAT Player::getRadius() const{
	return radius;
}

Velocity* Player::getVelocity() const{
	return velocity;
}

FLOAT Player::getSpeed() const{
	return velocity->getSpeed();
}

RECT Player::getSpritePart() const{
	return spritePart;
}


BigInteger Player::getScore() const{
	return score; 
}

bool Player::getCollision() const{
	return hasCollided;
}
