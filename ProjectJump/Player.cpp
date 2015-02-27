#include "Player.h"
#include "preproceccors.h"
#include "BubbleList.h"



Player::Player(LPDIRECT3DDEVICE9 d3d)
	: offset(PLAYER_RADIUS*2), radius(PLAYER_RADIUS), Sprite(d3d, PLAYER_TEXTURE){

	D3DXVECTOR3 zero(offset, offset, 0.0f);
	center = zero;
	
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT -150;

	setPosition();
	
	velocity = new Velocity(1.0f);
	xVelocity = new Velocity(0.0f, X_TOP_SPEED);
	atMaxHeight = false; 

	score = 0;
	hasCollided = false;


}


Player::~Player(void) {}

void Player::checkHeight(){

	Vector *v = velocity->getVector();

	if( v->size < 0 && v->direction
		|| v->size > 0 && !v->direction) velocity->flipVelocity();
	

	//player should be moved
	if(y <= WINDOW_HEIGHT - MAX_PLAYER_HEIGHT 
		&& v->direction){
		
			atMaxHeight = false;
	}
	 //bubbles should be moved
	else if(y <= WINDOW_HEIGHT - MAX_PLAYER_HEIGHT
		&& !v->direction )  {
		
		atMaxHeight = true;
	}
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
			return;
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
std::string Player::getFormatedScore(){
	std::string formated = bigIntegerToString(score);

	for(unsigned int i = 3; i < formated.length(); i+=4){
		formated.insert(formated.end()-i,',');
	}
	return formated;
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

//TODO: implement so that we can display a BigInt in a FloatingScore
BigInteger Player::getScore() const{
	return score; 
}

bool Player::getCollision() const{
	return hasCollided;
}