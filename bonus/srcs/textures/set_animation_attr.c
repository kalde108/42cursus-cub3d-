/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_animation_attr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:04 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:42:05 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "textures.h"
#include "cubdef.h"
#include "libft.h"

int	set_animation_attr(char *identifier, char *str, t_elem *elem)
{
	const char	*value[] = {ANIM_NONE, ANIM_LOOP, ANIM_SWAY, ANIM_RANDOM};
	t_anim		i;

	i = NONE;
	while (i <= RANDOM)
	{
		if (0 == ft_strcmp(value[i], str))
		{
			elem->attr.animation = i;
			return (0);
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_ANIMATION);
	return (1);
}
