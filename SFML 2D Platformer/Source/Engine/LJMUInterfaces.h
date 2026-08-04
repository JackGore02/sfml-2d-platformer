#ifndef __LJMU_INTERFACES_H_
#define __LJMU_INTERFACES_H_

//Include the SFML Timing System.
#include <SFML/System/Clock.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <LJMUSettings.h>

namespace sf
{
	///////////////////////////////
	// Abstract Class to represent 
	// objects which can be updated. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////

	enum class GameScreens
	{
		ScreenMenu,
		ScreenOptions,
		ScreenHub,
		ScreenShop,
		ScreenPlatform,

	};

	class ILJMUUpdatable
	{
	public:
		//-------INTERFACE FUNCTIONS-----------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) = 0;
	};

	///////////////////////////////
	// Interface to represent access
	// to key SFML Objects.
	//
	// Can be used to obtain references to 
	// objects from any Screen. 
	// 
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////

	class TheGameState
	{
	public:
		int coins = 0;

	};
	
	class ILJMUSFMLManager : public std::enable_shared_from_this<ILJMUSFMLManager>
	{
	public:
		//--------APPLICATION MANAGER INTERFACE--------------------------------
		virtual std::string getAppName() = 0; //Get the Application Name
		virtual sf::RenderWindow& getWindow() = 0; //Get the SFML Render Window
		virtual const LJMUSettings& getSettings() const = 0; //Get the LJMU Settings
		virtual const sf::Time& getTotalElapsedTime() const = 0; //Get the Total Elapsed Time
		virtual const sf::Time& getCurrentFrameTime() const = 0;  //Get the Current Frame Time

		virtual TheGameState& getGameState() = 0;

		//-------SCREEN MANAGER INTERFACE--------------------------------------
		virtual std::shared_ptr<class ILJMUScreenBase> getTopScreen() = 0;
		virtual std::shared_ptr<class ILJMUScreenBase> getScreenWithPos(int ppos) = 0;
		virtual std::shared_ptr<class ILJMUScreenBase> getScreenWithID(int pid) = 0;
		virtual bool removeTopScreen() = 0;
		virtual bool removeScreenWithPos(int ppos) = 0;
		virtual bool removeScreenWithID(int pid) = 0;
		virtual void addScreen(std::shared_ptr<class ILJMUScreenBase> pscreen, int pid) = 0;
		virtual void clearScreens() = 0;
	};

	enum class TransMode
	{
		TransOn,
		TransOff,
		Active,
		Hidden
	};

	///////////////////////////////
	// Interface to represent the 
	// screens of our application.
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////
	class ILJMUScreenBase
	{
	public: 
		ILJMUScreenBase();
		virtual ~ILJMUScreenBase();

	public:
		//------SCREEN INTERFACE-----------------------------------------------
		virtual void    loadContent() = 0;								//Load any content reliant on the GPU
		virtual void	handleEvent(const sf::Event& pevent) = 0;		//Process our Input Events
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) = 0;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) = 0;	//Update the State of the Game
		virtual void	render() = 0;									//Draw the Screen
		virtual void    cleanup() = 0;	//Cleanup any object
		virtual void    masterUpdate(sf::Time& ptpf, sf::Time& ptotal, bool potherfocused, bool poverlaid);

		//-------ACCESSORS/MUTATORS--------------------------------------------
		inline void   setID(int pid) { this->_id = pid; }
		inline int    getID() { return this->_id; }

	public: 
		//-----SCREEN MANAGEMENT FUNCTIONS----------------------------------------------
		bool exitScreen();
		
		void  setLJMUSFMLManager(std::shared_ptr<ILJMUSFMLManager> pmanager);
		std::weak_ptr<ILJMUSFMLManager> getLJMUSFMLManager();
		TransMode getScreenState();
		bool  isActive();
		bool isExiting();
		bool isPopupScreen();
		float getTransPos();
		float getTransAlpha();


	protected:
		bool isTransitioning(sf::Time& ptranstime,sf::Time& ptpf, int pdir);

		//-------CLASS MEMBERS------------------------------------------------
	protected:
		std::weak_ptr<ILJMUSFMLManager> _manager;	//Weak Pointer to the Manager Base Class
		int								_id;		//ID Number for the Screen
		float							_trans_pos; 
		TransMode						_trans_mode;
		bool							_popup;
		bool							_exiting;
		bool							_secondary;
		sf::Time						_trans_on_time;
		sf::Time						_trans_off_time;
	};
}
#endif