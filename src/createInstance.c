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

#include "createInstance.h"

void	createInstance(VkInstance *newInstance, char **extensions, uint32_t extensionsCount, const char	**validationLayers)
{
	VkApplicationInfo		appInfo = {};
	VkInstanceCreateInfo	createInfo = {};
	uint32_t				count;
	uint32_t				i;
	uint32_t				j;
	VkExtensionProperties	*availableExtensions;
	VkLayerProperties		*availableLayers;

	//Check extensions
	vkEnumerateInstanceExtensionProperties(NULL, &count, NULL);
	if (!(availableExtensions = malloc(count * sizeof(VkExtensionProperties))))
		cleanup(12, ERRLOC, 0, 0, 0);
	vkEnumerateInstanceExtensionProperties(NULL, &count, availableExtensions);

	for (i = 0; i < extensionsCount; i++)
	{
		for (j = 0; j < count && strcmp(extensions[i], availableExtensions[j].extensionName); j++);
		if (j == count)
		{
			printf("%s is missing\n", extensions[i]);
			cleanup(1, "some extensions are missing\n", 0, 0, 0);
		}
	}
	free(availableExtensions);

	//Settings
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = extensionsCount;
	createInfo.ppEnabledExtensionNames = (const char **) extensions;

	// Check validation layers
	if (DEBUG)
	{
		createInfo.enabledLayerCount = SZ_VALIDATION_LAYERS;
		createInfo.ppEnabledLayerNames = validationLayers;
		vkEnumerateInstanceLayerProperties(&count, NULL);
		if (!(availableLayers = malloc(count * sizeof(VkLayerProperties))))
			cleanup(12, ERRLOC, 0, 0, 0);
		vkEnumerateInstanceLayerProperties(&count, availableLayers);
		for (i = 0; i < SZ_VALIDATION_LAYERS; i++)
		{
			for (j = 0; j < count && strcmp(validationLayers[i], availableLayers[j].layerName); j++);
			if (j == count)
			{
				printf("The validation layers are activated but %s is missing\n", validationLayers[i]);
				createInfo.enabledLayerCount = 0;
				createInfo.ppEnabledLayerNames = NULL;
			}
		}
		free(availableLayers);
	}

	if (vkCreateInstance(&createInfo, NULL, newInstance) != VK_SUCCESS)
		cleanup(1, "Cannot create a Vulkan instance\n", 0, 0, 0);
}
