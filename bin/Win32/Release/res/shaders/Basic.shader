#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0f);
	v_Color = color;
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
};


#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;	// Coge la variable de otro shader
in float v_TexIndex; // Indice de la textura utilizada

uniform sampler2D u_Texture[32]; // Texturas

void main()
{
	int texIndex = int(v_TexIndex);
	vec4 texColor = v_Color;
	if ( texIndex != -1 )
		texColor = texture(u_Texture[texIndex], v_TexCoord);
	color = texColor;
};