//Inputs
in vec2 TexCoord;

//Outputs
out vec4 FragColor;

//Uniforms
uniform sampler2D SourceTexture;
uniform float Exposure;
uniform float Contrast;
uniform float HueShift;
uniform float Saturation;
uniform vec3 ColorFilter;
uniform sampler2D BloomTexture;

void main()
{
	vec4 sourceColor = texture(SourceTexture, TexCoord);

	// Add bloom texture to source color before applying exposure (and other post-processing effects)
	sourceColor.rgb = sourceColor.rgb + texture(BloomTexture, TexCoord).rgb;

	// Add Exposure
	vec3 color = vec3(1.0) - exp(-sourceColor.rgb * Exposure);

	// Add Contrast
	color = clamp((color - 0.5) * Contrast + 0.5, 0.0, 1.0);

	// Add Hue Shift
	color = RGBToHSV(color);
	color.x = fract(color.x + HueShift);
	color = HSVToRGB(color);

	// Saturation
	float luminance = GetLuminance(color);
	color = clamp((color - luminance) * Saturation + luminance, 0.0, 1.0);

	// Color Filter
	color = color * ColorFilter;

	FragColor = vec4(color, sourceColor.a);
}
