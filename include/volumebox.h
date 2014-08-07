/**
 *  include/volumebox.h
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

#ifndef _VOLUMEBOX_H
#define _VOLUMEBOX_H

#include "vector.h"

namespace oxygarum
{

/**
 * @class VolumeBox
 * @brief blub
 */
class VolumeBox
{
    public:
        VolumeBox();
        ~VolumeBox();

        void drawVolumeBox(void);
        void calcVolumeBox(void);

        Vector3D box_size1;
        Vector3D box_size2;
};

};

#endif

