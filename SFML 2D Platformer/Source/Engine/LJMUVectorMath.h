#ifndef __LJMU_VECTORMATH_H_
#define __LJMU_VECTORMATH_H_

//Include SFML Framework Classes
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

//Include Framework Trig Class
#include "LJMUTrigonometry.h"

//Include STL Assertions
#include <cassert>

namespace sf
{
	///////////////////////////////
	// Function Library for Helper
	// Functions relating to 
	// Vector, Rectangle
	// Manipulations. 
	// 
	// These functions are global 
	// to the sf namespace.  
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    23/05/2017
	///////////////////////////////

	template <typename T>
	T length(const sf::Vector2<T>& vector);	//Get the Magnitude of the Given Vector

	template <typename T>
	T squaredLength(const sf::Vector2<T>& vector); //Get the Square Magnitude of the Given Vector.

	template <typename T>
	void setLength(sf::Vector2<T>& vector, T newLength); //Set the Length of the Given Vector.

	template <typename T>
	sf::Vector2<T> unitVector(const sf::Vector2<T>& vector); //Return a Unit Vector Copy version of the Given Vector

	template <typename T>
	T polarAngle(const sf::Vector2<T>& vector); //Calculate the Polar Angle Representation of the Given Vector

	template <typename T>
	void setPolarAngle(sf::Vector2<T>& vector, T newAngle); //Set the Given Vector to a New Angle

	template <typename T>
	void rotate(sf::Vector2<T>& vector, T angle); //Rotate the Vector by a given amount

	template <typename T>
	sf::Vector2<T> rotatedVector(const sf::Vector2<T>& vector, T angle); //Return a copy of the Rotated Version of the Given vector.

	template <typename T>
	sf::Vector2<T> perpendicularVector(const sf::Vector2<T>& vector); //Return a copy of the perpendicular vector of the given vector

	template <typename T>
	T signedAngle(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs); //Calculate the Signed Angle between two vectors.

	template <typename T>
	T dotProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs); //Calculate the dot product between two vectors.

	template <typename T>
	sf::Vector2<T> cwiseProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs); //Calculate the clockwise product of two vectors

	template <typename T>
	sf::Vector2<T> cwiseQuotient(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs);//Calculate the clockwise quotient between two vectors.

	template <typename T>
	sf::Vector2<T> projectedVector(const sf::Vector2<T>& vector, const sf::Vector2<T>& axis); //Return the Resultant Vector of the given vector projected onto an axis. 

	//-----------VECTOR TYPE CONVERSION FUNCTIONS-------------------------------------------------------

	inline sf::Vector2f tof(sf::Vector2u pu); //Convert a Vector2u to a Vector2f

	inline sf::Vector2f tof(sf::Vector2i pi); //Convert a Vector2i to a Vector2f

	inline sf::Vector2u tou(sf::Vector2f pf); //Convert a Vector2f to a Vector2u

	inline sf::Vector2u tou(sf::Vector2i pi); //Convert a Vector2i to a Vector2u

	inline sf::Vector2i toi(sf::Vector2f pf); //Convert a Vector2f to a Vector2i

	inline sf::Vector2i toi(sf::Vector2u pu); //Convert a Vector2u to a Vector2i

	//-----------FLOAT RECTANGLE - VECTOR CONVERSION FUNCTIONS------------------------------------------------

	inline sf::Vector2f topLeft(sf::FloatRect pr); //Get the Top-Left Point of the Given Rectangle as a Vector

	inline sf::Vector2f topRight(sf::FloatRect pr);//Get the Top-Right Point of the Given Rectangle as a Vector

	inline sf::Vector2f btmLeft(sf::FloatRect pr);//Get the Bottom-Left Point of the Given Rectangle as a Vector

	inline sf::Vector2f btmRight(sf::FloatRect pr); //Get the Bottom-Right Point of the Given Rectangle as a Vector

	inline sf::Vector2f todimf(sf::FloatRect pr); //Get the Width and Height of the Given Rectangle as a Float Vector

	inline sf::Vector2i todimi(sf::FloatRect pr); //Get the Width and Height of the Given Rectangle as a Integer Vector


	//-----------INTEGER RECTANGLE - VECTOR CONVERSION FUNCTIONS------------------------------------------------

	inline sf::Vector2f topLeft(sf::IntRect pr); //Get the Top-Left Point of the Given Rectangle as a Vector

	inline sf::Vector2f topRight(sf::IntRect pr);//Get the Top-Right Point of the Given Rectangle as a Vector

	inline sf::Vector2f btmLeft(sf::IntRect pr);//Get the Bottom-Left Point of the Given Rectangle as a Vector

	inline sf::Vector2f btmRight(sf::IntRect pr);//Get the Bottom-Right Point of the Given Rectangle as a Vector

	inline sf::Vector2f todimf(sf::IntRect pr); //Get the Dimensions of the Given Rectangle as a float Vector.

	inline sf::Vector2i todimi(sf::IntRect pr); //Get the Dimension of the Given Rectangle as a Integer Vector

	//-----------RECTANGLE TYPE CONVERSION FUNCTIONS------------------------------------------------

	inline sf::IntRect  toi(sf::FloatRect pr); //Convert the Given Float Rectangle as an Integer Rectangle.

	inline sf::FloatRect tof(sf::IntRect pr);  //Convert the Given Integer Rectangle as a Float Rectangle.

	//-----------VECTOR - RECTANGLE CONVERSION FUNCTIONS--------------------------------------------

	inline sf::IntRect fromdimi(sf::Vector2f pdim); //Convert the Given Width and Height Float Vector to a Origin Positioned  Integer Rectangle

	inline sf::IntRect fromdimi(sf::Vector2i pdim); //Convert the Given Width and Height Integer Vector to a Origin Positioned Integer Rectangle

	inline sf::FloatRect fromdimf(sf::Vector2f pdim); //Convert the Given Width and Height Float Vector to a Origin Positioned Float Rectangle

	inline sf::FloatRect fromdimf(sf::Vector2i pdim); //Convert the Given Width and Height Integer Vector to a Origin Positioned Float Rectangle

}

//Templated Functions so header needs awareness
#include "LJMUVectorMath.inl"

#endif 