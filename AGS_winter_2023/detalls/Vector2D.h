#include <math.h>
#include "../common/Vector2D.h"

template <class T> 
Vector2DTmp<T>::Vector2DTmp()
{
	x = 0;
	y = 0;
}

template <class T>
Vector2DTmp<T>::Vector2DTmp(T x, T y)
{
	Vector2DTmp::x = x;
	Vector2DTmp::y = y;
}

template <class T>
Vector2DTmp<T>::~Vector2DTmp()
{
}

//‘ã“ü‰‰Zq
template <class T>
Vector2DTmp<T>& Vector2DTmp<T>::operator=(const Vector2DTmp& vec)
{
	x = vec.x;
	y = vec.y;

	return *this;

}

//“Y‚¦š‰‰Zq
template <class T>
T& Vector2DTmp<T>::operator[](int j)
{
	switch (j)
	{
	case 0:
		return x;
		//break;
	case 1:
		return y;
		//break;
	default:
		return x;
		//break;
	}
}

//’P€‰‰Zq
template <class T>
Vector2DTmp<T>& Vector2DTmp<T>::operator+=(const Vector2DTmp& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

template <class T>
Vector2DTmp<T>& Vector2DTmp<T>::operator-=(const Vector2DTmp& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

template <class T>
Vector2DTmp<T>& Vector2DTmp<T>::operator*=(const Vector2DTmp& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

template <class T>
Vector2DTmp<T>& Vector2DTmp<T>::operator/=(const Vector2DTmp& vec)
{
	//ƒK[ƒhˆ—
	if (vec.x)
	{
		x /= vec.x;
	}
	else
	{
		x = 0;
	}
	if (vec.y)
	{
		y /= vec.y;
	}
	else
	{
		y = 0;
	}

	return;
}

template <class T>
Vector2DTmp<T>& Vector2DTmp<T>::operator%=(const Vector2DTmp& vec)
{
	//ƒK[ƒhˆ—
	if (vec.x)
	{
		x = static_cast<int>(x) % static_cast<int>(x);
	}
	else
	{
		x = 0;
	}
	if (vec.y)
	{
		y = static_cast<int>(y) % static_cast<int>(y);
	}
	else
	{
		y = 0;
	}
	
	return *this;
}

template <class T>
Vector2DTmp<T> Vector2DTmp<T>::operator+() const
{
	return *this;
}

template <class T>
Vector2DTmp<T> Vector2DTmp<T>::operator-() const
{

	return{ -x,-y };
}

//“ñ€‰‰Zq
template <class T>
Vector2DTmp<T> Vector2DTmp<T>::operator+(const Vector2DTmp& vec)
{
	//Vector2D val;
	//val.x = x + vec.x;
	//val.y = y + vec.y;
	//return val;
	return { x + vec.x,y + vec.y };
}

template <class T>
Vector2DTmp<T> Vector2DTmp<T>::operator-(const Vector2DTmp& vec)
{
	return { x - vec.x,y - vec.y };
}

template <class T>
Vector2DTmp<T> Vector2DTmp<T>::operator*(const Vector2DTmp& vec)
{
	return { x * vec.x,y * vec.y };
}

template <class T>
Vector2DTmp<T> Vector2DTmp<T>::operator/(const Vector2DTmp& vec)
{
	Vector2D val;
	//ƒK[ƒhˆ—
	if (vec.x)
	{
		val.x = x / vec.x;
	}
	else
	{
		val.x = 0;
	}
	if (vec.y)
	{
		val.y = y / vec.y;
	}
	else
	{
		val.y = 0;
	}

	
	return val;
}

template <class T> 
Vector2DTmp<T> Vector2DTmp<T>::operator%(const Vector2DTmp& vec)
{
	Vector2DTmp val;
	//ƒK[ƒhˆ—
	if (vec.x)
	{
		val.x = x % vec.x;
	}
	else
	{
		val.x = 0;
	}
	if (vec.y)
	{
		val.y = y % vec.y;
	}
	else
	{
		val.y = 0;
	}
	return val;
}

//”äŠr‰‰Zq
template <class T>
bool Vector2DTmp<T>::operator==(const Vector2DTmp& vec) const
{
	//if (x == vec.x && y == vec.y)
	//{
	//	return true;
	//}
	//return false;
	return(x == vec.x && y == vec.y);
}

template <class T>
bool Vector2DTmp<T>::operator!=(const Vector2DTmp& vec) const
{
	return(x != vec.x && y != vec.y);
}

template <class T>
bool Vector2DTmp<T>::operator<(const Vector2DTmp& vec) const
{
	return(x < vec.x && y < vec.y);
}

template <class T>
bool Vector2DTmp<T>::operator<=(const Vector2DTmp& vec) const
{
	return(x <= vec.x && y <= vec.y);
}

template <class T>
bool Vector2DTmp<T>::operator>(const Vector2DTmp& vec) const
{
	return(x > vec.x && y > vec.y);
}

template <class T>
bool Vector2DTmp<T>::operator>=(const Vector2DTmp& vec) const
{
	return(x >= vec.x && y >= vec.y);
}

template<class T>
inline Vector2DTmp<T> Vector2DTmp<T>::Normalized(void) const
{
	auto len = hypotf(x, y);
	return { static_cast<T>(x / len),static_cast<T>(y / len) };
}

//®”Œ^
template <class T>
Vector2DTmp<T> operator*(const Vector2DTmp<T> vec, const int num)
{
	return{ vec.x * num,vec.y * num };
}

template <class T>
Vector2DTmp<T> operator*(const int num, const Vector2DTmp<T> vec)
{
	return{ vec.x * num,vec.y * num };
}

template <class T>
Vector2DTmp<T> operator*(const Vector2DTmp<T>& vec1, const Vector2DTmp<T>& vec2)
{
	return{ vec1.x * vec2.x,vec1.y * vec2.y };
}

//¬”“_‚à‰Â
template <class T>
Vector2DTmp<T> operator*(const Vector2DTmp<T> vec, const float num)
{
	return{ static_cast<T>(vec.x * num),static_cast<T>(vec.y * num) };
}

template <class T>
Vector2DTmp<T> operator*(const float num, const Vector2DTmp<T> vec)
{
	return{ static_cast<int>(vec.x * num),static_cast<int>(vec.y * num) };
}

template<class T>
inline Vector2DTmp<T> operator*=(const Vector2DTmp<T> vec, const float num)
{
	return { vec.x * num,vec.y * num };
}

template <class T>
Vector2DTmp<T> operator/(const Vector2DTmp<T> vec, const int num)
{
	return{ vec.x / num,vec.y / num };
}

template <class T>
Vector2DTmp<T> operator/(const Vector2DTmp<T> vec1, Vector2DTmp<T> vec2)
{
	Vector2DTmp val = { 0,0 };
	//ƒK[ƒhˆ—
	if (vec2.x)
	{
		val.x = vec1.x / vec2.x;
	}
	else
	{
		val.x = 0;
	}
	if (vec2.y)
	{
		val.y = vec1.y / vec2.y;
	}
	else
	{
		val.y = 0;
	}

	return val;
}
