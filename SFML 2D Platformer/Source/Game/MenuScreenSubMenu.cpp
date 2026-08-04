#include <MenuScreenSubMenu.h>
#include <LJMUSettings.h>
#include <LJMUTrigonometry.h>


///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUMenuScreenSubMenu::LJMUMenuScreenSubMenu()
	:_selected_index(0)
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUMenuScreenSubMenu::~LJMUMenuScreenSubMenu()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//  Setup the Initial Content of the 
//  Level.
/////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::loadContent()
{
	auto tmgr = this->getLJMUSFMLManager().lock();

	//Call our Sub-Routines - Some Order is Important
	this->loadResources();

	//Call our Setup Routines to Initialise the Menu
	this->setupMenuBG();
	this->setupMenuElements();

	//Setup our Cameras 
	this->setupCameras();
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::handleEvent(const sf::Event& pevent)
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
void LJMU::LJMUMenuScreenSubMenu::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::update(sf::Time & ptpf, sf::Time & ptotal)
{
	//-------GET THE UPDATE TIMES----------------------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	//--------MENU GRAPHICAL UPDATE------------------------------------------------
	int i = 0;
	for (auto telem : this->_menu_items)
	{
		bool tselected = i == this->_selected_index;
		sf::Color& tclr = tselected ? this->_clr_curr : this->_clr_other;
		telem->getText().setFillColor(tclr);
		if (tselected)
		{
			float tscale =	1.5f;
			telem->getText().setScale(tscale, tscale);
		}
		else
		{
			float tscale = 1.0f;
			telem->getText().setScale(tscale, tscale);
		}
		i++;
		this->_menu_actions[telem].OnUpdate(telem);
	}
}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const int tcm = 0;

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	this->_cameras[tcm].makeCurrent(twndw);
	
	//Draw the Background to Screen
	for (auto& tbg : this->_bg_layers) { tbg.render(twndw);  }
	for (auto& tmt : this->_menu_items) { tmt->render(twndw); }
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();
	using Keys = sf::Keyboard::Key;
	using Actions = MenuControls::MenuActions;

	this->_controls.setFlag(pkey, ppressed);
	if (this->_controls.isActive(Actions::MOVE_UP))
	{
		 this->onMoveUp();
	}
	else if (this->_controls.isActive(Actions::MOVE_DOWN))
	{
		 this->onMoveDown();
	}
	else if (this->_controls.isActive(Actions::SELECT))
	{
		 auto telem = this->_menu_items.at(this->_selected_index);
		 this->_menu_actions[telem].OnSelect(telem);
	}
	else if (this->_controls.isActive(Actions::BACK))
	{
		 this->onCancel();
	}
}
//-------------LOGICAL SUB-ROUTINES---------------------------------------

///////////////////////////////////////////
// Load our External DCC Resources
///////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu ::loadResources()
{
	//Load the Default Font
	std::string ts_dir = sf::LJMUSettings::DIR_STATICS;
	std::string tbg_dir = sf::LJMUSettings::DIR_BG;
	std::string tf_dir = sf::LJMUSettings::DIR_FONTS;
	std::string tts_dir = sf::LJMUSettings::DIR_TILESETS;
	std::string tdf_dir = sf::LJMUSettings::DIR_DATAFILES;

	using namespace LJMU;

	//Load the Fonts
	this->_res_font.load("Title" ,tf_dir + "Sansation.ttf");
	this->_res_font.load("Elems", tf_dir + "ca.ttf");
	
	//Load the backgrounds
	this->_res_level.load("menu_bg", tbg_dir + "menu_bg_2.png");
}

///////////////////////////////////////////
// Load our Level Resources
///////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu ::setupMenuBG()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	//Setup our Background Layer
	LJMU::GameObjectBasic tbg;
	tbg.getSprite().setTexture(this->_res_level.get("menu_bg"));
	sf::makeFullScreen(tbg.getSprite(), tscrdim);
	this->_bg_layers.push_back(tbg);
}

///////////////////////////////////////////
// Setup our Level Elements
///////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::setupMenuElements()
{
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	this->_clr_curr = sf::Color::Cyan;
	this->_clr_other = sf::Color::Magenta;

	//-------------Add the Menu Items----------------------------------------------------------------

	auto titem1 = this->createMenuItem("Return to Main Screen");
	this->addItem(titem1);


	
	//---------------Wire Up Delegates for each Menu Item---------------------------------------

	this->_menu_actions[titem1].Actions[MenuActionType::Selection] = [&](MenuItemPtr tptr)
	{
		auto tmgr = getLJMUSFMLManager().lock();
	
		tmgr->removeTopScreen();
	};
	//---------MOVEMENT AND UPDATE EVENTS------------------------------------------------
			
	//-----SAVE EVENTS-------------------------------------------------------------------------

	const sf::Vector2f tstartpos(300,200);
	sf::Vector2f tcurrpos = tstartpos;
	for (auto titem : this->_menu_items)
	{
		titem->getText().setPosition(tcurrpos);
		tcurrpos.y += 100;
		tcurrpos.x += 40;
	}

	//----------ASSOCIATE AN ICON WITH A MENU ITEM-----------------------------------------
}

///////////////////////////////////////////
// Setup our Cameras
///////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu ::setupCameras()
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

////////////////////////////////////////
// Construct a Menu Item and return the instance.
////////////////////////////////////////
LJMU::LJMUMenuScreenSubMenu::MenuItemPtr LJMU::LJMUMenuScreenSubMenu::createMenuItem(std::string pdefaulttext)
{
	//Setup the Shared Pointer to the Item.
	MenuItemPtr tptr = std::make_shared<LJMU::GameHUDElemBasic>();
	tptr->setString(pdefaulttext);
	tptr->getText().setCharacterSize(40);
	tptr->getText().setFont(this->_res_font.get("Title"));
	return tptr;
}

////////////////////////////////////////
// Add the given menu item to the 
// relevant data structures. 
////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::addItem(MenuItemPtr pitem)
{
	
	//Add the Item to the List of Menu Items and the Action Map. 
	this->_menu_items.push_back(pitem);
	this->_menu_actions.insert(std::make_pair(pitem, MenuActions()));

	//Create the Default Update Function
	auto tupdatefunc = [](MenuItemPtr pitem)
	{
		pitem->getText().setString(pitem->getString());
	};
	//Insert this Custom Event
	this->_menu_actions[pitem].Actions.insert(std::make_pair(MenuActionType::Update, tupdatefunc));
	
}

//-----------EVENT HANDLERS------------------------------------------

////////////////////////////////////////
// Handle Moving the Menu Item Down
////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::onMoveUp()
{
	const int titems = static_cast<int>(this->_menu_items.size());
	int tindex = this->_selected_index + titems; 
	this->_selected_index = --tindex % titems;
}

////////////////////////////////////////
// Handle Moving the Menu Item Up
////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::onMoveDown()
{
	const int titems = static_cast<int>(this->_menu_items.size());
	int tindex = this->_selected_index + titems;
	this->_selected_index = ++tindex % titems;
}

////////////////////////////////////////
//  Handle Back Events
////////////////////////////////////////
void LJMU::LJMUMenuScreenSubMenu::onCancel()
{
	//Close the Window - this will exit the game loop. 
	auto tmgr = this->getLJMUSFMLManager().lock();
	tmgr->getWindow().close();
}