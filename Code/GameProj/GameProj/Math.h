#pragma once
#include <vector>
#include <map>

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

template<typename T>
class Array
{
public:
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
private:
	std::vector<T> mVector;
};

template<typename TKey, typename TValue>
class Dictionary
{
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
	����һ��ֵ����ֵ���޶���һ�������ڣ���ֵ�������߽�ֵ���򷵻�������ӽ��ı߽�ֵ��
	value��Ҫ�����Ƶ�ֵ
	leftBorder����߽�ֵ
	rightBorder���ұ߽�ֵ
	����ֵ�������ƺ��ֵ
	*/
	inline static const float Clamp(const float& value, const float& leftBorder, const float& rightBorder);

	/*
	����һ��ֵ����ֵ���޶���һ�������ڣ����������ƽ�������ᣬ��ֵ�������߽�ֵ���򷵻ظ�ֵ���������ڵĶ�Ӧλ�á�
	value��Ҫ�����Ƶ�ֵ
	leftBorder����߽�ֵ
	rightBorder���ұ߽�ֵ
	����ֵ�������ƺ��ֵ
	*/
	inline static const float Loop(const float& value, const float& leftBorder, const float& rightBorder);

	//���ؽ�Сֵ
	inline static const float Min(const float& a, const float& b);

	//���ؽϴ�ֵ
	inline static const float Max(const float& a, const float& b);
};