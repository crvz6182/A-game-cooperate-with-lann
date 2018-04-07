#pragma once
#include <vector>
#include <map>
#include <initializer_list>

using Index = unsigned int;
using Count = unsigned int;
using Size1D = float;
using Percent = float;

struct Size2D
{
	Size1D Width;
	Size1D Height;
};

using Unit = float;
struct Point2D {
	Unit x;
	Unit y;

	Point2D(Unit _x = 0.f, Unit _y = 0.f) : x(_x), y(_y) {}
	Point2D& operator+=(const Point2D& rhs) 
	{ 
		x += rhs.x;
		y += rhs.y; 
		return *this;
	}

	Point2D& operator*=(const Percent scale) 
	{ 
		x *= scale;
		y *= scale; 
		return *this;
	}

	const Point2D operator*(const Percent scale)
	{
		Point2D tPoint = *this; 
		tPoint *= scale;
		return tPoint; 
	}

};

inline void BreakPoint()
{

}

template<typename T1, typename T2>
class Pair
{
public:
	Pair(const T1& first, const T2& second) :mPair(first, second) {}

	T1 GetFirst() const
	{
		return mPair.first;
	}

	T2 GetSecond() const
	{
		return mPair.second;
	}
private:
	std::pair<T1, T2> mPair;
};

template<typename T>
class Array
{
public:
	Array() {};
	~Array() {};

	Array(std::initializer_list<T> il) :mVector(il) {}

	void Append(T t)
	{
		mVector.push_back(t);
	}

	const Count GetLength() const
	{
		return mVector.size();
	}

	T& operator[](Index ind)
	{
		return mVector[ind];
	}

	//begin end 提供迭代器，用于for(auto :)式遍历
	auto begin() const
	{
		return mVector.cbegin();
	}

	auto end() const
	{
		return mVector.cend();
	}
private:
	std::vector<T> mVector;
};

template<typename TKey, typename TValue>
class Dictionary
{
public:
	void Create(const TKey& key, const TValue& value)
	{
		mMap[key] = value;
	}
private:
	std::map<TKey, TValue> mMap;
};

class Matrix3x3
{
private:
};

namespace Math 
{

	/*
	返回一个值，该值被限定在一个区域内，该值若超出边界值，则返回与其最接近的边界值。
	value：要求被限制的值
	leftBorder：左边界值
	rightBorder：右边界值
	返回值：被限制后的值
	*/
	inline static const float Clamp(const float& value, const float& leftBorder, const float& rightBorder);

	/*
	返回一个值，该值被限定在一个区域内，该区间假设平铺于数轴，该值若超出边界值，则返回该值处于区间内的对应位置。
	value：要求被限制的值
	leftBorder：左边界值
	rightBorder：右边界值
	返回值：被限制后的值
	*/
	inline static const float Loop(const float& value, const float& leftBorder, const float& rightBorder);

	//返回较小值
	inline static const float Min(const float& a, const float& b);

	//返回较大值
	inline static const float Max(const float& a, const float& b);
};
