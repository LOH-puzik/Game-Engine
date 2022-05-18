#version 400

in vec2 textureCoord;
in vec3 norm;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture2;

void main()
{
    fragColor = vec4(1, 0.917, 0.823, 1.0f);
    fragColor = fragColor * texture(texture2, textureCoord);
}