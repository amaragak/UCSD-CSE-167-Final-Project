uniform mat4 _projectionMatrix;
uniform mat4 _cameraModelViewMatrix;

varying vec4 vec_color;

varying vec3 N;
varying vec3 V;

void main()
{
	gl_Position = _projectionMatrix*_cameraModelViewMatrix*gl_Vertex;
	vec_color = gl_Color;
	V = vec3(_projectionMatrix*_cameraModelViewMatrix*gl_Vertex);
	N = normalize(gl_NormalMatrix*gl_Normal);
}

