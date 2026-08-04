#include <GameScreenSplash.h>

#include "GameScreenMenuRoot.h"
#include "MenuScreenSubMenu.h"

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::GameScreenSplash::GameScreenSplash()
{
	this->_trans_on_time = sf::seconds(1.0f);
	this->_trans_off_time = sf::seconds(4.0f); // adjust depending on how long the intro becomes
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::GameScreenSplash::~GameScreenSplash()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::GameScreenSplash::loadContent()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//Load the Default Font
	std::string ts_dir = sf::LJMUSettings::DIR_STATICS;
	std::string tbg_dir = sf::LJMUSettings::DIR_BG;
	std::string tf_dir = sf::LJMUSettings::DIR_FONTS;
	std::string tts_dir = sf::LJMUSettings::DIR_TILESETS;
	std::string tdf_dir = sf::LJMUSettings::DIR_DATAFILES;

	this->_res_font.load("Title", tf_dir + "Title.TTF");
	this->_res_font.load("Elems", tf_dir + "Ninja.otf");


	

	
	
	

	//this->_Intro.setColor(sf::Color::Red);

	this->_imgChar.loadFromFile("Assets/Statics/damage.png");
	this->_gameChar.setTexture(this->_imgChar);
	this->_gameChar.setPosition(sf::Vector2f(170, 20));
	this->_gameChar.setScale(.5,.5);
	this->_gameChar.setColor(sf::Color::Blue);

	this->setupCameras();

	this->setupTitle();
	this->setupIntro();
}

void LJMU::GameScreenSplash::setupTitle()
{
	SplashTitle.setString("IMORA 40K");//Place holder name until one is chosen by group
	SplashTitle.getText().setCharacterSize(55);
	SplashTitle.getText().setFont(this->_res_font.get("Title"));

	SplashTitle.getText().setPosition(650, 100);
	SplashTitle.getText().setString(SplashTitle.getString());

	SplashTitle.getText().setFillColor(sf::Color::White);
}

void LJMU::GameScreenSplash::setupIntro()
{


	
	Intro.setString("A Sci Fi Platformer! Developed by Team Ash Jack Sam Josh ");
	Intro.getText().setFont(this->_res_font.get("Elems"));
	Intro.getText().setCharacterSize(35);
	Intro.getText().setPosition(80, 300);
	Intro.getText().setFillColor(sf::Color::White);
	Intro.getText().setString(Intro.getString());
	
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::GameScreenSplash::handleEvent(const sf::Event& pevent)
{
	//Cache the passed event locally
	sf::Event tevent = pevent;

	//Switch Statement to decide between the different Event Types
	switch (tevent.type)
	{
	case sf::Event::KeyPressed:
	{
		this->handleInput(tevent.key.code, true);
		break;
	}
	case sf::Event::KeyReleased:
	{
		this->handleInput(tevent.key.code, false);
		break;
	}
	}
}

//////////////////////////////////////////
//  Secondary update function. 
//////////////////////////////////////////
void LJMU::GameScreenSplash::bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::GameScreenSplash::update(sf::Time& ptpf, sf::Time& ptotal)
{
	//-------GET THE UPDATE TIMES------------------------------------
	if (ptotal >= this->_trans_off_time)
	{
		// Replace the splash with the menu once the intro has completed.
		auto tmgr = getLJMUSFMLManager().lock();
		exitScreen();
		int tid = static_cast<int>(sf::GameScreens::ScreenMenu);
		tmgr->addScreen(std::make_shared<LJMU::GameScreenMenuRoot>(), tid);
	}

	//--------DEBUG OUTPUT-----------------------------------------------------------
#ifdef _DEBUG
	//Monitor the lists by outputting the size to the console
	sf::err() << "Debug Information: " << std::endl;
#endif
}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::GameScreenSplash::render()
{
	//Get Access to the Window via the Weak Pointer. 
	

	/*if (this->getTransPos() < 0.1f)
	{*/


		auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

		const int tcm = 0;

		//------RENDER THE GAMEPLAY LAYERS---------------------------------
		this->_cameras[tcm].makeCurrent(twndw);

		//------RENDER THE GAMEPLAY LAYERS---------------------------------
			twndw.draw(this->_gameChar);
	SplashTitle.render(twndw);
		Intro.render(twndw);
	

	/*}*/
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::GameScreenSplash::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::GameScreenSplash::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();

	if (pkey == sf::Keyboard::Key::P && !ppressed)
	{
		this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new GameScreenSplash()), 6);
	}
}

void LJMU::GameScreenSplash::setupCameras()
{
	
		auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
		const sf::Vector2f tscrdim = sf::tof(twndw.getSize());
		const sf::FloatRect tscrbound = sf::fromdimf(tscrdim);
		const sf::Vector2f tcamcentre = tscrdim * 0.5f;

		//Set the Camera View
		sf::View tcam;
		tcam.reset(tscrbound);
		tcam.setCenter(tcamcentre);

		//Create a GameCamera to hold the camera.
		GameCamera tcamobj;
		tcamobj.setView(tcam);

		//Add one Camera for the HUD
		this->_cameras.push_back(tcamobj);
	
}
