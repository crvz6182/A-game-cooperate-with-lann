#pragma once
#include <vector>
#include <map>
#include <initializer_list>
#include <DirectXMath.h>

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

	const Point2D operator+(const Point2D& rhs)
	{
		Point2D tAns = *this;
		tAns += rhs;
		return tAns;
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
using Direction2D = Point2D;

inline void BreakPoint()
{

}

template<typename T1, typename T2>
class Pair
{
public:
	Pair(const T1& first = T1(), const T2& second = T2()) :mPair(first, second) {}

	T1 GetFirst() const
	{
		return mPair.first;
	}

	T2 GetSecond() const
	{
		return mPair.second;
	}

	const bool operator<(const Pair& rhs) const
	{
		if (GetFirst() < rhs.GetFirst()) {
			return true;
		}
		if (rhs.GetFirst() < GetFirst()) {
			return false;
		}
		if (GetSecond() != rhs.GetSecond()) {
			BreakPoint();
		}
		return GetSecond() < rhs.GetSecond();
	}
private:
	std::pair<T1, T2> mPair;
};

template<typename T>
class Array
{
public:
	Array() {}
	Array(std::initializer_list<T> il) :mVector(il) {}

	void Append(T t)
	{
		mVector.push_back(t);
	}

	void Clear()
	{
		mVector.clear();
	}

	const Count GetLength() const
	{
		return (Count)mVector.size();
	}

	T& operator[](Index ind)
	{
		return mVector[ind];
	}

	//begin end 提供迭代器，用于for(auto :)式遍历
	auto begin() const
	{
		return mVector.begin();
	}

	auto end() const
	{
		return mVector.end();
	}
private:
	std::vector<T> mVector;
};

template<typename TKey, typename TValue>
class Dictionary
{
public:
	//创建一对字典键值
	void Create(const TKey& key, const TValue& value)
	{
		mMap[key] = value;
	}
	//修改一对字典键值
	void Modify(const TKey& key, const TValue& value)
	{
		mMap[key] = value;
	}

	auto& operator[](const TKey& i)
	{
		return mMap[i];
	}

	TValue* Get(const TKey& key)
	{
		auto result = mMap.find(key);
		if (result == mMap.cend()) {
			return nullptr;
		}
		return &(result->second);
	}

	auto begin()
	{
		return mMap.begin();
	}

	auto end()
	{
		return mMap.end();
	}
private:
	std::map<TKey, TValue> mMap;
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
	inline const float Clamp(const float& value, const float& leftBorder, const float& rightBorder)
	{
		if (value < leftBorder)
			return leftBorder;
		else if (value > rightBorder)
			return rightBorder;
		else
			return value;
	}

	/*
	返回一个值，该值被限定在一个区域内，该区间假设平铺于数轴，该值若超出边界值，则返回该值处于区间内的对应位置。
	value：要求被限制的值
	leftBorder：左边界值
	rightBorder：右边界值
	返回值：被限制后的值
	*/
	inline const float Loop(const float& value, const float& leftBorder, const float& rightBorder);

	//返回较小值
	inline const float Min(const float& a, const float& b);

	//返回较大值
	inline const float Max(const float& a, const float& b);
};

template<typename T, Index size>
struct ArrayFixed
{
public:

	T & operator[](Index ind) { return _t[ind]; }

	T* GetPointer() { return _t; }
private:
	T _t[size];
};

using Matrix4x4 = DirectX::XMMATRIX;
