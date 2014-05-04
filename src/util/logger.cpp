/**
 *  src/util/logger.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "list.h"
#include "logger.h"

namespace oxygarum {

Logger::Logger() {
	this->log_data = new List<LogData>();
	this->sub_loggers = new List<Logger>();
	this->parent = NULL;
}

Logger::Logger(char *prefix_) {
	this->generate_prefix_str(prefix_);
	this->log_data = new List<LogData>();
	this->sub_loggers = new List<Logger>();
	this->parent = NULL;
}

Logger::Logger(Logger *parent_, char *prefix_) {
	parent_->sub_loggers->add(parent_);
	this->parent = parent_;

	this->generate_prefix_str(prefix_);
	this->log_data = new List<LogData>();
	this->sub_loggers = new List<Logger>();
}

Logger::~Logger() {
}

void Logger::generate_prefix_str(char *prefix_) {
	strcpy(this->prefix, prefix_);

	if(this->parent != NULL) {
		strcpy(this->prefix_str, this->parent->prefix_str);
		strcat(this->prefix_str, "/");
	}
	strcat(this->prefix_str, prefix_);
}

void Logger::log(enum log_type type, const char *text, ...) {
	char buffer[256];
	va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

	LogData *data = new LogData(this, type, buffer);
	this->log_data->add(data);

	printf("[%s] %s: %s\n", data->getTypeString(), this->prefix_str, data->text);
}

LogData::LogData() {
}

LogData::LogData(enum log_type type_, const char *text_)
: type(type_) {
	strcpy(this->text, text_);
	this->parent = NULL;
}

LogData::LogData(Logger *parent_, enum log_type type_, const char *text_)
: parent(parent_), type(type_) {
	strcpy(this->text, text_);
}

LogData::~LogData() {
}

char *LogData::getTypeString(void) {
	char *type_str;
	switch(this->type) {
		case INFO:
			type_str = "INFO";
			break;
		case WARNING:
			type_str = "WARNING";
			break;
		case ERROR:
			type_str = "ERROR";
			break;
	}

	return type_str;
}

char *LogData::getPrefixString(void) {
	return (char*) &this->parent->prefix_str;
}

};

