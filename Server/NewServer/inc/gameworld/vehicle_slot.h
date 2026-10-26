#ifndef _VEHICLE_SLOT_H_
#define _VEHICLE_SLOT_H_

#include "spell_def.h"
#include "spell_slot.h"

#define MAX_VEHICLE_SLOT	4

class CCharacter;

class CVehicleSlot
{
public:
	CVehicleSlot(void);
	virtual ~CVehicleSlot(void);

	void Init(CCharacter* poOwner, BOOL bIsMoveController);

	inline void SetPassenger(CCharacter* poPassenger);

	inline CCharacter* GetPassenger(void);

	inline BOOL IsMoveController(void);

	inline CCharacter* GetOwner(void);

private:
	CCharacter* m_poOwner;
	CCharacter* m_poPassenger;

	CSpellSlot m_SpellSlot[qssSlotCount];

	BOOL m_bMoveController;
};

inline void CVehicleSlot::SetPassenger(CCharacter* poPassenger)
{
	m_poPassenger = poPassenger;
}

inline CCharacter* CVehicleSlot::GetPassenger(void)
{
	return m_poPassenger;
}

inline BOOL CVehicleSlot::IsMoveController(void)
{
	return m_bMoveController;
}

inline CCharacter* CVehicleSlot::GetOwner(void)
{
	return m_poOwner;
}

#endif // _mount_h__
