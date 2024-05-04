#include "cub3d.h"
#include "draw.h"
#include "minimap.h"

static void	draw_map(t_c3_env *env)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (test_map[i][j] == '1')
				color = 0x00FF0000;
			else if (test_map[i][j] == '0')
				color = 0xbc8128;
			else
			{
				j++;
				continue;
			}
			x = j * MINIMAP_SCALE;
			while (x < (j + 1) * MINIMAP_SCALE)
			{
				y = i * MINIMAP_SCALE;
				while (y < (i + 1) * MINIMAP_SCALE)
				{
					put_pixel(&env->img, x, y, color);
					y++;
				}
				x++;
			}
			j++;
		}
		i++;
	}
}

static void	draw_player(t_c3_env *env)
{
	int		x;
	int		y;
	int		i;
	int		j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			x = (int)(env->player.pos.x * MINIMAP_SCALE) + j - MINIMAP_SCALE / 2;
			y = (int)(env->player.pos.y * MINIMAP_SCALE) + i - MINIMAP_SCALE / 2;
			put_pixel(&env->img, x, y, 0x0000FF00);
			j++;
		}
		i++;
	}
}

static void	draw_view(t_c3_env *env)
{
	t_v2d_d	view_end;
	int		x;
	int		y;

	view_end.x = env->player.pos.x + env->player.dir.x * 2.5;
	view_end.y = env->player.pos.y + env->player.dir.y * 2.5;
	x = (int)(view_end.x * MINIMAP_SCALE);
	y = (int)(view_end.y * MINIMAP_SCALE);
	draw_line_gradient(&env->img, (int)(env->player.pos.x * MINIMAP_SCALE), (int)(env->player.pos.y * MINIMAP_SCALE), x, y, 0x0000FF00, 0x00FFFFFF);
}

static void	draw_plane(t_c3_env *env)
{
	t_v2d_d	plane_start;
	t_v2d_d	plane_end;

	plane_start.x = env->player.pos.x + env->player.dir.x * 2.5 - env->player.plane.x * 5 / 2;
	plane_start.y = env->player.pos.y + env->player.dir.y * 2.5 - env->player.plane.y * 5 / 2;
	plane_end.x = env->player.pos.x + env->player.dir.x * 2.5 + env->player.plane.x * 5 / 2;
	plane_end.y = env->player.pos.y + env->player.dir.y * 2.5 + env->player.plane.y * 5 / 2;
	draw_line_gradient(&env->img, (int)(plane_start.x * MINIMAP_SCALE), (int)(plane_start.y * MINIMAP_SCALE), (int)(plane_end.x * MINIMAP_SCALE), (int)(plane_end.y * MINIMAP_SCALE), 0x000000FF, 0x00FFFFFF);
}

void	draw_minimap(t_c3_env *env)
{
	draw_map(env);
	draw_view_cone(env);
	draw_view(env);
	draw_plane(env);
	draw_player(env);
}