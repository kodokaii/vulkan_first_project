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

#ifndef KDO_VULKAN_H
# define KDO_VULKAN_H

# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "cleanup.h"

# define ERRLOC "memory allocation error !\n"

# define WIDTH 1000
# define HEIGHT 1000

# define DEBUG 1

#define SZ_VALIDATION_LAYERS 1
#define SZ_REQUIRED_EXTENSIONS 0
#define SZ_REQUIRED_DEVICE_EXTENSIONS 1
#define SZ_QUEUES 2

#define VALIDATION_LAYERS "VK_LAYER_KHRONOS_validation"
#define REQUIRED_EXTENSIONS "VK_KHR_swapchain"
#define REQUIRED_DEVICE_EXTENSIONS "VK_KHR_SWAPCHAIN_EXTENSION_NAME"

#define QUEUE_REQUIRED	VK_QUEUE_GRAPHICS_BIT

#endif
