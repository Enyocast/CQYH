@echo off
REM
REM Copyright 2005-2011 Intel Corporation.  All Rights Reserved.
REM
REM The source code contained or described herein and all documents related
REM to the source code ("Material") are owned by Intel Corporation or its
REM suppliers or licensors.  Title to the Material remains with Intel
REM Corporation or its suppliers and licensors.  The Material is protected
REM by worldwide copyright laws and treaty provisions.  No part of the
REM Material may be used, copied, reproduced, modified, published, uploaded,
REM posted, transmitted, distributed, or disclosed in any way without
REM Intel's prior express written permission.
REM
REM No license under any patent, copyright, trade secret or other
REM intellectual property right is granted to or conferred upon you by
REM disclosure or delivery of the Materials, either expressly, by
REM implication, inducement, estoppel or otherwise.  Any license under such
REM intellectual property rights must be express and approved by Intel in
REM writing.
REM

:: Getting parameters
if ("%1") == ("") goto error
if ("%2") == ("") goto error
if ("%3") == ("") goto error
set arch=%1
if ("%2") == ("debug") set postfix=_debug
set output_dir=%3

:: Optional 4th parameter to set install root
if ("%4") NEQ ("") set TBB30_INSTALL_DIR=%4
:: Actually we can set install root by ourselves
if ("%TBB30_INSTALL_DIR%") == ("") set TBB30_INSTALL_DIR=%~d0%~p0..\..\

:: Getting vs folders in case vc_mt binaries are not provided
if ("%VS80COMNTOOLS%")  NEQ ("") set vc_dir=vc8
if ("%VS90COMNTOOLS%")  NEQ ("") set vc_dir=vc9
if ("%VS100COMNTOOLS%") NEQ ("") set vc_dir=vc10

:: Are we standalone/oss or inside compiler?
if exist "%TBB30_INSTALL_DIR%\bin\%arch%\vc8\tbb%postfix%.dll" set interim_path=bin\%arch%
if exist "%TBB30_INSTALL_DIR%\..\redist\%arch%\tbb\vc8\tbb%postfix%.dll" set interim_path=..\redist\%arch%\tbb
if ("%interim_path%") == ("") goto error

:: Do we provide vc_mt binaries?
if exist "%TBB30_INSTALL_DIR%\%interim_path%\vc_mt\tbb%postfix%.dll" set vc_dir=vc_mt
if ("%vc_dir%") == ("") goto error

:: We know everything we wanted and there are no errors
:: Copying binaries

copy "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbb%postfix%.dll" "%output_dir%"
copy "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbb%postfix%.pdb" "%output_dir%"
copy "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbbmalloc%postfix%.dll" "%output_dir%"
copy "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbbmalloc%postfix%.pdb" "%output_dir%"
if exist "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbb_preview%postfix%.dll" copy "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbb_preview%postfix%.dll" "%output_dir%"
if exist "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbb_preview%postfix%.pdb" copy "%TBB30_INSTALL_DIR%\%interim_path%\%vc_dir%\tbb_preview%postfix%.pdb" "%output_dir%"

goto end
:error
echo Error occured in libraries copying during post-build step.
exit /B 1

:end
exit /B 0

