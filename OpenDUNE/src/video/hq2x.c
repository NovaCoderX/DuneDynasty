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

#include "hqx.h"

static uint16_t palette_luma[256];

void set_palette_luma(uint8_t index, uint16_t entry) {
    palette_luma[index] = entry;
}

static inline int is_bright_edge(uint8_t e,
                                 uint8_t b, uint8_t d,
                                 uint8_t f, uint8_t h)
{   
    // Average neighbour brightness
    int le = palette_luma[e];
    int ln = (palette_luma[b] +
              palette_luma[d] +
              palette_luma[f] +
              palette_luma[h]) >> 2;
              
    // Threshold tuned for white text preservation
    return (le - ln) > 160;
}

void hq2x_8to32_rb(const uint8_t *source_pixels, int width, int height,
                   SDL_Surface *dest_surface, const uint32_t *rgb_palette) {
    
    int x, y;
    int dst_pitch_px = dest_surface->pitch >> 2;
    uint32_t *dp = (uint32_t *)dest_surface->pixels;
    const uint8_t *sp = source_pixels;

    for (y = 0; y < height; y++) {
        // Use pointers to avoid the extra "cache" copy loop
        const uint8_t* prev_line = (y > 0) ? sp - width : sp;
        const uint8_t* curr_line = sp;
        const uint8_t* next_line = (y < height - 1) ? sp + width : sp;

        uint32_t* dst_line1 = dp;
        uint32_t* dst_line2 = dp + dst_pitch_px;

        // Handle first pixel of the row (x=0) to remove the 'if (x > 0)' from the inner loop
        {
            uint8_t e = curr_line[0];
            uint8_t b = prev_line[0];
            uint8_t f = (width > 1) ? curr_line[1] : e;
            uint8_t h = next_line[0];
            uint8_t d = e; // Left clamp

            uint32_t p[4];
            if (b != h && d != f) {
                p[0] = rgb_palette[(d == b) ? d : e];
                p[1] = rgb_palette[(b == f) ? f : e];
                p[2] = rgb_palette[(d == h) ? d : e];
                p[3] = rgb_palette[(h == f) ? f : e];
            } else {
                uint32_t ce = rgb_palette[e];
                p[0] = p[1] = p[2] = p[3] = ce;
            }
            dst_line1[0] = p[0]; dst_line1[1] = p[1];
            dst_line2[0] = p[2]; dst_line2[1] = p[3];
        }

        // Inner loop: Optimized for the bulk of the scanline
        for (x = 1; x < width - 1; x++) {
            uint8_t e = curr_line[x];
            uint8_t b = prev_line[x];
            uint8_t d = curr_line[x-1];
            uint8_t f = curr_line[x+1];
            uint8_t h = next_line[x];
        
            int x2 = x << 1;
            
            uint32_t ce = rgb_palette[e];
        
            // The rest of your existing xBR logic...
            if (is_bright_edge(e, b, d, f, h))
            {
                // Preserve sharp text by expanding center pixel
                dst_line1[x2]     = ce;
                dst_line1[x2 + 1] = ce;
                dst_line2[x2]     = ce;
                dst_line2[x2 + 1] = ce;
            } else if (b != h && d != f) {
                dst_line1[x2]     = rgb_palette[(d == b) ? d : e];
                dst_line1[x2 + 1] = rgb_palette[(b == f) ? f : e];
                dst_line2[x2]     = rgb_palette[(d == h) ? d : e];
                dst_line2[x2 + 1] = rgb_palette[(h == f) ? f : e];
            } else {
                uint32_t ce = rgb_palette[e];
                dst_line1[x2]     = ce;
                dst_line1[x2 + 1] = ce;
                dst_line2[x2]     = ce;
                dst_line2[x2 + 1] = ce;
            }
        }

        // Handle last pixel of the row (x = width - 1)
        if (width > 1) {
            int x = width - 1;
            uint8_t e = curr_line[x];
            uint8_t b = prev_line[x];
            uint8_t d = curr_line[x-1];
            uint8_t f = e; // Right clamp
            uint8_t h = next_line[x];

            int x2 = x << 1;
            if (b != h && d != f) {
                dst_line1[x2]     = rgb_palette[(d == b) ? d : e];
                dst_line1[x2 + 1] = rgb_palette[(b == f) ? f : e];
                dst_line2[x2]     = rgb_palette[(d == h) ? d : e];
                dst_line2[x2 + 1] = rgb_palette[(h == f) ? f : e];
            } else {
                uint32_t ce = rgb_palette[e];
                dst_line1[x2] = ce; dst_line1[x2+1] = ce;
                dst_line2[x2] = ce; dst_line2[x2+1] = ce;
            }
        }

        sp += width;
        dp += (dst_pitch_px << 1);
    }
}

