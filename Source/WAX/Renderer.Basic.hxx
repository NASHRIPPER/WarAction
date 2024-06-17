/*
Copyright (c) 2024 Americus Maximus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "Basic.hxx"

#ifdef _WIN64
#define ACTIVATE_MODERN_MODE                TRUE
#endif

#define ACTIVE_TRUE_COLOR_MODE              TRUE

#define DEFAULT_SCREEN_COLOR_MASK           0xFFFF

#define BLACK_PIXEL                         0x0000
#define MAGENTA_PIXEL                       0xF81F
#define WHITE_PIXEL                         0xFFFF

#define RGB565_TO_RGB888(rgb565)            \
  ((((rgb565 & 0xF800) << 8) & 0xFF0000)    \
   | (((rgb565 & 0x07E0) << 5) & 0x00FF00)  \
   | (((rgb565 & 0x001F) << 3) & 0x0000FF))

#define SHADEPIXEL(pixel, mask) ((pixel & mask) >> 1)

typedef U16 PIXEL;
typedef U32 DOUBLEPIXEL;