#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in int texIndex; // Not uint: -1 can be No Texture

out vec4 v_Color;
out vec2 v_TexCoord;
flat out int v_TexIndex; // FLAT attribute: shares globally in PRIMITIVE (NO interpolation, same for every vertex in a Triangle)
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
flat in int v_TexIndex; // Indice de la textura utilizada

uniform sampler2D u_Texture[32]; // Texturas
uniform vec4 u_BlendColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

void main()
{
	vec4 texColor = v_Color;
	if ( v_TexIndex != -1 )
		texColor = texture(u_Texture[v_TexIndex], v_TexCoord);
	color = mix(texColor, u_BlendColor, u_BlendColor.w);
};