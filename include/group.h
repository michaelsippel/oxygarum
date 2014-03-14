/**
 *  include/group.h
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
#ifndef _GROUP_H
#define _GROUP_H

typedef struct group {
  int num_entries;
  struct group_entry *head;
  struct group_entry *current;
} group_t;

typedef struct group_entry {
  void *element;
  
  struct group_entry *prev;
  struct group_entry *next;
} group_entry_t;

group_t *oxygarum_create_group(void);
group_entry_t *oxygarum_group_add(group_t *group, void *element);
void oxygarum_group_remove(group_t *group, group_entry_t *entry);

#endif

