namespace sf
{
	//Static Function Library for Trigonometry on Floats using the STL Mathematics Functions. 
	template <>
	struct LJMUTrig <float>
	{
		typedef float Type;
		static Type sin(Type deg)					{ return std::sin(degToRad(deg)); }
		static Type cos(Type deg)					{ return std::cos(degToRad(deg)); }
		static Type tan(Type deg)					{ return std::tan(degToRad(deg)); }
		static Type arcSin(Type value)				{ return radToDeg(std::asin(value)); }
		static Type arcCos(Type value)				{ return radToDeg(std::acos(value)); }
		static Type arcTan2(Type valY, Type valX)	{ return radToDeg(std::atan2(valY, valX)); }
		static Type sqrt(Type value)				{ return std::sqrt(value); }

		static Type pi()							{ return 3.141592653589793238462643383f; }
		static Type radToDeg(Type rad)				{ return 180 / pi() * rad; }
		static Type degToRad(Type deg)				{ return pi() / 180 * deg; }
	};

	//Static Function Library for Trigonometry on Doubles using the STL Mathematics Functions
	template <>
	struct LJMUTrig <double>
	{
		typedef double Type;
		static Type sin(Type deg)					{ return std::sin(degToRad(deg)); }
		static Type cos(Type deg)					{ return std::cos(degToRad(deg)); }
		static Type tan(Type deg)					{ return std::tan(degToRad(deg)); }
		static Type arcSin(Type value)				{ return radToDeg(std::asin(value)); }
		static Type arcCos(Type value)				{ return radToDeg(std::acos(value)); }
		static Type arcTan2(Type valY, Type valX)	{ return radToDeg(std::atan2(valY, valX)); }
		static Type sqrt(Type value)				{ return std::sqrt(value); }

		static Type pi()							{ return 3.141592653589793238462643383; }
		static Type radToDeg(Type rad)				{ return 180 / pi() * rad; }
		static Type degToRad(Type deg)				{ return pi() / 180 * deg; }
	};

}