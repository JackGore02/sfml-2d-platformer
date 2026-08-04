#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace LJMU
{
	/////////////////////////////////////////////
	// Custom Class to Represent a Camera. 
	/////////////////////////////////////////////
	class GameCameraHUD
	{
	public:
		//----------CONSTRUCTOR/DESTRUCTOR---------------------------------
		explicit GameCameraHUD() :_name(), _view() {};
		virtual ~GameCameraHUD() {};

	public:
		//----------GETTERS/SETTERS----------------------------------------
		inline sf::View& getView() { return this->_view; };
		inline const sf::View& getViewRO() { return this->_view; };
		inline void setView(sf::View pview) { this->_view = pview; }

		inline std::string getName() { return this->_name; }
		inline void setName(std::string pname) { this->_name = pname; }

		//----------PUBLIC FUNCTIONS---------------------------------------
		void handleInput(float ptpf, float ptotal);
		void makeCurrent(sf::RenderWindow& pwndw);

	protected:
		//----------MEMBER DATA---------------------------------------------
		std::string _name;
		sf::View    _view;
	};

}