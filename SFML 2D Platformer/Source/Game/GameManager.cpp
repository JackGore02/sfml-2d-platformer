#include "GameManager.h"

using sf::LJMUSettings;

//--------------------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------

/////////////////////////////////////////////
// Constructor for our Game State Class.
/////////////////////////////////////////////
LJMU::LJMUGameManager::LJMUGameManager(): 
GameWorldWindow(),
CameraGame(),
CameraHUD(),
CameraControl(),
ResourceSprites(),
ResourceFonts(),
ResourceColour(),
MapEnemyTexture(),
MapEnemyColour(),
GameWorldSize(),
GameWorldBounds(),
WorldLevel(),
WorldHUD(),
GamePlayTime(),
GameLives(),
GameScore(),
Coins(),
GameMode()
{

}

/////////////////////////////////////////////
// Destructor for our Game State class. 
/////////////////////////////////////////////
LJMU::LJMUGameManager::~LJMUGameManager()
{
	this->destroy();
}

//---------------------PUBLIC METHODS---------------------------------------------------------------

/////////////////////////////////////////////
// Create the Game State
/////////////////////////////////////////////
void LJMU::LJMUGameManager::create(sf::Vector2f pwndsize)
{
	//----------SETUP THE INITIAL GAME DATA---------------------------------------------------------
	this->GameScore = 0;
	this->Coins = 100;
	this->GamePlayTime = 0.0f;
	this->GameStartTime = 3.0f;
	this->GameEndTimeStart = 0.0f;
	this->GameEndTimeDelay = 3.0f;
	this->GameLives = -1;
	this->GameWorldWindow = pwndsize;
	this->GameWorldSize = this->GameWorldWindow;
	this->GameWorldBounds = sf::fromdimf(this->GameWorldSize);
	this->GameMode = LJMUGamePlayMode::GAME_START;
	
	//----------SETUP UP THE GAME ASSETS----------------------------------------------------
	//Load the Default Font
	this->ResourceFonts.load(LJMUSIFont::SANSATION, LJMUSettings::DIR_FONTS + "Sansation.ttf");
	this->ResourceFonts.load(LJMUSIFont::RETRO, LJMUSettings::DIR_FONTS + "retrofont.ttf");

	//Load the Sprite Textures which are used in the game
	this->ResourceSprites.load(LJMUSIAssets::PLAYER_ANIM, LJMUSettings::DIR_ANIM + "player_anim.png");
	this->ResourceSprites.load(LJMUSIAssets::ALIEN_ONE_A, LJMUSettings::DIR_ANIM + "si_anim1.png");
	this->ResourceSprites.load(LJMUSIAssets::ALIEN_TWO_A, LJMUSettings::DIR_ANIM + "si_anim2.png");
	this->ResourceSprites.load(LJMUSIAssets::ALIEN_THREE_A, LJMUSettings::DIR_ANIM + "si_anim3.png");
	this->ResourceSprites.load(LJMUSIAssets::BG_ONE, LJMUSettings::DIR_BG + "bg_1.png");
	this->ResourceSprites.load(LJMUSIAssets::BG_TWO, LJMUSettings::DIR_BG + "bg_2.png");
	this->ResourceSprites.load(LJMUSIAssets::BULLET, LJMUSettings::DIR_STATICS + "bullet.png");

	//Create our Colour Palette Map
	this->ResourceColour[LJMUSIColour::RED] = sf::Color(255, 0, 0);
	this->ResourceColour[LJMUSIColour::BLUE] = sf::Color(0, 0, 255);
	this->ResourceColour[LJMUSIColour::GREEN] = sf::Color(0, 255, 0);
	this->ResourceColour[LJMUSIColour::PURPLE] = sf::Color(255, 0, 255);
	this->ResourceColour[LJMUSIColour::YELLOW] = sf::Color(255, 255, 0);
	this->ResourceColour[LJMUSIColour::WHITE] = sf::Color(255, 255, 255);

	//----------SETUP THE MAPS OF ENEMY TYPES------------------------------------------------
	//Create our Dictionary of Indices to Texture Type
	this->MapEnemyTexture[0] = LJMUSIAssets::ALIEN_ONE_A;
	this->MapEnemyTexture[1] = LJMUSIAssets::ALIEN_TWO_A;
	this->MapEnemyTexture[2] = LJMUSIAssets::ALIEN_THREE_A;

	//Create our Dictionary of Indices to Colour Type
	this->MapEnemyColour[0] = LJMUSIColour::RED;
	this->MapEnemyColour[1] = LJMUSIColour::BLUE;
	this->MapEnemyColour[2] = LJMUSIColour::PURPLE;
	this->MapEnemyColour[3] = LJMUSIColour::GREEN;
	this->MapEnemyColour[4] = LJMUSIColour::YELLOW;

	//----------CREATE THE GAME LEVEL---------------------------------------------------------

	//Populate our Level Background
	this->WorldLevel.push_back(sf::Sprite(this->ResourceSprites.get(LJMUSIAssets::BG_ONE)));
	this->WorldLevel.push_back(sf::Sprite(this->ResourceSprites.get(LJMUSIAssets::BG_TWO)));

	//Scale each Background to become Full Screen
	for (auto& tbg : this->WorldLevel)
	{
		sf::makeFullScreen(tbg, this->GameWorldSize);
	}

	//----------CREATE THE HUD----------------------------------------------------------------

	float txgap = (this->GameWorldBounds.width / 4.0f);
	float tsx = -50;
	float tty = 20;
	const int HUD_SCALE = 48;

	this->WorldHUD[LJMUSIHUD::LIVES] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::LIVES].setString("Lives : ");
	this->WorldHUD[LJMUSIHUD::LIVES].setPosition(tsx + txgap, tty);
	this->WorldHUD[LJMUSIHUD::LIVES].setFillColor(this->ResourceColour[LJMUSIColour::GREEN]);

	this->WorldHUD[LJMUSIHUD::SCORE] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::SCORE].setString("Score : ");
	this->WorldHUD[LJMUSIHUD::SCORE].setPosition(tsx + txgap * 2, tty);
	this->WorldHUD[LJMUSIHUD::SCORE].setFillColor(this->ResourceColour[LJMUSIColour::YELLOW]);

	this->WorldHUD[LJMUSIHUD::TIME] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::TIME].setString("Time : ");
	this->WorldHUD[LJMUSIHUD::TIME].setPosition(tsx + txgap * 3, tty);
	this->WorldHUD[LJMUSIHUD::TIME].setFillColor(this->ResourceColour[LJMUSIColour::YELLOW]);

	//-----------SETUP OUR GAME CAMERA--------------------------------------------------------
	//Setup our Game Camera
	sf::Vector2f tcamcentre = this->GameWorldSize * 0.5f;
	this->CameraGame.reset(this->GameWorldBounds);
	this->CameraGame.setCenter(tcamcentre);

	//Setup our HUD Camera
	this->CameraHUD.reset(this->GameWorldBounds);
	this->CameraHUD.setCenter(tcamcentre);
}

