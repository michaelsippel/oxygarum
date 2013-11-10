/**
 *  src/particle/physics.c
 *
 *  (C) Copyright 2013 Michael Sippel
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

char *particle_vertexshader = "\
#version 130\n\
attribute vec3 Pos;\n\
attribute vec3 Vel;\n\
attribute float Lifetime; \n\
attribute float Size;\n\
attribute vec4 Color;\n\
\n\
varying vec3 pos;\n\
varying vec3 vel;\n\
varying float lifetime;\n\
varying float size;\n\
varying vec4 color;\n\
void main() {\n\
  pos = Pos;\n\
  vel = Vel;\n\
  lifetime = Lifetime;\n\
  size = Size;\n\
  color = Color;\n\
  gl_Position = vec4(1,1,1,1);\n\
}\n";

char *particle_geometryshader = "\
#version 130\n\
#extension GL_EXT_geometry_shader4 : enable\n\
\n\
uniform float anim_speed;\n\
uniform float seed;\n\
uniform vec3 gravity_vector;\n\
uniform vec3 gravity_vertex;\n\
uniform float gravity_speed;\n\
\n\
varying vec3 pos;\n\
varying vec3 vel;\n\
varying float lifetime;\n\
varying float size;\n\
varying vec4 color;\n\
\n\
void main() {\n\
  lifetime -= 1;\n\
  if(lifetime > 0) {\
    vel += gravity_vector * gravity_speed * anim_speed;\n\
    pos += new_vel * anim_speed;\n\
    EmitVertex();\n\
  }\n\
}\n";

