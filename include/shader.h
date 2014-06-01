/**
 *  include/shader.h
 *
 *  Copyright (C) 2013-2014 Michael Sippel
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

#ifndef _SHADER_H
#define _SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "logger.h"
#include "list.h"

namespace oxygarum
{

class Shader
{
        friend class ShadeProgram;

    public:
        Shader();
        Shader(GLuint type_, const char *source, int len);
        ~Shader();

        void compile(GLuint type_, const char *source, int len);

        static Logger *logger;

    private:
        GLuint type;
        GLuint id;
};

class ShadeProgram
{
    public:
        ShadeProgram();
        ~ShadeProgram();

        void attach(Shader *shader);
        void link(void);
        void use(void);

        GLuint getID(void);

        static Logger *logger;

    private:
        GLuint id;
};

namespace loader
{
Shader *load_shader(GLuint type, const char *path);
};

};

#endif

