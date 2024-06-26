/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_frametime_attr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:42:09 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/10 19:42:10 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>

#include "cubdef.h"
#include "textures.h"
#include "libft.h"

int	set_frametime_attr(char *identifier, char *str, t_elem *elem)
{
	long	value;
	char	*end_ptr;

	errno = 0;
	value = ft_strtol(str, &end_ptr);
	if (errno == ERANGE || value < 0 || '\0' != *end_ptr)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR3, identifier, str, INVAL_FRAMETIME);
		return (1);
	}
	elem->attr.frametime = value;
	return (0);
}
