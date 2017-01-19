################################################################################
#
#    gdisofs - fuse module for mounting filesystems from Sega Dreamcast GD-ROMs
#    Copyright (C) 2017 snickerbockers
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
################################################################################

cmake_minimum_required(VERSION 2.6)
project(gdisofs)
set(gdisofs_VERSION_MAJOR 0)
set(gdisofs_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/src/config.h"
  )

# TODO: figure out how to run `pkg-config --cflags fuse glib-2.0` from cmake
set(CMAKE_C_FLAGS "-D_FILE_OFFSET_BITS=64  -I/usr/include/fuse -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -Werror -Wall")

set(gdisofs_sources   "${PROJECT_SOURCE_DIR}/src/gdi_file.h"
                    "${PROJECT_SOURCE_DIR}/src/isofs.h"
                    "${PROJECT_SOURCE_DIR}/linux/iso_fs.h"
                    "${PROJECT_SOURCE_DIR}/linux/rock.h"
                    "${PROJECT_SOURCE_DIR}/src/fuseiso.c"
                    "${PROJECT_SOURCE_DIR}/src/isofs.c"
                    "${PROJECT_SOURCE_DIR}/src/gdi_file.c")

include_directories("${PROJECT_SOURCE_DIR}"
                    "${PROJECT_BINARY_DIR}/src/")

add_executable(gdisofs ${gdisofs_sources})
target_link_libraries(gdisofs glib-2.0 fuse z)
