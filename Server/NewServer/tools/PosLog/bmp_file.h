#ifndef bmp_file_h__
#define bmp_file_h__

#pragma pack(push, 1)

struct bmp_file_header
{
	unsigned short _type;
	unsigned long _file_size;
	unsigned short _reserve1;
	unsigned short _reserve2;
	unsigned long _off_bits;
};

struct bmp_info_header
{
	unsigned long _size;
	long _width;
	long _height;
	unsigned short _planes;
	unsigned short _bit_count;
	unsigned long _bit_compression;
	unsigned long _size_image;
	long _x_pels_per_meter;
	long _y_pels_per_meter;
	unsigned long _clr_used;
	unsigned long _clr_important;
};

struct bmp_rgb
{
	unsigned char _b;
	unsigned char _g;
	unsigned char _r;
};

struct bmp_file_context
{
	FILE* _fp;
	bmp_file_header _file_header;
	bmp_info_header _info_header;
	bmp_rgb* _rgb_data;
};

#pragma pack(pop)

bool load_bmp(const char* file_name, bmp_file_header* file_header, bmp_info_header* info_header);

bool bmp_prepare_file(const char* file_name, bmp_file_context* context);
bool bmp_write_header(bmp_file_context* context);
bool bmp_write_color(const bmp_rgb* clr, bmp_file_context* context);
bool bmp_write_color(bmp_file_context* context);
bool bmp_write_over(bmp_file_context* context);


#endif // bmp_file_h__
