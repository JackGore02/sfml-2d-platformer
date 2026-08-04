#ifndef __LJMU_TRIG_H_
#define __LJMU_TRIG_H_

//Include STL Math Library
#include <cmath>

///////////////////////////////
// Templated class to represent
// Simple Trigonometric functions
// on base floating point types, 
// such as Float and Double. 
// We will not implement an 
// Integer version - use 
// casting from Float/Double
// for this purpose.  
// 
// AUTHOR:  DR CHRIS CARTER
// DATE:    23/05/2017
///////////////////////////////
namespace sf
{

	//Simple Templated Structure for Trigonometry - Avoid Inheritance
	//and Virtual Calls for Performance.  
	template <typename T>
	struct LJMUTrig
	{
	};

	//Convert a value from Radians to Degrees.
	template <typename T>
	T toDegree(T radian)
	{
		return LJMUTrig<T>::radToDeg(radian);
	}

	//Convert a value from Degrees to Radians.
	template <typename T>
	T toRadian(T degree)
	{
		return LJMUTrig<T>::degToRad(degree);
	}
}
#include "LJMUTrigonometry.inl"

#endif 