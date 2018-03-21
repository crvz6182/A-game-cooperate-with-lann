#pragma once

using Unit = float;

struct Point2D {
	Unit x;
	Unit y;
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