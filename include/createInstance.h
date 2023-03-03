/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createInstance.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kodokai <kodokai.featheur@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:03:01 by kodokai           #+#    #+#             */
/*   Updated: 2023/02/27 22:56:27 by kodokai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATEINSTANCE_H
# define CREATEINSTANCE_H

#include "kdo_vulkan.h"

void	createInstance(VkInstance *newInstance, char **extensions, uint32_t extensionsCount, const char	**validationLayers);

#endif

