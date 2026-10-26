#include "stdafx.h"
#include "anticheat_log.h"
#include <map>
#include <string>

struct anticheat_map_data
{
	char role_name[32];
	int action_time;
	int generate_time;
	int action_type;
};

struct anticheat_line_data
{
	line_data default_line_data;
	anticheat_map_data mp_data;
};

struct anticheat_log_context
{
	log_context default_log_context;
	int start_count;
	int generate_count;
	int success_count;
	int failed_count;
	int timeout_count;
	std::map<std::string, anticheat_map_data> result_map;
	anticheat_line_data ld;
};


anticheat_log_context anticheat_ctx;

bool anticheat_process_field(int field_idx, int line_idx, const char* field_value, log_context* context)
{
	anticheat_log_context* ac_log_context = (anticheat_log_context*)context;
	anticheat_line_data* ac_line_data = (anticheat_line_data*)context->ld;

	if (field_idx == ac_time)
	{
		int tm_fld_idx = 0;
		char val[8] = { 0 };
		int k = 0;

		for (int i = 0; i <= strlen(field_value); i++)
		{
			if (field_value[i] == ' ' || field_value[i] == '-' || field_value[i] == ':' || field_value[i] == 0)
			{
				ac_line_data->default_line_data.time_value[tm_fld_idx] = atoi(val);
				memset(val, 0, sizeof(val));
				tm_fld_idx++;
				k = 0;
			}
			else
				val[k++] = field_value[i];
		}
	}
	else if (field_idx == ac_name)
	{
		strncpy(ac_line_data->mp_data.role_name, field_value, 32);
	}
	else if (field_idx == ac_action)
	{
		ac_line_data->mp_data.action_time = 3600 * ac_line_data->default_line_data.time_value[tfHour] + 60 * ac_line_data->default_line_data.time_value[tfMin] + ac_line_data->default_line_data.time_value[tfSec];

		if (strcmp(field_value, "generate") == 0)
		{
			ac_log_context->generate_count++;
			ac_line_data->mp_data.generate_time = 3600 * ac_line_data->default_line_data.time_value[tfHour] + 60 * ac_line_data->default_line_data.time_value[tfMin] + ac_line_data->default_line_data.time_value[tfSec];
			ac_line_data->mp_data.action_type = aca_generate;
		}
		else if (strcmp(field_value, "success") == 0)
		{
			ac_log_context->success_count++;
			ac_line_data->mp_data.action_type = aca_succsss;
		}
		else if (strcmp(field_value, "failed") == 0)
		{
			ac_log_context->failed_count++;
			ac_line_data->mp_data.action_type = aca_failed;
		}
		else if (strcmp(field_value, "kick") == 0)
		{
			ac_log_context->failed_count++;
			ac_line_data->mp_data.action_type = aca_failed;
		}
		else if (strcmp(field_value, "start") == 0)
		{
			ac_log_context->start_count++;
			ac_line_data->mp_data.action_type = aca_started;
		}
	}

	return true;
}

bool anticheat_process_line(int line_idx, log_context* context)
{
	anticheat_log_context* ac_log_context = (anticheat_log_context*)context;
	anticheat_line_data* ac_line_data = (anticheat_line_data*)context->ld;

	{
		std::map<std::string, anticheat_map_data>::iterator itr = ac_log_context->result_map.find(ac_line_data->mp_data.role_name);
		if(itr == ac_log_context->result_map.end())
		{
			if (ac_line_data->mp_data.action_type != aca_generate)
				return false;

			return ac_log_context->result_map.insert(std::make_pair(std::string(ac_line_data->mp_data.role_name), ac_line_data->mp_data)).second;
		}
		else
		{
			anticheat_map_data& rld = itr->second;

			if (ac_line_data->mp_data.action_type == aca_failed && ac_line_data->mp_data.action_time - rld.generate_time >= 600)
				ac_log_context->timeout_count++;

			ac_log_context->result_map.erase(itr);
		}
	}

	memset(ac_line_data, 0, sizeof(anticheat_line_data));

	return true;
}

bool anticheat_end_func(log_context* context)
{
	anticheat_log_context* ctx = (anticheat_log_context*)context;

	printf("process end, start: %d, generate: %d, success: %d, failed: %d include timeout: %d", ctx->start_count, ctx->generate_count, ctx->success_count, ctx->failed_count, ctx->timeout_count);

	return true;
}

log_context* anticheat_init(void)
{
	memset(&anticheat_ctx.default_log_context, 0, sizeof(log_context));
	memset(&anticheat_ctx.ld, 0, sizeof(anticheat_line_data));
	anticheat_ctx.generate_count = 0;
	anticheat_ctx.success_count = 0;
	anticheat_ctx.failed_count = 0;
	anticheat_ctx.timeout_count = 0;

	anticheat_ctx.default_log_context.ld = (line_data*)&anticheat_ctx.ld;
	anticheat_ctx.default_log_context.field_func = anticheat_process_field;
	anticheat_ctx.default_log_context.line_func = anticheat_process_line;
	anticheat_ctx.default_log_context.end_func = anticheat_end_func;

	return (log_context*)&anticheat_ctx;
}

