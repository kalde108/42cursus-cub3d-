#include "cub3d.h"
#include "raycasting.h"
#include "draw.h"
#include "minimap.h"
#include "tile_address.h"

#include <math.h>

# include "libft.h"
# include <stdio.h>

static int	get_relative_position(int f1, int f2)
{
	int	diff;
	int	relative_position;

	diff = (f2 - f1) % 4;
	relative_position = (diff + 4) % 4;
	return (relative_position);
}

// static void	portal_hit(t_cubscene *scene, t_ray *ray)
// {
// 	int	portal_id;
// 	int	dest_portal_id;
// 	int	relative_position;
// 	t_portal	*portals;
// 	int	tmp;

// 	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
// 	portals = scene->portals.tab;
// 	if (portals[portal_id].is_open == 0)
// 		return ;	// portal is closed
// 	dest_portal_id = portals[portal_id].linked_portal;
// 	ray->map_pos = scene->portals.tab[dest_portal_id].pos;
// 	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
// 	if (relative_position == 0)	// same face
// 	{
// 		if (ray->side == 0)
// 		{
// 			ray->step.x = -ray->step.x;
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.x -= 1;
// 			else
// 				ray->map_pos.x += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			ray->step.y = -ray->step.y;
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.y -= 1;
// 			else
// 				ray->map_pos.y += 1;
// 		}
// 	}
// 	else if (relative_position == 1)	// left face
// 	{
// 		tmp = ray->step.x;
// 		ray->step.x = ray->step.y;
// 		ray->step.y = -tmp;
// 		// tmp = ray->ray_dir.x;
// 		// ray->ray_dir.x = ray->ray_dir.y;
// 		// ray->ray_dir.y = -tmp;
// 		// tmp = ray->delta_dist.x;
// 		// ray->delta_dist.x = ray->delta_dist.y;
// 		// ray->delta_dist.y = tmp;
// 		// tmp = ray->side_dist.x;
// 		// ray->side_dist.x = ray->side_dist.y;
// 		// ray->side_dist.y = -tmp;
// 		// ray->map_pos.x -= 1;
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 			// if (ray->ray_dir.x > 0)
// 			// 	ray->map_pos.y -= 1;
// 			// else
// 			// 	ray->map_pos.y += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 		}
// 		// ray->turn = 1;
// 	}
// 	else if (relative_position == 2)	// opposite face
// 	{
// 		// vector stays the same
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				ray->map_pos.x += 1;
// 			else
// 				ray->map_pos.x -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				ray->map_pos.y += 1;
// 			else
// 				ray->map_pos.y -= 1;
// 		}
// 	}
// 	else if (relative_position == 3)	// right face
// 	{
// 		tmp = ray->step.x;
// 		ray->step.x = -ray->step.y;
// 		ray->step.y = tmp;
// 	}

// 	// if (ray->side == 0)
// 	// {
// 	// 	if (ray->ray_dir.x > 0)
// 	// 		ray->map_pos.x += 1;
// 	// 	else
// 	// 		ray->map_pos.x -= 1;
// 	// }
// 	// else if (ray->side == 1)
// 	// {
// 	// 	if (ray->ray_dir.y > 0)
// 	// 		ray->map_pos.y += 1;
// 	// 	else
// 	// 		ray->map_pos.y -= 1;
// 	// }
// }

// void	ft_dda_fake(t_cubscene *scene, t_ray *ray, t_v2d_d player_pos, t_img *img)
// {
// 	int	hit;
// 	// t_v2d_d	ray_hit;
// 	t_v2d_d	prev;
// 	t_v2d_d cur;
// 	double	perp_wall_dist;
// 	t_v2d_i	jump;
// 	int		prev_hit;
// 	int		count;
// 	t_v2d_i diff;
// 	int		pid2;

