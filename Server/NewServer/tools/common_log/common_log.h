#ifndef common_log_h__
#define common_log_h__

#define MAX_FIELD_LEN	(1024)
#define POINT_PER_CM	(1LL << 10)

enum ETimeField
{
	tfYear = 0,
	tfMonth,
	tfDay,
	tfHour,
	tfMin,
	tfSec,

	tfCount
};

struct line_data
{
	int time_value[tfCount];
};

struct log_context;

typedef bool (*process_field_func)(int field_idx, int line_idx, const char* field_value, log_context* context);
typedef bool (*process_line_func)(int line_idx, log_context* context);
typedef bool (*process_end_func)(log_context* context);

struct log_context
{
	process_field_func field_func;
	process_line_func line_func;
	process_end_func end_func;

	line_data* ld;
};


bool load_file(const char* file_name, log_context* context);

#endif // common_log_h__

