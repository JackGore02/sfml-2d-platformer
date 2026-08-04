#ifndef _LJMU_SETTINGS_H_
#define _LJMU_SETTINGS_H_

//Include SFML Framework Classes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//Include STL String Class
#include <string>

namespace sf
{
	///////////////////////////////////////////
	// Class to represent Settings
	// for our Application - makes
	// use of Static Constants and 
	// Inline Settings - can be
	// Customised via the Instance
	// Data.
	// (Appropriate Setters/Friend Access needed)  
	// 
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    26/05/2017
	//////////////////////////////////////////
	class LJMUSettings
	{
	public:

		//---------CONSTANTS AS ENUMS/SELECTORS------------------------------------
		static constexpr char           VIDEO_MODE_USER = 'U';		//Constant for User Defined Video Mode.
		static constexpr char           VIDEO_MODE_BEST = 'B';		//Constant for Highest Resolution Video Mode.
		static constexpr char			VIDEO_MODE_DESKTOP = 'D';	//Constant for current Desktop Video Mode.

		//--------GAME CONSTANTS------------------------------------------------------
		static constexpr bool			  APP_FIXEDSTEP  = false;								//Set whether to use Fixed or Variable Time Step
		static constexpr unsigned int	  APP_FRAMERATE  = 60;									//Set the Desired Frame Rate if Fixed Step
		static constexpr float    		  APP_DELTA      = 1.0f /(float)APP_FRAMERATE;	//Set the Application Delta

		//--------WINDOW SETTING CONSTANTS--------------------------------------------
		static constexpr char			  APP_VIDEO_MODE	= LJMUSettings::VIDEO_MODE_USER;	//Set the Video Mode 'U', 'B', 'D'
		static constexpr unsigned int	  APP_CUST_WIDTH	= 1600U;							//Set the Default Screen Width
		static constexpr unsigned int	  APP_CUST_HEIGHT	= 900U;								//Set the Default Screen Height
		static constexpr unsigned int	  APP_CUST_CDEPTH	= 32U;								//Set the Default Colour Depth
		static constexpr bool			  APP_FS_MODE		= false;							//Set FullScreen Mode (True if FS, False otherwise)
		static constexpr bool			  APP_VSYNC			= false;							//Constant to represent the default VSync Status.
																										
		//--------INPUT SETTING CONSTANTS---------------------------------------------
		static constexpr bool			  APP_MOUSE_VISIBLE = false;							//Set whether the mouse is visible.
		static constexpr bool			  APP_MOUSE_GRAB    = true;								//Set whether the mouse is app locked. 
		static constexpr bool			  APP_KEY_REPEAT    = false;							//Set whether key repeating is enabled.

		//--------OPEN GL CONSTANTS----------------------------------------------------
		static constexpr unsigned int    OGL_DEPTH_BUFF		= 24U;								//Set the OpenGL Depth Buffer
		static constexpr unsigned int    OGL_STENCIL_BUFF	= 8U;								//Set the OpenGL Stencil Buffer
		static constexpr unsigned int    OGL_VERSION_MAJOR	= 4U;								//Set the OpenGL Major Version
		static constexpr unsigned int    OGL_VERSION_MINOR	= 4U;								//Set the OpenGL Minor Version
		static constexpr unsigned int    OGL_MSAA_MODE		= 8U;								//Set the OpenGL Anti-Aliasing Mode

		//--------STANDARD CONSTANTS (cannot be constexpr)-----------------------------																						//--------COLOUR CONSTANTS-----------------------------------------------------
		static const sf::Color      APP_CLEAR_COLOUR;		//Set the Default Clear Colour
		static const sf::Color      APP_DEBUG_COLOUR;		//Set the Default Debug Output Colour
		static const sf::Time		APP_TARGET_TPF;			//Set the Target Frame Delta
		static const std::string    DIR_ROOT;				//Specify the base directory for Assets
		static const std::string    DIR_AUDIO;				//Specify the Audio asset location
		static const std::string    DIR_ANIM;				//Specify the animation asset location
		static const std::string    DIR_BG;					//Specify the background image location
		static const std::string    DIR_DATAFILES;			//Specify the Data File asset location 
		static const std::string    DIR_FONTS;				//Specify the Font File asset location
		static const std::string    DIR_STATICS;			//Specify the static sprite location
		static const std::string    DIR_TILESETS;			//Specify the Tileset asset location
		static const std::string	APP_NAME;				//Set the Default Application Name

