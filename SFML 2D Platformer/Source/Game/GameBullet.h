#ifndef __GAME_BULLET_H_
#define __GAME_BULLET_H_

//Framework Include
#include <LJMUPCH.h>

//SFML Framework Includes
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

//Game Includes
#include <GameInterfaces.h>

namespace LJMU
{
	///////////////////////////////////////
	// Class to represent an individual 
	// Bullet within our game. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////////////
	class LJMUBullet : public sf::ILJMUUpdatable, public ILJMUObjectState
	{
	public:
		//----------CONSTANTS-----------------------------------------------------------
		static const int DEF_SPEED = 600;	//Default Speed (Magnitude) Constant
		static const int DEF_ALPHA = 255;	//Default Alpha (Transparency) Constant
	public:
		//----------CONSTRUCTORS/DESTRUCTORS--------------------------------------------
		//LJMUBullet();
		LJMUBullet(sf::Sprite psprite, sf::Vector2f pdir, sf::Vector2f pspawnpos, sf::Time pspawntime);
		~LJMUBullet();
	public:
		//----------PUBLIC METHODS------------------------------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;	//ILJMUUpdatable Implementation
	public:
		//----------ACCESSORS/MUTATORS--------------------------------------------------
		sf::Vector2f Direction;		//Direction of Bullet Travel
		sf::Vector2f SpawnPos;		//Initial Position of the Bullet
		float        Speed;			//Magnitude of Travel
		int          Alpha;			//Alpha Blending Value
		sf::Sprite   Bullet;		//Sprite Representation
		sf::Time     SpawnTime;		//Game Time the Bullet was Spawned
		float		 LifeTime;		//Lifetime of the Bullet
	};
}
#endif