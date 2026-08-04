#include "LJMUGameBase.h"

//---------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------------------------------------

//////////////////////////////////////////////////////
// Constructor for our Game Class
// Set the Initial State of our Class Members
//////////////////////////////////////////////////////
sf::LJMUGameBase::LJMUGameBase(void)
: 
_time_tpf()
, _time_total()
{
	//Nothing else to construct.
}

//////////////////////////////////////////////////////
// Destructor for our Game Class
//////////////////////////////////////////////////////
sf::LJMUGameBase::~LJMUGameBase(void)
{

}

//---------METHOD SPECIFICATION--------------------------------------------------------------------------------------

//////////////////////////////////////////////////////
// Initialise the State of our Game
//////////////////////////////////////////////////////
void sf::LJMUGameBase::initialise()
{
	//Create the Window. 
	this->_wndw.create(this->_settings.getVideoMode(),
		               this->_settings.getAppName(),
					   this->_settings.getAppStyle(),
					   this->_settings.getContext());

	//Setup the Input Modes
	this->_wndw.setKeyRepeatEnabled(this->_settings.isKeyRepeat());
	this->_wndw.setMouseCursorGrabbed(this->_settings.isMouseGrabbed());
	this->_wndw.setMouseCursorVisible(this->_settings.isMouseVisible());

	//Setup Game Timing.
	if (sf::LJMUSettings::APP_FIXEDSTEP)
	{
		this->_wndw.setFramerateLimit(sf::LJMUSettings::APP_FRAMERATE);
		this->_wndw.setVerticalSyncEnabled(this->_settings.isVSync());
	}

#ifdef _DEBUG
	//Output our OpenGL Settings
	sf::err() << sf::getContextInfo(this->_wndw);
#endif
}

//////////////////////////////////////////////////////
// Load Any Content Related to our game	
//////////////////////////////////////////////////////
void sf::LJMUGameBase::loadContent()
{
	//-------------Create our Game Screen-----------------------------------------

	//-------------Create the Debug Elements-------------------------------------
#ifdef _DEBUG
	this->setupDebugText();
#endif 		
}

//////////////////////////////////////////////////////
// Update the State of our Game
//////////////////////////////////////////////////////
void sf::LJMUGameBase::update()
{
	if (this->_screen_buffer.size() <= 0)
		return;

	//As the first screen we will process is on top, 
	//it is primary and not covered
	bool totherfocus = false;
	bool toverlaid = false;

	//Loop backwards through the deque.
	for (auto rit = this->_screen_buffer.rbegin(); rit != this->_screen_buffer.rend(); ++rit)
	{
		auto tscreen = *rit;
		tscreen->masterUpdate(this->_time_tpf, this->_time_total,totherfocus,toverlaid);
		if (tscreen->getScreenState() == sf::TransMode::TransOn || tscreen->getScreenState() == sf::TransMode::Active)
		{
			if (!totherfocus)
			{
				//We are the top most screen
				tscreen->update(this->_time_tpf, this->_time_total);
				totherfocus = true;
			}
			if (!tscreen->isPopupScreen())
				toverlaid = true;
		}
	}	
}


//////////////////////////////////////////////////////
// Process the Input Events Generated
//////////////////////////////////////////////////////
void sf::LJMUGameBase::handleEvents()
{
	//Clear the processing buffer
	this->_screen_buffer.clear();

	//Check the number of active screens
	if (this->_screen_active.size() <= 0)
		return;

	//-------UPDATE THE GAME SCREEN----------------------------------
	//Copy the Screens into the buffer
	for (auto tscreen : this->_screen_active)
	{
		this->_screen_buffer.push_back(tscreen);
	}

	//Create an Event Object
	sf::Event tevent;

	//Poll the Window for All Input Events (May be multiple in one frame)
	while (this->_wndw.pollEvent(tevent))
	{
		if (tevent.type == sf::Event::Closed)
		{
			//Close the Application Window
			this->_wndw.close();
			//No need to process further events.  
			return;
		}

		//Only the top most screen gets events (could change?)
		this->_screen_buffer.back()->handleEvent(tevent);
	}
}


//////////////////////////////////////////////////////
// Render our 2D Game World
//////////////////////////////////////////////////////
void sf::LJMUGameBase::render()
{
	if (this->_screen_active.size() <= 0)
		return;

	static sf::Color tclear = this->_settings.getClearColour();
	this->_wndw.clear(sf::Color(0,0,0,255));

	// The update buffer is a frame snapshot and can still contain a screen that
	// removed and cleaned itself up during update(). Render only screens that
	// remain active so cleaned resources are never dereferenced.
	for (auto& tscreen : this->_screen_active)
	{
		if(tscreen->getScreenState() != sf::TransMode::Hidden)
			tscreen->render();
	}

#if _DEBUG
	//Draw the FPS Text
	const sf::View tgameView = this->_wndw.getView();
	this->_wndw.setView(this->_wndw.getDefaultView());
	this->_wndw.draw(this->_text_fps);
	this->_wndw.setView(tgameView);
#endif

	//Flip the Back Buffer with the Front Buffer
	this->_wndw.display();
}

//////////////////////////////////////////////////////
// Clean up any dynamically allocated resources
//////////////////////////////////////////////////////
void sf::LJMUGameBase::cleanup()
{
	this->clearScreens();
}

//--------------IMPLEMENTATION OF THE GAME LOOP--------------------------------------------------------------

/////////////////////////////////////////////////////
// This function sets up the windowing system
/////////////////////////////////////////////////////
void sf::LJMUGameBase::setupEngine()
{
	//Initialise the Game Window
	this->initialise();
	this->loadContent();
}

