#include "MenuControls.h"
#include <algorithm>

namespace LJMU
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					MENU CONTROLS IMPLEMENTATION														//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//----------------CONSTRUCTORS/DESTRUCTORS----------------------------------------------------------------

	/////////////////////////////////////////////
	// Constructor for our Player Controls
	// Sets up the Default Control Scheme.
	/////////////////////////////////////////////
	MenuControls::MenuControls()
	{
		//Populate our Mappings of Key Controls
		this->_actions.insert(std::make_pair(keys::Up, MenuActions::MOVE_UP));
		this->_actions.insert(std::make_pair(keys::Down, MenuActions::MOVE_DOWN));
		this->_actions.insert(std::make_pair(keys::Left, MenuActions::DECREMENT));
		this->_actions.insert(std::make_pair(keys::Right, MenuActions::INCREMENT));
		this->_actions.insert(std::make_pair(keys::Space, MenuActions::SELECT));
		this->_actions.insert(std::make_pair(keys::Escape, MenuActions::BACK));
	}

	/////////////////////////////////////////////
	// Destructor for our Player Controls. 
	/////////////////////////////////////////////
	MenuControls::~MenuControls()
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
	void MenuControls::setActionMapping(MenuActions paction, keys pkey)
	{
		this->_actions[pkey] = paction;
		this->setFlag(paction, false);
	}

	/////////////////////////////////////////////
	// Remove the Default Mappings.
	/////////////////////////////////////////////
	void MenuControls::clearDefaults()
	{
		this->_actions.erase(this->_actions.begin(), this->_actions.end());
	}

	/////////////////////////////////////////////
	// Get the Action for a Given Key.  If the 
	// Key cannot be found then return the 
	// Unknown Action Enumeration. 
	/////////////////////////////////////////////
	MenuControls::MenuActions MenuControls::getAction(keys pkey)
	{
		if (this->_actions.find(pkey) != this->_actions.end())
			return this->_actions[pkey];
		else
			return MenuActions::ACTION_UNKNOWN;
	}

	/////////////////////////////////////////////
	// Get the First Keyboard Key mapping for an 
	// Action.  If it cannot be found then return
	// the unknown key. 
	/////////////////////////////////////////////
	MenuControls::keys MenuControls::getKey(MenuActions paction)
	{
		auto tpos = std::find_if(std::begin(this->_actions), std::end(this->_actions),
			[&](const std::pair<keys, MenuActions> &pair)
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
	void MenuControls::setFlag(MenuActions paction, bool pflag)
	{
		this->_flags[paction] = pflag;
	}

	/////////////////////////////////////////////
	// Get the Flag State for a Given Action. 
	/////////////////////////////////////////////
	bool MenuControls::isActive(MenuActions paction)
	{
		return this->_flags[paction];
	}

	/////////////////////////////////////////////
	// Set the Flag State for a Given Key.  If
	// the Key is not mapped to an action then 
	// nothing will happen. 
	/////////////////////////////////////////////
	void MenuControls::setFlag(keys pkey, bool pflag)
	{
		if (this->_actions.find(pkey) != this->_actions.end())
			this->_flags[this->_actions[pkey]] = pflag;
	}

	/////////////////////////////////////////////
	// Get the Flag State for a Given Key. If
	// the key is not mapped to an action then
	// the function will return false. 
	/////////////////////////////////////////////
	bool MenuControls::isActive(keys pkey)
	{
		if (this->_actions.find(pkey) != this->_actions.end())
			return this->_flags[this->_actions[pkey]];
		return false;
	}
}