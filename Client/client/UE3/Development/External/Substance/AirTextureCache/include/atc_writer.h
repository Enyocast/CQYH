/** 
  * @note This file is part of Air UE3 integration
  * @date 2012-03-05
  * @copyright Allegorithmic. All rights reserved. 
  */

#ifndef ATC_API_WRITER_H
#define ATC_API_WRITER_H

#include "atc_conf.h"
#include "atc_mipdata.h"
#include "atc_textureformats.h"

#include <vector>

namespace atc_api
{

class ATC_API_CONV Writer
{
public:
	/**
	  * @brief Create a new texture cache, able to store a bunch of textures.
	  *
	  * @param[in] cacheName The name of the texture cache to create. This is
	  *            the name without any extension (eg: cache and not 
	  *            cache.data.rtc nor cache.hdr.rtc)
	  * @param[in] split Should the texture cache be split in small
	  *            chunks instead of one big chunk. This is useful for patching
	  *            and avoid to rewrite a big file each time, just for one file
	  *            sometimes.
	  */
	Writer(const wchar_t * cacheName, bool split);

	/**
	  * @brief Release all resources associated with this texture cache.
	  *
	  * This will write the header file to the disk, and flush all pending
	  * IO. If this call is omitted, you get a memory leak, and you never
	  * finalize your texture cache, which makes it unusable.
	  */
	~Writer();

	/**
	  * @brief Write a new texture in the texture cache.
	  *
	  * @param[in] textureName The name of the texture to add (utf8)
	  * @param[in] textureUid The uid of the texture
	  * @param[in] textureName The name of the parent instance (utf8)
	  * @param[in] width0 The level 0 mipmap width.
	  * @param[in] height0 The level 0 mipmap height.
	  * @param[in] format The texture image format in use for this texture.
	  *
	  * @return true on success, false otherwise.
	  *
	  * @warning This is not thread-safe.
	  *
	  * @pre The texture should not already exist in the texture cache
	  * @pre Width and height should be power of 2
	  * @pre There should be at least one mipmap in the mipDataArray
	  * @pre The format should be valid
	  */
	bool addTexture(
		const char* textureName,
		const unsigned int textureUid,
		const size_t width0,
		const size_t height0,
		const TextureFormat format,
		MipDataArray& mips, 
		const char* instanceName,
		const char* packageName);

	/**
	  * @brief Register a Substance Package (sbsar)
	  * @param[in] objectName The package UE3 object URL (null terminated utf8 string)
	  * @param[in] data sbsar binary data
	  * @param[in] size sbsar binary data's size
	  */
	bool addSubstancePackage(
		const char* objectName,
		const char* data,
		const size_t size);

	/**
	  * @brief Register a substance's instance (as a preset)
	  *
	  * @param[in] instanceName The Graph Instance UE3 object URL (null terminated utf8 string)
	  * @param[in] parentName The Parent Desc UE3 object URL (null terminated utf8 string)
	  * @param[in] sbsprsData The instance's values desc, sbsprs (null terminated utf8 string)
	  * 
	  * @return true on success, false otherwise.
	  *
	  */
	bool addSubstanceInstance(
		const char* instanceName,
		const char* parentName,
		const char* sbsprsData);

	/**
	  * @brief Register an image input
	  *
	  * @param[in] imageName, name of the image, can be a SubstanceTexture or something else (in this case, the data is stored as is)
	  * 
	  * @return true on success, false otherwise.
	  *
	  */
	bool addSubstanceImageInput(
		const char* imageName,
		const MipData& imageData);

protected:
	// PIMPL idiom
	struct Impl;
	Impl * mImpl;
};

} // namespace atc_api

#endif // ATC_API_WRITER_H
