#pragma once		//	下に行かない
// template <class T> class クラス名

template <class T> class Vector2DTmp
{
public:
	Vector2DTmp();
	Vector2DTmp(T x, T y);
	~Vector2DTmp();
	T x;
	T y;

	//	代入演算子
	Vector2DTmp& operator=(const Vector2DTmp& vec);

	//	添え字演算子
	T& operator[](int j);

	//	単項演算子
	Vector2DTmp& operator+=(const Vector2DTmp& vec);
	Vector2DTmp& operator-=(const Vector2DTmp& vec);
	Vector2DTmp& operator*=(const Vector2DTmp& vec);
	Vector2DTmp& operator/=(const Vector2DTmp& vec);
	Vector2DTmp& operator%=(const Vector2DTmp& vec);
	Vector2DTmp operator+()const;
	Vector2DTmp operator-()const;

	//	二項演算子
	Vector2DTmp operator+(const Vector2DTmp& vec);
	Vector2DTmp operator-(const Vector2DTmp& vec);
	Vector2DTmp operator*(const Vector2DTmp& vec);
	Vector2DTmp operator/(const Vector2DTmp& vec);
	Vector2DTmp operator%(const Vector2DTmp& vec);

	//	比較演算子
	bool operator==(const Vector2DTmp& vec)const;
	bool operator!=(const Vector2DTmp& vec)const;
	bool operator<(const Vector2DTmp& vec)const;
	bool operator<=(const Vector2DTmp& vec)const;
	bool operator>(const Vector2DTmp& vec)const;
	bool operator>=(const Vector2DTmp& vec)const;

	Vector2DTmp Normalized(void)const;
};

//	引数の数や順番で判断しているので、順番や数が違うとエラーが起きる
//	整数型
template <class T>  
Vector2DTmp<T> operator*(const Vector2DTmp<T> vec,const int num);
template <class T>  
Vector2DTmp<T> operator*(const int num, const Vector2DTmp <T>vec);

//	小数点も可
template <class T>
Vector2DTmp<T> operator*(const Vector2DTmp<T>& vec1, const Vector2DTmp<T>& vec2);
template <class T>
Vector2DTmp<T> operator*(const Vector2DTmp<T> vec, const float num);
template <class T>
Vector2DTmp<T> operator*(const float num, const Vector2DTmp<T>vec);

template <class T>
Vector2DTmp<T> operator*=(const Vector2DTmp<T> vec, const float num);

template <class T>
Vector2DTmp<T> operator/(const Vector2DTmp<T> vec, const int num);
template <class T>
Vector2DTmp<T> operator/(const Vector2DTmp<T> vec1, Vector2DTmp<T> vec2);

//	使いやすいように名前を付ける
using Vector2D = Vector2DTmp<int>;
using Vector2DFlaot = Vector2DTmp<float>;
using Vector2DDouble = Vector2DTmp<double>;

struct Circle
{
	Vector2D pos;//中心
	float radius; //半径
};

#include "../detalls/Vector2D.h"