/**
 *  include/list.h
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

#ifndef _LIST_H
#define _LIST_H

/**
 * @class List
 */
template <typename T>
class List {
	public:
		List();
		~List();

		ListEntry<T> *add(T *element);
		ListEntry<T> *add(T *element, char *name);
		void add(ListEntry<T> *entry);
		void remove(ListEntry<T> *entry);
		void join(List<T> *list);

		ListEntry<T> *getEntry(char *name);
		int getSize(void);

	private:
		ListEntry<T> *head;
		ListEntry<T> *current;
		int size;
};

/**
 * @class ListEntry
 */
template <typename T>
class ListEntry {
	friend class List;

	public:
		ListEntry();
		ListEntry(T *element_);
		ListEntry(T *element_, char *name_);
		~ListEntry();

		T *element;
		char name[256];

	private:
		ListEntry<T> *prev;
		ListEntry<T> *next;
};

#endif

