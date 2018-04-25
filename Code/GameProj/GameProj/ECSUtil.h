#pragma once


//ECS 公共库
namespace ECSUtil
{
	//组件掩码类型，用于记录实体含有哪些组件
	using ComponentMaskType = int;

	//组件类型
	enum ComponentType
	{
		Component_None = 0,
		Component_Position = 1 << 0,
		Component_Velocity = 1 << 1,
		Component_Appearance = 1 << 2
	};

	//由于模板函数不可以偏特化
	//此处创建ECS公共类用于模板偏特化
	template<typename FirstComponent, typename...RestComponent>
	class ECSUtilLib
	{
	public:
		static const ComponentMaskType GetMaskType()
		{
			return (ECSUtilLib<FirstComponent>::GetMaskType() | ECSUtilLib<RestComponent...>::GetMaskType());
		}
	};

	template<typename OnlyComponent>
	class ECSUtilLib<OnlyComponent>
	{
	public:
		static const ComponentMaskType GetMaskType()
		{
			return OnlyComponent::GetType();
		}
	};

	//模板函数，获取组件对应的掩码
	template<typename FirstComponent, typename...RestComponent>
	const ComponentMaskType GetMaskType()
	{
		return ECSUtilLib<FirstComponent, RestComponent...>::GetMaskType();
	}
}