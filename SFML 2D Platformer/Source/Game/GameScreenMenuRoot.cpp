#include <GameScreenMenuRoot.h>
#include <LJMUSettings.h>
#include <LJMUTrigonometry.h>

//Include our game screens

#include <GameScreenMain.h>
#include <GameScreenLevel.h>

#include <MenuScreenSubMenu.h>

#include "GameScreenShop.h"
//#include <GameScreenHUB.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::GameScreenMenuRoot::GameScreenMenuRoot()
	:_selected_index(0)
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::GameScreenMenuRoot::~GameScreenMenuRoot()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//  Setup the Initial Content of the 
//  Level.
/////////////////////////////////////////
void LJMU::GameScreenMenuRoot::loadContent()
{
	auto tmgr = this->getLJMUSFMLManager().lock();

	//Call our Sub-Routines - Some Order is Important
	this->loadResources();

	//Call our Setup Routines to Initialise the Menu
	this->setupMenuBG();
	this->setupTitle();
	this->setupMenuElements();

	//Setup our Cameras 
	this->setupCameras();
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::GameScreenMenuRoot::handleEvent(const sf::Event& pevent)
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
void LJMU::GameScreenMenuRoot::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::GameScreenMenuRoot::update(sf::Time & ptpf, sf::Time & ptotal)
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
void LJMU::GameScreenMenuRoot::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const int tcm = 0;

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	this->_cameras[tcm].makeCurrent(twndw);
	
	//Draw the Background to Screen
	for (auto& tbg : this->_bg_layers) { tbg.render(twndw);  }
	MenuTitle.render(twndw);
	for (auto& tmt : this->_menu_items) { tmt->render(twndw); }
	for (auto& tms : this->_menu_sprites) { tms.second.render(twndw); }
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::GameScreenMenuRoot::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::GameScreenMenuRoot::handleInput(sf::Keyboard::Key pkey, bool ppressed)
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
	else if (this->_controls.isActive(Actions::INCREMENT))
	{
		 auto telem = this->_menu_items.at(this->_selected_index);
		 this->_menu_actions[telem].OnIncrement(telem);
	}
	else if (this->_controls.isActive(Actions::DECREMENT))
	{
		 auto telem = this->_menu_items.at(this->_selected_index);
		 this->_menu_actions[telem].OnDecrement(telem);
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
void LJMU::GameScreenMenuRoot::loadResources()
{
	//Load the Default Font
	std::string ts_dir = sf::LJMUSettings::DIR_STATICS;
	std::string tbg_dir = sf::LJMUSettings::DIR_BG;
	std::string tf_dir = sf::LJMUSettings::DIR_FONTS;
	std::string tts_dir = sf::LJMUSettings::DIR_TILESETS;
	std::string tdf_dir = sf::LJMUSettings::DIR_DATAFILES;

	using namespace LJMU;

	//Load the Fonts
	this->_res_font.load("Title", tf_dir + "Title.TTF");
	this->_res_font.load("Elems", tf_dir + "Ninja.otf");

	//Load the backgrounds
	this->_res_level.load("menu_bg", tbg_dir + "menu_bg_3.png");

	//Load the Static Sprites
	this->_res_static.load("menu_icons", tts_dir + "ms_iconset.png");
}

///////////////////////////////////////////
// Load our Level Resources
///////////////////////////////////////////
void LJMU::GameScreenMenuRoot ::setupMenuBG()
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
void LJMU::GameScreenMenuRoot::setupMenuElements()
{
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	this->_clr_curr = sf::Color::Cyan;
	this->_clr_other = sf::Color::Magenta;


	//-------------Add the Menu Items----------------------------------------------------------------

	auto itemOptions = this->createMenuItem("Options Menu");
	this->addItem(itemOptions);

	auto itemPlatformer = this->createMenuItem("Platformer!");
	this->addItem(itemPlatformer);

	auto itemHub = this->createMenuItem("HUB");
	this->addItem(itemHub);

	auto itemShop = this->createMenuItem("Shop");
	this->addItem(itemShop);

	auto ExitGame = this->createMenuItem("Exit");
	this->addItem(ExitGame);



	//---------------Wire Up Delegates for each Menu Item---------------------------------------

	//---------MOVEMENT AND UPDATE EVENTS------------------------------------------------

	

	//----SELECTION EVENTS-----------------------------------------------------------------------

	//Options
	this->_menu_actions[itemOptions].Actions[MenuActionType::Selection] = [&](MenuItemPtr tptr)
	{
		auto tmgr = getLJMUSFMLManager().lock();
		onSaveAll();
		tmgr->getGameState().coins = 100;
		int tid = static_cast<int>(sf::GameScreens::ScreenOptions);
		tmgr->addScreen(std::make_shared<LJMU::LJMUMenuScreenSubMenu>(),tid);
	};

	//Platformer!
	this->_menu_actions[itemPlatformer].Actions[MenuActionType::Selection] = [&](MenuItemPtr tptr)
	{
		auto tmgr = getLJMUSFMLManager().lock();
		onSaveAll();
		int tid = static_cast<int>(sf::GameScreens::ScreenPlatform);
		tmgr->addScreen(std::make_shared<LJMU::LJMUGameScreenLevel>(), tid);
	};

	//HUB
	this->_menu_actions[itemHub].Actions[MenuActionType::Selection] = [&](MenuItemPtr tptr)
	{
		auto tmgr = getLJMUSFMLManager().lock();
		onSaveAll();
		int tid = static_cast<int>(sf::GameScreens::ScreenHub);
		//tmgr->addScreen(std::make_shared<LJMU::GameScreenHUB>(), tid);
	};

	//SHOP
	this->_menu_actions[itemShop].Actions[MenuActionType::Selection] = [&](MenuItemPtr tptr)
	{
		auto tmgr = getLJMUSFMLManager().lock(); // using auto keyword to mitigate needing to specify what the data type is
		onSaveAll();
		int tid = static_cast<int>(sf::GameScreens::ScreenShop);
		tmgr->addScreen(std::make_shared<LJMU::GameScreenShop>(), tid);
	};

	//Exit Game
	this->_menu_actions[ExitGame].Actions[MenuActionType::Selection] = [&](MenuItemPtr tptr)
	{
		auto tmgr = this->getLJMUSFMLManager().lock();
		tmgr->getWindow().close();
	};

	

	////-----SAVE EVENTS-------------------------------------------------------------------------
	//this->_menu_actions[titem1].Actions[MenuActionType::Save] = [&](MenuItemPtr tptr)
	//{
	//	sf::LJMUGameState& tsgs = this->getLJMUSFMLManager().lock()->getGameState();
	//	tsgs.setStringProp("difficulty", _s_diff.Options[_s_diff.Index]);
	//};
	//this->_menu_actions[titem2].Actions[MenuActionType::Save] = [&](MenuItemPtr tptr)
	//{
	//	sf::LJMUGameState& tsgs = this->getLJMUSFMLManager().lock()->getGameState();
	//	tsgs.setStringProp("chartype", _s_char.Options[_s_char.Index]);
	//};

	const sf::Vector2f tstartpos(300,200);
	sf::Vector2f tcurrpos = tstartpos;
	for (auto titem : this->_menu_items)
	{
		titem->getText().setPosition(tcurrpos);
		tcurrpos.y += 100;
		tcurrpos.x += 40;
	}

	//----------ASSOCIATE AN ICON WITH A MENU ITEM-----------------------------------------
	

	GameObjectBasic Options;
	Options.getSprite().setTexture(this->_res_static.get("menu_icons"));
	Options.getSprite().setTextureRect(sf::IntRect(384, 0, 128, 128));

	this->_menu_sprites.insert(std::make_pair(itemOptions, Options));

	GameObjectBasic Platformer;
	Platformer.getSprite().setTexture(this->_res_static.get("menu_icons"));
	Platformer.getSprite().setTextureRect(sf::IntRect(128, 0, 128, 128));


	this->_menu_sprites.insert(std::make_pair(itemPlatformer, Platformer));

	GameObjectBasic HUB;
	HUB.getSprite().setTexture(this->_res_static.get("menu_icons"));
	HUB.getSprite().setTextureRect(sf::IntRect(256, 0, 128, 128));

	this->_menu_sprites.insert(std::make_pair(itemHub, HUB));

	GameObjectBasic Shop;
	Shop.getSprite().setTexture(this->_res_static.get("menu_icons"));
	Shop.getSprite().setTextureRect(sf::IntRect(0, 0, 128, 128));

	this->_menu_sprites.insert(std::make_pair(itemShop, Shop));

	

	for (auto& tpair : this->_menu_sprites)
	{
		sf::Vector2f tpos = tpair.first->getText().getPosition();
		tpos.x -= 150;
		tpair.second.getSprite().setPosition(tpos);
		tpair.second.getSprite().setScale(0.6f, 0.6f);
	}
}

///////////////////////////////////////////
// Setup our Cameras
///////////////////////////////////////////
void LJMU::GameScreenMenuRoot ::setupCameras()
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

void LJMU::GameScreenMenuRoot::setupTitle()
{
	MenuTitle.setString("IMORA 40K");//Place holder name untill one is chosen by group
	MenuTitle.getText().setCharacterSize(55);
	MenuTitle.getText().setFont(this->_res_font.get("Title"));

	MenuTitle.getText().setPosition(650,100);
	MenuTitle.getText().setString(MenuTitle.getString());

	MenuTitle.getText().setFillColor(sf::Color::White);
}

////////////////////////////////////////
// Construct a Menu Item and return the instance.
////////////////////////////////////////
LJMU::GameScreenMenuRoot::MenuItemPtr LJMU::GameScreenMenuRoot::createMenuItem(std::string pdefaulttext)
{
	//Setup the Shared Pointer to the Item.
	MenuItemPtr tptr = std::make_shared<LJMU::GameHUDElemBasic>();
	tptr->setString(pdefaulttext);
	tptr->getText().setCharacterSize(40);
	tptr->getText().setFont(this->_res_font.get("Elems"));
	return tptr;
}

////////////////////////////////////////
// Add the given menu item to the 
// relevant data structures. 
////////////////////////////////////////
void LJMU::GameScreenMenuRoot::addItem(MenuItemPtr pitem)
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
void LJMU::GameScreenMenuRoot::onMoveUp()
{
	const int titems = static_cast<int>(this->_menu_items.size());
	int tindex = this->_selected_index + titems; 
	this->_selected_index = --tindex % titems;
}

////////////////////////////////////////
// Handle Moving the Menu Item Up
////////////////////////////////////////
void LJMU::GameScreenMenuRoot::onMoveDown()
{
	const int titems = static_cast<int>(this->_menu_items.size());
	int tindex = this->_selected_index + titems;
	this->_selected_index = ++tindex % titems;
}

////////////////////////////////////////
//  Handle Back Events
////////////////////////////////////////
void LJMU::GameScreenMenuRoot::onCancel()
{
	//Close the Window - this will exit the game loop. 
	auto tmgr = this->getLJMUSFMLManager().lock();
	tmgr->getWindow().close();
}

////////////////////////////////////////
//  Handle Save Events
////////////////////////////////////////
void LJMU::GameScreenMenuRoot::onSaveAll()
{	
	for (auto telempair : this->_menu_actions)
	{
		telempair.second.OnSave(telempair.first);
	}
}