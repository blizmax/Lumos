#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec2 a_TexCoord;

layout(set = 0,binding = 0) uniform UniformBufferObject 
{    
	mat4 u_MVP;
} ubo;

layout(location = 0) out vec2 v_TexCoord;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
	vec4 position = ubo.u_MVP * vec4(a_Position, 1.0);
	gl_Position = position;

	v_TexCoord = a_TexCoord;
}