#pragma once

//Include the LJMU Framework
#include <LJMUPCH.h>
#include <GameObjectBasic.h>
//Include the Transform and Time Classes of SFML
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>

//Include the Player Control Scheme. 
#include "GameControls.h"
#include "GameEnums.h"
#include "GameInterfaces.h"

namespace LJMU
{
	///////////////////////////////////////
	// Class to represent an individual
	// Player within our game.  
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    05/06/2017
	///////////////////////////////////////
	class GamePlayer : public sf::ILJMUUpdatable, public ILJMUObjectState
	{
	public:
		//--------------------CONSTANTS---------------------------------------
		const int DEF_SPEED = 300;
		const int DEF_LIVES = 5;
		const float GRAVITY = 9.81f;
		const float MAX_FALL_SPEED = 5;
		const float JUMP_VELOCITY = -3.5;
		const float SPRINT_X_MULTIPLIER = 1.5f;
		const float SPRINT_Y_MULTIPLIER = 1.2f;

		//--------------------CONSTRUCTORS/DESTRUCTORS------------------------
		GamePlayer(LJMUPlayerControls& pcontrols, sf::Vector2f pspawnpos);
		~GamePlayer();
	public:
		//--------------------PUBLIC METHODS-----------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;
		sf::LJMUAnimSprite& getSprite() { return Player; }
		int getLives() { return Lives; }
		void setLives(int value) { Lives = value; }
		void decrementLives() { Lives--; }
		void incrementLives() { Lives++; }

		bool isOnPlatform() { return onPlatform; }
		void checkCollision(GameObjectBasic& telem);
		bool levelCompleted;

	public:
		//--------------------ACCESSORS/MUTATORS-------------------------------
	private:
		//--------------------CLASS MEMBERS------------------------------------
		void handleMovement(sf::Time& ptpf);
		void handleAnimationStates();

		sf::LJMUAnimSprite	Player;
		LJMUPlayerControls&	Controls;
		sf::Vector2f		SpawnPos;
		float				Speed;
		int                 Lives;
		sf::Time            LastChange;
		int                 IdleFrame;
		bool				isMoving;
		bool				isJumping;
		bool				onPlatform;
		float				xVelocity;
		float				yVelocity;
		bool				isSprinting;
		bool				jumpWasPressed;
		sf::Vector2f		previousPosition;

		float scale;
		PlayerState state;

		sf::LJMUResourceHelper<sf::Texture, LJMU::PlayerAnimTextures> _player_anim_textures;
		std::vector<sf::LJMUAnimSeq> _player_anim_sequences;

		bool collidingLeft;
		bool collidingRight;
		bool beingPushed;
	};
}
