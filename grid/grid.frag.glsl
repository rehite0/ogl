#version 450@

out vec3 worldpos;
uniform mat4 trans_mat;
uniform vec3 camera_pos;

const vec3 pos[4]=vec3[4](
					vec3( -1.0, +0.0, -1.0),
					vec3( +1.0, +0.0, -1.0),
					vec3( +1.0, +0.0, +1.0),
					vec3( -1.0, +0.0, +1.0),
					);
const int idx[6]=int[6](0,2,1,2,0,3);

void main(){
	int i=idx[gl_VertexID];
	vec4 vpos=vec4(pos[i], 1.0);
	vpos.x+=camera_pos.x;
	vpos.z+=camera_pos.z;
	worldpos=vpos.xyz;
	gl_Position=vpos*trans_mat;
}
