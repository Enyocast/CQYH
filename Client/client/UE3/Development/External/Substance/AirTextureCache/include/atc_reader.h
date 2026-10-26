/** 
  * @note This file is part of Air UE3 integration
  * @date 2012-03-05
  * @copyright Allegorithmic. All rights reserved. 
  */

#ifndef ATC_API_READER_H
#define ATC_API_READER_H

#include "atc_conf.h"

namespace atc_api
{

class ATC_API_CONV Reader
{
	// PIMPL idiom
	struct Impl;
	Impl * mImpl;

public:
	/**
	  * @brief Open a texture cache for reading.
	  *
	  * @param[in] cacheName The name of the texture cache to create. This is
	  *            the name without any extension (eg: cache and not 
	  *            cache.data.rtc nor cache.hdr.rtc).
	  */
	Reader(const wchar_t* cacheName);

 	/**
 	  * @brief Release all resources associated with this texture cache.
 	  */
	~Reader();

	/**
	  * @brief Grab a mipmap from this texture cache.
	  *
	  * @param[in] textureName The name of the texture to grab the mipmap from (utf8)
	  * @param[in] width The mipmap width.
	  * @param[in] height The mipmap height.
	  * @param[out] dataPtr An already allocated dataSize bytes buffer able to
	  *             receive the mipmap data, in its original format.
	  * @param[in] dataSize The size, in bytes of the mipmap buffer (data 
	  *            parameter).
	  */
	bool getMipMap(
		const char* textureName,
		size_t width,
		size_t height,
		char* dataPtr,
		size_t dataSize);
};

} // namespace atc_api

#endif // ATC_API_READER_H
