#!/bin/bash
rm -rf Obj/NGP
rm Lib/NGP/Release_NoRTTI/*.a
rm Lib/NGP/Debug_NoRTTI/*.a
rm Lib/NGP/Shipping_NoRTTI/*.a

mkdir -p Obj/NGP/include/sys
touch Obj/NGP/include/sys/types.h

make -j 16 P=NGP C=Release+NoRTTI Lib/NGP/Release_NoRTTI/libgfx.a
make -j 16 P=NGP C=Release+NoRTTI Lib/NGP/Release_NoRTTI/libgfx_as2.a
make -j 16 P=NGP C=Release+NoRTTI Lib/NGP/Release_NoRTTI/libgfx_as3.a

make -j 16 P=NGP C=Debug+NoRTTI Lib/NGP/Debug_NoRTTI/libgfx.a
make -j 16 P=NGP C=Debug+NoRTTI Lib/NGP/Debug_NoRTTI/libgfx_as2.a
make -j 16 P=NGP C=Debug+NoRTTI Lib/NGP/Debug_NoRTTI/libgfx_as3.a

make -j 16 P=NGP C=Shipping+NoRTTI Lib/NGP/Shipping_NoRTTI/libgfx.a
make -j 16 P=NGP C=Shipping+NoRTTI Lib/NGP/Shipping_NoRTTI/libgfx_as2.a
make -j 16 P=NGP C=Shipping+NoRTTI Lib/NGP/Shipping_NoRTTI/libgfx_as3.a

exit
