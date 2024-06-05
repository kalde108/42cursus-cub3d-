#include <math.h>

#include "cub3d.h"
#include "draw.h"
#include "libft.h"

# include <stdio.h>

static inline t_v2d_d	sprite_transform(t_player *player, t_entity *entity)
{
	t_v2d_d	sprite_pos;

	sprite_pos = (t_v2d_d){entity->pos.x - player->camera.pos.x,
		entity->pos.y - player->camera.pos.y};
	
	double inv_det = 1.0 / (player->camera.plane.x * player->camera.dir.y -
		player->camera.dir.x * player->camera.plane.y);

	t_v2d_d transform;

	transform.x = inv_det * (player->camera.dir.y * sprite_pos.x -
		player->camera.dir.x * sprite_pos.y);
	transform.y = inv_det * (-player->camera.plane.y * sprite_pos.x +
		player->camera.plane.x * sprite_pos.y);

	return (transform);
}

static inline void	render_entitie(t_c3_env *env, t_entity *entity)
{
	t_v2d_d transform;

	transform = sprite_transform(&env->player, entity);

	int sprite_screen_x;

	sprite_screen_x = ((int)(WIDTH / 2) * (1 + transform.x / transform.y));

	int	v_move_screen = (int)(V_MOVE / transform.y);

	t_v2d_i sprite_size;
	sprite_size.y = ft_abs((int)(HEIGHT / transform.y)) / V_DIV;

	t_v2d_i draw_start;
	draw_start.y = -sprite_size.y / 2 + HEIGHT / 2 + v_move_screen;
	if (draw_start.y < 0)
		draw_start.y = 0;
	
	t_v2d_i draw_end;
	draw_end.y = sprite_size.y / 2 + HEIGHT / 2 + v_move_screen;
	if (draw_end.y >= HEIGHT)
		draw_end.y = HEIGHT - 1;
	
	sprite_size.x = ft_abs((int)(HEIGHT / transform.y)) / U_DIV;
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
		tex_pos.x = (stripe - (-sprite_size.x / 2 + sprite_screen_x)) *
			entity->sprites[0].frames->width / sprite_size.x;
		if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < env->z_buffer[stripe])
		{
			int y;
			y = draw_start.y;
			while (y <= draw_end.y && y < HEIGHT)
			{
				int d;
				// d = (y - v_move_screen) * 256 - HEIGHT * 128 + sprite_size.y * 128;
				d = y - HEIGHT / 2 + sprite_size.y / 2 - v_move_screen;
				// tex_pos.y = ((d * entity->sprites[0].sprite->height) / sprite_size.y);
				tex_pos.y = ((d * entity->sprites[0].frames->height) / sprite_size.y);
				int color;
				color = entity->sprites[0].frames->addr[tex_pos.y * entity->sprites[0].frames->width + tex_pos.x].argb;
				if ((color & 0x00FFFFFF) != 0)
					env->img.addr[(y << WIDTH_LOG2) + stripe].argb = color;
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
		render_entitie(env, entity);
		// if (entity->type == MONSTER)
		// 	render_enemy(env, entity);
		// else if (entity->type == BOXES)
		// 	render_box(env, entity);
		i++;
	}
}