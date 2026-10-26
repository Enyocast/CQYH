#ifndef _DOODAD_DEF_H_
#define _DOODAD_DEF_H_

// tolua_begin

#define MAX_DOODAD_LEVEL        (60)

enum DOODAD_TYPE
{
    dtInvalid,

    dtResource,
    dtTreasureBox,
    dtQuest,
    dtDestrucible,
    dtCorpse,

    dtTotal
};

enum DOODAD_SUB_TYPE
{
    dstInvalid,

    // dtResource
    dstOre,
    dstHerb,
    dstFishingPool,

    // dtQuest
    dstItem,
    dstBook,

    dstTotal
};
// tolua_end

#endif  // _DOODAD_DEF_H_