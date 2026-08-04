#ifndef __GAME_ENUMS_H_
#define __GAME_ENUMS_H_

///////////////////////////////
// Set of C++ 11 Scoped Enum 
// Classes for various purposes. 
//
// AUTHOR:  DR CHRIS CARTER
// DATE:    01/06/2017
///////////////////////////////

namespace LJMU
{
	//----------------C++ 11 ENUMERATION DEFINITIONS--------------------------------------

	////////////////////////////////
	// Enumeration to represent the 
	// Types of HUD Display our Game
	// Has.
	////////////////////////////////
	enum class LJMUSIHUD
	{
		SCORE,
		LIVES,
		TIME
	};

	/////////////////////////////////
	// Enumeration to represent the 
	// Colour Schemes of the Enemies.
	/////////////////////////////////
	enum class LJMUSIColour
	{
		RED,
		BLUE,
		GREEN,
		PURPLE,
		YELLOW,
		WHITE
	};

	///////////////////////////////////
	// Enumeration of all the different
	// motion paths we could create. 
	///////////////////////////////////
	enum class LJMUEnemyMotion
	{
		LINEAR,
		CIRCULAR,
		SINUSOIDAL,
		QUADRATIC
	};

	///////////////////////////////////
	// Enumeration to represent the 
	// states of the Gameplay.  
	///////////////////////////////////
	enum class LJMUGamePlayMode
	{
		GAME_START,
		GAME_PLAYING,
		GAME_WON,
		GAME_LOST,
		GAME_END
	};

	enum class PlayerAnimTextures
	{
		idleTexture,
		walkTexture,
		jumpTexture
	};

	enum PlayerAnimSeq
	{
		idleSeq,
		walkSeq,
		jumpSeq 
	};

	enum HubPlayerAnimSeq
	{
		walkUpSeq,
		walkDownSeq,
		walkSideSeq
	};
	
	enum class PlayerState
	{
		IDLE,
		WALKING,
		JUMPING
	};

	enum HubPlayerAnimTextures
	{
		walkUpTexture,
		walkDownTexture,
		walkSideTexture,
		idleTexture
	};



	enum HubPlayerDirection
	{
		IDLE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
}
#endif