#pragma once
#include "Math.h"

using Translation2D = Point2D;

namespace {
	Translation2D NoTranslation = Translation2D(0.f, 0.f);
}

using Rotation2D = float;

namespace {
	Rotation2D NoRotation = 0.f;
}

using Scale2D = Point2D;

namespace {
	Scale2D NoScale = Scale2D(1.0f, 1.0f);
}

class Transform2D
{
public:
	Transform2D(const Scale2D& scale = NoScale, const Rotation2D& rotate = NoRotation, const Translation2D& translation = NoTranslation);
	~Transform2D();
	
	void SetScale(const Scale2D& scale) { mScale = scale; }
	void SetRotation(const Rotation2D& rotation) { mRotation = rotation; }
	void SetTranslation(const Translation2D& translation) { mTranslation = translation; }

	void Set(const Scale2D& scale, const Rotation2D& rotate, const Translation2D& translation) { SetScale(scale); SetRotation(rotate); SetTranslation(translation); }

	const Translation2D GetTranslation() const { return mTranslation; }

private:
	Translation2D		mTranslation;
	Rotation2D			mRotation;
	Scale2D				mScale;
};

using Velocity2D = Translation2D;

using AngularVelocity2D = Rotation2D;

using ScaleVelocity2D = Scale2D;

class TransformDerivative
{
	TransformDerivative(const ScaleVelocity2D& scale = NoScale, const AngularVelocity2D& rotate = NoRotation, const Velocity2D& translation = NoTranslation);
	~TransformDerivative() {}

	void SetScaleVelocity(const ScaleVelocity2D& scaleVelocity) { mScaleVelocity = scaleVelocity; }
	void SetRotationVelocity(const AngularVelocity2D& angularVelocity) { mAngularVelocity = angularVelocity; }
	void SetTranslationVelocity(const Velocity2D& velocity) { mVelocity = velocity; }

	void Set(const ScaleVelocity2D& scale, const AngularVelocity2D& rotate, const Velocity2D& translation) { SetScaleVelocity(scale); SetRotationVelocity(rotate); SetTranslationVelocity(translation); }
private:
	Velocity2D				mVelocity;
	AngularVelocity2D	mAngularVelocity;
	ScaleVelocity2D		mScaleVelocity;
};