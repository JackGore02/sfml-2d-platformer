#include <GameScreenMain.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenMain::LJMUGameScreenMain()
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenMain::~LJMUGameScreenMain()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::LJMUGameScreenMain::loadContent()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	player = new GamePlayer(playerControls, sf::Vector2f(sf::Vector2f(twndw.getSize().x / 2, twndw.getSize().y / 2)));
	hubPlayer = new HubPlayer(playerControls, sf::Vector2f(300, 300));
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::handleEvent(const sf::Event& pevent)
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
void LJMU::LJMUGameScreenMain::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::update(sf::Time & ptpf, sf::Time & ptotal)
{
	//-------GET THE UPDATE TIMES------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	player->update(ptpf, ptotal);
	hubPlayer->update(ptpf, ptotal);


	//--------DEBUG OUTPUT-----------------------------------------------------------
#ifdef _DEBUG
	//Monitor the lists by outputting the size to the console
	//sf::err() << "Debug Information: " << std::endl;
#endif
}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	twndw.clear(sf::Color::Black);

	//Render player
	twndw.draw(player->getSprite());
	twndw.draw(hubPlayer->getSprite());
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::LJMUGameScreenMain::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();

	//Update controls
	if (sf::Keyboard::isKeyPressed(this->playerControls.getKey(LJMUPlayerActions::MOVE_LEFT)))
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_LEFT, true);
	else
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_LEFT, false);

	if (sf::Keyboard::isKeyPressed(this->playerControls.getKey(LJMUPlayerActions::MOVE_RIGHT)))
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_RIGHT, true);
	else
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_RIGHT, false);
	if (sf::Keyboard::isKeyPressed(this->playerControls.getKey(LJMUPlayerActions::MOVE_UP)))
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_UP, true);
	else
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_UP, false);

	if (sf::Keyboard::isKeyPressed(this->playerControls.getKey(LJMUPlayerActions::MOVE_DOWN)))
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_DOWN, true);
	else
		this->playerControls.setFlag(LJMUPlayerActions::MOVE_DOWN, false);

	if (sf::Keyboard::isKeyPressed(this->playerControls.getKey(LJMUPlayerActions::JUMP)))
		this->playerControls.setFlag(LJMUPlayerActions::JUMP, true);
	else
		this->playerControls.setFlag(LJMUPlayerActions::JUMP, false);

	if (sf::Keyboard::isKeyPressed(this->playerControls.getKey(LJMUPlayerActions::SPRINT)))
		this->playerControls.setFlag(LJMUPlayerActions::SPRINT, true);
	else
		this->playerControls.setFlag(LJMUPlayerActions::SPRINT, false);

}