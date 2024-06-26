/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:56 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/08 19:24:09 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "ft_math.h"

# define PLAYER_MOVEMENT_SPEED 0.03
# define PLAYER_ROTATION_SPEED 0.01
# define PLAYER_SIZE 0.1

typedef struct s_player
{
	t_v2d_d	pos;
	t_v2d_d	dir;
	t_v2d_d	plane;
	double	mv_speed;
	double	rt_speed;
}	t_player;

#endif //PLAYER_H
