#version 120

varying vec3 position;
varying vec3 normal;
varying vec3 lightvec;

void main(void)
{
  normal = normalize(gl_NormalMatrix * gl_Normal);
  position = vec3(gl_ModelViewMatrix * gl_Vertex);
  lightvec = normalize(gl_LightSource[0].position.xyz - position);  

  gl_FrontColor	= gl_Color;
  gl_TexCoord[0]= gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

