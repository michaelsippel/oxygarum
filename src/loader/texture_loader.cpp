/**
 *  src/loader/texture_loader.cpp
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"

namespace oxygarum {
namespace loader {

Texture *load_texture(const char *path) {
	SDL_Surface *surface = IMG_Load(path);
	unsigned int width = surface->w;
	unsigned int height = surface->h;
	unsigned int bpp = surface->format->BytesPerPixel;
	uint8_t *data = (uint8_t*) surface->pixels;

	// flip image
	unsigned int i,j,k;
	uint8_t tmp;
	#define SWAP(a,b) {tmp = a; a = b; b = tmp;}
	for(i = 0; i < (height / 2); i++) {
		for(j = 0; j < width * bpp;  j += bpp) {
			for(k = 0; k < bpp; k++) {
				SWAP(data[(i * width * bpp) + j + k],
				data[((height - i - 1) * width * bpp) + j + k]);
			}
		}
	}

	return new Texture(width, height, bpp, data);
}

};
};

