/**
 *  src/gui/window.c
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
#include <gui.h>
#include <stdlib.h>
/*
oxygarum_window_t *oxygarum_create_window(float width, float height, texture_t *texture) {
  oxygarum_window_t *win = malloc(sizeof(oxygarum_window_t));
  
  win->size.x = width;
  win->size.y = height;
  
  win->material = oxygarum_create_material();
  oxygarum_group_add(win->material, texture, NULL);
  
  int i;
  for(i = 0; i < NUM_WINDOW_VERTICES; i++) {
    win->vertices[i] = malloc(sizeof(vertex2d_t));
  }  
  
  return win;
}

face_t *oxygarum_create_window_part(oxygarum_window_t *win, int part, uv_t *uv_map, float width, float height) {
  vertex_id *v = calloc(4, sizeof(vertex_id));
  v[0] = part*4 + 0;
  v[1] = part*4 + 1;
  v[2] = part*4 + 2;
  v[3] = part*4 + 3;
  
  // calculate X
  switch(part) {
    case OXYGARUM_WINDOW_TOP_LEFT:
    case OXYGARUM_WINDOW_MIDDLE_LEFT:
    case OXYGARUM_WINDOW_BOTTOM_LEFT:
      win->vertices[v[0]]->x = 0;
      break;
    case OXYGARUM_WINDOW_TOP_CENTER:
    case OXYGARUM_WINDOW_MIDDLE_CENTER:
    case OXYGARUM_WINDOW_BOTTOM_CENTER:
      win->vertices[v[0]]->x = (win->size.x - width) / 2;
      break;
    case OXYGARUM_WINDOW_BOTTOM_RIGHT:
    case OXYGARUM_WINDOW_MIDDLE_RIGHT:
    case OXYGARUM_WINDOW_TOP_RIGHT:
      win->vertices[v[0]]->x = win->size.x - width;
  }
  
  // calculate Y
  switch(part) {
    case OXYGARUM_WINDOW_TOP_LEFT:
    case OXYGARUM_WINDOW_TOP_CENTER:
    case OXYGARUM_WINDOW_TOP_RIGHT:
      win->vertices[v[0]]->y = 0;
      break;
    case OXYGARUM_WINDOW_MIDDLE_LEFT:
    case OXYGARUM_WINDOW_MIDDLE_CENTER:
    case OXYGARUM_WINDOW_MIDDLE_RIGHT:
      win->vertices[v[0]]->y = (height - win->size.y) / 2;
      break;
    case OXYGARUM_WINDOW_BOTTOM_LEFT:
    case OXYGARUM_WINDOW_BOTTOM_CENTER:
    case OXYGARUM_WINDOW_BOTTOM_RIGHT:
      win->vertices[v[0]]->y = height - win->size.y;
      break;
  }
  
  win->vertices[v[1]]->x = win->vertices[v[0]]->x + width;
  win->vertices[v[1]]->y = win->vertices[v[0]]->y;
  
  win->vertices[v[2]]->x = win->vertices[v[0]]->x + width;
  win->vertices[v[2]]->y = win->vertices[v[0]]->y - height;
  
  win->vertices[v[3]]->x = win->vertices[v[0]]->x;
  win->vertices[v[3]]->y = win->vertices[v[0]]->y - height; 
  
  win->faces[part] = oxygarum_create_face(4, v, uv_map);
  
  return win->faces[part];
}

object2d_t *oxygarum_create_window_obj(oxygarum_window_t *win) {
  mesh2d_t *mesh = oxygarum_create_mesh2d(NUM_WINDOW_VERTICES, win->vertices, NUM_WINDOW_FACES, win->faces, win->material);
  return win->obj;
}
*/
