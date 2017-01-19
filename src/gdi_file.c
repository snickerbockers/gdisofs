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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

#include "gdi_file.h"

/* enforce sane limits */
#define MAX_TRACKS 16
#define MAX_TRACK_FIELDS 16

void parse_gdi(gdi_info *outp, char const *path) {
    long file_sz;

    FILE *stream = fopen(path, "r");

    if (fseek(stream, 0, SEEK_END) != 0)
        err(1, "While loading gdi file \"%s\"", path);

    if ((file_sz = ftell(stream)) < 0)
        err(1, "While loading gdi file \"%s\"", path);

    if (fseek(stream, 0, SEEK_SET) != 0)
        err(1, "While loading gdi file \"%s\"", path);

    /* room to append a terminator at the end just in case */
    long buf_sz = file_sz + 1;
    char *buf = (char*)g_malloc(buf_sz);

    if (fread(buf, sizeof(char), file_sz, stream) != file_sz)
        errx(1, "Failed to read from gdi file \"%s\"", path);
    buf[buf_sz - 1] = '\0';

    char **lines = g_strsplit_set(buf, "\n", MAX_TRACKS);

    if (!lines[0])
        errx(1, "Malformed gdi file \"%s\"\n", path);

    unsigned n_tracks = atoi(lines[0]);
    if (n_tracks > MAX_TRACKS) {
        errx(1, "Malformed gdi file \"%s\": too many tracks (%u)\n",
             path, n_tracks);
    }

    gdi_track *tracks = (gdi_track*)g_malloc(sizeof(gdi_track) * n_tracks);

    char *gdi_dir = g_path_get_dirname(path);

    unsigned track_no;
    for (track_no = 1; track_no <= n_tracks; track_no++) {
        gdi_track *cur_track = tracks + (track_no - 1);
        char **track_info = g_strsplit_set(lines[track_no], " \t",
                                           MAX_TRACK_FIELDS);

        /* maybe it's legal for them to be out of order, IDK... */
        if (!(track_info[0] && (atoi(track_info[0]) == track_no))) {
            errx(1, "Malformed gdi file \"%s\": missing track %d\n",
                 path, track_no);
        }

        if (!track_info[1] || !track_info[2] ||
            !track_info[3] || !track_info[4]) {
            errx(1, "Malformed gdi file \"%s\": track %u corrupted\n",
                 path, track_no);
        }

        cur_track->lba_start = atoi(track_info[1]);
        cur_track->ctrl = atoi(track_info[2]);
        cur_track->sector_size = atoi(track_info[3]);
        cur_track->path = g_build_filename(gdi_dir, track_info[4], NULL);

        g_strfreev(track_info);
    }

    outp->n_tracks = n_tracks;
    outp->tracks = tracks;

    g_free(gdi_dir);
}

void cleanup_gdi(gdi_info *info) {
    unsigned track_no;

    for (track_no = 1; track_no <= info->n_tracks; track_no++) {
        gdi_track *cur_track = info->tracks + (track_no - 1);
        g_free(cur_track->path);
    }

    free(info->tracks);
    info->tracks = NULL;
    info->n_tracks = 0;
}
