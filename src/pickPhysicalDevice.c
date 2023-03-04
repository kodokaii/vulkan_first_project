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

#include "pickPhysicalDevice.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	VkPhysicalDeviceProperties	deviceProperties;
	VkPhysicalDeviceFeatures	deviceFeatures;
	VkQueueFamilyProperties		*queueFamilies;
	VkExtensionProperties		*availableExtensions;
	char					*requiredExtensions[SZ_REQUIRED_DEVICE_EXTENSIONS] = {REQUIRED_DEVICE_EXTENSIONS};
	uint32_t					queueFamilyCount;
	uint32_t					extensionCount;
	uint32_t					i;
	int							presentExtension = 1;
	VkQueueFlags				queueRequired = QUEUE_REQUIRED;
	VkBool32					presentSupport = 0;

	//check extensions
	vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);
	if (!(availableExtensions = malloc(extensionCount * sizeof(VkExtensionProperties))))
		return (-1);
	vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions);
	for (uint32_t j = 0; j < SZ_REQUIRED_DEVICE_EXTENSIONS; j++)
	{
		for (i = 0; i < extensionCount && ft_strcmp(requiredExtensions[j], availableExtensions[i].extensionName); i++);
		if (i == extensionCount)
		{
			presentExtension = 0;
			printf("%s is missing\n", requiredExtensions[j]);
		}
	}
	free(availableExtensions);
	
	//check Queue
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);
	if (!(queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties))))
		return (-1);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);
	for (i = 0; i < queueFamilyCount && (queueRequired || !presentSupport); i++)
	{
		if (!presentSupport)
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
		queueRequired ^= queueFamilies[i].queueFlags & queueRequired;
	}
	free(queueFamilies);

	//check device
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	return (deviceFeatures.geometryShader && deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && !queueRequired && presentSupport && presentExtension);
}

void	pickPhysicalDevice(VkPhysicalDevice *physicalDevice, VkInstance instance, VkSurfaceKHR surface)
{
	VkPhysicalDevice			*devices;
	uint32_t					deviceCount;
	uint32_t					i;

	vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
	if (!deviceCount)
		cleanup(1, "No graphics card supports Vulkan\n", surface, instance, 0);
	if (!(devices = malloc(deviceCount * sizeof(VkPhysicalDevice))))
		cleanup(12, ERRLOC, surface, instance, 0);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
	for (i = 0; i < deviceCount && !isDeviceSuitable(devices[i], surface); i++)
	if (i == deviceCount)
		cleanup(1, "Couldn't find a suitable GPU\n", surface, instance, 0);
	*physicalDevice = devices[i];
	free(devices);
}
