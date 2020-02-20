#include "VulkanCommandPool.h"

vk::CommandBuffer VulkanCommandPool::AllocateCommandBuffer()
{
	return AllocateCommandBuffers(1)[0];
}

std::vector<vk::CommandBuffer> VulkanCommandPool::AllocateCommandBuffers(uint32_t count)
{
	vk::CommandBufferAllocateInfo allocInfo = vk::CommandBufferAllocateInfo(commandPool);
	allocInfo.commandBufferCount = count;

	std::vector<vk::CommandBuffer> commandBuffers = device.allocateCommandBuffers(allocInfo);
	return commandBuffers;
}

void VulkanCommandPool::Destroy()
{
	device.destroyCommandPool(commandPool);
}