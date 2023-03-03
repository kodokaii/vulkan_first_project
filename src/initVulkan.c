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

#include "initVulkan.h"

void	initVulkan(GLFWwindow	*window)
{
	const char				*validationLayers[SZ_VALIDATION_LAYERS] = {VALIDATION_LAYERS};
	char					**extensions;
	uint32_t				extensionsCount;
	VkInstance				instance;
	VkSurfaceKHR			surface;
	VkPhysicalDevice		physicalDevice;
	VkDevice				device;
	VkQueue					queues[SZ_QUEUES];

	getExtensions(&extensions, &extensionsCount);
	createInstance(&instance, extensions, extensionsCount, validationLayers);
	createSurface(&surface, instance, window);
	pickPhysicalDevice(&physicalDevice, instance, surface);
	createLogicalDevice(&device, queues, physicalDevice, validationLayers, instance, surface);

	free(extensions);
}
