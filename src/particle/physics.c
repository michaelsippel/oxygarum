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
\n\
in vec3 Pos;\n\
in vec3 Vel;\n\
in float Lifetime; \n\
in float Size;\n\
in vec4 Color;\n\
\n\
out vec3 pos;\n\
out vec3 vel;\n\
out float lifetime;\n\
out float size;\n\
out vec4 color;\n\
void main() {\n\
  vel = Vel;\n\
  pos = Pos;\n\
  lifetime = Lifetime;\n\
  size = Size;\n\
  color = Color;\n\
  gl_Position = gl_Vertex;\n\
}\n";

char *particle_geometryshader = "\
#version 130\n\
#extension GL_ARB_geometry_shader4:enable\n\
\n\
uniform float anim_speed;\n\
uniform float seed;\n\
uniform vec3 gravity_vector;\n\
uniform vec3 gravity_vertex;\n\
uniform float gravity_speed;\n\
\n\
in vec3 Pos;\n\
in vec3 Vel;\n\
in float Lifetime; \n\
in float Size;\n\
in vec4 Color;\n\
\n\
out vec3 pos;\n\
out vec3 vel;\n\
out float lifetime;\n\
out float size;\n\
out vec4 color;\n\
\n\
void main() {\n\
  lifetime = Lifetime - anim_speed;\n\
  if(lifetime > 0) {\
    vel = Vel + gravity_vector * gravity_speed * anim_speed;\n\
    pos = Pos + vel * anim_speed;\n\
    EmitVertex();\n\
  }\n\
}\n";

