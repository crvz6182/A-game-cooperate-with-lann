#pragma once
#include <vector>
#include <map>

using Index = unsigned int;
using Count = unsigned int;
using Size1D = int;
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
};

template<typename T>
class Array
{
private:
	std::vector<T> mVector;
};

template<typename TKey, typename TValue>
class Dictionary
{
private:
	std::map<TKey, TValue> mMap;
};

class Math {
public:

	//构造和析构函数
	Math();
	~Math();

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