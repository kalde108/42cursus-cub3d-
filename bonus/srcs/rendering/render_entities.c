#include <math.h>

#include "cub3d.h"
#include "draw.h"
#include "libft.h"

# include <stdio.h>

static void	render_enemy(t_c3_env *env, t_entity *entity)
{
	t_v2d_d	sprite_pos;

	sprite_pos = (t_v2d_d){entity->pos.x - env->player.pos.x,
		entity->pos.y - env->player.pos.y};
	
	double inv_det = 1.0 / (env->player.plane.x * env->player.dir.y -
		env->player.dir.x * env->player.plane.y);

	t_v2d_d transform;

	transform.x = inv_det * (env->player.dir.y * sprite_pos.x -
		env->player.dir.x * sprite_pos.y);
	transform.y = inv_det * (-env->player.plane.y * sprite_pos.x +
		env->player.plane.x * sprite_pos.y);

	int sprite_screen_x;

	sprite_screen_x = ((int)(WIDTH / 2) * (1 + transform.x / transform.y));

	t_v2d_i sprite_size;
	sprite_size.y = ft_abs((int)(HEIGHT / transform.y));

	t_v2d_i draw_start;
	draw_start.y = -sprite_size.y / 2 + HEIGHT / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	
	t_v2d_i draw_end;
	draw_end.y = sprite_size.y / 2 + HEIGHT / 2;
	if (draw_end.y >= HEIGHT)
		draw_end.y = HEIGHT - 1;
	
	sprite_size.x = ft_abs((int)(HEIGHT / transform.y));
	draw_start.x = -sprite_size.x / 2 + sprite_screen_x;
	if (draw_start.x < 0)
		draw_start.x = 0;
	draw_end.x = sprite_size.x / 2 + sprite_screen_x;
	if (draw_end.x >= WIDTH)
		draw_end.x = WIDTH - 1;
	
	int stripe;

	stripe = draw_start.x;
	while (stripe < draw_end.x)
	{
		t_v2d_i tex_pos;
		tex_pos.x = (int)(256 * (stripe - (-sprite_size.x / 2 + sprite_screen_x)) *
			entity->sprites[0].sprite->width / sprite_size.x) / 256;
		if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < env->z_buffer[stripe])
		{
			int y;
			y = draw_start.y;
			while (y < draw_end.y)
			{
				int d;
				d = (y) * 256 - HEIGHT * 128 + sprite_size.y * 128;
				tex_pos.y = ((d * entity->sprites[0].sprite->height) / sprite_size.y) / 256;
				int color;
				color = *(int *)(entity->sprites[0].sprite->addr + (tex_pos.y * entity->sprites[0].sprite->line_length + tex_pos.x * (entity->sprites[0].sprite->bits_per_pixel / 8)));
				if ((color & 0x00FFFFFF) != 0)
					put_pixel(&env->img, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}

void	render_entities(t_c3_env *env)
{
	size_t		i;
	t_entity	*entity;

	// dprintf(2, "\nentity_count: %zu\n", env->entity_count);
	i = 0;
	while (i < env->entity_count)
	{
		entity = &env->entities[i];
		render_enemy(env, entity);
		// if (entity->type == MONSTER)
		// 	render_enemy(env, entity);
		// else if (entity->type == BOXES)
		// 	render_box(env, entity);
		i++;
	}
}