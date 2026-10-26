/** 
  * @note This file is part of Air UE3 integration
  * @date 2012-03-05
  * @copyright Allegorithmic. All rights reserved. 
  */

#ifndef ATC_API_MIPDATA_H
#define ATC_API_MIPDATA_H

#include "atc_conf.h"

namespace atc_api
{

//! @brief Small utility class to contain a mip data description
class ATC_API_CONV MipData
{
	const void * mData;
	size_t mSize;

public:
	MipData(const void * data = 0, size_t size = 0);

	size_t size() const;

	const void * data() const;
};

class ATC_API_CONV MipDataArray
{
public:
	//! @brief Create a new MipData array
	MipDataArray();

	//! @brief Destroy the current array
	~MipDataArray();

	//! @brief Erase the content of this array
	void clear();

	/**
	 * @brief Append a MipData element at the end of the array
	 *
	 * @return true on successful insertion, false otherwise. It can fail
	 *         because the container has a statically determined maximum 
	 *         size (64 max)
	 */
	bool push_back(const MipData & mipData);

	//! @brief Return the current size of this array
	size_t size() const;

	//! @brief Access a MipData element
	const MipData & operator[](size_t index) const;

protected:
	// PIMPL idiom
	struct Impl;
	Impl * mImpl;
};

} // namespace atc_api

#endif // ATC_API_MIPDATA_H
