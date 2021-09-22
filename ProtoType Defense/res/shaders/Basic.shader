#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 v_Color;
out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0f);
	v_Color = color;
	v_TexCoord = texCoord;
};


#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;	// Coge la variable de otro shader

uniform sampler2D u_Texture[32]; // Texturas
uniform vec4 u_BlendColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
uniform int u_TexIndex = 0;

void main()
{
	vec4 texColor = v_Color;
	if ( u_TexIndex != -1 )
		texColor = texture(u_Texture[u_TexIndex], v_TexCoord);
	// Mezcla el filtro Blend tal que solo afecta a la textura PNG, si alpha = 0 --> no textura, no blendea
	color = mix(texColor, u_BlendColor, u_BlendColor.w * texColor.w);
};