/**
 *  src/material/texture.c
 *
 *  (C) Copyright 2013 Michael Sippel
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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <GL/gl.h>

#include "texture.h"

static texture_id texture_counter = 0;

uint8_t *oxygarum_load_png(const char *path, unsigned int *width, unsigned int *height) {
  int i;
  png_byte header[8];
  
  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    return NULL;
  }
  
  fread(header, 1, 8, fp);
  
  if (png_sig_cmp(header, 0, 8)) {
    fclose(fp);
    return NULL;
  }
  
  png_struct *pngp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (pngp == NULL) {
    fclose(fp);
    return NULL;
  }
  
  png_info *infop = png_create_info_struct(pngp);
  if (infop == NULL) {
    png_destroy_read_struct(&pngp, NULL, NULL);
    fclose(fp);
    return NULL;
  }
  
  png_info *endip = png_create_info_struct(pngp);
  if (endip == NULL) {
    png_destroy_read_struct(&pngp, &infop, NULL);
    fclose(fp);
    return NULL;
  }
  
  if (setjmp(png_jmpbuf(pngp))) {
    png_destroy_read_struct(&pngp, &infop, &endip);
    fclose(fp);
    return NULL;
  }
  
  png_init_io(pngp, fp);
  png_set_sig_bytes(pngp, 8);
  png_read_info(pngp, infop);
  
  int depth, type;
  png_uint_32 w, h;
  png_get_IHDR(pngp, infop, &w, &h, &depth, &type, NULL, NULL, NULL);
  
  if (width != NULL) {
    *width = w;
  }

  if (height != NULL) {
    *height = h;
  }  

  png_read_update_info(pngp, infop);
  int rowsz = png_get_rowbytes(pngp, infop);
  
  uint8_t *img_data = (uint8_t *)malloc(rowsz * h);
  if (img_data == NULL) {
    png_destroy_read_struct(&pngp, &infop, &endip);
    fclose(fp);
    return NULL;
  }
  
  png_byte **rowps = (png_byte **)malloc(h * sizeof(*rowps));
  if (rowps == NULL) {
    free(img_data);
    png_destroy_read_struct(&pngp, &infop, &endip);
    fclose(fp);
    return NULL;
  }
  
  for (i = 0; i < (int)h; i++) {
    rowps[h - 1 - i] = (png_byte *)img_data + i * rowsz;
  }
  
  png_read_image(pngp, rowps);
  
  png_destroy_read_struct(&pngp, &infop, &endip);
  free(rowps);
  fclose(fp);
  
  return img_data;
}

texture_t *oxygarum_load_texture(const char *path) {
  texture_t *tex = (texture_t*) malloc(sizeof(texture_t));
  
  tex->data = oxygarum_load_png(path, &tex->width, &tex->height);
  
  glGenTextures(1, &tex->id);
  printf("tex-id = 0x%x\n", tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
  
  return tex;
}

