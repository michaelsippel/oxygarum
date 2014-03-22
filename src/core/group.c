/**
 *  src/core/group.c
 *
 *  (C) Copyright 2014 Michael Sippel
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
#include "group.h"

#include <stdlib.h>

group_t *oxygarum_create_group(void) {
  group_t *group = malloc(sizeof(group_t));
  
  group->num_entries = 0;
  group->head = NULL;
  group->current = NULL;
  
  return group;
}

group_entry_t *oxygarum_group_add(group_t *group, void *element) {
  group_entry_t *entry = malloc(sizeof(group_entry_t));
  
  entry->element = element;
  entry->next = NULL;
  entry->prev = group->current;
  
  if(group->current != NULL) {
    group->current->next = entry;
  }
  group->current = entry;
  if(group->head == NULL) {
    group->head = entry;
  }
  
  group->num_entries++;
  
  return entry;
}

void oxygarum_group_remove(group_t *group, group_entry_t *entry) {
  if(entry->prev != NULL) {
    entry->prev->next = entry->next;
  } else {
    group->head = entry->next;
  }
  
  if(entry->next != NULL) {
    entry->next->prev = entry->prev;
  } else {
    group->current = entry->prev;
  }

  free(entry);
  group->num_entries--;
}

void oxygarum_group_join(group_t *g1, group_t *g2) {
  if(g1 != NULL && g2 != NULL) {
    g1->current->next = g2->head;
    g2->head->prev = g1->current;
  }
}

