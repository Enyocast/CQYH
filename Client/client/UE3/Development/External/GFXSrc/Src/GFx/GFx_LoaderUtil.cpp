/**************************************************************************

Filename    :   GFx_LoaderUtil.cpp
Content     :   Eval License Reading code 
Created     :   March 16, 2012
Authors     :

Copyright   :   Copyright 2012 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

// Validate Check - Eval License Reader code was moved here so that 
// other engines could more easily replace it with their own validation checking code.

**************************************************************************/

#include "GFxConfig.h"

void    GFx_ValidateEvaluation();

// Internal GFC Evaluation License Reader
#ifdef SF_BUILD_EVAL
#define SF_EVAL(x) GFx_##x
#define SF_LIB_NAME_S "GFx"
#include "GFCValidateEval.cpp"
#else
void    GFx_ValidateEvaluation() { }
#endif
