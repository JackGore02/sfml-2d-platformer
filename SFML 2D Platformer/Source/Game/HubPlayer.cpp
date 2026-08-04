#include "HubPlayer.h"

//--------------------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------

/////////////////////////////////////////////
//
/////////////////////////////////////////////
LJMU::HubPlayer::HubPlayer(LJMUPlayerControls& pcontrols, sf::Vector2f pspawnpos)
	:ILJMUObjectState(),
	Controls(pcontrols),
	SpawnPos(pspawnpos),
	Speed(static_cast<float>(DEF_SPEED)),
	Lives(DEF_LIVES),
	IdleFrame(0),
	LastChange(sf::seconds(0)),
	isMoving(false),
	state(PlayerState::IDLE),
	moveDirection(IDLE),
	prevDirection(IDLE),
	SCALE(2.f),
	xVelocity(0.f),
	yVelocity(0.f)
{
	//Load textures for player
	this->_player_anim_textures.load(HubPlayerAnimTextures::walkUpTexture, "Assets/Animations/HubPlayer/WalkUp.png");
	this->_player_anim_textures.load(HubPlayerAnimTextures::walkSideTexture, "Assets/Animations/HubPlayer/WalkSide.png");
	this->_player_anim_textures.load(HubPlayerAnimTextures::walkDownTexture, "Assets/Animations/HubPlayer/WalkDown.png");
	//TODO: add idle

	//Create animation sequences and add to vector of animation sequences.
	//Walk Up
	int numFrames = 9;
	int frameWidth = 30;
	int	frameHeight = 51;
	sf::LJMUAnimSeq walk_up_seq;
	//Add the animation frames
	for (int i = 0; i < numFrames; i++)
		walk_up_seq.addFrame(sf::IntRect(0 + i * frameWidth, 0, frameWidth, frameHeight));
	walk_up_seq.setSpriteSheet(this->_player_anim_textures.get(HubPlayerAnimTextures::walkUpTexture));
	_player_anim_sequences.push_back(walk_up_seq);

	//Walk Down
	numFrames = 9;
	frameWidth = 30;
	frameHeight = 50;
	sf::LJMUAnimSeq walk_down_seq;
	//Add the animation frames
	for (int i = 0; i < numFrames; i++)
		walk_down_seq.addFrame(sf::IntRect(0 + i * frameWidth, 0, frameWidth, frameHeight));
	walk_down_seq.setSpriteSheet(this->_player_anim_textures.get(HubPlayerAnimTextures::walkDownTexture));
	_player_anim_sequences.push_back(walk_down_seq);

	//Walk Sideways (using scale to change L/R, default L)
	numFrames = 9;
	frameWidth = 30;
	frameHeight = 50;
	sf::LJMUAnimSeq walk_side_seq;
	for (int i = 0; i < numFrames; i++)
		walk_side_seq.addFrame(sf::IntRect(0 + i * frameWidth, 0, frameWidth, frameHeight));
	walk_side_seq.setSpriteSheet(this->_player_anim_textures.get(HubPlayerAnimTextures::walkSideTexture));
	_player_anim_sequences.push_back(walk_side_seq);

	//TODO: add idle seq
	numFrames = 1;
	frameWidth = 30;



	//Set the animation to the idle sequence
	Player.setAnimation(_player_anim_sequences[HubPlayerAnimSeq::walkUpSeq]);
	Player.setScale(SCALE, SCALE);
	sf::setOriginCentre(Player);

	this->Player.setFrameTime(sf::seconds(0.07f));
	this->Player.setPosition(pspawnpos);
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////
LJMU::HubPlayer::~HubPlayer()
{

}

//---------------------PUBLIC METHODS---------------------------------------------------------------

/////////////////////////////////////////////
// Update the player 
/////////////////////////////////////////////
void LJMU::HubPlayer::update(sf::Time& ptpf, sf::Time& ptotal)
{
	//Handle Movement
	handleMovement(ptpf);

	//Handle Animation States
	handleAnimationStates();

	//Update animated sprite
	this->Player.update(ptpf);
	
}

void LJMU::HubPlayer::handleAnimationStates()
{
	//Animation States
	if (isMoving)
	{
		//Play animation
		Player.play();
		if (moveDirection != prevDirection)
		{
			//Theres been a change in direction, swap animation sequence
			switch (moveDirection)
			{
				case UP:
				{
					Player.setAnimation(_player_anim_sequences[walkUpSeq]);
					break;
				}
				case DOWN:
				{
					Player.setAnimation(_player_anim_sequences[walkDownSeq]);
					break;
				}
				case LEFT:
				{
					Player.setAnimation(_player_anim_sequences[walkSideSeq]);
					break;
				}
				case RIGHT:
				{
					Player.setAnimation(_player_anim_sequences[walkSideSeq]);
					break;
				}
			}
		}
	}
	else
	{
		//Not moving, stop animation and set frame to 1 (to pause in current direction)
		Player.setFrame(0);
		Player.pause();
	}

	prevDirection = moveDirection;
}

void LJMU::HubPlayer::handleMovement(sf::Time& ptpf)
{
	//Reset Movement Vector, direction and isMoving
	isMoving = false;
	moveDirection = IDLE;
	sf::Vector2f tvel(0, 0);

	//Check for Movement, and adjust velocities, move direction, isMoving bool and scale (negative x for moving right, normal for all others)


	if (this->Controls.isActive(LJMUPlayerActions::MOVE_UP))
	{
		tvel.y -= 1.0f;
		isMoving = true;
		moveDirection = UP;
		Player.setScale(SCALE, SCALE);
	}
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_DOWN))
	{
		tvel.y += 1.0f;
		isMoving = true;
		moveDirection = DOWN;
		Player.setScale(SCALE, SCALE);
	}
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_RIGHT))
	{
		tvel.x += 1.0f;
		isMoving = true;
		moveDirection = RIGHT;
		Player.setScale(-SCALE, SCALE);
	}
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_LEFT))
	{
		tvel.x -= 1.0f;
		isMoving = true;
		moveDirection = LEFT;
		Player.setScale(SCALE, SCALE);
	}
	this->Player.move(tvel * this->Speed * ptpf.asSeconds());
}