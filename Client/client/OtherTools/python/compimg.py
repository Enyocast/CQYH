__author__ = 'dbg'

import os, sys, Image, ImageDraw

srcImg = 'NoiseVolume.bmp'
saveImg = 'T_NoiseVolume.bmp'


srcImg = '2DUI_BarbarianResourceGlobe.bmp'
saveImg = 'T_2DUI_BarbarianResourceGlobe.bmp'

'''
srcIconW = 48
srcIconH = 49
rows = [42, 18]
rowsY = [0, srcIconH]

srcIconWTar = 64
newImgSize = (512, 512)
iconColCount = 8
'''

srcImg = 'NoiseVolume.bmp'
saveImg = 'T_NoiseVolume.bmp'
srcIconW = 128
srcIconH = 128
rows = [128]
rowsY = [0]

srcIconWTar = 128
newImgSize = (2048, 1024)
iconColCount = 16

tarIconIdx = 0



img = Image.open(srcImg)
print img.format, img.size, img.mode

imgNew512 = Image.new('RGB', newImgSize)

tarSpaceX = (srcIconWTar - srcIconW) / 2
tarSpaceY = (srcIconWTar - srcIconH) / 2

#img = Image.open('2DUI_BarbarianResourceGlobe.bmp')

def procRow(i, srcY):
    global tarIconIdx
    global iconColCount
    global imgNew512
    global tarSpaceX
    global tarSpaceY
    global srcIconWTar
    global srcIconW
    global srcIconH
    global img

    srcX = i * srcIconW
    #srcY = 0
    srcRect = (srcX, srcY, srcX + srcIconW, srcY + srcIconH)
    #print img.format, img.size, img.mode
    cpyImg = img.crop(srcRect)

    targXIdx = tarIconIdx % iconColCount
    targYIdx = tarIconIdx / iconColCount

    targX = targXIdx * srcIconWTar + tarSpaceX
    #targX = targX + tarSpaceX
    targY = targYIdx * srcIconWTar + tarSpaceY

    targRect = (targX, targY)

    imgNew512.paste(cpyImg, targRect)
    tarIconIdx = tarIconIdx + 1

    debugDraw = ImageDraw.Draw(imgNew512)
    dbgX = targXIdx * srcIconWTar
    dbgY = targYIdx * srcIconWTar
    targRectD = (dbgX, dbgY, dbgX + srcIconWTar, dbgY + srcIconWTar)
    #debugDraw.text((dbgX, dbgY), str(tarIconIdx - 1))
    #debugDraw.rectangle(targRectD)


    print 'src:', srcRect, ' dest:', targRect, ' targXIdx:', targXIdx, ' targYIdx:', targYIdx, ' dbgRc:', targRectD

for r in range(0, len(rows)):
    for i in range(0, rows[r]):
        procRow(i, rowsY[r])


imgNew512.save(saveImg, 'BMP')