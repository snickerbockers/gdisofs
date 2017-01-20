/***************************************************************************
 *   Copyright (C) 2017 snickerbockers                                     *
 *   chimerasaurusrex@gmail.com                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef GDI_FILE_H_
#define GDI_FILE_H_

#include <stdint.h>

#define GDI_DATA_TRACK 3

#define GDI_SECONDARY_DATA_TRACK 5

typedef struct _gdi_track {
    char *path;
    unsigned lba_start;    // block address offset
    unsigned ctrl;         // ???
    unsigned sector_size;  // sector size, typically (but not always) 2352
} gdi_track;

typedef struct _gdi_info {
    unsigned n_tracks;

    gdi_track *tracks;
} gdi_info;

void parse_gdi(gdi_info *outp, char const *path);

#endif
