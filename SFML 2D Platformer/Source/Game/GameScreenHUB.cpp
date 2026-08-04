#include "GameScreenHUB.h"
#include "HubPlayer.h"


///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::GameScreenHUB::GameScreenHUB()
{
	
}

///////////////////////////////////////
// Destructor for the Screen
///////////////////////////////////////
LJMU::GameScreenHUB::~GameScreenHUB()
{
	
}

void LJMU::GameScreenHUB::loadContent()
{
	auto tmgr = this->getLJMUSFMLManager().lock();

	//Call our Sub-Routines - Some Order is Important
	this->loadResources();

	//Call our Setup Routines to Initialise the Menu
	this->setupHUB();
	//this->setupSelections();

	//Setup our Cameras 
	this->setupCameras();


}

void LJMU::GameScreenHUB::handleEvent(const sf::Event& pevent)
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

void LJMU::GameScreenHUB::bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered)
{


}

void LJMU::GameScreenHUB::update(sf::Time& ptpf, sf::Time& ptotal)
{
	//-------GET THE UPDATE TIMES----------------------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();


	//hub_player->update(ptpf, ptotal);


	this->handleCamera(ttpf, ttotal);


}

void LJMU::GameScreenHUB::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	this->_camera_hub.makeCurrent(twndw);

	//Draw the Background to Screen
	for (auto& tbg : this->_bg_layers) { tbg.render(twndw); }
	for (auto& sI : this->_HubItems) { sI->render(twndw); }

	twndw.draw(hub_player->getSprite());
}

void LJMU::GameScreenHUB::cleanup()
{
}

void LJMU::GameScreenHUB::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
}

void LJMU::GameScreenHUB::handleCamera(float ptpf, float ttotal)
{
}

void LJMU::GameScreenHUB::loadResources()
{

	std::string tbg_dir = sf::LJMUSettings::DIR_BG;
	std::string tf_dir = sf::LJMUSettings::DIR_FONTS;

	
	//Load the backgrounds
	//this->_res_level.load("", tbg_dir + "background.png");
}

void LJMU::GameScreenHUB::setupHUB()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	

}

void LJMU::GameScreenHUB::setupSelections()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();


	level level1{ "Level 1", {100, 100}, true };
	level level2{ "Level 2", {300, 100}, false };
	level level3{ "Shop", {500, 100}, false };
	level level4{ "Menu", {700, 100}, false };
	//level1.doorTexture.loadFromFile("DoorUnlocked.png");
	level1.doorSprite.setTexture(level1.doorTexture);
	level1.doorSprite.setPosition(level1.position.first, level1.position.second);
	//level2.doorTexture.loadFromFile("DoorUnlocked.png");
	level2.doorSprite.setTexture(level2.doorTexture);
	level2.doorSprite.setPosition(level2.position.first, level2.position.second);
	//level3.doorTexture.loadFromFile("DoorUnlocked.png");
	level3.doorSprite.setTexture(level3.doorTexture);
	level3.doorSprite.setPosition(level3.position.first, level3.position.second);
	//level4.doorTexture.loadFromFile("DoorUnlocked.png");
	level4.doorSprite.setTexture(level4.doorTexture);
	level4.doorSprite.setPosition(level4.position.first, level4.position.second);
}

void LJMU::GameScreenHUB::setupCameras()
{
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());
	const sf::FloatRect tscrbound = sf::fromdimf(tscrdim);
	const sf::Vector2f tcamcentre = tscrdim * 0.5f;
	//Setup our Game Camera

	//Set the Camera View
	sf::View tcam;
	tcam.reset(tscrbound);
	tcam.setCenter(tcamcentre);

	//Create a GameCamera to hold the camera.
	GameCamera tcamobj;
	tcamobj.setView(tcam);

	//Add Camera for the Game
	this->_camera_hub = tcamobj;
}
