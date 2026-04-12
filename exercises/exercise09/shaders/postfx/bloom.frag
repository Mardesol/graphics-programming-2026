//Inputs
in vec2 TexCoord;

//Outputs
out vec4 FragColor;

//Uniforms
uniform sampler2D SourceTexture;
uniform vec2 Range;
uniform float Intensity;

void main()
{
	vec3 color = texture(SourceTexture, TexCoord).rgb;

	float luminance = GetLuminance(color);
	// Remap the luminance value to the range uniform: 0 if is less or equal than Range.x, 1 if it is greater or equal than Range.y, and linear values in between.
	float remapLuminance = clamp((luminance - Range.x) / (Range.y - Range.x), 0.0, 1.0);

	FragColor = vec4(color * remapLuminance * Intensity, 1.0);
}
