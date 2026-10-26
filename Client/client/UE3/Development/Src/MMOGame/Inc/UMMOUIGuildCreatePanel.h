#ifndef _UMMOUIGUILDCREATEPANEL_H_
#define _UMMOUIGUILDCREATEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildCreatePanel();
void UpdateGuildCreatePanel();
void CreateGuild(const FString& guildName, const FString& guildAnnounce);

#endif