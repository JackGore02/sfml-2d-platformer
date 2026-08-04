#ifndef __LJMU_POLARVECTOR_H_
#define __LJMU_POLARVECTOR_H_

//Include SFML Vector Class
#include <SFML/System/Vector2.hpp>

namespace sf
{

	///////////////////////////////
	// Structure to represent 2D 
	// Polar Coordinates. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    24/05/2017
	///////////////////////////////
	template <typename T>
	struct LJMUPolar2
	{
		T	r;										//Radius	
		T	phi;									//Angle	
		LJMUPolar2();								//Default Constructor
		LJMUPolar2(T radius, T angle);				//Complete Constructor
		LJMUPolar2(const sf::Vector2<T>& vector);	//Copy Constructor for Vector2
		operator sf::Vector2<T> () const;			//Overloaded Cast Operator
	};

	typedef LJMUPolar2<float> LJMUPolar2f;			//Create the Float Version

	//Function to calculate the length of a Polar
	template <typename T>
	T length(const LJMUPolar2<T>& vector);

	//Function to calculate the angle of a Polar. 
	template <typename T>
	T polarAngle(const LJMUPolar2<T>& vector);
} 

#include "LJMUPolar.inl"	//Include the Definition of the Functions

#endif 