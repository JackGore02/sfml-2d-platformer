#pragma once

//STL Includes
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>

//SFML Includes
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//Framework Includes
#include <LJMUAnimSprite.h>

namespace sf
{
	///////////////////////////////
	// Collection of Useful Utility
	// Functions 
	// 
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    23/05/2017
	///////////////////////////////

	//String Output Functions for SFML Data Types
	inline std::string getContextInfo(sf::RenderWindow& pwndw);
	inline std::string getSpriteState(sf::Sprite& psprite);
	inline std::string getFPS(sf::Time ptpf);
	inline std::string getIntegerFPS(sf::Time ptpf);

	//Origin Helper functions for our Different Sprite Objects.
	inline void setOriginCentre(sf::Sprite& psprite);
	inline void setOriginCentre(sf::LJMUAnimSprite& psprite);

	//Full Screen Helper function for Static Sprites.
	inline void makeFullScreen(sf::Sprite& psprite, sf::Vector2f pscreendim);

    //Apply Banker's Rounding to the Given Float Value.
	inline int rounding(float pfloat); 
	
	//---------------UTILITY FUNCTION IMPLEMENATIONS---------------------------------------------------------------------

	///////////////////////////////
	// Get the Context Information
	// for the Given SFML Windows
	// and return it as a formatted
	// string. 
    ///////////////////////////////
	inline std::string getContextInfo(sf::RenderWindow& pwndw)
	{
		//Get the OpenGL Context and the Screen Resolution
		sf::ContextSettings togls = pwndw.getSettings();
		sf::Vector2u tscreenres = pwndw.getSize();

		std::ostringstream tss;
		tss << "***************OUTPUT SETTINGS*****************************************" << std::endl;
		tss << " Depth Buffer (Bits):    " << togls.depthBits << std::endl;
		tss << " Stencil Buffer (Bits):  " << togls.stencilBits << std::endl;
		tss << " MSAA Level:             " << togls.antialiasingLevel << std::endl;
		tss << " Open GL Version:        " << togls.majorVersion << "." << togls.minorVersion << std::endl;
		tss << " Resolution:             " << tscreenres.x << ", " << tscreenres.y << std::endl;
		tss << "***********************************************************************" << std::endl;
		return tss.str();
	}

	///////////////////////////////
	// Get the Geometric Properties
	// Of the Given Sprite Object
	// and return these properties
	// as a formatted string. 
	///////////////////////////////
	inline std::string getSpriteState(sf::Sprite& psprite)
	{
		Vector2f tpos = psprite.getPosition();
		Vector2u tsize = psprite.getTexture()->getSize();
		Vector2f tscale = psprite.getScale();
		float tlength = sqrtf(tpos.x * tpos.x + tpos.y * tpos.y);
		float tangle = tlength > 0 ? atan2f(tpos.y, tpos.x) : 0.0f;

		Vector2f tdir;
		if (tlength > 0)
			tdir = tpos / tlength;

		String tinfo;
		tinfo += "Current Position:  " + std::to_string(tpos.x) + " : " + std::to_string(tpos.y) + "\n";
		tinfo += "Magnitude/Length:  " + std::to_string(tlength) + "\n";
		tinfo += "Polar Angle:       " + std::to_string(tangle) + "\n";
		tinfo += "Vector Direction:  " + std::to_string(tdir.x) + " : " + std::to_string(tdir.y) + "\n";
		tinfo += "Sprite Dimensions: " + std::to_string(tsize.x) + " : " + std::to_string(tsize.y) + "\n";
		tinfo += "Sprite Rotation:   " + std::to_string(psprite.getRotation()) + "\n";
		std::string tscaletext(std::to_string(tscale.x));
		tscaletext += " : ";
		tscaletext += std::to_string(tscale.y) + "\n";
		tinfo += "Sprite Scale:      " + tscaletext;
		return tinfo;
	}

	///////////////////////////////
	// Represent the Given Time 
	// Per Frame data as an accurate
	// FPS Rate, returning this 
	// as a formatted string. 
	/////////////////////////////
	inline std::string getFPS(sf::Time ptpf)
	{
		return std::to_string(1.0f / ptpf.asSeconds());
	}

	///////////////////////////////
	// Represent the Given Time 
	// Per Frame data as an accurate
	// FPS Rate, returning this 
	// as a formatted string. 
	/////////////////////////////
	inline std::string getIntegerFPS(sf::Time ptpf)
	{
		return std::to_string(rounding(1.0f / ptpf.asSeconds()));
	}

	///////////////////////////////
	// Set the Sprite's Origin to 
	// its Centre Position.
	///////////////////////////////
	inline void setOriginCentre(sf::Sprite& psprite)
	{
		sf::Vector2i tframe;
		tframe.x = static_cast<int>(psprite.getLocalBounds().width);
		tframe.y = static_cast<int>(psprite.getLocalBounds().height);
		sf::Vector2f torigin(tframe);
		torigin *= 0.5f;
		psprite.setOrigin(torigin);
	}

	///////////////////////////////
	// Set the given Animated Sprite's
	// Origin to its centre position.
	///////////////////////////////
	inline void setOriginCentre(sf::LJMUAnimSprite& psprite)
	{
		sf::Vector2i tframe;
		tframe.x = static_cast<int>(psprite.getLocalBounds().width);
		tframe.y = static_cast<int>(psprite.getLocalBounds().height);
		sf::Vector2f torigin(tframe);
		torigin *= 0.5f;
		psprite.setOrigin(torigin);
	}

	inline void makeFullScreen(sf::Sprite& psprite, sf::Vector2f pscreendim)
	{
		//Get the Sprite Dimensions
		sf::Vector2f tspritedim = sf::Vector2f(psprite.getLocalBounds().width, psprite.getLocalBounds().height);
		sf::Vector2f tscale = sf::Vector2f(pscreendim.x / tspritedim.x, pscreendim.y / tspritedim.y);
		psprite.setScale(tscale);
	}

	/////////////////////////////////
	// Get the Banker's Rounded Integer
	// Representation of the Given 
	// Float. 
	/////////////////////////////////
	int rounding(float pfloat)
	{
		return static_cast<int>(pfloat + 0.5f);
	}
}