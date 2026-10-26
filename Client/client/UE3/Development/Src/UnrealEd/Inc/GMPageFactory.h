/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __GMPAGEFACTORY_H__
#define __GMPAGEFACTORY_H__

// Forward declarations.
class WxGMPage;
class FGMGame;
class wxNotebook;

/**
 * Factory interface for creating GM pages. Clients register these interfaces
 * to register additional GM page types.
 */
class FGMPageFactory
{
public:
	/**
	 * The constructor registers this factory object with the GM frame.
	 */
	FGMPageFactory();
	virtual ~FGMPageFactory() {}

	/**
	 * Called by the GM frame's constructor to instance pages.
	 */
	virtual WxGMPage *CreatePage(FGMGame *pGame, wxNotebook *pNotebook) const=0;
};

/**
 * Template implementation of FGMPageFactory that probably will handle most cases.
 */
template <class T>
class TGMPageFactory : public FGMPageFactory
{
public:
	/**
	 * Called by the GM frame's constructor to instance pages.
	 */
	virtual WxGMPage *CreatePage(FGMGame *pGame, wxNotebook *pNotebook) const
	{
		return new T(pGame, pNotebook);
	}
};

#endif // __GMPAGEFACTORY_H__
