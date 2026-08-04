#pragma once
#ifndef __GAME_SCREEN_HUB_H_
#define __GAME_SCREEN_HUB_H_

//Include our Framework Library
#include <LJMUPCH.h>

//Include our Game Application Classes
#include "GameCamera.h"
#include "GameEnums.h"
#include "HubPlayer.h"
#include "GameHUDElemBasic.h"
#include "GamePlayer.h"
#include <GameDataFiles.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

namespace LJMU
{
	class GameScreenHUB : public sf::ILJMUScreenBase
	{

		using HUBItmPtr = std::shared_ptr<LJMU::GameObjectBasic>;
		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		GameScreenHUB();	//Default Constructor
		~GameScreenHUB();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;


		//----------------PROTECTED FUNCTIONS---------------------//

	protected:

		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events
		void handleCamera(float ptpf, float ttotal);

		//Sub-Routines
		void loadResources();

		//Sub Routines of our HUB
		void setupHUB();
		void setupSelections();


		void setupCameras();
		void resetCamera();

		void returnToMainMenu();

		//Hub world navigation

		void onMoveUp();
		void onMoveDown();


	public:

		//---------------STRUCT OF LEVELS--------------//

		struct level
		{
			std::string name; // name of the level or destination
			std::pair<int, int> position; // position on screen
			bool unlocked;
			sf::Texture doorTexture; // texture for the door
			sf::Sprite doorSprite; // sprite for the door
		};


	protected:

		//--------------CLASS MEMBERS OF HUB--------------------//

		//Game Cameras
		LJMU::GameCamera							_camera_hub;			//Hub Cameras

		std::vector<HUBItmPtr> _HubItems;		//HubItems vector

		std::vector<LJMU::GameObjectBasic>			     _bg_layers;		//Level Collection


		sf::LJMUResourceHelper<sf::Texture, std::string>   _res_level;		//Resource Manager for Level BG
		sf::LJMUResourceHelper<sf::Texture, std::string>   _res_static;	    //Resource Manager for Static Sprites
		sf::LJMUResourceHelper<sf::Font, std::string>	  _res_font;        //Resource Manager for Fonts

		//Selection Index
		int												 selected_index;	//Selected Index
		int												 selectedItem;	//Selected Hub level

		//Hub Player
		HubPlayer* hub_player;
		LJMUPlayerControls playerControls;
		
	};
}
#endif
