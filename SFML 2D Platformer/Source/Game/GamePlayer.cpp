#include "GamePlayer.h"

//--------------------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------

/////////////////////////////////////////////
//
/////////////////////////////////////////////
LJMU::GamePlayer::GamePlayer(LJMUPlayerControls& pcontrols, sf::Vector2f pspawnpos)
	:ILJMUObjectState(),
	Controls(pcontrols),
	SpawnPos(pspawnpos),
	Speed(static_cast<float>(DEF_SPEED)),
	Lives(DEF_LIVES),
	IdleFrame(0),
	LastChange(sf::seconds(0)),
	isMoving(false),
	isJumping(false),
	state(PlayerState::WALKING),
	scale(0.2f),
	onPlatform(true),
	xVelocity(0.f),
	yVelocity(0.f),
	isSprinting(false),
	jumpWasPressed(false),
	previousPosition(pspawnpos),
	collidingLeft(false),
	collidingRight(false),
	beingPushed(false),
	levelCompleted(false)
{
	//Load textures for player
	this->_player_anim_textures.load(PlayerAnimTextures::idleTexture, "Assets/Animations/LevelPlayer/Idle.png");
	this->_player_anim_textures.load(PlayerAnimTextures::walkTexture, "Assets/Animations/LevelPlayer/Walk.png");
	this->_player_anim_textures.load(PlayerAnimTextures::jumpTexture, "Assets/Animations/LevelPlayer/Jump.png");

	//Create animation sequences and add to vector of animation sequences.
	//Idle
	int numFrames = 10;
	int frameWidth = 273;
	int frameHeight = 463;
	sf::LJMUAnimSeq idle_seq;
	//Add the animation frames
	for (int i = 0; i < numFrames; i++)
		idle_seq.addFrame(sf::IntRect(0 + i * frameWidth, 0, frameWidth, frameHeight));
	idle_seq.setSpriteSheet(this->_player_anim_textures.get(PlayerAnimTextures::idleTexture));
	_player_anim_sequences.push_back(idle_seq);

	//Walk
	numFrames = 8;
	frameWidth = 370;
	frameHeight = 463;
	sf::LJMUAnimSeq walk_seq;
	//Add the animation frames
	for (int i = 0; i < numFrames; i++)
		walk_seq.addFrame(sf::IntRect(0 + i * frameWidth, 0, frameWidth, frameHeight));
	walk_seq.setSpriteSheet(this->_player_anim_textures.get(PlayerAnimTextures::walkTexture));
	_player_anim_sequences.push_back(walk_seq);

	//Jump
	numFrames = 10;
	frameWidth = 390;
	frameHeight = 463;
	sf::LJMUAnimSeq jump_seq;
	//Add the animation frames
	for (int i = 0; i < numFrames; i++)
		jump_seq.addFrame(sf::IntRect(0 + i * frameWidth, 0, frameWidth, frameHeight));
	jump_seq.setSpriteSheet(this->_player_anim_textures.get(PlayerAnimTextures::jumpTexture));
	_player_anim_sequences.push_back(jump_seq);


	//Create animation sequences
	//Set the animation to the idle sequence
	Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::idleSeq]);
	Player.setScale(scale,scale);
	sf::setOriginCentre(Player);

	this->Player.setFrameTime(sf::seconds(0.07f));
	this->Player.setPosition(pspawnpos);
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////
LJMU::GamePlayer::~GamePlayer()
{

}

//---------------------PUBLIC METHODS---------------------------------------------------------------

/////////////////////////////////////////////
// Update the player 
/////////////////////////////////////////////
void LJMU::GamePlayer::update(sf::Time& ptpf,sf::Time& ptotal)
{
	previousPosition = Player.getPosition();

	//Handle movement
	handleMovement(ptpf);

	//Handle Animation states
	handleAnimationStates();

	//Update animated sprite
	this->Player.update(ptpf);

	//Reset collision check bools
	onPlatform = false;
	collidingLeft = false;
	collidingRight = false;
}

void::LJMU::GamePlayer::handleAnimationStates()
{
	switch (state)
	{
		case PlayerState::IDLE:
		{
			if (isJumping)
			{
				Player.setLooping(false);
				Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::jumpSeq]);
				state = PlayerState::JUMPING;
				break;
			}
			if (isMoving)
			{
				Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::walkSeq]);
				state = PlayerState::WALKING;
				break;
			}
			break;
		}

		case PlayerState::WALKING:
		{
			if (isJumping)
			{
				Player.setLooping(false);
				Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::jumpSeq]);
				state = PlayerState::JUMPING;
				break;
			}
			
			if (!isMoving)
			{
				Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::idleSeq]);
				state = PlayerState::IDLE;
				break;
			}
			break;
		}
		
		case PlayerState::JUMPING:
		{
			if (onPlatform)
			{
				
				if (isMoving)
				{
					Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::walkSeq]);
					Player.setLooping(true);
					Player.play();
					state = PlayerState::WALKING;
					break;
				}

				Player.setAnimation(_player_anim_sequences[PlayerAnimSeq::idleSeq]);
				Player.setLooping(true);
				Player.play();
				state = PlayerState::IDLE;
				break;
			}
			break;
		}
	}
}

