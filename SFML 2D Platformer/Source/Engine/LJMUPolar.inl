#include "LJMUPolar.h"
#ifndef __LJMU_POLAR_INL_
#define __LJMU_POLAR_INL_

//-----------CONSTRUCTORS-----------------------------------------

template <typename T>
inline sf::LJMUPolar2<T>::LJMUPolar2()
: r(), phi()
{
}

template <typename T>
inline sf::LJMUPolar2<T>::LJMUPolar2(T pradius, T pangle)
: r(pradius), phi(pangle)
{
}

//-----------CONVERSION CONSTRUCTOR + OPERATOR--------------------------------

template <typename T>
inline sf::LJMUPolar2<T>::LJMUPolar2(const sf::Vector2<T>& pvector)
: r(length(pvector)), phi(vector == sf::Vector2<T>() ? 0.f : polarAngle(pvector))
{
}

template<typename T>
inline sf::LJMUPolar2<T>::operator sf::Vector2<T>() const
{
	return sf::Vector2<T>(this->r * LJMUTrig<T>::cos(phi),this->r * LJMUTrig<T>::sin(phi));
}


//------------SF NAMESPACE FUNCTIONS--------------------------------------------

template <typename T>
inline T sf::length(const LJMUPolar2<T>& pvector)
{
	return pvector.r;
}

template <typename T>
inline T sf::polarAngle(const LJMUPolar2<T>& pvector)
{
	return pvector.phi;
}

#endif