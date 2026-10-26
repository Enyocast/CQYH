/**************************************************************************

Filename    :   AS3_CodeExecute.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_CodeExecute_H
#define INC_AS3_CodeExecute_H


///////////////////////////////////////////////////////////////////////////////
namespace Scaleform { namespace GFx { namespace AS3 { namespace Abc
{
    ///////////////////////////////////////////////////////////////////////////
    // Forward declaration.
    class Code;
    class OpCodeCallback;

    ///////////////////////////////////////////////////////////////////////////
    // Return *true* if execution is finished completely ...
    /*
    bool ExecuteCode(
        const Code& code, 
        AS3::VM& vm,
        int start_offset = 0
        );
    */
}}}} // namespace Scaleform { namespace GFx { namespace AS3 { namespace Abc {

#endif // INC_AS3_CodeExecute_H
