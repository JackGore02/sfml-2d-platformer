#include "GameControls.h"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//					PLAYER CONTROLS IMPLEMENTATION														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------CONSTRUCTORS/DESTRUCTORS----------------------------------------------------------------

/////////////////////////////////////////////
// Constructor for our Player Controls
// Sets up the Default Control Scheme.
/////////////////////////////////////////////
LJMU::LJMUPlayerControls::LJMUPlayerControls(bool pprimary)
{
	if (pprimary)
	{
		//Populate our Mappings of Key Controls
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::Left, LJMUPlayerActions::MOVE_LEFT));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::Down, LJMUPlayerActions::MOVE_DOWN));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::Right, LJMUPlayerActions::MOVE_RIGHT));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::Up, LJMUPlayerActions::MOVE_UP));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::M, LJMUPlayerActions::ANIM_DEC_FRAME));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::N, LJMUPlayerActions::ANIM_INC_FRAME));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::Space, LJMUPlayerActions::JUMP));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::LShift, LJMUPlayerActions::SPRINT));
	}
	else
	{
		this->_actions.insert(std::make_pair(sf::Keyboard::A, LJMUPlayerActions::MOVE_LEFT));
		this->_actions.insert(std::make_pair(sf::Keyboard::D, LJMUPlayerActions::MOVE_RIGHT));
		this->_actions.insert(std::make_pair(sf::Keyboard::W, LJMUPlayerActions::MOVE_UP));
		this->_actions.insert(std::make_pair(sf::Keyboard::S, LJMUPlayerActions::MOVE_DOWN));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::Z, LJMUPlayerActions::ANIM_DEC_FRAME));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::X, LJMUPlayerActions::ANIM_INC_FRAME));
		this->_actions.insert(std::make_pair(sf::Keyboard::Return, LJMUPlayerActions::JUMP));
		this->_actions.insert(std::make_pair(sf::Keyboard::Key::LShift, LJMUPlayerActions::SPRINT));
	}

	//Populate our Mappings of Flags for Actions
	this->_flags.insert(std::make_pair(LJMUPlayerActions::MOVE_LEFT, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::MOVE_DOWN, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::MOVE_RIGHT, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::MOVE_UP, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::ANIM_DEC_FRAME, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::ANIM_INC_FRAME, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::JUMP, false));
	this->_flags.insert(std::make_pair(LJMUPlayerActions::SPRINT, false));
}

/////////////////////////////////////////////
// Destructor for our Player Controls. 
/////////////////////////////////////////////
LJMU::LJMUPlayerControls::~LJMUPlayerControls()
{
	//Erase the Structures entirely
	this->_actions.erase(this->_actions.begin(), this->_actions.end());
	this->_flags.erase(this->_flags.begin(), this->_flags.end());
}

//----------------PUBLIC METHODS---------------------------------------------------------------------------

/////////////////////////////////////////////
// Create a Mapping between an action and a
// Keyboard Key. 
/////////////////////////////////////////////
void LJMU::LJMUPlayerControls::setActionMapping(LJMUPlayerActions paction, sf::Keyboard::Key pkey)
{
	this->_actions[pkey] = paction;
	this->setFlag(paction, false);
}

/////////////////////////////////////////////
// Remove the Default Mappings.
/////////////////////////////////////////////
void LJMU::LJMUPlayerControls::clearDefaults()
{
	this->_actions.erase(this->_actions.begin(), this->_actions.end());
}

/////////////////////////////////////////////
// Get the Action for a Given Key.  If the 
// Key cannot be found then return the 
// Unknown Action Enumeration. 
/////////////////////////////////////////////
LJMU::LJMUPlayerActions LJMU::LJMUPlayerControls::getAction(sf::Keyboard::Key pkey)
{
	if (this->_actions.find(pkey) != this->_actions.end())
		return this->_actions[pkey];
	else
		return LJMUPlayerActions::ACTION_UNKNOWN;
}

/////////////////////////////////////////////
// Get the First Keyboard Key mapping for an 
// Action.  If it cannot be found then return
// the unknown key. 
/////////////////////////////////////////////
sf::Keyboard::Key LJMU::LJMUPlayerControls::getKey(LJMUPlayerActions paction)
{
	auto tpos = std::find_if(std::begin(this->_actions), std::end(this->_actions),
		[&](const std::pair<sf::Keyboard::Key, LJMUPlayerActions> &pair)
	{
		return paction == pair.second;
	});
	if (tpos != this->_actions.end())
		return tpos->first;
	else
		return sf::Keyboard::Key::Unknown;
}

/////////////////////////////////////////////
// Set the Flag State for a Given Action. 
/////////////////////////////////////////////
void LJMU::LJMUPlayerControls::setFlag(LJMUPlayerActions paction, bool pflag)
{
	this->_flags[paction] = pflag;
}

/////////////////////////////////////////////
// Get the Flag State for a Given Action. 
/////////////////////////////////////////////
bool LJMU::LJMUPlayerControls::isActive(LJMUPlayerActions paction)
{
	return this->_flags[paction];
}

/////////////////////////////////////////////
// Set the Flag State for a Given Key.  If
// the Key is not mapped to an action then 
// nothing will happen. 
/////////////////////////////////////////////
void LJMU::LJMUPlayerControls::setFlag(sf::Keyboard::Key pkey, bool pflag)
{
	if (this->_actions.find(pkey) != this->_actions.end())
		this->_flags[this->_actions[pkey]] = pflag;
}

