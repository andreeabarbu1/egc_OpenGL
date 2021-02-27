#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

out vec3 frag_normal;
out vec2 texcoord;

// 3D noise function
float rand3D(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,121.7272))) * 100758.5453);
}


void main()
{
	// pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;

	if(time >= 0)
		texcoord = vec2(texcoord.x + time / 10, texcoord.y);
	
	vec3 world_pos, world_normal;
    float noise;

	world_pos = (Model * vec4(v_position,1)).xyz;
    world_normal = normalize( mat3(Model) * v_normal);
	frag_normal = v_normal;

	 // choose a displacement amount
    //noise = texture2D(texcoord, vec2(world_pos.z, world_pos.y)).r;
	noise = rand3D(world_pos) ;

	// move the vertex
    vec3 newPosition = v_position + v_normal * noise * 0.25; 
	gl_Position = Projection * View * Model * vec4(newPosition, 1.0);
}
