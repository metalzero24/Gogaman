#pragma once

#ifdef GM_PLATFORM_WINDOWS
	#include "Platform/Vulkan/RenderHardwareInterface/VulkanComputeCommandRecorder.h"
#else
	#error "Unsupported platform"
#endif