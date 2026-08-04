#include "GameCameraHUD.h"
#include <SFML/Window/Keyboard.hpp>


///////////////////////////
// Handle Input Controls.  
///////////////////////////
void LJMU::GameCameraHUD::handleInput(float ptpf, float ptotal)
{
	float tzoomfactor = 1.0f;
	const float tvel = 200.0f;
	const float trot = 180.0f;

	using kb = sf::Keyboard;
	using keys = sf::Keyboard::Key;
	if (kb::isKeyPressed(keys::Numpad4))
		this->_view.move(sf::Vector2f(-tvel * ptpf, 0));
	if (kb::isKeyPressed(keys::Numpad6))
		this->_view.move(sf::Vector2f(tvel* ptpf, 0));
	if (kb::isKeyPressed(keys::Numpad8))
		this->_view.move(sf::Vector2f(0, -tvel * ptpf));
	if (kb::isKeyPressed(keys::Numpad2))
		this->_view.move(sf::Vector2f(0, tvel* ptpf));
	if (kb::isKeyPressed(keys::Add))
		this->_view.rotate(trot * ptpf);
	if (kb::isKeyPressed(keys::Subtract))
		this->_view.rotate(-trot * ptpf);
	if (kb::isKeyPressed(keys::Multiply))
		tzoomfactor -= 1.0f * ptpf;
	if (kb::isKeyPressed(keys::Divide))
		tzoomfactor += 1.0f * ptpf;
	this->_view.zoom(tzoomfactor);
}

//////////////////////////
// Make this instance 
// the current camera.
//////////////////////////
void LJMU::GameCameraHUD::makeCurrent(sf::RenderWindow & pwndw)
{
	//Set this Camera as the Current View
	pwndw.setView(this->_view);
}
