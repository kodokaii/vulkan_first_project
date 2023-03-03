/* *********************************************************************************** */
/*       :::    ::: ::::::::  :::::::::   ::::::::  :::    :::     :::     ::::::::::: */
/*      :+:   :+: :+:    :+: :+:    :+: :+:    :+: :+:   :+:    :+: :+:       :+:      */
/*     +:+  +:+  +:+    +:+ +:+    +:+ +:+    +:+ +:+  +:+    +:+   +:+      +:+       */
/*    +#++:++   +#+    +:+ +#+    +:+ +#+    +:+ +#++:++    +#++:++#++:     +#+        */
/*   +#+  +#+  +#+    +#+ +#+    +#+ +#+    +#+ +#+  +#+   +#+     +#+     +#+         */
/*  #+#   #+# #+#    #+# #+#    #+# #+#    #+# #+#   #+#  #+#     #+#     #+#          */
/* ###    ### ########  #########   ########  ###    ### ###     ### ###########       */
/*                        <kodokai.featheur@gmail.com>                                 */
/* *********************************************************************************** */

#include "createLogicalDevice.h"

int	addQueueCreateInfo(VkDeviceQueueCreateInfo *queueInfo, VkPhysicalDevice physicalDevice, VkQueueFlags findFlags, uint32_t findQueueCount, VkDeviceQueueCreateFlags queueFlags, const float *queuePriorities, VkSurfaceKHR surface)
{
	VkQueueFamilyProperties		*queueFamilies;
	uint32_t					queueFamilyCount;
	VkBool32					presentSupport = 1;
	uint32_t					index = -1;

	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
	if (!(queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties))))
		return (1);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);

	do
	{
		index++;
		if (surface)
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, index, surface, &presentSupport);
	}
	while (index < queueFamilyCount && queueFamilies[index].queueCount < findQueueCount && findFlags != (queueFamilies[index].queueFlags & findFlags) && presentSupport);

	queueInfo->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueInfo->pNext = NULL;
	queueInfo->flags = queueFlags;
	queueInfo->queueFamilyIndex = index;
	queueInfo->queueCount = findQueueCount;
	queueInfo->pQueuePriorities = queuePriorities; 

	free(queueFamilies);
	return (0);
}

void	createLogicalDevice(VkDevice *device, VkQueue *queues, VkPhysicalDevice physicalDevice, const char **validationLayers, VkInstance instance, VkSurfaceKHR surface)
{
	VkDeviceQueueCreateInfo		queueCreateInfo[SZ_QUEUES];
	VkDeviceCreateInfo			createInfo = {};
	VkPhysicalDeviceFeatures	deviceFeatures = {};
	float						queuePriority = 1.0f;

	if (addQueueCreateInfo(queueCreateInfo, physicalDevice, 0, 1, 0, &queuePriority, surface))
		cleanup(1, "Failed find queue\n", surface, instance, 0);
	if (addQueueCreateInfo(queueCreateInfo + 1, physicalDevice, VK_QUEUE_GRAPHICS_BIT, 1, 0, &queuePriority, 0))
		cleanup(1, "Failed find queue\n", surface, instance, 0);

	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.pNext = NULL;

	if (DEBUG)
	{
		createInfo.enabledLayerCount = SZ_VALIDATION_LAYERS;
		createInfo.ppEnabledLayerNames = validationLayers;
	}
	else
		createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(physicalDevice, &createInfo, NULL, device) != VK_SUCCESS)
		cleanup(1, "Logical device creation failed\n", surface, instance, 0);

	for(int i = 0; i < SZ_QUEUES; i++)
		vkGetDeviceQueue(*device, queueCreateInfo[i].queueFamilyIndex, 0, queues + i);
}
