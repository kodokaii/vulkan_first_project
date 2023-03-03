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

#ifndef CREATELOGICALDEVICE_H
# define CREATELOGICALDEVICE_H

#include "kdo_vulkan.h"

int	addQueueCreateInfo(VkDeviceQueueCreateInfo *queueInfo, VkPhysicalDevice physicalDevice, VkQueueFlags findFlags, uint32_t findQueueCount, VkDeviceQueueCreateFlags queueFlags, const float *queuePriorities, VkSurfaceKHR surface);
void freeQueueInfo(VkDeviceQueueCreateInfo *root);
void	createLogicalDevice(VkDevice *device, VkQueue *queues, VkPhysicalDevice physicalDevice, const char **validationLayers, VkInstance instance, VkSurfaceKHR surface);

#endif