////////////////////////////////////////////////////
// This is the game loop of the application.
////////////////////////////////////////////////////
void sf::LJMUGameBase::runGameLoop()
{	
	sf::Clock tclock;
	sf::Time tprevtime  = tclock.restart();

	//Start the game loop - while the window is open, run. 
	while (this->_wndw.isOpen())
	{
		//Update our Timers
		sf::Time tcurrtime = tclock.getElapsedTime();
		this->_time_total = tcurrtime;
		this->_time_tpf = tcurrtime - tprevtime;	
		tprevtime = tcurrtime;
		
		//Process the Game Loop
		this->handleEvents();
		this->update();	
		this->render();		
#ifdef _DEBUG
		this->_text_fps.setString("Current FPS: " + sf::getIntegerFPS(this->_time_tpf));
#endif
	}
	this->cleanup();
}

//-----------------------INTERFACE IMPLEMENTATION-------------------------------------------

///////////////////////////////////////////////
// Get access to the Application Name as a Copy.
///////////////////////////////////////////////
std::string sf::LJMUGameBase::getAppName()
{
	return this->_settings.getAppName();
}

///////////////////////////////////////////////
// Get Access to the SFML Window - Mutable.
///////////////////////////////////////////////
sf::RenderWindow& sf::LJMUGameBase::getWindow()
{
	return this->_wndw;
}

///////////////////////////////////////////////
// Get Access to the Game Settings - Immutable
///////////////////////////////////////////////
const sf::LJMUSettings& sf::LJMUGameBase::getSettings() const
{
	return this->_settings;
}

sf::TheGameState& sf::LJMUGameBase::getGameState()
{
	return this->_gameState;
}

///////////////////////////////////////////////
// Get an Immutable Reference to the Total 
// Game Time. 
///////////////////////////////////////////////
const sf::Time & sf::LJMUGameBase::getTotalElapsedTime() const
{
	return this->_time_total;
}

///////////////////////////////////////////////
// Get an Immutable Reference to the current
// Elapsed Frame Time. 
///////////////////////////////////////////////
const sf::Time & sf::LJMUGameBase::getCurrentFrameTime() const
{
	return this->_time_tpf;
}


std::shared_ptr<sf::ILJMUScreenBase> sf::LJMUGameBase::getTopScreen()
{
	if(this->_screen_active.size() > 0)
		return this->_screen_active.back();
	return nullptr;
}

std::shared_ptr<sf::ILJMUScreenBase> sf::LJMUGameBase::getScreenWithPos(int ppos)
{
	if (ppos >= 0 && ppos < this->_screen_active.size())
	{
		//Cleanup the Screen and remove from the vector
		return this->_screen_active.at(ppos);
	}
	return nullptr;
}

std::shared_ptr<sf::ILJMUScreenBase> sf::LJMUGameBase::getScreenWithID(int pid)
{
	auto tscreen = std::find_if(this->_screen_active.begin(), this->_screen_active.end(), [pid](std::shared_ptr<ILJMUScreenBase> i)->bool { return i->getID() == pid; });
	if (tscreen == this->_screen_active.end())
		return nullptr;
	else
		return *tscreen;
}

bool sf::LJMUGameBase::removeTopScreen()
{
	if (this->_screen_active.size() > 0)
	{
		this->_screen_active.back()->cleanup();
		this->_screen_active.pop_back();
		return true;
	}
	return false;
}

bool sf::LJMUGameBase::removeScreenWithPos(int ppos)
{
	if (ppos >= 0 && ppos < this->_screen_active.size())
	{
		//Cleanup the Screen and remove from the vector
		this->_screen_active.at(ppos)->cleanup();
		this->_screen_active.erase(this->_screen_active.begin() + ppos);
		return true;
	}
	return false;
}

bool sf::LJMUGameBase::removeScreenWithID(int pid)
{
	auto tscreen = std::find_if(this->_screen_active.begin(), this->_screen_active.end(), [pid](std::shared_ptr<ILJMUScreenBase> i)->bool { return i->getID() == pid; });
	if (tscreen != this->_screen_active.end())
	{
		(*tscreen)->cleanup();
		this->_screen_active.erase(tscreen);
		return true;
	}
	return false;
}

void sf::LJMUGameBase::addScreen(std::shared_ptr<sf::ILJMUScreenBase> pscreen, int pid)
{
	pscreen->setID(pid);
	pscreen->setLJMUSFMLManager(shared_from_this());
	pscreen->loadContent();
	this->_screen_active.push_back(pscreen);
}

void sf::LJMUGameBase::clearScreens()
{
	for (auto tscreen : this->_screen_active)
	{
		tscreen->cleanup();
	}
	this->_screen_active.clear();
}

//-----------------------DEBUG ONLY METHODS-------------------------------------------------

#ifdef _DEBUG

///////////////////////////////////////////////
// Setup the Debugging Text
///////////////////////////////////////////////
void sf::LJMUGameBase::setupDebugText()
{
	//We don't need the Resource Helper for this one object
	this->_debug_fnt.loadFromFile(LJMUSettings::DIR_FONTS + "Sansation.ttf");

	//Setup the FPS Text Display. 
	this->_text_fps.setFont(this->_debug_fnt);
	this->_text_fps.setPosition(5.0f, this->_wndw.getSize().y - 25.0f);
	this->_text_fps.setFillColor(this->_settings.getDebugColour());
	this->_text_fps.setCharacterSize(18);
}

#endif
