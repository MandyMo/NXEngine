matrix ViewMatrix;
matrix ViewProjMatrix;
vector AmbientMtrl;
vector DiffuseMtrl;
vector LightDirection;

vector DiffuseLightIntensity = {1.0f, 1.0f, 1.0f, 1.0f};
vector AmbientLightIntensity = {1.0f, 1.0f, 1.0f, 1.0f};

struct VS_INPUT {
	vector position: POSITION;
	vector normal  : NORMAL;
};

struct VS_OUTPUT {
	vector position: POSITION;
	vector diffuse : COLOR;
};

VS_OUTPUT Main(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = mul(input.position, ViewProjMatrix);
	
	LightDirection.w = 0.0f;
	input.normal.w = 0.0f;
	LightDirection = mul(LightDirection, ViewMatrix);
	input.normal = mul(input.normal, ViewMatrix);
	float s = saturate(dot(LightDirection, input.normal));
	output.diffuse = (AmbientMtrl * AmbientLightIntensity ) + (s * (DiffuseLightIntensity ) * 0.2);
	return output;
}