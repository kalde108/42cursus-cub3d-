/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:51:23 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/20 21:18:21 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "raycasting.h"
#include "tile_address.h"

# include <stdio.h>

void	render_map_chunk(t_c3_env *env, int start, int end)
{
	t_ray	ray;
	// t_vline	line;
	// t_texdata	*texture;
	// int		tex_x;
	int				x;
	t_hit_buffer	buffer[MAX_LAYERS];
	int				hit_count;

	x = start;
	while (x < end)
	{
		hit_count = 0;
		ray_calculation(&env->player, &ray, x);
		while (NOT_WALL(ray.hit_type) && hit_count < MAX_LAYERS)
		{
			ft_dda(&env->scene, &ray);
			// if (!hit_count)
				env->z_buffer[x] = ray.perp_wall_dist;
			// if (NOT_WALL(ray.hit_type) && NOT_PORTAL(ray.hit_type))
			// 	dprintf(2, "No hit?: %d\n", ray.hit_type);
			buffer[hit_count].texture = get_wall_texture(&env->scene, ray.hit_type, env->scene.elems);
			buffer[hit_count].tex_x = get_tex_x(&ray, buffer[hit_count].texture->width, env->player);
			get_line_y(buffer + hit_count, ray.perp_wall_dist);
			buffer[hit_count].side = ray.side;
			buffer[hit_count].cell = ray.hit_type;
			hit_count++;
			// draw_v_line(&env->img, &line, tex_x, texture, &ray);
		}
		while (hit_count-- > 0)
		{
			if (IS_WALL(buffer[hit_count].cell))
				draw_wall(&env->img, buffer + hit_count, x);
			else if (IS_PORTAL(buffer[hit_count].cell))
				draw_portal(&env->img, buffer + hit_count, x);
		}
		
		x++;
	}
}

void	*render_map_thread(void *arg)
{
	static int	call = 0;
	t_c3_env	*env;
	int			start;
	int			end;

	env = (t_c3_env *)arg;
	pthread_mutex_lock(&env->call_mutex);
	call++;
	call = call % CPUCORES;
	start = call * (WIDTH / CPUCORES);
	end = (call + 1) * (WIDTH / CPUCORES);
	pthread_mutex_unlock(&env->call_mutex);
	render_map_chunk(env, start, end);
	return (NULL);
}

int	render_map(t_c3_env *env)
{
	pthread_t	threads[CPUCORES];
	int			i;
	int			err;

	err = 0;
	i = 0;
	while (i < CPUCORES)
	{
		err = pthread_create(&threads[i], NULL, render_map_thread, env);
		if (err)
			break ;
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	return (err);
}
