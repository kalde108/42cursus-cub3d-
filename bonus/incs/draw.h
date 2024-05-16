/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:48 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/16 18:59:39 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

typedef struct s_vline
{
	int		x;
	double		start;
	double		end;
}	t_vline;

void	draw_v_line(t_img *img, t_vline *line, int tex_x, t_texdata *texture);

void	put_pixel(t_img *img, int x, int y, int color);
void	put_pixel_alpha(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void	draw_line_gradient(t_img *img, int x1, int y1, int x2, int y2, int color1, int color2);

t_texdata	*get_wall_texture(t_cubscene *scene, t_v2d_i map_pos, t_elem **textures);

#endif