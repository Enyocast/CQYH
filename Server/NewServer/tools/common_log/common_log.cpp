#include "stdafx.h"
#include "common_log.h"

bool load_file(const char* file_name, log_context* context)
{
	int field_idx = 0;
	int line = 0;
	int i = 0;
	char field[MAX_FIELD_LEN] = { 0 };

	FILE* fp = fopen(file_name, "rb");
	if (!fp)
		return false;

	if (context->field_func == NULL)
		return false;

	if (context->line_func == NULL)
		return false;

	if (context->end_func == NULL)
		return false;

	while (!feof(fp))
	{
		char c = (char)fgetc(fp);

		switch (c)
		{
		case '\t':
			(*context->field_func)(field_idx, line, field, context);
			field_idx++;
			memset(field, 0, sizeof(field));
			i = 0;
			break;
		case EOF:
		case '\r':
			(*context->field_func)(field_idx, line, field, context);
			field_idx = 0;
			memset(field, 0, sizeof(field));
			i = 0;
			break;
		case '\n':
			(*context->line_func)(line, context);
			line++;
			break;
		default:
			field[i++] = c;
			break;
		}
	}

	(*context->end_func)(context);

	return true;
}
