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
	//初始化输出
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//获得光照矢量，与光线传播方向相反
	float3 lightV = -L.Direction;

	//添加环境光
	ambient = m.Ambient * L.Ambient;

	//添加漫反射和镜面光
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

	//光照矢量：表面指向光源的矢量
	float3 lightV = L.Position - P;

	//求模（距离）
	float distance = length(lightV);

	if (distance > L.Range) {
		return;
	}

	//单位化光照矢量
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