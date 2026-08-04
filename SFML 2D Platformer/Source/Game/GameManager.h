#ifndef __GAME_MANAGER_H_
#define __GAME_MANAGER_H_

#include <LJMUPCH.h>

#include <SFML/Graphics.hpp>

#include "GameControls.h"
#include "GameAssets.h"
#include "GameEnums.h"

namespace LJMU
{

	///////////////////////////////////////
	// Class to represent the Global State
	// of the Game. 
	//
	// AUTHOR: CHRIS CARTER
	// DATE:   03/06/2017
	///////////////////////////////////////
	class LJMUGameManager : sf::ILJMUUpdatable
	{
		//--------------------CONSTRUCTORS/DESTRUCTORS------------------------
	public:
		LJMUGameManager();
		~LJMUGameManager();
	public:
		//--------------------PUBLIC METHODS-----------------------------------
		void create(sf::Vector2f pwndsize);
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;
		void destroy();
	public:

	public:
		//--------------------CLASS MEMBERS------------------------------------
		sf::View											CameraGame;
		sf::View											CameraHUD;
		LJMUCamControls										CameraControl;
		sf::LJMUResourceHelper<sf::Texture, LJMUSIAssets>   ResourceSprites;
		sf::LJMUResourceHelper<sf::Font, LJMUSIFont>   	    ResourceFonts;
		std::map<LJMUSIColour, sf::Color>					ResourceColour;
		std::map<int, LJMUSIAssets>							MapEnemyTexture;
		std::map<int, LJMUSIColour>							MapEnemyColour;

		unsigned int										GameLives;
		unsigned int										GameScore;

		int                                                 Coins;

		sf::Vector2f										GameWorldSize;
		sf::Vector2f										GameWorldWindow;
		sf::FloatRect										GameWorldBounds;
		LJMUGamePlayMode									GameMode;
		float                                               GamePlayTime;
		float												GameStartTime; 
		float												GameEndTimeStart;
		float												GameEndTimeDelay;

		std::vector<sf::Sprite>								WorldLevel;
		std::map<LJMUSIHUD, sf::Text>						WorldHUD;
	};
}
#endif