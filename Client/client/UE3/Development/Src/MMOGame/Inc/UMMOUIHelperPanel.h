#ifndef _UMMOUIHELPERPANEL_H_
#define _UMMOUIHELPERPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);

void UpdateHelperList(INT base, INT sub);
void UpdateHelperDetail(INT base, INT sub);
void UpdateHelperPos();

void ShowHelperPanel(const FString& panelName);

#endif