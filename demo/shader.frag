#version 120

varying vec3 position;
varying vec3 normal;
varying vec3 lightvec;

uniform sampler2D Texture0; // diffuse
uniform sampler2D Texture1; // normal
uniform sampler2D Texture2; // emit

vec2 uShift = vec2(0.01, 0);
const int gaussRadius = 11;
const float gaussFilter[gaussRadius] = float[gaussRadius](
	0.0402,0.0623,0.0877,0.1120,0.1297,0.1362,0.1297,0.1120,0.0877,0.0623,0.0402
);

void main(void) {
  vec3 Eye = normalize(-position);
  vec2 TexCoord = vec2(gl_TexCoord[0]);
  
  // emit (with blur)
  vec2 texCoord = gl_TexCoord[0].xy - float(int(gaussRadius/2)) * uShift;
  vec3 emit = vec3(0.0, 0.0, 0.0); 
  for (int i=0; i<gaussRadius; ++i) { 
    emit += gaussFilter[i] * texture2D(Texture2, texCoord).xyz;
    texCoord += uShift;
  }
  
  // normal
  vec3 q0 = dFdx(Eye.xyz);
  vec3 q1 = dFdy(Eye.xyz);
  vec2 st0 = dFdx(TexCoord.st);
  vec2 st1 = dFdy(TexCoord.st);
  
  vec3 S = normalize( q0 * st1.t - q1 * st0.t);
  vec3 T = normalize(-q0 * st1.s + q1 * st0.s);
  
  mat3 M = mat3(-T, -S, normal);
  vec3 nor = normalize(M * (vec3(texture2D(Texture1, TexCoord)) - vec3(0.5, 0.5, 0.5)));
  
  // lighting
  vec3 Reflected = normalize(reflect(-lightvec, nor)); 
  vec4 ambient  = gl_LightSource[0].ambient  * gl_FrontMaterial.ambient;
  vec4 diffuse  = gl_LightSource[0].diffuse  * gl_FrontMaterial.diffuse  * max(dot(nor, lightvec), 0.0);
  vec4 specular = gl_LightSource[0].specular * gl_FrontMaterial.specular * pow(max(dot(Reflected, Eye), 0.0), gl_FrontMaterial.shininess);
  
  gl_FragColor = (gl_FrontLightModelProduct.sceneColor + diffuse+specular + vec4(emit, 1.0)) * texture2D(Texture0, TexCoord);
}

