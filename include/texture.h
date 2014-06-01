/**
 *  include/texture.h
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

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <stdint.h>
#include <GL/gl.h>

#include "list.h"

namespace oxygarum
{

/**
 * @class TextureParameter
 * @brief Parameters for loading textures
 *
 * e.g. texture filters, mipmapping
 */
class TextureParameter
{
    public:
        TextureParameter();
        TextureParameter(GLenum type_, GLenum value_);
        ~TextureParameter();

        GLenum type;
        GLenum value;
};

/**
 * @class Texture
 * @brief Texture class
 */
class Texture
{
    public:
        Texture();
        Texture(unsigned int width_, unsigned int height_, uint8_t *data_);
        Texture(unsigned int width_, unsigned int height_, unsigned int bpp_, uint8_t *data_);
        Texture(unsigned int width_, unsigned int height_, unsigned int bpp_, uint8_t *data_, List<TextureParameter> *params_);
        ~Texture();

        List<TextureParameter> *params;

        void load(void);
        void load(unsigned int width_, unsigned int height_, unsigned int bpp_, uint8_t *data_);
        void bind(void);

        int getWidth(void);
        int getHeight(void);
        int getBpp(void);
        GLenum getFormat(void);
        GLuint getID(void);

    private:
        unsigned int width;
        unsigned int height;
        unsigned int bpp;
        uint8_t *data;
        GLenum format;
        GLuint id;
};

namespace loader
{
Texture *load_texture(const char *path);
};

};

#endif

