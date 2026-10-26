
#ifndef _MMOPowerPart_H_
#define _MMOPowerPart_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"

#define HEAVEN_OPEN_LEVEL 10

class MMOPowerPart
{
public:

	MMOPowerPart();
	virtual ~MMOPowerPart(){};

	virtual void RecountPower();
	virtual INT GetPow();
	void Reset(){ _initial = FALSE; }
protected:

	INT _partPower;
	BOOL _initial;
	
};


class MMOPowerPart_Heaven: public MMOPowerPart
{
public:

	virtual void RecountPower();
		
protected:

};

class MMOPowerPart_Suit: public MMOPowerPart
{
public:

	virtual void RecountPower();

protected:

};

class MMOPowerPart_Title: public MMOPowerPart
{
public:

	virtual void RecountPower();

protected:

};

class MMOPowerPart_EquipSlotEnhance: public MMOPowerPart
{
public:

	virtual void RecountPower();

protected:

};


class MMOPowerPart_EquippedAll: public MMOPowerPart
{
public:

	virtual void RecountPower();

protected:

};

class MMOPowerPart_CharacterBase: public MMOPowerPart
{
public:

	virtual void RecountPower();

protected:

};

class MMOPowerPart_Skill: public MMOPowerPart
{
public:

	virtual void RecountPower();

protected:

};

#endif