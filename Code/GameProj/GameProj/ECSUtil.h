#pragma once


//ECS ������
namespace ECSUtil
{
	//����������ͣ����ڼ�¼ʵ�庬����Щ���
	using ComponentMaskType = int;

	//�������
	enum ComponentType
	{
		Component_None = 0,
		Component_Position = 1 << 0,
		Component_Velocity = 1 << 1,
		Component_Appearance = 1 << 2
	};

	//����ģ�庯��������ƫ�ػ�
	//�˴�����ECS����������ģ��ƫ�ػ�
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

	//ģ�庯������ȡ�����Ӧ������
	template<typename FirstComponent, typename...RestComponent>
	const ComponentMaskType GetMaskType()
	{
		return ECSUtilLib<FirstComponent, RestComponent...>::GetMaskType();
	}
}