#ifndef common_log_h__
#define common_log_h__

#define MAX_FIELD_LEN	(1024)
#define POINT_PER_CM	(1LL << 10)

enum ELogField
{
	lfTime = 0,
	lfAreaID,
	lfGroupID,
	lfRoleID,
	lfSceneTempID,
	lfSceneID,
	lfX,
	lfY,
	lfZ,

	lfCount
};

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
	int line_idx;
	int time_value[tfCount];
	int scene_temp_id;

	__int64 x;
	__int64 y;
};

struct log_context;

typedef bool(*process_field_func)(int field_idx, int line_idx, const char* field_value, line_data* ld, log_context* context);
typedef bool(*process_line_func)(int line_idx, const line_data* ld, log_context* context);
typedef bool(*process_over_func)(log_context* context);

struct log_context
{
	process_field_func _field_func;
	process_line_func _line_func;
	process_over_func _over_func;

};

bool load_file(const char* file_name, log_context* context);

#endif // common_log_h__