// 	prev_hit = -1;
// 	prev = player_pos;
// 	cur = player_pos;
// 	hit = 0;
// 	count = 0;
// 	jump = (t_v2d_i){0, 0};
// 	while (hit == 0 && count < 100)
// 	{
// 		// drpintf(2, "count: %d\n", count);
// 		// if (prev_hit != -1)
// 		// {
// 		// 	(void)debug;
// 		// 	// if (debug)
// 		// 	// {
// 		// 	// 	dprintf(2, "prev_hit: %d\n", prev_hit);
// 		// 	// 	dprintf(2, "linked_portal: %d\n", scene->portals.tab[prev_hit].linked_portal);
// 		// 	// }
// 		// 	// // else
// 		// 	// // 	dprintf(2, ".");
// 		// 	// if (prev_hit != 0)
// 		// 	// 	dprintf(2, "AAAAAAAAAAAAAAAAAAAAAA: %d\n", prev_hit);
// 		// 	pid2 = scene->portals.tab[prev_hit].linked_portal;
// 		// 	diff.x = scene->portals.tab[pid2].pos.x - scene->portals.tab[prev_hit].pos.x;
// 		// 	diff.y = scene->portals.tab[pid2].pos.y - scene->portals.tab[prev_hit].pos.y;
// 		// 	// if (ray->side == 0)
// 		// 	// {
// 		// 	// 	if (ray->ray_dir.x > 0)
// 		// 	// 		diff.x += 1;
// 		// 	// 	else
// 		// 	// 		diff.x -= 1;
// 		// 	// }
// 		// 	// else if (ray->side == 1)
// 		// 	// {
// 		// 	// 	if (ray->ray_dir.y > 0)
// 		// 	// 		diff.y += 1;
// 		// 	// 	else
// 		// 	// 		diff.y -= 1;
// 		// 	// }
// 		// 	// diff.x -= 1;
// 		// 	if (ray->side == 0)
// 		// 	{
// 		// 		if (ray->ray_dir.y > 0)
// 		// 			diff.y += 1;
// 		// 		else
// 		// 			diff.y -= 1;
// 		// 		// if (ray->ray_dir.x > 0)
// 		// 		// 	ray->map_pos.y -= 1;
// 		// 		// else
// 		// 		// 	ray->map_pos.y += 1;
// 		// 	}
// 		// 	else if (ray->side == 1)
// 		// 	{
// 		// 		if (ray->ray_dir.y > 0)
// 		// 			diff.x += 1;
// 		// 		else
// 		// 			diff.x -= 1;
// 		// 	}
// 		// 	prev.x += diff.x;
// 		// 	prev.y += diff.y;
// 		// 	jump.x += diff.x;
// 		// 	jump.y += diff.y;
// 		// 	prev_hit = -1;
// 		// }
// 		if (ray->side_dist.x < ray->side_dist.y)
// 		{
// 			ray->side_dist.x += ray->delta_dist.x;
// 			ray->map_pos.x += ray->step.x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist.y += ray->delta_dist.y;
// 			ray->map_pos.y += ray->step.y;
// 			ray->side = 1;
// 		}
// 		if (IS_WALL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
// 		{
// 			hit = 1;
// 			prev_hit = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
// 		}
// 		if (IS_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]))
// 		{
// 			// hit = 1;
// 			ray->hit_type = scene->map[ray->map_pos.y * scene->width + ray->map_pos.x];
// 			prev_hit = GET_PORTAL(ray->hit_type);
// 			portal_hit(scene, ray);

// 		}
// 		// else if (scene->map[ray->map_pos.y * scene->width + ray->map_pos.x] == '2')
// 		// {
// 		// 	ray->map_pos = (t_v2d_i){1, 9};
// 		// 	// if (test_flag)
// 		// 	// {
// 		// 		// jump = -27.0;
// 		// 		// prev.x -= 27.0;
// 		// 	// }
// 		// 	prev_type = '2';
// 		// }
// 		// else if (scene->map[ray->map_pos.y * scene->width + ray->map_pos.x] == '3')
// 		// {
// 		// 	ray->map_pos = (t_v2d_i){27, 9};
// 		// 	// if (test_flag)
// 		// 	// {
// 		// 		// jump = 27.0;
// 		// 		// prev.x += 27.0;
// 		// 	// }
// 		// 	prev_type = '3';
// 		// }
// 		if (ray->side == 0)
// 			perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
// 		else
// 			perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
// 		cur.x = player_pos.x + (ray->ray_dir.x) * perp_wall_dist + jump.x;
// 		cur.y = player_pos.y + (ray->ray_dir.y) * perp_wall_dist + jump.y;
// 		draw_line(img,
// 			(int)(prev.x * MINIMAP_SCALE),
// 			(int)(prev.y * MINIMAP_SCALE),
// 			(int)(cur.x * MINIMAP_SCALE),
// 			(int)(cur.y * MINIMAP_SCALE),
// 			0x007F00);
// 		prev = cur;
// 		count++;
// 	}
// }

