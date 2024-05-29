/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_enclosed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:04:37 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/29 18:44:19 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "libft.h"
#include "cubdef.h"
#include "parsing.h"

static enum e_mapstatus	is_enclosed(t_vector *map, t_v2d_i start);
static enum e_mapstatus	flood_fill_routine(t_vector *map, t_vector *stack);

int	is_player_enclosed(t_vector *map, t_c3_env *env)
{
	enum e_mapstatus	enclosed;

	enclosed = is_enclosed(map,
		(t_v2d_i){env->player.pos.x, env->player.pos.y});
	if (INVAL_FATAL == enclosed)
	{
		ft_dprintf(STDERR_FILENO, SCENE_ERR2, FATAL, strerror(errno));
		return (0);
	}
	if (VALID_MAP != enclosed)
		return (0);
	if ('.' != *(char *)(ft_vector_get(ft_vector_get(map, env->monster.pos.y), env->monster.pos.x)))
	{
		ft_dprintf(STDERR_FILENO, MAP_ERR2, MONSTER_NOPATH);
		return (0);
	}
	return (1);
}

#include "stdio.h"

static enum e_mapstatus	is_enclosed(t_vector *map, t_v2d_i start)
{
	t_vector			stack;
	enum e_mapstatus	enclosed;

	if (ft_vector_init(&stack, sizeof(t_v2d_i), 0, NULL)
		|| ft_vector_add(&stack, &start))
	{
		ft_vector_free(&stack);
		return (-1);
	}
	enclosed = VALID_MAP;
	while (stack.total > 0 && enclosed == VALID_MAP)
		enclosed = flood_fill_routine(map, &stack);
	ft_vector_free(&stack);
	return (enclosed);
}

static enum e_mapstatus	flood_fill_routine(t_vector *map, t_vector *stack)
{	
	t_v2d_i		current;
	char		*cell;

	current = *(t_v2d_i *)ft_vector_get(stack, stack->total - 1);
	ft_vector_delete(stack, stack->total - 1);
	cell = ft_vector_get(ft_vector_get(map, current.y), current.x);
	if (NULL == cell)
	{
		ft_dprintf(STDERR_FILENO, INVAL_PORTAL_CELL, current.x, current.y);
		return (INVAL_WALL);
	}
	// printf("CELL=%c| x%d y%d\n", *cell, current.x, current.y);
	if (ft_ischarset(*cell, ".abcdefghijklmnopqrstuvwxyz"))
		return (VALID_MAP);
	if (*cell == 'P')
	{
		*cell = -*cell;
		return (VALID_MAP);
	}
	else if (*cell == -'P')
	{
		ft_dprintf(STDERR_FILENO, INVAL_PORTAL_CELL, current.x, current.y);
		return (INVAL_PORTAL);
	}
	*cell = '.';
	if (ft_vector_add(stack, &(t_v2d_i){current.x, current.y - 1})
		|| ft_vector_add(stack, &(t_v2d_i){current.x - 1, current.y})
		|| ft_vector_add(stack, &(t_v2d_i){current.x, current.y + 1})
		|| ft_vector_add(stack, &(t_v2d_i){current.x + 1, current.y}))
		return (INVAL_FATAL);
	return (VALID_MAP);
}
