/**
 *  src/core/list.cpp
 *
 *  Copyright (C) 2014 Michael Sippel
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#include <stdlib.h>
#include <string.h>

#include "list.h"

List::List() {
	this->head = NULL;
	this->current = NULL;
}

List::~List() {
}

void List::add(ListEntry<T> *entry) {
	entry->next = NULL;
	entry->prev = this->current;

	if(this->current != NULL) {
		this->current->next = entry;
	}
	this->current = entry;
	if(group->head == NULL) {
		group->head = entry;
	}

	this->size++;
}

void List::add(T *element) {
	ListEntry<T> *entry = new ListEntry(element)<T>;
	this->add(entry);

	return entry;
}

void List::add(T *element, char *name) {
	ListEntry<T> *entry = new ListEntry(element, name)<T>;
	this->add(entry);

	return entry;
}

void List::remove(ListEntry<T> *entry) {
	if(entry->prev != NULL) {
		entry->prev->next = entry->next;
	} else {
		this->head = entry->next;
	}

	if(entry->next != NULL) {
		entry->next->prev = entry->prev;
	} else {
		this->current = entry->prev;
	}	
}

void List::join(List<T> *list) {
	if(list != NULL) {
		if(this->head == NULL) {
			this->head = list->head;
			this->current = list->current;
		} else {
			if(this->current != NULL) {
				this->current->next = list->head;
			}

			if(list->head != NULL) {
				list->head->prev = this->current;
			}
		}
	}
}

ListEntry<T> *List::get_entry(char *name) {
	ListEntry *entry = this->head;
	while(entry != NULL) {
		if(strcmp(entry->name, name) == 0) {
			return entry;
		}
		entry = entry->next;
	}

	return NULL;
}

ListEntry::ListEntry() {
	this->element = NULL;
	strcpy(this->name, "");
	this->prev = NULL;
	this->next = NULL;
}

ListEntry::ListEntry(T *element_)
: element(element_) {
	strcpy(this->name, "");
	this->prev = NULL;
	this->next = NULL;
}

ListEntry::ListEntry(T *element_, char *name_)
: element(element_) {
	strcpy(this->name, name_);
	this->prev = NULL;
	this->next = NULL;
}

ListEntry::~ListEntry() {
}