// static void	delta_dist_init(t_ray *ray)
// {
// 	if (ray->ray_dir.x == 0)
// 		ray->delta_dist.x = 1e30;
// 	else
// 		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
// 	if (ray->ray_dir.y == 0)
// 		ray->delta_dist.y = 1e30;
// 	else
// 		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
// }

// static void	step_init(t_v2d_d *pos, t_ray *ray)
// {
// 	if (ray->ray_dir.x < 0)
// 	{
// 		ray->step.x = -1;
// 		ray->side_dist.x = (pos->x - ray->map_pos.x) \
// 							* ray->delta_dist.x;
// 	}
// 	else
// 	{
// 		ray->step.x = 1;
// 		ray->side_dist.x = (ray->map_pos.x + 1.0 - pos->x) \
// 							* ray->delta_dist.x;
// 	}
// 	if (ray->ray_dir.y < 0)
// 	{
// 		ray->step.y = -1;
// 		ray->side_dist.y = (pos->y - ray->map_pos.y) \
// 							* ray->delta_dist.y;
// 	}
// 	else
// 	{
// 		ray->step.y = 1;
// 		ray->side_dist.y = (ray->map_pos.y + 1.0 - pos->y) \
// 							* ray->delta_dist.y;
// 	}
// }

// static void	portal_hit(t_cubscene *scene, t_ray *ray, t_v2d_d *prev_start, t_player *player)
// {
// 	int	portal_id;
// 	int	dest_portal_id;
// 	int	relative_position;
// 	t_portal	*portals;
// 	t_v2d_d		diff;
// 	double	tmp1;
// 	t_v2d_d	tmp3;

// 	portals = scene->portals.tab;
// 	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
// 	if (portals[portal_id].is_open == 0)
// 		return ;	// portal is closed
// 	dest_portal_id = portals[portal_id].linked_portal;
// 	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
// 	diff.x = scene->portals.tab[dest_portal_id].pos.x - scene->portals.tab[portal_id].pos.x;
// 	diff.y = scene->portals.tab[dest_portal_id].pos.y - scene->portals.tab[portal_id].pos.y;
// 	if (relative_position == 0)	// same face
// 	{
// 		// no change
// 	}
// 	else if (relative_position == 1)	// left face
// 	{
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				diff.y -= 1;
// 			else
// 				diff.y += 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				diff.x += 1;
// 			else
// 				diff.x -= 1;
// 		}
// 	}
// 	else if (relative_position == 2)	// opposite face
// 	{
// 		// vector stays the same
// 		tmp1 = ray->ray_dir.x;
// 		ray->ray_dir.x = ray->ray_dir.y;
// 		ray->ray_dir.y = -tmp1;
// 		delta_dist_init(ray);
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				diff.x += 1;
// 			else
// 				diff.x -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				diff.y += 1;
// 			else
// 				diff.y -= 1;
// 		}
// 		tmp3.x = ray->map_pos.x + (player->camera.pos.x - floor(player->camera.pos.x));
// 		tmp3.y = ray->map_pos.y + (player->camera.pos.y - floor(player->camera.pos.y));
// 		step_init(&tmp3, ray);
// 	}
// 	else if (relative_position == 3)	// right face
// 	{
// 		if (ray->side == 0)
// 		{
// 			if (ray->ray_dir.x > 0)
// 				diff.y += 1;
// 			else
// 				diff.y -= 1;
// 		}
// 		else if (ray->side == 1)
// 		{
// 			if (ray->ray_dir.y > 0)
// 				diff.x -= 1;
// 			else
// 				diff.x += 1;
// 		}
// 	}
// 	prev_start->x += diff.x;
// 	prev_start->y += diff.y;
// }

static void	apply_rotation(t_camera *camera, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = camera->dir.x;
	camera->dir.x = camera->dir.x * cos(angle) \
						- camera->dir.y * sin(angle);
	camera->dir.y = old_dir_x * sin(angle) + camera->dir.y * cos(angle);
	old_plane_x = camera->plane.x;
	camera->plane.x = camera->plane.x * cos(angle) \
							- camera->plane.y * sin(angle);
	camera->plane.y = old_plane_x * sin(angle) + \
							camera->plane.y * cos(angle);
}

