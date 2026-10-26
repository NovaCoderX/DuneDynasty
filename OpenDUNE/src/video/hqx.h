/*
 * Copyright (C) 2003 Maxim Stepin ( maxst@hiend3d.com )
 *
 * Copyright (C) 2010 Cameron Zemek ( grom@zeminvaders.net)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __HQX_H_
#define __HQX_H_


#include <stdint.h>
#include <SDL.h>


void set_palette_luma(uint8_t index, uint16_t entry);

/**
 * hq2x_8to32_rb
 *
 * Scales an 8-bit source array to a 32-bit SDL Surface (2x size).
 * Optimized for Amiga CyberGraphics / Big-Endian ARGB.
 */
void hq2x_8to32_rb(const uint8_t *source_pixels, int source_width, int source_height,
                SDL_Surface *destination_surface, const uint32_t *rgb_palette);



#endif
