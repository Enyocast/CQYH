#include "stdafx.h"
#include "common_log.h"
#include "anticheat_log.h"

int main(int argc, char** argv)
{
	log_context* ctx = anticheat_init();

	bool ret = load_file("d:\\log\\anticheat111.txt", ctx);

	return 0;
}