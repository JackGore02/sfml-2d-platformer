#include "GameScreenLevel.h"

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenLevel::LJMUGameScreenLevel()
	: player(nullptr)
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenLevel::~LJMUGameScreenLevel()
{
	//Nothing Dynamic to Destruct. 
}

void LJMU::LJMUGameScreenLevel::loadContent()
{
	auto tmgr = this->getLJMUSFMLManager().lock();

	//Call our Sub-Routines - Some Order is Important
	switch (currentLevel)
	{
	case GameLevels::Level1:
		this->loadLevel1Resources();
		break;
	case GameLevels::Level2:
		this->loadLevel2Resources();
		break;
	}

	//Call our Setup Routines to Initialise the Game World
	switch (currentLevel)
	{
	case GameLevels::Level1:
		this->setupLevel1();
		break;
	case GameLevels::Level2:
		this->setupLevel2();
		break;
	}
	
	this->setupPickups();
	this->setupPlayers();
	this->setupHUD();

	//Setup our Cameras 
	this->setupCameras();
	//-----------------------------------------------
#ifdef _DEBUG
	//this->_debug_gp.setThickness(1.0f);
	//this->_debug_gp.setVisiblity(false, false, false, false);

	//this->_debug_hud.setThickness(1.0f);
	//this->_debug_hud.setColours(sf::Color::Green, sf::Color::Green, sf::Color::Green, sf::Color::Green);
	//this->_debug_hud.setVisiblity(false, false, false, false);
#endif
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenLevel::handleEvent(const sf::Event& pevent)
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
void LJMU::LJMUGameScreenLevel::bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenLevel::update(sf::Time& ptpf, sf::Time& ptotal)
{
	//-------GET THE UPDATE TIMES----------------------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	//--------OBJECT TRANSFORMATION LOGIC--------------------------------------------
	//for (auto& tp : this->_level_players)
		//tp.update(ptpf, ptotal);
	player->update(ptpf, ptotal);

	for (auto& tbe : this->_level_elems)
	{
		if (tbe.getIsMovable())
		{
			auto& ts = tbe.getSprite();
			sf::Vector2f tinitialpos = tbe.getOrigPos();
			sf::Vector2f tdisp(0, sinf(ttotal * 2.0f) * tbe.getAmplitude());
			ts.setPosition(tinitialpos + tdisp);
		}
		tbe.update(ptpf, ptotal);
	}


	//----COLLISION DETECTION--------------------------------------------------------
	for (auto& telem : this->_level_elems)
	{
		player->checkCollision(telem);
	}

	if (player->getSprite().getPosition().y > 2000)
	{
		player->getSprite().setPosition(100, 300);

		resetCamera();
	}

	//----Check for level completion--------------
	if (player->levelCompleted)
	{
		if (currentLevel == GameLevels::Level1)
		{
			currentLevel = GameLevels::Level2;
			cleanup();
			loadContent();
		}
		else
		{
			returnToMainMenu();
		}
		return;
	}

	//----Handle Input on our Active Camera------------------------------------------
	this->handleCamera(ttpf, ttotal);

	//--------HUD UPDATES------------------------------------------------------------


	//--------DEBUG OUTPUT-----------------------------------------------------------
}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenLevel::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	this->_camera_gp.makeCurrent(twndw);
	//Draw the Background to Screen
	for (auto& tbg : this->_level_env) { tbg.render(twndw); }
	//Draw the Background layer
	for (auto& tback : this->_level_back) { tback.render(twndw); }

	//for (auto& tp : this->_level_players) { tp.render(twndw); }
	//Draw the Elements
	for (auto& tbe : this->_level_elems) { tbe.render(twndw); }
	//Draw the Pickups
	//this->_level_pickups.render(twndw);
	//Draw the Players
	twndw.draw(player->getSprite());
	//Draw the Foreground Layer
	for (auto& tfore : this->_level_fore) { tfore.render(twndw); }
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenLevel::cleanup()
{
	//Clean up all of our STL Data Structures. 
	this->_level_env.clear();
	this->_level_back.clear();
	this->_level_elems.clear();
	this->_level_fore.clear();
	player.reset();

	// ResourceHelper uses insert-only keys. Clear level-owned resources so the
	// next level can load its own assets under the same logical names.
	this->_res_anim.clear();
	this->_res_level.clear();
	this->_res_static.clear();
	this->_res_colls.clear();
	//this->_level_players.clear();

	//Cleanup our Game Objects
	//this->_level_hud.cleanup();
}

void LJMU::LJMUGameScreenLevel::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	this->playerControls.setFlag(pkey, ppressed);
}