void::LJMU::GamePlayer::handleMovement(sf::Time& ptpf)
{
	//Reset x velocity (if not being pushed)
	if (!beingPushed)
		xVelocity = 0;
	
	//If on a platform, no y downward movement. Otherwise (in air), apply gravity (cap the speed at MAX_FALL_SPEED)
	if (onPlatform)
		yVelocity = 0.f;
	else
		yVelocity = std::min(MAX_FALL_SPEED, yVelocity + GRAVITY * ptpf.asSeconds());

	//Check for Movement (left and right), add velocity in X
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_RIGHT) && !beingPushed)
	{
		if (!collidingRight)
			xVelocity = 1.0f;
		Player.setScale(scale, scale);
		isMoving = true;
	}
	else if (this->Controls.isActive(LJMUPlayerActions::MOVE_LEFT) && !beingPushed)
	{
		if (!collidingLeft)
			xVelocity = -1.0f;
		Player.setScale(-scale, scale);
		isMoving = true;
	}
	else
		isMoving = false;

	//Check for Jumping (can only jump if on a platform, not im midair)
	const bool tjumpPressed = this->Controls.isActive(LJMUPlayerActions::JUMP);
	if (tjumpPressed && !jumpWasPressed && onPlatform)
	{
		isJumping = true;
		yVelocity = JUMP_VELOCITY;
		//Lift player up, to stop colliding with platform
		Player.setPosition(Player.getPosition().x, Player.getPosition().y - 5.1f);
		onPlatform = false;
	}
	jumpWasPressed = tjumpPressed;

	//Check for Sprinting
	if (this->Controls.isActive(LJMUPlayerActions::SPRINT))
		isSprinting = true;
	else
		isSprinting = false;

	sf::Vector2f tvel(xVelocity, yVelocity);
	
	//Apply final movement
	if (isSprinting)
		this->Player.move(sf::Vector2f(tvel.x * SPRINT_X_MULTIPLIER, tvel.y * SPRINT_Y_MULTIPLIER) * this->Speed * ptpf.asSeconds());
	else
		this->Player.move(tvel * this->Speed * ptpf.asSeconds());
}

void LJMU::GamePlayer::checkCollision(GameObjectBasic& telem)
{
	const sf::FloatRect telemBounds = telem.getSpriteRO().getGlobalBounds();
	const sf::FloatRect tplayerBounds = Player.getGlobalBounds();

	if (telem.getIsGoal())
	{
		if (telemBounds.intersects(tplayerBounds) && isJumping)
			levelCompleted = true;
		return;
	}

	if (telem.getIsTrap())
	{
		if (!beingPushed && telemBounds.intersects(tplayerBounds))
		{
			Player.move(0.f, -5.1f);
			onPlatform = false;
			beingPushed = true;
			yVelocity = -3.f;

			if (xVelocity > 0.f)
				xVelocity = -1.f;
			else if (xVelocity < 0.f)
				xVelocity = 1.f;
			else
				xVelocity = (rand() % 2 == 0) ? -1.f : 1.f;
		}
		return;
	}

	const sf::Vector2f tmovement = Player.getPosition() - previousPosition;
	const sf::FloatRect tpreviousBounds(
		tplayerBounds.left - tmovement.x,
		tplayerBounds.top - tmovement.y,
		tplayerBounds.width,
		tplayerBounds.height);

	const float tplayerTop = tplayerBounds.top;
	const float tplayerBottom = tplayerBounds.top + tplayerBounds.height;
	const float tplayerLeft = tplayerBounds.left;
	const float tplayerRight = tplayerBounds.left + tplayerBounds.width;
	const float tpreviousTop = tpreviousBounds.top;
	const float tpreviousBottom = tpreviousBounds.top + tpreviousBounds.height;
	const float tpreviousLeft = tpreviousBounds.left;
	const float tpreviousRight = tpreviousBounds.left + tpreviousBounds.width;
	const float telemTop = telemBounds.top;
	const float telemBottom = telemBounds.top + telemBounds.height;
	const float telemLeft = telemBounds.left;
	const float telemRight = telemBounds.left + telemBounds.width;
	const float tcontactTolerance = 5.f;

	const bool thorizontalOverlap = tplayerRight > telemLeft && tplayerLeft < telemRight;
	const bool tverticalOverlap = tplayerBottom > telemTop && tplayerTop < telemBottom;

	// Previous and current bounds provide a swept check, preventing fast falls
	// and jumps from passing completely through a platform between frames.
	if (yVelocity >= 0.f && thorizontalOverlap &&
		tpreviousBottom <= telemTop + tcontactTolerance &&
		tplayerBottom >= telemTop - tcontactTolerance)
	{
		Player.move(0.f, telemTop - tplayerBottom);
		yVelocity = 0.f;
		onPlatform = true;
		beingPushed = false;
		isJumping = false;
		return;
	}

	if (yVelocity < 0.f && thorizontalOverlap &&
		tpreviousTop >= telemBottom - tcontactTolerance && tplayerTop <= telemBottom)
	{
		Player.move(0.f, telemBottom - tplayerTop);
		yVelocity = 0.f;
		return;
	}

	if (xVelocity > 0.f && tverticalOverlap &&
		tpreviousRight <= telemLeft && tplayerRight >= telemLeft)
	{
		Player.move(telemLeft - tplayerRight, 0.f);
		xVelocity = 0.f;
		collidingRight = true;
		return;
	}

	if (xVelocity < 0.f && tverticalOverlap &&
		tpreviousLeft >= telemRight && tplayerLeft <= telemRight)
	{
		Player.move(telemRight - tplayerLeft, 0.f);
		xVelocity = 0.f;
		collidingLeft = true;
	}
}
