
#ifndef __ICANVASRENDERABLE_H__
#define __ICANVASRENDERABLE_H__

class ICanvasRenderable
{
public:

	virtual void OnCanvasPostRender(class UCanvas* canvas, FLOAT fDelta) = 0;
};

#endif