/*=============================================================================
	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __GMGAMEEXTENSION_H__
#define __GMGAMEEXTENSION_H__

// Forward declarations.
class FGMGame;
class FGMGameExtension;

/**
 * An abstract extension interface for communicating with the game. This allows other
 * systems to extend GM's game interface without having to add it to the core interface.
 */
class FGMGameExtension
{
public:
	explicit FGMGameExtension(FGMGame& InGame)
		:	Game( InGame )
	{
	}

	virtual ~FGMGameExtension()
	{
	}

	FGMGame& GetGame() const
	{ 
		return Game;
	}

private:
	FGMGame& Game;
};

/**
 * Factory interface for creating GM game extensions
 */
class FGMGameExtensionFactory
{
public:
	virtual ~FGMGameExtensionFactory() {}

	virtual FGMGameExtension* CreateExtension(FGMGame* InGame) const=0;
};

#define GM_EXTENSION_TYPE(ExtensionInterface) \
	G##ExtensionInterface##_Factory

#define DECLARE_GM_EXTENSION_FACTORY(ExtensionInterface) \
class ExtensionInterface##_Factory : public FGMGameExtensionFactory \
{ \
public: \
	virtual FGMGameExtension* CreateExtension(FGMGame* InGame) const; \
}; \
extern ExtensionInterface##_Factory  G##ExtensionInterface##_Factory;

#define BEGIN_IMPLEMENT_GM_EXTENSION_FACTORY(ExtensionInterface) \
	ExtensionInterface##_Factory  G##ExtensionInterface##_Factory; \
	FGMGameExtension* ExtensionInterface##_Factory :: CreateExtension(FGMGame* InGame) const \
	{ \

// @todo: actually make this return the right extension implementation based on the passed in GM game interface
#define PC_GM_EXTENSION(Implementation) return new Implementation(*InGame);
#define XBOX_GM_EXTENSION(Implementation)
#define PS3_GM_EXTENSION(Implementation)

#define END_IMPLEMENT_GM_EXTENSION_FACTORY(ExtensionInterface) \
	}

#endif // __GMGAMEEXTENSION_H__
