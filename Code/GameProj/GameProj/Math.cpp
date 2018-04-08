#include "stdafx.h"
#include "Math.h"

inline const float Math::Loop(const float& value, const float& leftBorder, const float& rightBorder) {
	if (value < leftBorder || value > rightBorder) {
		float tValue = value;
		float tLength = rightBorder - leftBorder;
		if (tValue < leftBorder)
			while (tValue < leftBorder)
				tValue += tLength;
		else
			while (tValue > rightBorder)
				tValue -= tLength;
		return tValue;
	}
	else
		return value;
}

inline const float Math::Min(const float& a, const float& b) {
	return a > b ? b : a;
}

inline const float Math::Max(const float& a, const float& b) {
	return a > b ? a : b;
}