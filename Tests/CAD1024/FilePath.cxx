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

#include "FilePath.hxx"

#include <stdio.h>

struct
{
    CHAR FilePath[MAX_PATH];
    CHAR Parameters[MAX_PATH];
} State;

LPCSTR MakeNameParams(LPCSTR params)
{
    sprintf_s(State.Parameters, MAX_PATH - 1, params);

    CHAR* src = NULL;
    CHAR* dst = NULL;

    for (src = dst = State.Parameters; *src != NULL; src++)
    {
        *dst = *src;

        if (*dst != ' ' && *dst != ':') { dst++; }
    }

    *dst = NULL;

    return State.Parameters;
}

LPCSTR MakeFileName(LPCSTR name, LPCSTR ext, LPCSTR params)
{
    sprintf_s(State.FilePath, MAX_PATH - 1, "%s%s.%s", name, MakeNameParams(params), ext);

    return State.FilePath;
}