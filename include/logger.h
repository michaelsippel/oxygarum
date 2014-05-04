/**
 *  include/logger.h
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

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */

#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdio.h>
#include "list.h"

namespace oxygarum {

class Logger;
enum log_type {
	INFO,
	WARNING,
	ERROR
};

class LogData {
	friend class Logger;

	public:
		LogData();
		LogData(enum log_type type_, const char *text_);
		LogData(Logger *parent_, enum log_type type_, const char *text_);
		~LogData();

		char *getTypeString(void);
		char *getPrefixString(void);

	private:
		Logger *parent;
		char prefix_str[256];

		enum log_type type;
		char text[256];
};

class Logger {
	public:
		Logger();
		Logger(char *prefix_);
		Logger(Logger *parent_, char *prefix_);
		~Logger();

		List<LogData> *log_data;
		List<Logger> *sub_loggers;

		Logger *parent;
		char prefix[64];

		void log(enum log_type type, const char *text);
};

};

#endif _LOGGER_H

