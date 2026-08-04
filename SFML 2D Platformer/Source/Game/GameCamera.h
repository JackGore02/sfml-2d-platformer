#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <array>

namespace LJMU
{
//Legacy C++ Technique
#define CAM_UP 0
#define CAM_DOWN 1
#define CAM_LEFT 2
#define CAM_RIGHT 3
#define CAM_ROT_CW 4
#define CAM_ROT_CCW 5
#define CAM_ZOOM_IN 6
#define CAM_ZOOM_OUT 7
#define CAM_RESET 8
#define CAM_COUNT 9

	/////////////////////////////////////////////
	// Custom Class to Represent a Camera. 
	/////////////////////////////////////////////
	class GameCamera
	{
		//-----------CONSTANTS/TYPE DEFS-----------------------------------
		using keys = sf::Keyboard::Key;
		static constexpr float DEF_MOVE_SPEED = 2000.0f;
		static constexpr float DEF_ROT_RATE = 360.0f;
		static constexpr float DEF_ZOOM_RATE = 1.0f;

	public:
		//----------CONSTRUCTOR/DESTRUCTOR---------------------------------
		explicit GameCamera();
		virtual ~GameCamera() {};

	public:
		//----------GETTERS/SETTERS----------------------------------------
		inline sf::View& getView() { return this->_view; };
		inline const sf::View& getViewRO() { return this->_view; };
		inline void setView(sf::View pview) 
		{ 
			this->_view = pview; 
			this->_origin = pview.getCenter();
			this->_size = pview.getSize();
		}

		inline std::string getName() { return this->_name; }
		inline void setName(std::string pname) { this->_name = pname; }

		//----------PUBLIC FUNCTIONS---------------------------------------
		void handleInput(float ptpf, float ptotal);
		void makeCurrent(sf::RenderWindow& pwndw);
		void setMoveControls(keys pup,keys pleft, keys pright,keys pdown);
		void setZoomRotControls(keys protcw,keys protccw, keys pzi, keys pzo);
		void setResetControls(keys preset);

	public: 
		bool Updatable;
		bool Controllable;

	protected:
		//----------MEMBER DATA---------------------------------------------
		std::string					_name;
		sf::View					_view;
		float						_lin_vel;
		float						_rot_vel;
		float						_zoom_rate;
		sf::Vector2f				_origin;
		sf::Vector2f				_size; 
		std::array<keys,CAM_COUNT>	_keys; 
	};

}
