#include "stdafx.h"
#include "Transform.h"

Transform2D::Transform2D(const Scale2D & scale, const Rotation2D & rotate, const Translation2D & translation) 
{
	Set(scale, rotate, translation);
}

Transform2D::~Transform2D()
{
}
