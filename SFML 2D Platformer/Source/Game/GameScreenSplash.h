#ifndef __GAME_SCREEN_SPLASH_H_
#define __GAME_SCREEN_SPLASH_H

//Include our Framework Library
#include <LJMUPCH.h>

#include "GameCamera.h"
#include "GameHUDElemBasic.h"


//Include our Game Application Classes


namespace LJMU
{


	class GameScreenSplash : public sf::ILJMUScreenBase
	{
		//---------CONSTANTS-------------------------------------------------------
		static const unsigned int   HUD_SCALE = 48;   //Constant to hold the scale of the HUD

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		

		GameScreenSplash();	//Default Constructor
		~GameScreenSplash();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

	public:
		//-----------PUBLIC FUNCTIONS----------------------------------------

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events

		void setupCameras();

		void setupTitle();
		void setupIntro();
	public:

		//-----------GETTERS/SETTERS-----------------------------------------

	protected:
		//-----------CLASS MEMBERS-------------------------------------------
		sf::LJMUResourceHelper<sf::Font, std::string>	  _res_font;

		LJMU::GameHUDElemBasic                          SplashTitle;

		std::deque<LJMU::GameCamera>		        	_cameras;					//Menu Cameras

		/*std::deque<LJMU::GameCamera>			_cameras;*/

		sf::LJMUResourceHelper<sf::Texture, std::string>  _imgBG;
		sf::Texture _imgChar;

		LJMU::GameHUDElemBasic                           Intro;
		
		sf::Sprite _gameChar;


	};
}
#endif