#pragma once

//Include the LJMU Framework
#include <LJMUPCH.h>

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
	class HubPlayer : public sf::ILJMUUpdatable, public ILJMUObjectState
	{
	public:
		//--------------------CONSTANTS---------------------------------------
		const int DEF_SPEED = 200;
		const int DEF_LIVES = 5;
		const float SCALE;

		//--------------------CONSTRUCTORS/DESTRUCTORS------------------------
		HubPlayer(LJMUPlayerControls& pcontrols, sf::Vector2f pspawnpos);
		~HubPlayer();
	public:
		//--------------------PUBLIC METHODS-----------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;
		sf::LJMUAnimSprite getSprite() { return Player; }
		int getLives() { return Lives; }
		void setLives(int value) { Lives = value; }
		void decrementLives() { Lives--; }
		void incrementLives() { Lives++; }



	public:
		//--------------------ACCESSORS/MUTATORS-------------------------------
	private:
		//--------------------CLASS MEMBERS------------------------------------
		void handleMovement(sf::Time& ptpf);
		void handleAnimationStates();

		sf::LJMUAnimSprite	Player;
		LJMUPlayerControls& Controls;
		sf::Vector2f		SpawnPos;
		float				Speed;
		int                 Lives;
		sf::Time            LastChange;
		int                 IdleFrame;
		bool				isMoving;
		float				xVelocity;
		float				yVelocity;

		PlayerState state;
		HubPlayerDirection moveDirection;
		HubPlayerDirection prevDirection;

		sf::LJMUResourceHelper<sf::Texture, LJMU::HubPlayerAnimTextures> _player_anim_textures;
		std::vector<sf::LJMUAnimSeq> _player_anim_sequences;

	};
}