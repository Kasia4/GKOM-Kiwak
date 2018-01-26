#version 330 core

in vec2 TexCoord;
in vec3 norm_v;
in vec3 light_v;
in vec3 eye_v;
in vec3 reflect_v;

out vec4 color;

uniform sampler2D Texture0;
uniform	bool iftexture;

uniform float ambientLevel;
uniform vec3 ambientColor;

uniform vec3 lightColor;
uniform float lightPower;

uniform vec4 materialColor;
uniform vec2 textureScale;
uniform float glossiness;
uniform float specularLevel;

void main()
{
	if (iftexture) {
		color = texture(Texture0, TexCoord * textureScale);
	}
	else {
		color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	float cosTheta = clamp( dot(norm_v, light_v), 0, 1); 
	float cosAlpha = clamp( dot(eye_v, reflect_v), 0, 1);

	color = color * ( ambientLevel * vec4(ambientColor, 1.0) +
			lightColor * materialColor * lightPower * (cosTheta + specularLevel * pow(cosAlpha, glossiness)));
			 
}