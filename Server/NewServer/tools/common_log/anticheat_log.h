#ifndef anticheat_log_h__
#define anticheat_log_h__

#include "common_log.h"

enum anticheat_line_field
{
	ac_time = 0,
	ac_action,
	ac_name,
	ac_level,
	ac_punish_level,
	ac_image_idx,
	ac_answer_idx,
};

enum anticheat_action_type
{
	aca_invalid = 0,
	aca_generate,
	aca_succsss,
	aca_failed,
	aca_kicked,
	aca_started,
};

log_context* anticheat_init(void);
bool anticheat_process_line(int line_idx, log_context* context);
bool anticheat_process_field(int field_idx, int line_idx, const char* field_value, log_context* context);

#endif // anticheat_log_h__
