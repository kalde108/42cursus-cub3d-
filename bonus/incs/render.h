/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:52:43 by ibertran          #+#    #+#             */
/*   Updated: 2024/06/08 19:36:45 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

int		screen_raycast(t_c3_env *env);
int		render_backgound(t_c3_env *env);
int		render_wall(t_c3_env *env);
void	cub_options(t_c3_env *env);
void	hud(t_c3_env *env);
void	update_mouse(t_c3_env *env);
void	update_frames(t_c3_env *env);
void	update_player(t_c3_env *env);
void	display_fps(t_c3_env *env);

#endif