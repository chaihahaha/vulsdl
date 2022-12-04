#pragma once
#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

#include <iostream>
#include <optional>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <set>

#include <SDL.h>
#include <SDL_image.h>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, 
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
    const VkAllocationCallbacks* pAllocator, 
    VkDebugUtilsMessengerEXT* pDebugMessenger
);

void DestroyDebugUtilsMessengerEXT(
    VkInstance instance, 
    VkDebugUtilsMessengerEXT debugMessenger, 
    const VkAllocationCallbacks* pAllocator
);

VkSampleCountFlagBits getMaxUsableSampleCount(VkPhysicalDevice physicalDevice);

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VmaAllocationCreateFlagBits flags, VkBuffer& buffer, VmaAllocation& bufferAllocation, VmaAllocator& vmaAllocator);

VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels, VkDevice device);

void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VmaAllocation& allocation, VmaAllocator& vmaAllocator);

void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels, VkQueue graphicsQueue, VkCommandPool commandPool, VkDevice device);

void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkQueue graphicsQueue, VkCommandPool commandPool, VkDevice device);

VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool, VkDevice device);

void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue graphicsQueue, VkCommandPool commandPool, VkDevice device);

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkQueue graphicsQueue, VkCommandPool commandPool, VkDevice device);

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

bool isDeviceSuitable(std::vector<const char*> deviceExtensions, VkPhysicalDevice device, VkSurfaceKHR surface);

bool checkDeviceExtensionSupport(std::vector<const char*> deviceExtensions, VkPhysicalDevice device);

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

bool checkValidationLayerSupport(std::vector<const char*> validationLayers);