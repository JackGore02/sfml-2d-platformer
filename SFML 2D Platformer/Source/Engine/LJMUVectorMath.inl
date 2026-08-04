namespace sf
{


template <typename T>
T length(const sf::Vector2<T>& vector)
{
	return LJMUTrig<T>::sqrt(squaredLength(vector));
}

template <typename T>
T squaredLength(const sf::Vector2<T>& vector)
{
	return dotProduct(vector, vector);
}

template <typename T>
void setLength(sf::Vector2<T>& vector, T newLength)
{
	assert(vector != sf::Vector2<T>());
	vector *= newLength / length(vector);
}

template <typename T>
sf::Vector2<T> unitVector(const sf::Vector2<T>& vector)
{
	//assert(vector != sf::Vector2<T>());
	return vector / length(vector);
}

template <typename T>
T polarAngle(const sf::Vector2<T>& vector)
{
	assert(vector != sf::Vector2<T>());
	return LJMUTrig<T>::arcTan2(vector.y, vector.x);
}

template <typename T>
void setPolarAngle(sf::Vector2<T>& vector, T newAngle)
{
	T vecLength = length(vector);
	vector.x = vecLength * LJMUTrig<T>::cos(newAngle);
	vector.y = vecLength * LJMUTrig<T>::sin(newAngle);
}

template <typename T>
void rotate(sf::Vector2<T>& vector, T angle)
{
	T cos = LJMUTrig<T>::cos(angle);
	T sin = LJMUTrig<T>::sin(angle);
	vector = sf::Vector2<T>(cos * vector.x - sin * vector.y,sin * vector.x + cos * vector.y);
}

template <typename T>
sf::Vector2<T> rotatedVector(const sf::Vector2<T>& vector, T angle)
{
	sf::Vector2<T> copy = vector;
	rotate(copy, angle);
	return copy;
}

template <typename T>
sf::Vector2<T> perpendicularVector(const sf::Vector2<T>& vector)
{
	return sf::Vector2<T>(-vector.y, vector.x);
}

// ---------------------------------------------------------------------------------------------------------------------------

template <typename T>
T signedAngle(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	assert(lhs != sf::Vector2<T>() && rhs != sf::Vector2<T>());
	return LJMUTrig<T>::arcTan2(crossProduct(lhs, rhs).z, dotProduct(lhs, rhs));
}

template <typename T>
T dotProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
sf::Vector2<T> cwiseProduct(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	return sf::Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T>
sf::Vector2<T> cwiseQuotient(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	assert(rhs.x != 0 && rhs.y != 0);
	return sf::Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <typename T>
sf::Vector2<T> projectedVector(const sf::Vector2<T>& vector, const sf::Vector2<T>& axis)
{
	assert(axis != sf::Vector2<T>());
	return dotProduct(vector, axis) / squaredLength(axis) * axis;
}

sf::Vector2f tof(sf::Vector2u pu)
{
	return sf::Vector2f(pu);
}

sf::Vector2f tof(sf::Vector2i pi)
{
	return sf::Vector2f(pi);
}

sf::Vector2u tou(sf::Vector2f pf)
{
	return sf::Vector2u(pf);
}

sf::Vector2u tou(sf::Vector2i pi)
{
	return sf::Vector2u(pi);
}

sf::Vector2i toi(sf::Vector2f pf)
{
	return sf::Vector2i(pf);
}

sf::Vector2i toi(sf::Vector2u pu)
{
	return sf::Vector2i(pu);
}

sf::Vector2f topLeft(sf::FloatRect pr)
{
	return sf::Vector2f(pr.left, pr.top);
}

sf::Vector2f topRight(sf::FloatRect pr)
{
	return sf::Vector2f(pr.left + pr.width, pr.top);
}

sf::Vector2f btmLeft(sf::FloatRect pr)
{
	return sf::Vector2f(pr.left, pr.top + pr.height);
}

sf::Vector2f btmRight(sf::FloatRect pr)
{
	return sf::Vector2f(pr.left + pr.width, pr.top + pr.height);
}

sf::Vector2f todimf(sf::FloatRect pr)
{
	return sf::Vector2f(pr.width, pr.height);
}

sf::Vector2i todimi(sf::FloatRect pr)
{
	return toi(todimf(pr));
}

sf::Vector2f topLeft(sf::IntRect pr)
{
	return sf::Vector2f(static_cast<float>(pr.left), static_cast<float>(pr.top));
}

sf::Vector2f topRight(sf::IntRect pr)
{
	return sf::Vector2f(static_cast<float>(pr.left + pr.width), static_cast<float>(pr.top));
}

sf::Vector2f btmLeft(sf::IntRect pr)
{
	return sf::Vector2f(static_cast<float>(pr.left), static_cast<float>(pr.top + pr.height));
}

sf::Vector2f btmRight(sf::IntRect pr)
{
	return sf::Vector2f(static_cast<float>(pr.left + pr.width), static_cast<float>(pr.top + pr.height));
}

sf::Vector2f todimf(sf::IntRect pr)
{
	return sf::Vector2f(static_cast<float>(pr.width), static_cast<float>(pr.height));
}

sf::Vector2i todimi(sf::IntRect pr)
{
	return toi(todimf(pr));
}

sf::IntRect  toi(sf::FloatRect pr)
{
	sf::IntRect trect;
	trect.left		= rounding(pr.left);
	trect.top		= rounding(pr.top);
	trect.width		= rounding(pr.width);
	trect.height	= rounding(pr.height);
	return trect;
}

sf::FloatRect tof(sf::IntRect pr)
{
	sf::FloatRect trect;
	trect.left = static_cast<float>(pr.left);
	trect.top = static_cast<float>(pr.top);
	trect.width = static_cast<float>(pr.width);
	trect.height = static_cast<float>(pr.height);
	return trect;
}

sf::IntRect fromdimi(sf::Vector2f pdim)
{
	return sf::IntRect(sf::Vector2i(0, 0), toi(pdim));
}

sf::IntRect fromdimi(sf::Vector2i pdim)
{
	return sf::IntRect(sf::Vector2i(0, 0),pdim);
}

sf::FloatRect fromdimf(sf::Vector2f pdim)
{
	return sf::FloatRect(sf::Vector2f(0, 0),pdim);
}

sf::FloatRect fromdimf(sf::Vector2i pdim)
{
	return sf::FloatRect(sf::Vector2f(0, 0),tof(pdim));
}

} 