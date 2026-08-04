#include <GameScreenMenuRoot.h>
#include <LJMUSettings.h>
#include <LJMUTrigonometry.h>
#include "GameManager.h"
//Include our game screens

#include <GameScreenMain.h>



#include "GameScreenShop.h"

#include "GameShopElemsBasic.h"

LJMU::GameScreenShop::GameScreenShop()
	:_selected_index(0),
     _selectedItem(0)
{

}

LJMU::GameScreenShop::~GameScreenShop()
{
}

void LJMU::GameScreenShop::loadContent()
{
	auto tmgr = this->getLJMUSFMLManager().lock();

	//Call our Sub-Routines - Some Order is Important
	this->loadResources();

	//Call our Setup Routines to Initialise the Menu
	this->setupShopBG();
	this->setupTitle();
	this->setupShopElements();

	//Setup our Cameras 
	this->setupCameras();
}

void LJMU::GameScreenShop::handleEvent(const sf::Event& pevent)
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

void LJMU::GameScreenShop::bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered)
{

}

void LJMU::GameScreenShop::update(sf::Time& ptpf, sf::Time& ptotal)
{
	//-------GET THE UPDATE TIMES----------------------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	//--------MENU GRAPHICAL UPDATE------------------------------------------------
	int i = 0;
	for (auto& telem : this->_shopItems)
	{
		const bool tselected = i == this->_selected_index;
		telem->IsSelected = tselected;
		this->_shopActions[telem].OnUpdate(telem);
		i++;
		telem->update(ptpf, ptotal);
	}
}



void LJMU::GameScreenShop::cleanup()
{
}

void LJMU::GameScreenShop::handleInput(sf::Keyboard::Key pkey, bool ppressed)
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
		auto telem = this->_shopItems.at(this->_selected_index);
		this->_shopActions[telem].OnIncrement(telem);
	}
	else if (this->_controls.isActive(Actions::DECREMENT))
	{
		auto telem = this->_shopItems.at(this->_selected_index);
		this->_shopActions[telem].OnDecrement(telem);
	}
	else if (this->_controls.isActive(Actions::SELECT))
	{
		auto telem = this->_shopItems.at(this->_selected_index);
		this->_shopActions[telem].OnSelect(telem);
	}
	else if (this->_controls.isActive(Actions::BACK))
	{
		this->onBack(); // onBack will have the player close the shop screen, and return to the now un paused, GameScreenMain
	}
}

void LJMU::GameScreenShop::onBack()
{

	auto tmgr = getLJMUSFMLManager().lock();
	
	tmgr->getGameState().coins = 100;
	int tid = static_cast<int>(sf::GameScreens::ScreenOptions);
	tmgr->addScreen(std::make_shared<LJMU::GameScreenMenuRoot>(), tid);
}

void LJMU::GameScreenShop::loadResources()
{
	//Load the Default Font
	
	std::string tbg_dir = sf::LJMUSettings::DIR_BG;
	std::string tf_dir = sf::LJMUSettings::DIR_FONTS;
	
	using namespace LJMU;
	//Load the backgrounds
	this->_res_level.load("menu_bg", tbg_dir + "shop_bg.png");
	//Load the Fonts
	this->_res_font.load("Title", tf_dir + "Title.TTF");

	
}

void LJMU::GameScreenShop::setupShopBG()
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

void LJMU::GameScreenShop::setupShopElements()
{

	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());


	//-------------Add the Shop Items----------------------------------------------------------------
	const ShopItemPtr ItemHealth = std::make_shared<GameShopElemBasic>();
	ItemHealth->SetItemName("HEALTH");
	ItemHealth->SetItDescription("Consume to regain crucial HP!");
	ItemHealth->SetItemCost(30);
	ItemHealth->setImageId(0);
	ItemHealth->loadContent();
	this->addItem(ItemHealth);



	const ShopItemPtr ItemSpeed = std::make_shared<GameShopElemBasic>();
	ItemSpeed->SetItemName("SPEED");
	ItemSpeed->SetItDescription("Consume to temporarily boost \n speed!");
	ItemSpeed->SetItemCost(20);
	ItemSpeed->setImageId(2);
	ItemSpeed->loadContent();
	this->addItem(ItemSpeed);


	const ShopItemPtr ItemInvincible = std::make_shared<GameShopElemBasic>();
	ItemInvincible->SetItemName("INVINCIBILITY");
	ItemInvincible->SetItDescription("Consume to become temporarily invincibilty!");
	ItemInvincible->SetItemCost(50);
	ItemInvincible->setImageId(1);
	ItemInvincible->loadContent();
	this->addItem(ItemInvincible);


	
	//---------------Wire Up Delegates for each Menu Item---------------------------------------

	//---------MOVEMENT AND UPDATE EVENTS------------------------------------------------



	//----SELECTION EVENTS-----------------------------------------------------------------------

	//Health
	this->_shopActions[ItemHealth].Actions[ShopActionType::Selection] = [&](ShopItemPtr tptr)
	{
		 
	}
	



	////-----SAVE EVENTS-------------------------------------------------------------------------
;

int i = 0;
//Position the Shop Items. 
for (auto& telem : this->_shopItems)
{
	const sf::Vector2f tpos(100.f + (static_cast<float>(i) * 400.f), 300.f);
	telem->setItemPos(tpos);
	telem->loadContent();
	++i;
}

	//----------ASSOCIATE AN ICON WITH A MENU ITEM-----------------------------------------


}

void LJMU::GameScreenShop::setupCameras()
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

void LJMU::GameScreenShop::setupTitle()
{

	ShopTitle.setString("THE SHOP");//Place holder name for shop until i think of a better one
	ShopTitle.getText().setCharacterSize(55);
	ShopTitle.getText().setFont(this->_res_font.get("Title"));

	ShopTitle.getText().setPosition(650, 100);
	ShopTitle.getText().setString(ShopTitle.getString());

	ShopTitle.getText().setFillColor(sf::Color::White);
}

void LJMU::GameScreenShop::onMoveUp()
{
	const int titems = static_cast<int>(this->_shopItems.size());
	int tindex = this->_selected_index + titems;
	this->_selected_index = --tindex % titems;
	
}

void LJMU::GameScreenShop::onMoveDown()
{
	const int titems = static_cast<int>(this->_shopItems.size());
	int tindex = this->_selected_index + titems;
	this->_selected_index = ++tindex % titems;
}





void LJMU::GameScreenShop::addItem(ShopItemPtr pitem)
{
	//Add the Item to the List of Menu Items and the Action Map. 
	this->_shopItems.push_back(pitem);
	this->_shopActions.insert(std::make_pair(pitem, ShopActions()));


}


void LJMU::GameScreenShop::onPurchase()
{
	
}




void LJMU::GameScreenShop::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const int tcm = 0;

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	this->_cameras[tcm].makeCurrent(twndw);

	//Draw the Background to Screen
	for (auto& tbg : this->_bg_layers) { tbg.render(twndw); }
	ShopTitle.render(twndw);
	for (auto& sI : this->_shopItems) { sI->render(twndw); }
	
}
