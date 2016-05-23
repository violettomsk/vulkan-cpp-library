/*
* Copyright 2016 Google Inc. All Rights Reserved.

* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

* http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef _VCC_INTERNAL_LOADER_H_
#define _VCC_INTERNAL_LOADER_H_

#include <istream>
#include <vcc/image.h>
#include <vcc/queue.h>

namespace vcc {
namespace image {
namespace internal {

struct loader_type {
	virtual bool can_load(std::istream &stream) = 0;
	virtual image::image_type load(
		const type::supplier<vcc::queue::queue_type> &queue,
		VkImageCreateFlags flags,
		VkImageUsageFlags usage,
		VkFormatFeatureFlags feature_flags,
		VkSharingMode sharingMode,
		const std::vector<uint32_t> &queueFamilyIndices,
		std::istream &stream) = 0;
};

#if !defined(__ANDROID__) && !defined(ANDROID)

struct png_loader_type : public loader_type {
	bool can_load(std::istream &stream);
	image::image_type load(
		const type::supplier<vcc::queue::queue_type> &queue,
		VkImageCreateFlags flags,
		VkImageUsageFlags usage,
		VkFormatFeatureFlags feature_flags,
		VkSharingMode sharingMode,
		const std::vector<uint32_t> &queueFamilyIndices,
		std::istream &stream);
};

#endif // __ANDROID__

struct gli_loader_type : public loader_type {
	bool can_load(std::istream &stream);
	image::image_type load(
		const type::supplier<vcc::queue::queue_type> &queue,
		VkImageCreateFlags flags,
		VkImageUsageFlags usage,
		VkFormatFeatureFlags feature_flags,
		VkSharingMode sharingMode,
		const std::vector<uint32_t> &queueFamilyIndices,
		std::istream &stream);
};

/*
* Copy to the mipmap level 0, array 0 of an image.
* According to Vulkan specs, the base requirement of VK_IMAGE_TILING_LINEAR on page 207
* indicates we can't expect much more of the linear layout.
*/
void copy_to_image(queue::queue_type &queue, VkPhysicalDevice physical_device,
	VkFormat format, VkImageAspectFlags aspect_mask, VkExtent2D extent,
	const void *source, std::size_t block_size, std::size_t row_pitch,
	image::image_type &target_image);

uint32_t bytes_per_pixel(VkFormat format);

}  // namespace internal
}  // namespace image
}  // namespace vcc

#endif // _VCC_INTERNAL_LOADER_H_

