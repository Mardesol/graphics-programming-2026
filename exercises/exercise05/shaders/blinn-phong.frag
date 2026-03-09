#version 330 core

in vec3 WorldPosition;
in vec3 WorldNormal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 Color;
uniform sampler2D ColorTexture;
uniform vec3 AmbientColor;
uniform float AmbientReflection;
uniform float DiffuseReflection;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform float SpecularReflection;
uniform float SpecularExponent;
uniform vec3 CameraPosition;

vec3 GetAmbientReflection(vec3 I_a, float K_a, vec3 color)
{
    vec3 R_ambient = (I_a * K_a * color);
    return R_ambient;
}

vec3 GetDiffuseReflection(vec3 I_light, float K_d, vec3 color, vec3 L, vec3 N)
{
    float NL = max(dot(N, L), 0);
    vec3 R_diffuse = (I_light * K_d * color) * NL;
    return R_diffuse;
}

vec3 GetSpecularReflection(vec3 I_light, float K_s, vec3 N, vec3 H)
{
    float NH = max(dot(N, H), 0);
    float NH_exp = pow(NH, SpecularExponent);
    vec3 R_specular = I_light * K_s * NH_exp;
    return R_specular;
}

vec3 GetBlinnPhongReflection(vec3 I_a, float K_a, vec3 color, vec3 L, vec3 N, vec3 H)
{
    vec3 R_ambient  = GetAmbientReflection(I_a, K_a, color);
    vec3 R_diffuse  = GetDiffuseReflection(LightColor, DiffuseReflection, color, L, N);
    vec3 R_specular = GetSpecularReflection(LightColor, SpecularReflection, N, H);
    vec3 BlinnPhongReflection = R_ambient + R_diffuse + R_specular;
    
    return BlinnPhongReflection;
}

void main()
{
	vec3 color = texture(ColorTexture, TexCoord).rgb * Color.rgb;

    vec3 L = normalize(LightPosition - WorldPosition);
    vec3 N = normalize(WorldNormal);
    vec3 V = normalize(CameraPosition - WorldPosition);
    vec3 H = normalize(L + V);

    vec3 reflection = GetBlinnPhongReflection(AmbientColor, AmbientReflection, color, L, N, H);
    FragColor = vec4(reflection, 1.0);
}
