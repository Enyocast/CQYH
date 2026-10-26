#!/bin/bash
rm -rf Obj
rm Lib/MacOS-x86_64/Release_NoRTTI/*.a
rm Lib/MacOS-x86_64/Debug_NoRTTI/*.a
rm Lib/MacOS-x86_64/Shipping_NoRTTI/*.a

make -j 16 P=MacOS C=Release+NoRTTI Lib/MacOS-x86_64/Release_NoRTTI/libgfx.a
make -j 16 P=MacOS C=Release+NoRTTI Lib/MacOS-x86_64/Release_NoRTTI/libgfx_as2.a
make -j 16 P=MacOS C=Release+NoRTTI Lib/MacOS-x86_64/Release_NoRTTI/libgfx_as3.a

make -j 16 P=MacOS C=Debug+NoRTTI Lib/MacOS-x86_64/Debug_NoRTTI/libgfx.a
make -j 16 P=MacOS C=Debug+NoRTTI Lib/MacOS-x86_64/Debug_NoRTTI/libgfx_as2.a
make -j 16 P=MacOS C=Debug+NoRTTI Lib/MacOS-x86_64/Debug_NoRTTI/libgfx_as3.a

make -j 16 P=MacOS C=Shipping+NoRTTI Lib/MacOS-x86_64/Shipping_NoRTTI/libgfx.a
make -j 16 P=MacOS C=Shipping+NoRTTI Lib/MacOS-x86_64/Shipping_NoRTTI/libgfx_as2.a
make -j 16 P=MacOS C=Shipping+NoRTTI Lib/MacOS-x86_64/Shipping_NoRTTI/libgfx_as3.a
exit
