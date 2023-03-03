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

#include "getExtensions.h"

void	getExtensions(char ***extensions, uint32_t *extensionsCount)
{
	//const char			*extensionsRequired[SZ_REQUIRED_EXTENSIONS] = {REQUIRED_EXTENSIONS};
	const char				**glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(extensionsCount);
	if (!(*extensions = memcpy(malloc((SZ_REQUIRED_EXTENSIONS + *extensionsCount) * sizeof(char *)), glfwExtensions, *extensionsCount * sizeof(char *))))
		cleanup(12, ERRLOC, 0, 0, 0);
	//memcpy((*extensions) + *extensionsCount, extensionsRequired, SZ_REQUIRED_EXTENSIONS * sizeof(char *));
	*extensionsCount += SZ_REQUIRED_EXTENSIONS;
}
