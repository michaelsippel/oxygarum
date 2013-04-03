/**
 *  src/object.c
 *
 *  (C) Copyright 2012 Michael Sippel
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
#include <stdlib.h>

#include "vertex.h"
#include "face.h"
#include "object.h"

object_t *oxygarum_create_object(unsigned int num, face_t **faces) {
  object_t *object = malloc(sizeof(object_t));
  
  object->face_counter = num;
  object->faces = faces;
  
  return object;
}

void oxygarum_display_object(object_t *object) {
  int i;
  for(i = 0; i < object->face_counter; i++) {
    oxygarum_display_face(object->faces[i]);
  }
}
