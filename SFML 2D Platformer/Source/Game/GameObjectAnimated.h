#pragma once


#include <LJMUAnimSprite.h>
#include <IGameObjectBase.h>

namespace LJMU
{
	/////////////////////////////////////////////
	// Custom Game Object Class to hold
	// Animated Sprite Instances.  
	/////////////////////////////////////////////
	class GameObjectAnimated : public IGameObjectBase
	{
	public:
		//----------CONSTRUCTOR/DESTRUCTOR---------------------------------
		explicit GameObjectAnimated() :IGameObjectBase(),_anim(){};
		virtual ~GameObjectAnimated() {};

	public:
		//----------GETTERS/SETTERS----------------------------------------
		inline sf::LJMUAnimSprite& getAnim() { return this->_anim; };
		inline const sf::LJMUAnimSprite& getAnimRO() { return this->_anim; };
		inline sf::LJMUAnimSprite  getAnimCopy() { return this->_anim; }

		inline void setSprite(sf::LJMUAnimSprite panim) { this->_anim = panim; }

		//----------INTERFACE IMPLEMENTATION-------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void render(sf::RenderWindow& pwndw) override;

	protected:
		//----------MEMBER DATA---------------------------------------------
		sf::LJMUAnimSprite  _anim;
	};

}