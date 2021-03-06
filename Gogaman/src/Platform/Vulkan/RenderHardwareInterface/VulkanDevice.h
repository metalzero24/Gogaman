#pragma once

#include "Gogaman/RenderHardwareInterface/AbstractDevice.h"

#include "Gogaman/Core/Base.h"

#include "Gogaman/RenderHardwareInterface/CommandHeap.h"

#include "Gogaman/RenderHardwareInterface/DeviceMemory.h"

#include <vulkan/vulkan.h>

namespace Gogaman
{
	namespace RHI
	{
		class Device : public AbstractDevice<Device>
		{
		private:
			struct NativeData
			{
				VkInstance                   vulkanInstance;
				#if GM_RHI_DEBUGGING_ENABLED
					VkDebugUtilsMessengerEXT vulkanDebugMessenger;
				#endif
				VkSurfaceKHR                 vulkanSurface;
				VkPhysicalDevice             vulkanPhysicalDevice;
				VkPhysicalDeviceLimits       vulkanPhysicalDeviceLimits;
				DeviceMemory::Allocator      vulkanMemoryAllocator;
				//std::vector<VkQueue>         vulkanQueues[3];
				VkQueue                      vulkanQueues[3];
				VkDevice                     vulkanDevice;
				VkSwapchainKHR               vulkanSwapChain;
				std::vector<VkImage>         vulkanSwapChainImages;
				std::vector<VkImageView>     vulkanSwapChainImageViews;
				VkSurfaceFormatKHR           vulkanSwapChainSurfaceFormat;
				VkSemaphore                  vulkanSwapChainImageAvailableSemaphores[GM_RHI_CONCURRENT_FRAME_COUNT], vulkanRenderCompletedSemaphores[GM_RHI_CONCURRENT_FRAME_COUNT];
				//VkFence                      vulkanPresentFences[GM_RHI_CONCURRENT_FRAME_COUNT];
				uint32_t                     vulkanQueueFamilyIndices[3];
				uint32_t                     vulkanSwapChainImageIndex;
				uint32_t                     vulkanPresentSynchronizationIndex = 0;
			};
		public:
			Device(void *nativeWindow);
			
			~Device();

			void CreateSwapChain(const uint16_t width, const uint16_t height, const VerticalSynchronization verticalSynchronization);

			void RecreateSwapChain(const uint16_t width, const uint16_t height, const VerticalSynchronization verticalSynchronization);

			void SubmitCommands(const CommandHeap::Type type, const uint8_t commandBufferCount, CommandBuffer *commandBuffers, Fence *fence = nullptr);
			void SubmitCommands(const CommandHeap::Type type, const uint8_t commandBufferCount, CommandBufferID *commandBufferIDs, Fence *fence = nullptr);
			//TEMPORARY
			void SubmitRenderCommands(const uint8_t commandBufferCount, CommandBufferID *commandBufferIDs, Fence *fence);

			void Present();

			inline constexpr uint32_t GetTextureWidthLimit()  const { return m_NativeData.vulkanPhysicalDeviceLimits.maxImageDimension1D; }
			inline constexpr uint32_t GetTextureHeightLimit() const { return m_NativeData.vulkanPhysicalDeviceLimits.maxImageDimension2D; }
			inline constexpr uint32_t GetTextureDepthLimit()  const { return m_NativeData.vulkanPhysicalDeviceLimits.maxImageDimension3D; }

			inline constexpr uint32_t GetSamplerAnisotropyLimit() const { return (uint32_t)m_NativeData.vulkanPhysicalDeviceLimits.maxSamplerAnisotropy; }

			inline constexpr uint32_t GetVertexShaderInputAttributeCountLimit() const { return m_NativeData.vulkanPhysicalDeviceLimits.maxVertexInputAttributes; }

			inline constexpr uint32_t GetPixelShaderOutputAttachmentCountLimit() const { return m_NativeData.vulkanPhysicalDeviceLimits.maxFragmentOutputAttachments; }

			inline constexpr const uint32_t *GetComputeShaderWorkGroupCountLimit()      const { return m_NativeData.vulkanPhysicalDeviceLimits.maxComputeWorkGroupCount;       }
			inline constexpr uint32_t        GetComputeShaderWorkGroupInvocationLimit() const { return m_NativeData.vulkanPhysicalDeviceLimits.maxComputeWorkGroupInvocations; }
			inline constexpr const uint32_t *GetComputeShaderWorkGroupSizeLimit()       const { return m_NativeData.vulkanPhysicalDeviceLimits.maxComputeWorkGroupSize;        }

			inline constexpr uint32_t GetRenderSurfaceWidthLimit()                const { return m_NativeData.vulkanPhysicalDeviceLimits.maxFramebufferWidth;  }
			inline constexpr uint32_t GetRenderSurfaceHeightLimit()               const { return m_NativeData.vulkanPhysicalDeviceLimits.maxFramebufferHeight; }
			inline constexpr uint32_t GetRenderSurfaceDepthLimit()                const { return m_NativeData.vulkanPhysicalDeviceLimits.maxFramebufferLayers; }
			inline constexpr uint32_t GetRenderSurfaceColorAttachmentCountLimit() const { return m_NativeData.vulkanPhysicalDeviceLimits.maxColorAttachments;  }
			
			inline constexpr uint32_t GetViewportCountLimit() const { return m_NativeData.vulkanPhysicalDeviceLimits.maxViewports; }

			inline constexpr const NativeData &GetNativeData() const { return m_NativeData; }
			inline constexpr       NativeData &GetNativeData()       { return m_NativeData; }

			inline constexpr uint32_t GetNativeCommandHeapType(const CommandHeap::Type type) const { return m_NativeData.vulkanQueueFamilyIndices[(uint8_t)type]; }
		private:
			Device(const Device &) = delete;
			Device(Device &&)      = delete;

			Device &operator=(const Device &) = delete;
			Device &operator=(Device &&)      = delete;

			static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * callbackData, void *userData);
		private:
			NativeData m_NativeData;
		private:
			friend AbstractDevice;
		};
	}
}