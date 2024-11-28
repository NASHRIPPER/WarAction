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

#include <Bink.h>
#include <RendererModule.Basic.hxx>
#include <Sound.hxx>

#define BINKSURFACEINVALID  (-1)

typedef enum BinkVideoResult
{
    BINKVIDEORESULT_CONTINUE    = 0,
    BINKVIDEORESULT_COMPLETED   = 1,
    BINKVIDEORESULT_2           = 2, // TODO
    BINKVIDEORESULT_FORCE_DWORD = 0x7FFFFFFF
} BINKVIDEORESULT, * BINKVIDEORESULTPTR;

BOOL InitializeBink(LPCSTR name, RENDERERMODULESTATECONTAINERPTR renderer, SOUNDPTR sound, CONST U32 max, CONST U32 frames);
BINKVIDEORESULT PlayBinkVideo(VOID);
BOOL ShowBinkFrame(VOID);
BOOL ReleaseBink(VOID);