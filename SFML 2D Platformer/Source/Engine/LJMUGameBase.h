#ifndef __LJMU_GAME_BASE_H_
#define __LJMU_GAME_BASE_H_

//Include our Framework Classes
#include <LJMUPCH.h>

namespace sf
{
	////////////////////////////////////////
	// Class to represent our basic SFML Game
	// Application.
	//
	// AUTHOR:  DR CHRIS CARTER
	////////////////////////////////////////
	class LJMUGameBase : private sf::NonCopyable, public ILJMUSFMLManager
	{
	public:
		//---------CONSTRUCTORS / DESTRUCTORS--------------------------------------
		LJMUGameBase(void);					//Constructor for the Game Class
		~LJMUGameBase(void);				//Destructor for the Game Class

		//---------PUBLIC METHODS--------------------------------------------------
		void    setupEngine();			//Method which controls the initialisation of the game engine
		void	runGameLoop();			//Method which controls the entire game loop of the application

	public:
		//----------INTERFACE IMPLEMENTATION-------------------------------------------
		virtual std::string getAppName() override;
		virtual sf::RenderWindow& getWindow() override;
		virtual const LJMUSettings& getSettings() const override;
		TheGameState& getGameState() override;
		virtual const sf::Time& getTotalElapsedTime() const override;
		virtual const sf::Time& getCurrentFrameTime() const override;
		
		//----------SCREEN MANAGER INTERFACE IMPLEMENTATION----------------------------
		virtual std::shared_ptr<ILJMUScreenBase> getTopScreen() override;
		virtual std::shared_ptr<ILJMUScreenBase> getScreenWithPos(int ppos) override;
		virtual std::shared_ptr<ILJMUScreenBase> getScreenWithID(int pid) override;
		virtual bool removeTopScreen() override;
		virtual bool removeScreenWithPos(int ppos) override;
		virtual bool removeScreenWithID(int pid) override;
		virtual void addScreen(std::shared_ptr<ILJMUScreenBase> pscreen, int pid) override;
		virtual void clearScreens() override;

	private:
		//---------INTERNAL METHODS------------------------------------------------
		void    initialise();			//Initialise the State of the Window 
		void    loadContent();          //Load any content reliant on the GPU
		void	handleEvents();         //Process our Input Events
		void	update();				//Update the State of the Game
		void	render();				//Draw the Screen
		void    cleanup();				//Cleanup any object


#ifdef _DEBUG
		void    setupDebugText();		//Set the Debug Text
#endif		

	private:
		sf::Time							_time_tpf;		//Time object storing the current time per frame
		sf::Time							_time_total;	//Time object storing the current total time
		sf::RenderWindow					_wndw;			//The SFML Graphics Window
		sf::LJMUSettings					_settings;		//Application Settings
		std::deque<std::shared_ptr<ILJMUScreenBase>>   _screen_buffer; 
		std::deque<std::shared_ptr<ILJMUScreenBase>>   _screen_active;

		TheGameState                        _gameState;
#ifdef _DEBUG
		sf::Text			_text_fps;		//Text to Display the Frame Rate
		sf::Font			_debug_fnt;     //Debug Font to use for Rendering
#endif
	};

}
#endif 
