#ifndef _MMOAttriListener_H_
#define _MMOAttriListener_H_

enum AttrListenerType
{
	AttrListenerType_Mine,
	AttrListenerType_OtherPlayer,
	AttrListenerType_Count,
};

class MMOAttrListener
{
public:
	MMOAttrListener(){
		Type = AttrListenerType_Mine;
	};
	virtual ~MMOAttrListener(){};


	virtual INT GetAttribute( INT attrId ) = 0;
	virtual INT GetPkValue() = 0;
	virtual INT GetLevel() = 0;
	virtual INT GetClassId() = 0;
	virtual INT GetFatigue() = 0;
	virtual INT GetPower() = 0;

	AttrListenerType GetType() { return Type; }
protected:
	AttrListenerType Type; 
};


class MMOAttrListener_Mine:public MMOAttrListener
{
public:
	MMOAttrListener_Mine(){ Type = AttrListenerType_Mine; }
	virtual ~MMOAttrListener_Mine(){};

	virtual INT GetAttribute( INT attrId );
	virtual INT GetPkValue();
	virtual INT GetLevel();
	virtual INT GetClassId();
	virtual INT GetFatigue();
	virtual INT GetPower();
};

class MMOAttrListener_OtherPlayer:public MMOAttrListener
{
public:
	MMOAttrListener_OtherPlayer(){ Type = AttrListenerType_OtherPlayer; };
	virtual ~MMOAttrListener_OtherPlayer(){};

	virtual INT GetAttribute( INT attrId );
	virtual INT GetPkValue();
	virtual INT GetLevel();
	virtual INT GetClassId();
	virtual INT GetFatigue();
	virtual INT GetPower();
};

#endif