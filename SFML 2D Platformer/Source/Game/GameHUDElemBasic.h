#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <IGameObjectBase.h>

namespace LJMU
{
	////////////////////////////
	// Class to represent some 
	// In Game Text.
	////////////////////////////
	class GameHUDElemBasic : public IGameObjectBase
	{

	public:
		//--------CONSTRUCTORS/DESTRUCTORS---------------------------------
		explicit GameHUDElemBasic() :IGameObjectBase(),_hud(){ }
		virtual ~GameHUDElemBasic() {};

		//----------GETTERS/SETTERS----------------------------------------
		inline sf::Text& getText() { return this->_hud; };
		inline const sf::Text& getTextRO() { return this->_hud; };
		inline sf::Text  getTextCopy() { return this->_hud; }
		inline void setText(sf::Text psprite) { this->_hud = psprite; }
		inline std::string getString() {return this->_data;	}
		void setString(std::string pdata) { this->_data = pdata; }

		//----------INTERFACE IMPLEMENTATION-------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal)override;
		virtual void render(sf::RenderWindow& pwndw) override;


	protected:
		//----------MEMBER DATA--------------------------------------------
		sf::Text    _hud;
		std::string _data;
	};

}