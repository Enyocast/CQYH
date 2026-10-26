#include "stdafx.h"
#include "bmp_file.h"

bool load_bmp(const char* file_name, bmp_file_header* file_header, bmp_info_header* info_header)
{
	FILE* fp = fopen(file_name, "rb");
	if (!fp)
		return false;

	if (fread(file_header, sizeof(char), sizeof(bmp_file_header), fp) != sizeof(bmp_file_header))
		return false;

	if (fread(info_header, sizeof(char), sizeof(bmp_info_header), fp) != sizeof(bmp_info_header))
		return false;

	return true;
}

bool bmp_prepare_file(const char* file_name, bmp_file_context* context)
{
	memset(context, 0, sizeof(bmp_file_context));

	context->_fp = fopen(file_name, "wb");
	if (!context->_fp)
		return false;

	return true;
}

bool bmp_write_header(bmp_file_context* context)
{
	if (!context->_fp)
		return false;

	if (fwrite(&context->_file_header, sizeof(char), sizeof(bmp_file_header), context->_fp) != sizeof(bmp_file_header))
		return false;

	if (fwrite(&context->_info_header, sizeof(char), sizeof(bmp_info_header), context->_fp) != sizeof(bmp_info_header))
		return false;

	return true;
}

bool bmp_write_color(const bmp_rgb* clr, bmp_file_context* context)
{
	if (!context->_fp)
		return false;

	if (fwrite(clr, sizeof(char), sizeof(bmp_rgb), context->_fp) != sizeof(bmp_rgb))
		return false;

	return true;
}

bool bmp_write_color(bmp_file_context* context)
{
	if (!context->_fp)
		return false;

	if (!context->_rgb_data)
		return false;

	if (fwrite(context->_rgb_data, sizeof(char), context->_info_header._size_image, context->_fp) != context->_info_header._size_image)
		return false;

	return true;

}

bool bmp_write_over(bmp_file_context* context)
{
	if (!context->_fp)
		return false;

	fclose(context->_fp);

	return true;
}
