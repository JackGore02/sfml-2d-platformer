#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <IGameObjectBase.h>

namespace LJMU
{
	/////////////////////////////////////////////
	// Custom Game Object to represent Static 
	// Sprites.  
	/////////////////////////////////////////////
	class GameObjectBasic : public IGameObjectBase
	{
	public:
		//----------CONSTRUCTOR/DESTRUCTOR---------------------------------
		explicit GameObjectBasic()
			: IGameObjectBase(), _sprite(), _isMovable(false), _origpos(0.f, 0.f),
			_amplitude(0.f), _isTrap(false), _isGoal(false) {};
		virtual ~GameObjectBasic() {};

	public:
		//----------GETTERS/SETTERS----------------------------------------
		inline sf::Sprite& getSprite() { return this->_sprite; };
		inline const sf::Sprite& getSpriteRO() { return this->_sprite; };
		inline sf::Sprite  getSpriteCopy() { return this->_sprite; }
		inline void setSprite(sf::Sprite psprite) { this->_sprite = psprite; }

		bool getIsMovable() { return this->_isMovable; }
		void setIsMovable(bool pmovable) { this->_isMovable = pmovable; }

		sf::Vector2f getOrigPos() { return this->_origpos; }
		void setOrigPos(sf::Vector2f ppos) { this->_origpos = ppos; this->_sprite.setPosition(ppos); }

		float getAmplitude() { return this->_amplitude; }
		void setAmplitude(float pamp) { this->_amplitude = pamp; }

		bool getIsTrap() { return this->_isTrap; }
		void setIsTrap(bool ptrap) { this->_isTrap = ptrap; }

		bool getIsGoal() { return this->_isGoal; }
		void setIsGoal(bool pgoal) { this->_isGoal = pgoal; }

		//----------INTERFACE IMPLEMENTATION-------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal)override;
		virtual void render(sf::RenderWindow& pwndw) override;

	protected:
		//----------MEMBER DATA---------------------------------------------
		sf::Sprite  _sprite;
		bool _isMovable;
		sf::Vector2f _origpos;
		float _amplitude;
		bool _isTrap;
		bool _isGoal;
	};

}
