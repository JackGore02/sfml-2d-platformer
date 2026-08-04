#include "LJMUInterfaces.h"
#include <math.h>


sf::ILJMUScreenBase::ILJMUScreenBase():
_manager(),
_exiting(false),
_popup(false),
_secondary(false),
_trans_mode(TransMode::TransOn),
_trans_pos(1.0f),
_trans_off_time(sf::seconds(0.0f)),
_trans_on_time(sf::seconds(0.0f))
{

}

sf::ILJMUScreenBase::~ILJMUScreenBase()
{

}

void sf::ILJMUScreenBase::masterUpdate(sf::Time & ptpf, sf::Time & ptotal, bool potherfocused,bool poverlaid)
{
	this->_secondary = potherfocused;

	if (this->_exiting)
	{
		this->_trans_mode = TransMode::TransOff;
		if (!isTransitioning(this->_trans_off_time,ptpf,1))
		{
			this->_trans_off_time = sf::seconds(0);
			this->exitScreen();
		}
	}
	else if (poverlaid)
	{
		if (isTransitioning(this->_trans_off_time,ptpf,1))
			this->_trans_mode = TransMode::TransOff;
		else
			this->_trans_mode = TransMode::Hidden;
	}
	else
	{
		if (isTransitioning(this->_trans_on_time, ptpf,-1))
			this->_trans_mode = TransMode::TransOn;
		else
			this->_trans_mode = TransMode::Active;
	}

	this->bgUpdate(ptpf, ptotal, poverlaid);
}

bool sf::ILJMUScreenBase::exitScreen()
{
	if (this->_trans_off_time == sf::seconds(0))
		return this->getLJMUSFMLManager().lock()->removeScreenWithID(this->_id);
	else
		this->_exiting = true;
	return true;
}

bool sf::ILJMUScreenBase::isTransitioning(sf::Time & ptranstime,sf::Time& ptpf, int pdir)
{
	float ttransdelta;
	if (ptranstime == sf::seconds(0.0f))
		ttransdelta = 1;
	else
	{
		const float ttpf = ptpf.asSeconds();
		const float ttranstime = ptranstime.asSeconds();
		ttransdelta = ttpf / ttranstime;
	}
	
	this->_trans_pos += ttransdelta * pdir;

	if ((pdir < 0 && _trans_pos <= 0) || (pdir > 0 && _trans_pos >= 1))
	{
		this->_trans_pos = std::min(1.0f,std::max(_trans_pos,0.0f)); 
		return false;
	}
	return true;
}

void sf::ILJMUScreenBase::setLJMUSFMLManager(std::shared_ptr<sf::ILJMUSFMLManager> pmanager)
{
	this->_manager = pmanager;
	this->_exiting = false;
}

std::weak_ptr<sf::ILJMUSFMLManager> sf::ILJMUScreenBase::getLJMUSFMLManager()
{
	return this->_manager;
}

sf::TransMode sf::ILJMUScreenBase::getScreenState()
{
	return this->_trans_mode;
}

bool sf::ILJMUScreenBase::isActive()
{
	return !this->_secondary && (this->_trans_mode == TransMode::TransOn || this->_trans_mode == TransMode::Active);
}

bool sf::ILJMUScreenBase::isExiting()
{
	return this->_exiting;
}

bool sf::ILJMUScreenBase::isPopupScreen()
{
	return this->_popup;
}

float sf::ILJMUScreenBase::getTransPos()
{
	return this->_trans_pos;
}

float sf::ILJMUScreenBase::getTransAlpha()
{
	return (1.0f - this->_trans_pos);
}
