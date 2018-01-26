#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 norm_v;
out vec3 light_v;
out vec3 eye_v;
out vec3 reflect_v;

uniform vec3 lightPosition;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);
	vec3 vecWorldSpace = (transform * vec4(position, 1.0f)).xyz;
	vec3 vecCameraSpace = (view * transform * vec4(position, 1.0f)).xyz;
	vec3 eyedir = vec3(0,0,0) - vecCameraSpace;
	vec3 lightCameraSpace = (view * vec4(lightPosition, 1.0f)).xyz;
	vec3 lightDir = lightCameraSpace + eyedir;
	vec3 normCameraSpace = (view * transform * vec4(normal, 0)).xyz;
	norm_v = normalize(normCameraSpace);
	light_v = normalize(lightDir);
	eye_v = normalize(eyedir);
	reflect_v = reflect(-light_v, norm_v);

	TexCoord = texCoord;
} 