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

#define MAX_CONTROL_COMMAND_ITEMS_COUNT 256

typedef struct ControlCommand
{
    U32             Command;
    U32             Action;
    U32             Parameter1;
    U32             Parameter2;
} CONTROLCOMMAND, * CONTROLCOMMANDPTR;

typedef struct ControlCommandStateModuleContainer
{
    CONTROLCOMMAND  Items[MAX_CONTROL_COMMAND_ITEMS_COUNT]; // 0x10059bcc
    S32             WriteIndex;                             // 0x1005abcc
    S32             ReadIndex;                              // 0x1005abd0
} CONTROLCOMMANDSTATEMODULECONTAINER, * CONTROLCOMMANDSTATEMODULECONTAINERPTR;

EXTERN CONTROLCOMMANDSTATEMODULECONTAINER CommandControlState;

BOOL DequeueControlCommand(CONST U32 command);
BOOL DequeueControlCommand(CONTROLCOMMANDPTR command, CONST BOOL remove);
CONTROLCOMMANDPTR DequeueControlCommand(CONST BOOL remove);
VOID EnqueueControlCommand(CONST U32 command, CONST U32 action, CONST U32 param1, CONST U32 param2);

#define CONTROLCOMMAND_TEXT_CONTROL     0x23232323 /* #### */ /* TODO NAME */
#define CONTROLCOMMAND_VIDEO_CONTROL    0x236D6C74 /* #mlt */
#define CONTROLCOMMAND_KBD              0x2f4b4244 /* /KBD */
#define CONTROLCOMMAND_UTF              0x2F555446 /* /UTF */

#define CONTROLCOMMANDACTION_2          0x02 /* TODO */
#define CONTROLCOMMANDACTION_4          0x04 /* TODO */
#define CONTROLCOMMANDACTION_8          0x08 /* TODO */
#define CONTROLCOMMANDACTION_10         0x10 /* TODO */