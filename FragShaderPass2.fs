uniform mat4 _projectionMatrix;
uniform mat4 _cameraModelViewMatrix;

varying vec4 vec_color;

varying vec3 N;
varying vec3 V;


void main()
{
   vec3 L = normalize(gl_LightSource[0].position.xyz - V);   
   vec3 E = normalize(-V); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   vec3 R = normalize(-reflect(L,N));  
 
   //calculate Ambient Term:  
   vec4 Iamb = vec_color; 
   Iamb = 0.2*clamp(Iamb, 0.0, 1.0);

   //calculate Diffuse Term:  
   vec4 Idiff = vec_color * max(dot(N,L), 0.0);
   Idiff = 0.7*clamp(Idiff, 0.0, 1.0);     
   
   // calculate Specular Term:
   vec4 Ispec = vec_color * pow(max(dot(R,E),0.0),0.3*4.0);
   Ispec = 0.2*clamp(Ispec, 0.0, 1.0); 

   // write Total Color:  
   gl_FragColor = Iamb + Idiff + Ispec; 
}