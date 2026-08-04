#ifndef __GAME_CONTROLS_H_
#define __GAME_CONTROLS_H_

//Include the LJMU Framework
#include <LJMUPCH.h>

//Include the SFML Framework Classes
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

namespace LJMU
{
	//Use the sf::Keyboard class
	using sf::Keyboard;

	///////////////////////////////////////
	// Enumeration to represent each
	// of the different types of action
	// of the Player Control Scheme. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////////////
	enum class LJMUPlayerActions
	{
		ACTION_UNKNOWN = 0,	//Set Enum Value 0 as Action Unknown
		MOVE_LEFT,		//Move Left
		MOVE_RIGHT,		//Move Right
		MOVE_UP,		//Move Up
		MOVE_DOWN,		//Move Down
		ANIM_INC_FRAME, //Increment Animation Frame
		ANIM_DEC_FRAME, //Decrement Animation Frame
		JUMP,			//Jumping
		SPRINT			//Sprinting
	};

	//////////////////////////////////////
	// Implementation of the player keyboard controls
	// Handled via a Tri-Partite Mapping via
	// Two interconnected maps. 
	// Two Schemes are supported in the code. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	/////////////////////////////////////
	class LJMUPlayerControls
	{
	public:
		//-----------CONSTRUCTORS/DESTRUCTORS--------------------
		LJMUPlayerControls(bool pprimary = true); //Default Parameter True = Player 1, False = Player 2
		~LJMUPlayerControls();

		//-----------PUBLIC METHODS------------------------------
		void setActionMapping(LJMUPlayerActions paction, Keyboard::Key pkey);	//Set the Action Mapping
		void clearDefaults();													//Clear the Default Values

		LJMUPlayerActions getAction(sf::Keyboard::Key pkey);	//Get the Corresponding Action for the Key
		sf::Keyboard::Key getKey(LJMUPlayerActions paction);	//Get the Corresponding Key for the Action

		void setFlag(LJMUPlayerActions paction, bool pflag);	//Set the Flag for a Given Action 
		void setFlag(sf::Keyboard::Key pkey, bool pflag);		//Set the Flag for a Given Key (Assumes 1-1)

		bool isActive(LJMUPlayerActions paction);	//Is the Current Action Triggered?
		bool isActive(sf::Keyboard::Key pkey);		//Is the Current Key Down?

	protected:
		//-----------CLASS MEMBERS-------------------------------
		std::map<sf::Keyboard::Key, LJMUPlayerActions>   _actions; //Mapping of Keys to Actions
		std::map<LJMUPlayerActions, bool>			    _flags;	   //Mapping of Actions to States
	};

	///////////////////////////////////////
	// Enumeration to represent each
	// of the different types of action
	// of the Camera Control Scheme. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////////////
	enum class LJMUCameraActions
	{
		ACTION_UNKNOWN = 0,//Set Enum Value 0 as Action Unknown
		MOVE_CAM_LEFT,	   //Move the Camera Left
		MOVE_CAM_RIGHT,	   //Move the Camera Right
		MOVE_CAM_UP,       //Move the Camera Up
		MOVE_CAM_DOWN,     //Move the Camera Down
		ROT_CAM_CW,		   //Rotate Camera Clockwise
		ROT_CAM_CCW,	   //Rotate Camera Counter-Clockwise
		ZOOM_CAM_IN,	   //Zoom the Camera In
		ZOOM_CAM_OUT	   //Zoom the Camera Out
	};

	/////////////////////////////////////////
	// Implementation of the player keyboard controls
	// Handled via a Tri-Partite Mapping via
	// Two interconnected maps. 
	// Two Schemes are supported in the code. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	/////////////////////////////////////////
	class LJMUCamControls
	{
	public:
		//-----------CONSTRUCTORS/DESTRUCTORS--------------------
		LJMUCamControls();
		~LJMUCamControls();

		//-----------PUBLIC METHODS------------------------------
		void setActionMapping(LJMUCameraActions paction, Keyboard::Key pkey);	//Set the Action Mapping
		void clearDefaults();													//Clear the Default Values

		LJMUCameraActions getAction(sf::Keyboard::Key pkey);	//Get the Corresponding Action for the Key
		sf::Keyboard::Key getKey(LJMUCameraActions paction);	//Get the Corresponding Key for the Action

		void setFlag(LJMUCameraActions paction, bool pflag);	//Set the Flag for a Given Action 
		void setFlag(sf::Keyboard::Key pkey, bool pflag);		//Set the Flag for a Given Key (Assumes 1 - 1)

		bool isActive(LJMUCameraActions paction);				//Is the Current Action Triggered?
		bool isActive(sf::Keyboard::Key pkey);					//Is the Current Key Down?

	protected:
		//-----------CLASS MEMBERS-------------------------------
		std::map<sf::Keyboard::Key, LJMUCameraActions>   _actions; //Mapping of Keys to Actions
		std::map<LJMUCameraActions, bool>			    _flags;   //Mapping of Actions to States
	};
}
#endif