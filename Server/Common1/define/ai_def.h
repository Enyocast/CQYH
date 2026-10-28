#ifndef _AI_DEF_H_
#define _AI_DEF_H_

/// @file ai_def.h 
/// @brief AI Func List

enum SIGNAL_TYPE
{
    sigInvalid,
    sigSpreadHate,      ///< deliver hate to my tarAITarget, with param indicating deliver to how far
    sigAssistOnce,      ///< attack issuer's target once with assist spell
    sigAssist,          ///< attack issuer's target once with assist spell, and change AI target to issuer's target
    sigHelpSpellHeal,   ///< cast a heal spell to me
    sigHelpSpellHarm,   ///< cast a harm spell to my tarAITarget

    sigUserDefine = 32,      ///< customize signal start

    sigEnd = 64,        ///< max signal type, equal to bits of m_qwSignalBitMask
};


enum AI_PATROL_STYLE
{
    apsInvalid = 0,

    apsLine,         // from head to end, just one shoot
    apsLineBack,     // head to end, end to head, again and again
    apsCircle,       // from head to end, then jump to head, again and again

    apsTotal
};

#endif // _AI_DEF_H_
