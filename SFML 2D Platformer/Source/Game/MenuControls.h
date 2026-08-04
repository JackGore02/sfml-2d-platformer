#ifndef __MENU_CONTROLS_H_
#define __MENU_CONTROLS_H_

//Include the LJMU Framework
#include <LJMUPCH.h>


//Include the SFML Framework Classes
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

namespace LJMU
{
	class MenuControls
	{
	public:
		enum class MenuActions
		{
			ACTION_UNKNOWN,
			MOVE_UP,
			MOVE_DOWN,
			SELECT,
			BACK,
			INCREMENT,
			DECREMENT
		};

		//Use the sf::Keyboard class
		using kb = sf::Keyboard;
		using keys = kb::Key;

	public:
		//-----------CONSTRUCTORS/DESTRUCTORS--------------------
		MenuControls();
		~MenuControls();

		//-----------PUBLIC METHODS------------------------------
		void setActionMapping(MenuActions paction, keys pkey);		//Set the Action Mapping
		void clearDefaults();											//Clear the Default Values

		MenuActions getAction(keys pkey);	//Get the Corresponding Action for the Key
		keys getKey(MenuActions paction);	//Get the Corresponding Key for the Action

		void setFlag(MenuActions paction, bool pflag);	//Set the Flag for a Given Action 
		void setFlag(keys pkey, bool pflag);				//Set the Flag for a Given Key (Assumes 1-1)

		bool isActive(MenuActions paction);	//Is the Current Action Triggered?
		bool isActive(keys pkey);				//Is the Current Key Down?

	protected:
		//-----------CLASS MEMBERS-------------------------------
		std::map<keys, MenuActions>				_actions;  //Mapping of Keys to Actions
		std::map<MenuActions, bool>			    _flags;	   //Mapping of Actions to States
		
	};
}
#endif