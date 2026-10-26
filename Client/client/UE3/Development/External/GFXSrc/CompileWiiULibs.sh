#!/bin/bash
rm -rf Obj/WiiU
rm Lib/WiiU/Release/*.a
rm Lib/WiiU/Debug/*.a
rm Lib/WiiU/Shipping/*.a

mkdir -p Obj/WiiU/include/sys
touch Obj/WiiU/include/sys/types.h

make -j 16 P=WiiU C=Release Lib/WiiU/Release/libgfx.a
make -j 16 P=WiiU C=Release Lib/WiiU/Release/libgfx_as2.a
make -j 16 P=WiiU C=Release Lib/WiiU/Release/libgfx_as3.a
make -j 16 P=WiiU C=Release Lib/WiiU/Release/libgfxsound_null.a

make -j 16 P=WiiU C=Debug Lib/WiiU/Debug/libgfx.a
make -j 16 P=WiiU C=Debug Lib/WiiU/Debug/libgfx_as2.a
make -j 16 P=WiiU C=Debug Lib/WiiU/Debug/libgfx_as3.a
make -j 16 P=WiiU C=Debug Lib/WiiU/Debug/libgfxsound_null.a

make -j 16 P=WiiU C=Shipping Lib/WiiU/Shipping/libgfx.a
make -j 16 P=WiiU C=Shipping Lib/WiiU/Shipping/libgfx_as2.a
make -j 16 P=WiiU C=Shipping Lib/WiiU/Shipping/libgfx_as3.a
make -j 16 P=WiiU C=Shipping Lib/WiiU/Shipping/libgfxsound_null.a

exit
