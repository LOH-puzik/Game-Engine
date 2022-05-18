#version 400

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

out vec2 textureCoord;
out vec3 norm;
out vec3 fragPos;

uniform mat4 MVP;
uniform mat4 model;
uniform float time;

float Ai, Di, Wi, Fi;

void main()
{
	vec3 r = pos;
	Ai = 0.55;
	Di = 3 ;
	Wi = 0.08 ;
	Fi = 0.9 ;
	
	//r.y += 2 * 9 * pow((sin(dot(vec2(0, 1), vec2(r.x, r.z)) * time * 4) + 1) / 2, 2);

	r.y += 2 * Ai * pow((sin(Di * dot(vec2(1, 1), vec2(r.x, r.z)) * Wi + time * Fi) + 1) / 2, 2);

	textureCoord = texCoord;
	fragPos = vec3(model * vec4(r, 1.0f));
	norm = mat3(transpose(inverse(model))) * normals;
	gl_Position = MVP * vec4(r, 1.0f);
}