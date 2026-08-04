#include "GameCamera.h"
#include <SFML/Window/Keyboard.hpp>



////////////////////////////
// Constructor for the Class
////////////////////////////
LJMU::GameCamera::GameCamera() :_name(), _view(),
Updatable(true),Controllable(true),
_lin_vel(DEF_MOVE_SPEED),_rot_vel(DEF_ROT_RATE),
_zoom_rate(DEF_ZOOM_RATE)
{
	//Set the Default Camera Mapping. 
	this->_keys[CAM_UP] = keys::Up;
	this->_keys[CAM_DOWN] = keys::Down;
	this->_keys[CAM_LEFT] = keys::Left;
	this->_keys[CAM_RIGHT] = keys::Right;
	this->_keys[CAM_ROT_CW] = keys::PageDown;
	this->_keys[CAM_ROT_CCW] = keys::PageUp;
	this->_keys[CAM_ZOOM_IN] = keys::Insert;
	this->_keys[CAM_ZOOM_OUT] = keys::Delete;
	this->_keys[CAM_RESET] = keys::R;
}

///////////////////////////
// Handle Input Controls.  
///////////////////////////
void LJMU::GameCamera::handleInput(float ptpf, float ptotal)
{
	if (!Controllable)
		return;

	float tzoomfactor = 1.0f;
	using kb = sf::Keyboard;
	if (kb::isKeyPressed(this->_keys[CAM_LEFT]))
		this->_view.move(sf::Vector2f(-this->_lin_vel * ptpf, 0));
	if (kb::isKeyPressed(this->_keys[CAM_RIGHT]))
		this->_view.move(sf::Vector2f(this->_lin_vel * ptpf, 0));
	if (kb::isKeyPressed(this->_keys[CAM_UP]))
		this->_view.move(sf::Vector2f(0, -this->_lin_vel * ptpf));
	if (kb::isKeyPressed(this->_keys[CAM_DOWN]))
		this->_view.move(sf::Vector2f(0, this->_lin_vel * ptpf));
	if (kb::isKeyPressed(this->_keys[CAM_ROT_CW]))
		this->_view.rotate(this->_rot_vel * ptpf);
	if (kb::isKeyPressed(this->_keys[CAM_ROT_CCW]))
		this->_view.rotate(-this->_rot_vel * ptpf);
	if (kb::isKeyPressed(this->_keys[CAM_ZOOM_OUT]))
		tzoomfactor -= this->_zoom_rate * ptpf;
	if (kb::isKeyPressed(this->_keys[CAM_ZOOM_IN]))
		tzoomfactor += this->_zoom_rate * ptpf;
	this->_view.zoom(tzoomfactor);

	if (kb::isKeyPressed(this->_keys[CAM_RESET]))
	{
		this->_view.setCenter(this->_origin);
		this->_view.setRotation(0.0f);
		this->_view.setSize(this->_size);
	}
}

//////////////////////////
// Make this instance 
// the current camera.
//////////////////////////
void LJMU::GameCamera::makeCurrent(sf::RenderWindow & pwndw)
{
	//Set this Camera as the Current View
	pwndw.setView(this->_view);
}

/////////////////////////
// Set the Camera Movement
// Controls
/////////////////////////
void LJMU::GameCamera::setMoveControls(keys pup, keys pleft, keys pright, keys pdown)
{
	this->_keys[CAM_UP] = pup;
	this->_keys[CAM_DOWN] = pdown;
	this->_keys[CAM_LEFT] = pleft;
	this->_keys[CAM_RIGHT] = pright;
}

//////////////////////////
// Set the Zoom Controls
//////////////////////////
void LJMU::GameCamera::setZoomRotControls(keys protcw, keys protccw, keys pzi, keys pzo)
{
	this->_keys[CAM_ROT_CW] = protcw;
	this->_keys[CAM_ROT_CCW] = protccw;
	this->_keys[CAM_ZOOM_IN] = pzi;
	this->_keys[CAM_ZOOM_OUT] = pzo;
}

//////////////////////////
// Set the Reset Key
//////////////////////////
void LJMU::GameCamera::setResetControls(keys preset)
{
	this->_keys[CAM_RESET] = preset;
}
