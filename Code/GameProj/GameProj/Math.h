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

	//�������������
	Math();
	~Math();

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