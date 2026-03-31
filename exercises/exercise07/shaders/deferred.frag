//Inputs
in vec2 TexCoord;

//Outputs
out vec4 FragColor;

//Uniforms
uniform sampler2D DepthTexture;
uniform sampler2D AlbedoTexture;
uniform sampler2D NormalTexture;
uniform sampler2D OthersTexture;
uniform mat4 InvViewMatrix;
uniform mat4 InvProjMatrix;

void main()
{
	// Information we have been recovering
	vec3 albedo = texture(AlbedoTexture, TexCoord).rgb;
	vec3 normal = GetImplicitNormal(texture(NormalTexture, TexCoord).xy);
	vec3 viewPos = ReconstructViewPosition(DepthTexture, TexCoord, InvProjMatrix);
	vec4 others = texture(OthersTexture, TexCoord);

	// Compute view vector in view space
	vec3 viewDir = GetDirection(viewPos, vec3(0, 0, 0));

	// Transform the normal from view space to world space
	viewPos = (InvViewMatrix * vec4(viewPos, 1)).xyz;
	normal = (InvViewMatrix * vec4(normal, 0)).xyz;
	viewDir = (InvViewMatrix * vec4(viewDir, 0)).xyz;

	// Our custom struct
	SurfaceData data;
	data.normal = normal;
	data.reflectionColor = albedo;
	data.ambientReflectance = others.x;
	data.diffuseReflectance = others.y;
	data.specularReflectance = others.z;
	data.specularExponent = others.w;

	vec3 lighting = ComputeLighting(viewPos, data, viewDir, true);

	FragColor = vec4(lighting, 1.0f);	
}
