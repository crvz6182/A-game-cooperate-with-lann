struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Reflect;
};

struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float pad;
};

struct PointLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

	float3 Position;
	float Range;

	float3 Attenuation;
	float pad;
};

struct SpotLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

	float3 Position;
	float Range;

	float3 Direction;
	float Spot;

	float3 Attenuation;
	float pad;
};

void ComputeDirectionalLight(Material m, DirectionalLight L,
	float3 N, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 specular)
{
	//��ʼ�����
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//��ù���ʸ��������ߴ��������෴
	float3 lightV = -L.Direction;

	//��ӻ�����
	ambient = m.Ambient * L.Ambient;

	//���������;����
	float diffuseFactor = dot(lightV, N);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 V = reflect(-lightV, N);
		float specFactor = pow(max(dot(V, toEye), 0.0f), m.Specular.w);
		diffuse = diffuseFactor * m.Diffuse * L.Diffuse;
		specular = specFactor * m.Specular * L.Specular;
	}
}

void ComputePointLight(Material m, PointLight L,
	float3 P, float3 N, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//����ʸ��������ָ���Դ��ʸ��
	float3 lightV = L.Position - P;

	//��ģ�����룩
	float distance = length(lightV);

	if (distance > L.Range) {
		return;
	}

	//��λ������ʸ��
	lightV /= distance;

	ambient = m.Ambient * L.Ambient;

	float diffuseFactor = dot(lightV, N);

	[flatten]
	if (diffuseFactor > 0.0f) {
		float3 V = reflect(-lightV, N);
		float specFactor = pow(max(dot(V, toEye), 0.0f), m.Specular.w);

		diffuse = diffuseFactor * m.Diffuse * L.Diffuse;
		specular = specFactor * m.Specular * L.Specular;
	}

	float attenuation = 1.0f / dot(L.Attenuation, float3(1.0f, distance, distance*distance));

	diffuse *= attenuation;
	specular *= attenuation;
}

void ComputeSpotLight(Material m, SpotLight L,
	float3 P, float3 N, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 specular)
{
	ambient = float4(0.0f, 00.f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightV = L.Position - P;

	float distance = length(lightV);

	if (distance > L.Range) {
		return;
	}

	lightV /= distance;

	ambient = m.Ambient * L.Ambient;
	
	float diffuseFactor = dot(lightV, N);

	[flatten]
	if (diffuseFactor > 0.0f) {
		float3 V = reflect(-lightV, N);
		float specFactor = pow(max(dot(V, toEye), 0.0f), m.Specular.w);

		diffuse = diffuseFactor * m.Diffuse * L.Diffuse;
		specular = specFactor * m.Specular * L.Specular;
	}

	float spot = pow(max(dot(-lightV, L.Direction), 0.0f), L.Spot);

	float attenuation = spot / dot(L.Attenuation, float3(1.0f, distance, distance*distance));

	ambient *= spot;
	diffuse *= attenuation;
	specular *= attenuation;
}