static void	fake_portal_hit(t_cubscene *scene, t_ray *ray, t_camera *camera)
{
	int	portal_id;
	int	dest_portal_id;
	int	relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

	(void)camera;
	portal_id = GET_PORTAL(scene->map[ray->map_pos.y * scene->width + ray->map_pos.x]);
	portals = scene->portals.tab;
	if (portals[portal_id].is_open == 0)
		return ;	// portal is closed
	dest_portal_id = portals[portal_id].linked_portal;
	diff.x = (portals[portal_id].pos.x + 0.5) - camera->pos.x;
	diff.y = (portals[portal_id].pos.y + 0.5) - camera->pos.y;
	relative_position = get_relative_position(portals[portal_id].face, portals[dest_portal_id].face);
	if (relative_position == 0)	// same face
	{
		// rotate vector (diff) 180 degrees relative to the portal
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		apply_rotation(camera, PI);
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.x -= 0.999999999;
			else
				camera->pos.x += 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.y -= 0.999999999;
			else
				camera->pos.y += 0.999999999;
		}
	}
	else if (relative_position == 1)	// left face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff = (t_v2d_d){-diff.y, diff.x};
		apply_rotation(camera, -PI_2);
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.y -= 0.999999999;
			else
				camera->pos.y += 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.x += 0.999999999;
			else
				camera->pos.x -= 0.999999999;
		}
	}
	else if (relative_position == 2)	// opposite face
	{
		// rotate vector (diff) 0 degrees relative to the portal
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff.x = -diff.x;
		diff.y = -diff.y;
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.x += 0.999999999;
			else
				camera->pos.x -= 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.y += 0.999999999;
			else
				camera->pos.y -= 0.999999999;
		}
	}
	else if (relative_position == 3)	// right face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		diff.x *= 0.9999999999999;	// to avoid floating point precision errors
		diff.y *= 0.9999999999999;	// to avoid floating point precision errors
		diff = (t_v2d_d){diff.y, -diff.x};
		apply_rotation(camera, PI_2);
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
		if (ray->side == 0)
		{
			if (ray->ray_dir.x > 0)
				camera->pos.y += 0.999999999;
			else
				camera->pos.y -= 0.999999999;
		}
		else if (ray->side == 1)
		{
			if (ray->ray_dir.y > 0)
				camera->pos.x -= 0.999999999;
			else
				camera->pos.x += 0.999999999;
		}
	}
}

void	draw_view_cone(t_c3_env *env)
{
	(void)env;
	t_ray	ray;
	t_v2d_d	ray_hit;
	int		x;
	int		hit_count;
	double	total_perp_wall_dist;
	t_v2d_i tmp;
	t_camera	camera;

	g_debug = 4;
	x = 0;
	while (x < WIDTH)
	{
		camera.pos = env->player.camera.pos;
		camera.dir = env->player.camera.dir;
		camera.plane = env->player.camera.plane;
		hit_count = 0;
		ray = (t_ray){0};
		while ((NOT_WALL(ray.hit_type) && !(IS_PORTAL(ray.hit_type) && -1 == env->scene.portals.tab[GET_PORTAL(ray.hit_type)].linked_portal)) && hit_count < MAX_LAYERS)
		{
			if (IS_PORTAL(ray.hit_type))
				fake_portal_hit(&env->scene, &ray, &camera);
			screen_ray_calculation(&camera, &ray, x);
			ft_dda(&env->scene, &ray);
			ray_hit.x = camera.pos.x + ray.ray_dir.x * (ray.perp_wall_dist);
			ray_hit.y = camera.pos.y + ray.ray_dir.y * (ray.perp_wall_dist);
			total_perp_wall_dist = ray.perp_wall_dist;
			draw_line(&env->img,
				(int)(camera.pos.x * MINIMAP_SCALE),
				(int)(camera.pos.y * MINIMAP_SCALE),
				(int)(ray_hit.x * MINIMAP_SCALE),
				(int)(ray_hit.y * MINIMAP_SCALE),
				0x007F00);
			tmp = (t_v2d_i){(int)(camera.pos.x * MINIMAP_SCALE), (int)(camera.pos.y * MINIMAP_SCALE)};
			draw_rectangle(&env->img, tmp, (t_v2d_i){2, 2}, 0xff7eeb);
			tmp = (t_v2d_i){(int)(ray_hit.x * MINIMAP_SCALE), (int)(ray_hit.y * MINIMAP_SCALE)};
			draw_rectangle(&env->img, tmp, (t_v2d_i){2, 2}, 0x11d280);
			camera.pos = ray_hit;
			hit_count++;
		}
		x++;
	}
	g_debug = 0;
}