void LJMU::LJMUGameScreenLevel::handleCamera(float ptpf, float ttotal)
{
	sf::Vector2f tlastpos = this->_camera_gp.getViewRO().getCenter();

	//this->_camera_gp.handleInput(ptpf, ttotal);

	float tscreenhalf = static_cast<float>(this->_manager.lock()->getWindow().getSize().x) * 0.5f;
	if (player->getSprite().getPosition().x > tscreenhalf)
	{
		float tx = this->player->getSprite().getPosition().x;
		float ty = tlastpos.y;
		this->_camera_gp.getView().setCenter(tx, ty);
	}

	sf::Vector2f tcurrpos = this->_camera_gp.getViewRO().getCenter();
	sf::Vector2f tdiff = tcurrpos - tlastpos;

	//Parallax scrolling effect for foreground
	float tcamx = tcurrpos.x - tscreenhalf;
	float tcamy = 0;
	for (auto& tbg : this->_level_env)
	{
		tbg.getSprite().setPosition(tcamx, tcamy);
	}
	for (auto& tfore : this->_level_fore)
	{
		tfore.getSprite().move(-tdiff * 1.25f);
	}
}

void LJMU::LJMUGameScreenLevel::loadLevel1Resources()
{
	//Load the Default Font
	std::string ta_dir = sf::LJMUSettings::DIR_ANIM;
	std::string td_dir = sf::LJMUSettings::DIR_DATAFILES;

	using namespace LJMU;
	this->_res_colls.load("bg", td_dir + "assets_bg.txt");
	this->_res_colls.load("level", td_dir + "assets_level.txt");

	auto tenv = this->_res_colls.get("bg");
	for (auto ts : tenv.Assets)
	{
		std::string tkey = ts.first;
		std::string tpath = sf::LJMUSettings::DIR_BG + ts.second;
		this->_res_static.load(tkey, tpath);
	}
	auto tlevel = this->_res_colls.get("level");
	for (auto ts : tlevel.Assets)
	{
		std::string tkey = ts.first;
	    std::string tpath = sf::LJMUSettings::DIR_STATICS + ts.second;
		this->_res_level.load(tkey, tpath);
	}
}

void LJMU::LJMUGameScreenLevel::loadLevel2Resources()
{
	//Load the Default Font
	std::string ta_dir = sf::LJMUSettings::DIR_ANIM;
	std::string td_dir = sf::LJMUSettings::DIR_DATAFILES;

	using namespace LJMU;
	this->_res_colls.load("bg", td_dir + "assets_bg_lvl2.txt");
	this->_res_colls.load("level", td_dir + "assets_level2.txt");

	auto tenv = this->_res_colls.get("bg");
	for (auto ts : tenv.Assets)
	{
		std::string tkey = ts.first;
		std::string tpath = sf::LJMUSettings::DIR_BG + ts.second;
		this->_res_static.load(tkey, tpath);
	}
	auto tlevel = this->_res_colls.get("level");
	for (auto ts : tlevel.Assets)
	{
		std::string tkey = ts.first;
		std::string tpath = sf::LJMUSettings::DIR_STATICS + ts.second;
		this->_res_level.load(tkey, tpath);
	}
}

