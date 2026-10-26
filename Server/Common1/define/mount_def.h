#ifndef _MOUNT_DEF_H_
#define _MOUNT_DEF_H_

enum MOUNT_QUALITY_TYPE
{
	mqtInvalid = -1,

	mqtCommon,
	mqtUncommon,
	mqtRare,
	mqtEpic,

	mqtTotal
};

enum MOUNT_FRAG_TYPE
{
	mftInvalid = -1,

	mftFragA,
	mftFragB,
	mftFragC,

	mftCount,
};

#endif // _mount_def_h__
