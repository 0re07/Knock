#pragma once		//	���ɍs���Ȃ�
// template <class T> class �N���X��

template <class T> class Vector2DTmp
{
public:
	Vector2DTmp();
	Vector2DTmp(T x, T y);
	~Vector2DTmp();
	T x;
	T y;

	//	������Z�q
	Vector2DTmp& operator=(const Vector2DTmp& vec);

	//	�Y�������Z�q
	T& operator[](int j);

	//	�P�����Z�q
	Vector2DTmp& operator+=(const Vector2DTmp& vec);
	Vector2DTmp& operator-=(const Vector2DTmp& vec);
	Vector2DTmp& operator*=(const Vector2DTmp& vec);
	Vector2DTmp& operator/=(const Vector2DTmp& vec);
	Vector2DTmp& operator%=(const Vector2DTmp& vec);
	Vector2DTmp operator+()const;
	Vector2DTmp operator-()const;

	//	�񍀉��Z�q
	Vector2DTmp operator+(const Vector2DTmp& vec);
	Vector2DTmp operator-(const Vector2DTmp& vec);
	Vector2DTmp operator*(const Vector2DTmp& vec);
	Vector2DTmp operator/(const Vector2DTmp& vec);
	Vector2DTmp operator%(const Vector2DTmp& vec);

	//	��r���Z�q
	bool operator==(const Vector2DTmp& vec)const;
	bool operator!=(const Vector2DTmp& vec)const;
	bool operator<(const Vector2DTmp& vec)const;
	bool operator<=(const Vector2DTmp& vec)const;
	bool operator>(const Vector2DTmp& vec)const;
	bool operator>=(const Vector2DTmp& vec)const;

	Vector2DTmp Normalized(void)const;
};

//	�����̐��⏇�ԂŔ��f���Ă���̂ŁA���Ԃ␔���Ⴄ�ƃG���[���N����
//	�����^
template <class T>  
Vector2DTmp<T> operator*(const Vector2DTmp<T> vec,const int num);
template <class T>  
Vector2DTmp<T> operator*(const int num, const Vector2DTmp <T>vec);

//	�����_����
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

//	�g���₷���悤�ɖ��O��t����
using Vector2D = Vector2DTmp<int>;
using Vector2DFlaot = Vector2DTmp<float>;
using Vector2DDouble = Vector2DTmp<double>;

struct Circle
{
	Vector2D pos;//���S
	float radius; //���a
};

#include "../detalls/Vector2D.h"