		//----------STATIC FUNCTIONS--------------------------------------------------

		////////////////////////////////////////
		// Get the Rendering Context for SFML (OpenGL)
		// Based on the Constant Values of this Class. 
		////////////////////////////////////////
		static inline sf::ContextSettings getContext()
		{
			sf::ContextSettings toglsettings(OGL_DEPTH_BUFF,
				OGL_STENCIL_BUFF,
				OGL_MSAA_MODE,
				OGL_VERSION_MAJOR,
				OGL_VERSION_MINOR);
			return toglsettings;
		}

	public:
		//--------CONSTRUCTORS/DESTRUCTORS-----------------------------------------

		/////////////////////////////////////////
		// Default Constructor for the Settings Class
		/////////////////////////////////////////
		LJMUSettings()
		{
			this->_debug_clr = APP_DEBUG_COLOUR;
			this->_wnd_clr = APP_CLEAR_COLOUR;
			this->_app_style = APP_FS_MODE ? sf::Style::Fullscreen : sf::Style::Close;
			this->_app_name = APP_NAME;
			this->_key_repeat = APP_KEY_REPEAT;
			this->_mouse_grabbed = APP_MOUSE_GRAB;
			this->_mouse_visible = APP_MOUSE_VISIBLE;
			this->_app_vsync = APP_VSYNC;

			if (APP_VIDEO_MODE == 'U')
				this->_app_vmode = sf::VideoMode(APP_CUST_WIDTH, APP_CUST_HEIGHT, APP_CUST_CDEPTH);
			else if (APP_VIDEO_MODE == 'B')
				this->_app_vmode = sf::VideoMode::getFullscreenModes()[0];
			else
				this->_app_vmode = sf::VideoMode::getDesktopMode();
		}

		///////////////////////////////////////////
		// Default Destructor for the Class
		///////////////////////////////////////////
		~LJMUSettings() {};

	public:
		//--------ACCESSORS/MUTATORS-----------------------------------------------
		inline sf::Color	   getDebugColour() { return this->_debug_clr; }	//Get the Debug Data Colour
		inline sf::Color	   getClearColour() { return this->_wnd_clr; }	//Get the Windows Clear Colour
		inline std::string	   getAppName() { return this->_app_name; } //Get the Application Name
		inline sf::VideoMode   getVideoMode() { return this->_app_vmode; } //Get the Current Video Mode Object
		inline unsigned int    getAppStyle() { return this->_app_style; } //Get the Application Style Flags
		inline bool isKeyRepeat() { return this->_key_repeat; } //Check whether Key Repeating is enabled
		inline bool isVSync() { return this->_app_vsync; } //Check whether Vertical Sync is enabled
		inline bool isMouseGrabbed() { return this->_mouse_grabbed; } //Check whether the mouse is app locked
		inline bool isMouseVisible() { return this->_mouse_visible; } //Check whether the cursor is visible

	private:
		//--------CLASS MEMBERS----------------------------------------------------
		std::string			_app_name;		//String representing the window title
		sf::VideoMode		_app_vmode;		//SFML Video Mode representing the screen mode
		unsigned int 		_app_style;		//Enum value representing the style of SFML Window (FullScreen etc).
		bool				_app_vsync;		//Flag for whether Vertical Refresh Syncing is enabled
		sf::Color			_debug_clr;		//Colour of our debug text. 
		sf::Color			_wnd_clr;		//Colour of our Clear Window
		bool				_key_repeat;	//Flag for whether Key Repeats are enabled
		bool				_mouse_grabbed; //Flag for whether the Application grabs the Mouse Cursor
		bool				_mouse_visible; //Flag for whether the Application shows the Mouse Cursor
	};
}
#endif