void LJMU::LJMUGameScreenLevel::setupPlayers()
{
	player.reset(new GamePlayer(playerControls, sf::Vector2f(100,300)));
}

void LJMU::LJMUGameScreenLevel::setupLevel1()
{
	//Load up the environment
	SideEnvMgr tenv;
	tenv.loadFromFile("Assets/Data/level_env.txt");
	for (auto& te : tenv.Environments)
	{
		GameObjectBasic tenv;
		tenv.setLayer(te.Layer);
		tenv.getSprite().setTexture(this->_res_static.get(te.TexRef));
		tenv.getSprite().setPosition(te.Position);

		if (te.WithCamera)
			this->_level_env.push_back(tenv);
		else if (te.Layer < 2)
			this->_level_back.push_back(tenv);
		else
		{
			tenv.setOrigPos(te.Position);
			this->_level_fore.push_back(tenv);
		}
	}

	//Load up the level
	SideLevelMgr tlmgr;
	if (!tlmgr.loadFromFile("Assets/Data/level_geom.txt"))
		throw std::runtime_error("Unable to load Assets/Data/level_geom.txt");
	for (auto& tl : tlmgr.Elements)
	{
		GameObjectBasic telem;
		telem.setLayer(2);
		telem.getSprite().setPosition(tl.Pos);
		telem.getSprite().setTexture(this->_res_level.get(tl.TexRef));
		telem.setIsMovable(tl.isMovable);
		telem.setOrigPos(tl.Pos);
		telem.setAmplitude(tl.Amplitude);
		telem.setIsTrap(tl.isTrap);
		telem.setIsGoal(tl.isGoal);
		this->_level_elems.push_back(telem);
	}
}

void LJMU::LJMUGameScreenLevel::setupLevel2()
{
	//Load up the environment
	SideEnvMgr tenv;
	tenv.loadFromFile("Assets/Data/level2_env.txt");
	for (auto& te : tenv.Environments)
	{
		GameObjectBasic tenv;
		tenv.setLayer(te.Layer);
		tenv.getSprite().setTexture(this->_res_static.get(te.TexRef));
		tenv.getSprite().setPosition(te.Position);

		if (te.WithCamera)
			this->_level_env.push_back(tenv);
		else if (te.Layer < 2)
			this->_level_back.push_back(tenv);
		else
		{
			tenv.setOrigPos(te.Position);
			this->_level_fore.push_back(tenv);
		}
	}

	//Load up the level
	SideLevelMgr tlmgr;
	if (!tlmgr.loadFromFile("Assets/Data/level2_geom.txt"))
		throw std::runtime_error("Unable to load Assets/Data/level2_geom.txt");
	for (auto& tl : tlmgr.Elements)
	{
		GameObjectBasic telem;
		telem.setLayer(2);
		telem.getSprite().setPosition(tl.Pos);
		telem.getSprite().setTexture(this->_res_level.get(tl.TexRef));
		telem.setIsMovable(tl.isMovable);
		telem.setOrigPos(tl.Pos);
		telem.setAmplitude(tl.Amplitude);
		telem.setIsTrap(tl.isTrap);
		telem.setIsGoal(tl.isGoal);
		this->_level_elems.push_back(telem);
	}
}

void LJMU::LJMUGameScreenLevel::setupPickups()
{

}

void LJMU::LJMUGameScreenLevel::setupHUD()
{

}

void LJMU::LJMUGameScreenLevel::setupCameras()
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
	this->_camera_gp = tcamobj;
}

void LJMU::LJMUGameScreenLevel::resetCamera()
{
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	sf::Vector2f tcamcentre = sf::tof(twndw.getSize()) * 0.5f;
	this->_camera_gp.getView().setCenter(tcamcentre);

	//Reset the foreground
	for (auto& tfore : this->_level_fore)
	{
		tfore.getSprite().setPosition(tfore.getOrigPos());
	}
}

void LJMU::LJMUGameScreenLevel::returnToMainMenu()
{
	exitScreen();
}
