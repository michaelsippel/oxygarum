/**
 *  src/particle/physics.c
 *
 *  (C) Copyright 2013-2014 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

char *particle_vertexshader =
"\
#version 120\n\
\n\
attribute vec3 Pos;\n\
attribute vec3 Vel;\n\
attribute float Lifetime; \n\
attribute float Size;\n\
attribute vec4 Color;\n\
attribute float Seed;\n\
\n\
varying vec3 pos;\n\
varying vec3 vel;\n\
varying float lifetime;\n\
varying float size;\n\
varying vec4 color;\n\
varying float seed;\n\
\n\
uniform sampler1D rand_tex;\n\
uniform float aspeed;\n\
uniform vec3 gvector;\n\
uniform vec3 gvertex;\n\
uniform float gspeed;\n\
\n\
float rand_1D(float min, float max) {\n\
  float diff = max - min;\n\
  float rand = min + float(texture1D(rand_tex, seed)) * diff;\n\
  seed += 0.0123;\n\
  return rand;\n\
}\n\
vec3 rand_3D(vec3 min, vec3 max) {\n\
  vec3 diff = max - min;\n\
  vec3 rand = min + vec3(texture1D(rand_tex, seed)) * diff;\n\
  seed += 0.0123;\n\
  return rand;\n\
}\n\
vec4 rand_4D(vec4 min, vec4 max) {\n\
  vec4 diff = max - min;\n\
  vec4 rand = min + texture1D(rand_tex, seed) * diff;\n\
  seed += 0.0123;\n\
  return rand;\n\
}\n\
\n\
vec3 vel_min = vec3(-0.01, 0, -0.01);\n\
vec3 vel_max = vec3( 0.01, 0,  0.01);\n\
vec3 pos_min = vec3(-0.1, 0, -0.1);\n\
vec3 pos_max = vec3( 0.1, 0,  0.1);\n\
vec4 col_min = vec4(1,0,0,1);\n\
vec4 col_max = vec4(1,1,0,1);\n\
float life_min = 100;\n\
float life_max = 500;\n\
\n\
void main() {\n\
  lifetime = Lifetime;\n\
  lifetime -= aspeed;\n\
  seed = Seed + 0.00234;\n\
  if(lifetime > 0) { // calculate\n\
    vel = Vel;\n\
    vel += gvector * 0.01;\n\
    pos = Pos + vel;\n\
    size = Size;\n\
    color = Color;\n\
  } else { // respawn\n\
    vel = rand_3D(vel_min, vel_max);\n\
    pos = rand_3D(pos_min, pos_max);\n\
    size = Size;\n\
    color = rand_4D(col_min, col_max);\n\
    lifetime = rand_1D(life_min, life_max);\n\
  }\n\
  gl_Position = gl_Vertex;\n\
}\n";

