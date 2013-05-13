/**
 *  src/oxygarum.c
 *
 *  (C) Copyright 2012 Michael Sippel
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
#include <GL/glut.h>
#include "opengl.h"

#include "oxygarum.h"

#ifdef __WIN32__
#include <windows.h>
void usleep(unsigned int usec) {
  HANDLE timer = NULL;
  LARGE_INTEGER sleepTime;
  sleepTime.QuadPart = usec * 10000;
  
  timer = CreateWaitableTimer (NULL, TRUE, NULL);
  SetWaitableTimer(timer, &sleepTime, 0, NULL, NULL, 0);
  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);
}
#endif

void init_oxygarum(int argc, char **argv) {
  oxygarum_init_opengl(argc, argv);
}

