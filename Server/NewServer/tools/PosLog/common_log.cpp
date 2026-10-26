#include "stdafx.h"
#include "common_log.h"

static bool process_field(int field_idx, int line_idx, const char* field_value, line_data* ld, log_context* context)
{
	if (field_idx == lfSceneTempID)
		ld->scene_temp_id = atoi(field_value);

	if (field_idx == lfTime)
	{
		int tm_fld_idx = 0;
		char val[8] = { 0 };
		int k = 0;

		for (int i = 0; i <= strlen(field_value); i++)
		{
			if (field_value[i] == ' ' || field_value[i] == '-' || field_value[i] == ':' || field_value[i] == 0)
			{
				ld->time_value[tm_fld_idx] = atoi(val);
				memset(val, 0, sizeof(val));
				tm_fld_idx++;
				k = 0;
			}
			else
				val[k++] = field_value[i];
		}
	}

	if (field_idx == lfX)
	{
		ld->x = atoi(field_value);
	}

	if (field_idx == lfY)
	{
		ld->y = atoi(field_value);
	}

	return true;
}

static void convert_pos(__int64 x, __int64 y)
{

}

static bool process_line(int line_idx, const line_data* ld, log_context* context)
{
	return false;
}

bool load_file(const char* file_name, log_context* context)
{
	int field_idx = 0;
	int line = 0;
	int i = 0;
	char field[MAX_FIELD_LEN] = { 0 };
	line_data ld = { 0 };

	if (context->_field_func == NULL || context->_line_func == NULL)
		return false;

	FILE* fp = fopen(file_name, "rb");
	if (!fp)
		return false;

	while (!feof(fp))
	{
		char c = (char)fgetc(fp);

		if (c == '\n')
		{
			if (line > 0)
				(*context->_line_func)(line, &ld, context);
			line++;
			memset(&ld, 0, sizeof(ld));
			ld.line_idx = line;
		}
		else if (line > 0)
		{
			switch (c)
			{
			case '\t':
				(*context->_field_func)(field_idx, line, field, &ld, context);
				field_idx++;
				memset(field, 0, sizeof(field));
				i = 0;
				break;
			case EOF:
			case '\r':
				(*context->_field_func)(field_idx, line, field, &ld, context);
				field_idx = 0;
				memset(field, 0, sizeof(field));
				i = 0;
				break;
			case '\n':
				break;
			default:
				field[i++] = c;
				break;
			}
		}
	}

	(*context->_over_func)(context);

	return true;
}