/////////////////////////////////////////////
// Update the Game State.
/////////////////////////////////////////////
void LJMU::LJMUGameManager::update(sf::Time& ptpf, sf::Time& ptotal)
{
	this->GamePlayTime += ptpf.asSeconds();
	float ttpf = ptpf.asSeconds();

	if (this->GameMode == LJMUGamePlayMode::GAME_START)
	{
		this->WorldHUD[LJMUSIHUD::SCORE].setString("");
		this->WorldHUD[LJMUSIHUD::LIVES].setString("GAME START");
		this->WorldHUD[LJMUSIHUD::TIME].setString("");

		if (this->GamePlayTime >= this->GameStartTime)
		{
			this->GameMode = LJMUGamePlayMode::GAME_PLAYING;
		}
	}
	else if (this->GameMode == LJMUGamePlayMode::GAME_PLAYING)
	{
		float tzoomfactor = 1;
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_LEFT))
			this->CameraGame.move(sf::Vector2f(-200.0f* ttpf, 0));
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_RIGHT))
			this->CameraGame.move(sf::Vector2f(200.0f* ttpf, 0));
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_UP))
			this->CameraGame.move(sf::Vector2f(0, -200.0f* ttpf));
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_DOWN))
			this->CameraGame.move(sf::Vector2f(0, 200.0f* ttpf));
		if (this->CameraControl.isActive(LJMUCameraActions::ROT_CAM_CCW))
			this->CameraGame.rotate(180.0f * ttpf);
		if (this->CameraControl.isActive(LJMUCameraActions::ROT_CAM_CW))
			this->CameraGame.rotate(-180.0f * ttpf);
		if (this->CameraControl.isActive(LJMUCameraActions::ZOOM_CAM_OUT))
			tzoomfactor -= 1.0f * ttpf;
		if (this->CameraControl.isActive(LJMUCameraActions::ZOOM_CAM_IN))
			tzoomfactor += 1.0f * ttpf;
		this->CameraGame.zoom(tzoomfactor);

		int tdisptime = static_cast<int>(std::floor(this->GamePlayTime));
		this->WorldHUD[LJMUSIHUD::SCORE].setString("Score : " + std::to_string(this->GameScore));
		this->WorldHUD[LJMUSIHUD::LIVES].setString("Lives : " + std::to_string(this->GameLives));
		this->WorldHUD[LJMUSIHUD::TIME].setString("Time:  " + std::to_string(tdisptime));
	}
	else if (this->GameMode == LJMUGamePlayMode::GAME_WON)
	{
		this->WorldHUD[LJMUSIHUD::SCORE].setString("");
		this->WorldHUD[LJMUSIHUD::LIVES].setString("PLAYER WINS");
		this->WorldHUD[LJMUSIHUD::TIME].setString("");

		if (this->GamePlayTime > this->GameEndTimeStart + this->GameEndTimeDelay)
		{
			this->GameMode = LJMUGamePlayMode::GAME_END;
		}
	}
	else if (this->GameMode == LJMUGamePlayMode::GAME_LOST)
	{
		this->WorldHUD[LJMUSIHUD::SCORE].setString("");
		this->WorldHUD[LJMUSIHUD::LIVES].setString("GAME OVER");
		this->WorldHUD[LJMUSIHUD::TIME].setString("");

		if (this->GamePlayTime > this->GameEndTimeStart + this->GameEndTimeDelay)
		{
			this->GameMode = LJMUGamePlayMode::GAME_END;
		}
	}
	else if (this->GameMode == LJMUGamePlayMode::GAME_END)
	{
		this->WorldHUD[LJMUSIHUD::SCORE].setString("");
		this->WorldHUD[LJMUSIHUD::LIVES].setString("");
		this->WorldHUD[LJMUSIHUD::TIME].setString("");
		//TODO: Add Game Ending Logic
	}
}

/////////////////////////////////////////////
// Destroy the Game State.
/////////////////////////////////////////////
void LJMU::LJMUGameManager::destroy()
{
	//Cleanup our STL Containers
	this->MapEnemyColour.clear();
	this->MapEnemyTexture.clear();
	this->WorldHUD.clear();
	this->WorldLevel.clear();
	this->ResourceColour.clear();
	this->ResourceFonts.clear();
	this->ResourceSprites.clear();
}