/////////////////////////////////////////////
// Get the Flag State for a Given Key. If
// the key is not mapped to an action then
// the function will return false. 
/////////////////////////////////////////////
bool LJMU::LJMUPlayerControls::isActive(sf::Keyboard::Key pkey)
{
	if (this->_actions.find(pkey) != this->_actions.end())
		return this->_flags[this->_actions[pkey]];
	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//					CAMERA CONTROLS IMPLEMENTATION														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------CONSTRUCTORS/DESTRUCTORS----------------------------------------------------------------

/////////////////////////////////////////////
// Constructor for the Camera controls, this
// creates the default control scheme for the
// camera. 
/////////////////////////////////////////////
LJMU::LJMUCamControls::LJMUCamControls()
{
	//Populate our Mappings of Key Controls
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::A, LJMUCameraActions::MOVE_CAM_LEFT));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::S, LJMUCameraActions::MOVE_CAM_DOWN));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::D, LJMUCameraActions::MOVE_CAM_RIGHT));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::W, LJMUCameraActions::MOVE_CAM_UP));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::R, LJMUCameraActions::ROT_CAM_CCW));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::T, LJMUCameraActions::ROT_CAM_CW));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::Q, LJMUCameraActions::ZOOM_CAM_IN));
	this->_actions.insert(std::make_pair(sf::Keyboard::Key::E, LJMUCameraActions::ZOOM_CAM_OUT));

	//Populate our Mappings of Flags for Actions
	this->_flags.insert(std::make_pair(LJMUCameraActions::MOVE_CAM_LEFT, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::MOVE_CAM_DOWN, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::MOVE_CAM_RIGHT, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::MOVE_CAM_UP, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::ROT_CAM_CCW, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::ROT_CAM_CW, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::ZOOM_CAM_IN, false));
	this->_flags.insert(std::make_pair(LJMUCameraActions::ZOOM_CAM_OUT, false));
}

/////////////////////////////////////////////
// Destructor for the Camera Controls. 
/////////////////////////////////////////////
LJMU::LJMUCamControls::~LJMUCamControls()
{
	this->_actions.erase(this->_actions.begin(),this->_actions.end());
	this->_flags.erase(this->_flags.begin(), this->_flags.end());
}

//----------------PUBLIC METHODS---------------------------------------------------------------------------

/////////////////////////////////////////////
// Add a mapping between a given action and
// a keyboard key. 
/////////////////////////////////////////////
void LJMU::LJMUCamControls::setActionMapping(LJMUCameraActions paction, sf::Keyboard::Key pkey)
{
	this->_actions[pkey] = paction;
	this->setFlag(paction, false);
}

/////////////////////////////////////////////
// Remove the Default Mappings.
/////////////////////////////////////////////
void LJMU::LJMUCamControls::clearDefaults()
{
	this->_actions.erase(this->_actions.begin(), this->_actions.end());
}

/////////////////////////////////////////////
// Get the Action that is mapped to a Given
// Key  If no key can be found then the 
// Unknown Action is returned. 
/////////////////////////////////////////////
LJMU::LJMUCameraActions LJMU::LJMUCamControls::getAction(sf::Keyboard::Key pkey)
{
	if (this->_actions.find(pkey) != this->_actions.end())
		return this->_actions[pkey];
	else
		return LJMUCameraActions::ACTION_UNKNOWN;
}

/////////////////////////////////////////////
// Get the First Keyboard key found that is mapped
// to a  given action.  If no key can be found
// then the unknown key is returned. 
/////////////////////////////////////////////
sf::Keyboard::Key LJMU::LJMUCamControls::getKey(LJMUCameraActions paction)
{
	auto tpos = std::find_if(std::begin(this->_actions), std::end(this->_actions), 
	[&](const std::pair<sf::Keyboard::Key,LJMUCameraActions> &pair)
	{
		return paction == pair.second;
	});
	if (tpos != this->_actions.end())
		return tpos->first;
	else
		return sf::Keyboard::Key::Unknown;
}

/////////////////////////////////////////////
// Set the Flag State of the given action. 
/////////////////////////////////////////////
void LJMU::LJMUCamControls::setFlag(LJMUCameraActions paction, bool pflag)
{
	this->_flags[paction] = pflag;
}

/////////////////////////////////////////////
// Return the Flag state of the given action.
/////////////////////////////////////////////
bool LJMU::LJMUCamControls::isActive(LJMUCameraActions paction)
{
	return this->_flags[paction];
}

/////////////////////////////////////////////
// Set the Flag state for the action that is 
// mapped to the given key. If there is no
// key found then this function does nothing. 
/////////////////////////////////////////////
void LJMU::LJMUCamControls::setFlag(sf::Keyboard::Key pkey, bool pflag)
{
	if(this->_actions.find(pkey) != this->_actions.end())
		this->_flags[this->_actions[pkey]] = pflag;
}

/////////////////////////////////////////////
// Return the Flag State of the action mapped to 
// the given key.  If there is no action mapped
// to the given key then this function will
// return false. 
/////////////////////////////////////////////
bool LJMU::LJMUCamControls::isActive(sf::Keyboard::Key pkey)
{
	if (this->_actions.find(pkey) != this->_actions.end())
		return this->_flags[this->_actions[pkey]];
	return false;
}
