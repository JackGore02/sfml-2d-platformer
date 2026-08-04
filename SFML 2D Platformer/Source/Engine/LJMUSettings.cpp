#include <LJMUSettings.h>

namespace sf
{
	
	//--------------CONSTANT DEFINITION--------------------------------------------------------------------------
	const std::string  LJMUSettings::DIR_ROOT = "Assets/";									//Specify the base directory for Assets
	const sf::Color    LJMUSettings::APP_CLEAR_COLOUR = sf::Color(0, 0, 0, 255);			//Set the Default Clear Colour
	const sf::Color    LJMUSettings::APP_DEBUG_COLOUR = sf::Color(255, 255, 255, 255);		//Set the Default Debug Output Colour
	const sf::Time	   LJMUSettings::APP_TARGET_TPF = sf::seconds(LJMUSettings::APP_DELTA);	//Set the Target Frame Delta
	const std::string  LJMUSettings::DIR_AUDIO = DIR_ROOT + "Audio/";						//Specify the Audio asset location
	const std::string  LJMUSettings::DIR_ANIM = DIR_ROOT + "Animations/";					//Specify the animation asset location
	const std::string  LJMUSettings::DIR_BG = DIR_ROOT + "Backgrounds/";					//Specify the background image location
	const std::string  LJMUSettings::DIR_DATAFILES = DIR_ROOT + "Data/";					//Specify the Data File asset location 
	const std::string  LJMUSettings::DIR_FONTS = DIR_ROOT + "Fonts/";						//Specify the Font File asset location
	const std::string  LJMUSettings::DIR_STATICS = DIR_ROOT + "Statics/";					//Specify the  sprite location
	const std::string  LJMUSettings::DIR_TILESETS = DIR_ROOT + "TileSets/";					//Specify the Tileset asset location
	const std::string  LJMUSettings::APP_NAME = "SFML 2D Platformer";							//Set the Default Application Name
}