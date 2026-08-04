#ifndef __GAME_SCREEN_Level_H_
#define __GAME_SCREEN_Level_H_

//Include our Framework Library
#include <LJMUPCH.h>
//Include our Game Application Classes
#include <GamePCH.h>
//Include our Debug Renderer
//#include <GameDebugRenderer.h>
#include <GameDataFiles.h>
#include "GamePlayer.h"

namespace LJMU
{
	class LJMUGameScreenLevel : public sf::ILJMUScreenBase
	{
		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		LJMUGameScreenLevel();	//Default Constructor
		~LJMUGameScreenLevel();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events
		void handleCamera(float ptpf, float ttotal);

		//Sub-Routines
		void loadLevel1Resources();
		void loadLevel2Resources();

		//Sub Routines of our Game
		void setupPlayers();
		void setupLevel1();
		void setupLevel2();
		void setupPickups();
		void setupHUD();
		void setupCameras();

		void resetCamera();

		void returnToMainMenu();

	protected:
		//-----------CLASS MEMBERS-------------------------------------------
		sf::LJMUResourceHelper <sf::Texture, std::string> _res_anim;		//Resource Manager for SpriteSheets
		sf::LJMUResourceHelper <sf::Texture, std::string>  _res_level;		//Resource Manager for Levels
		sf::LJMUResourceHelper<sf::Texture, std::string>	  _res_static;		//Resource Manager for Static Sprites
		sf::LJMUResourceHelper <LJMU::AssetColl, std::string> _res_colls;   //Resource Manager for Asset Collections

		//GameSide Elements
		std::vector<LJMU::GameObjectBasic>			_level_env;			//Level Collection
		std::vector<LJMU::GameObjectBasic>			_level_fore;		//Level Collection
		std::vector<LJMU::GameObjectBasic>			_level_back;		//Level Collection
		//std::vector<LJMU::LJMUPlayer>				_level_players;		//Player Collection
		std::vector<LJMU::GameObjectBasic>			_level_elems;		//Level Elements
		//LJMU::SidePickups							_level_pickups;     //Pickup Objects  
		//LJMU::SideHUD								_level_hud;			//HUD Collection (Self-Contained)

		//Game Cameras
		LJMU::GameCamera							_camera_gp;			//GameSide Cameras

		//Player
		std::unique_ptr<GamePlayer> player;
		LJMUPlayerControls playerControls;

		//Levels
		enum class GameLevels
		{
			Level1,
			Level2
		};

		GameLevels currentLevel = GameLevels::Level1;
	};
}
#endif

