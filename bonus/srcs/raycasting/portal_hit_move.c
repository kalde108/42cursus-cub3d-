#include "raycasting.h"
#include "tile_address.h"

# include <stdio.h>
# include <math.h>

static int	get_relative_position(int f1, int f2)
{
	// int	diff;
	// int	relative_position;
	static int	relative_positions[4][4] = {
		{0, 1, 2, 3},
		{3, 0, 1, 2},
		{2, 3, 0, 1},
		{1, 2, 3, 0}
	};

	// diff = (f2 - f1) % 4;
	// relative_position = (diff + 4) % 4;
	// return (relative_position);
	return (relative_positions[f1][f2]);
}

static void	apply_rotation(t_camera *camera, double angle)
{
	double	old_x;

	old_x = camera->dir.x;
	camera->dir.x = camera->dir.x * cos(angle) \
						- camera->dir.y * sin(angle);
	camera->dir.y = old_x * sin(angle) + camera->dir.y * cos(angle);
	old_x = camera->plane.x;
	camera->plane.x = camera->plane.x * cos(angle) \
							- camera->plane.y * sin(angle);
	camera->plane.y = old_x * sin(angle) + \
							camera->plane.y * cos(angle);
}

void	portal_hit_move(t_cubscene *scene, t_ray *ray, t_camera *camera, double *rot)
{
	int	portal_id;
	int	dest_portal_id;
	int	relative_position;
	t_portal	*portals;
	t_v2d_d		diff;

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
		apply_rotation(camera, PI);
		*rot = PI;
		if (ray->side == 0)
			diff = (t_v2d_d){-diff.x, diff.y};
		else if (ray->side == 1)
			diff = (t_v2d_d){diff.x, -diff.y};
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
	}
	else if (relative_position == 1)	// left face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		apply_rotation(camera, -PI_2);
		*rot = -PI_2;
		if (ray->side == 0)
			diff = (t_v2d_d){-diff.y, -diff.x};
		else if (ray->side == 1)
			diff = (t_v2d_d){diff.y, diff.x};
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
	}
	else if (relative_position == 2)	// opposite face
	{
		// rotate vector (diff) 0 degrees relative to the portal
		*rot = 0;
		if (ray->side == 0)
			diff = (t_v2d_d){diff.x, -diff.y};
		else if (ray->side == 1)
			diff = (t_v2d_d){-diff.x, diff.y};
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
	}
	else if (relative_position == 3)	// right face
	{
		// rotate vector (diff) 90 degrees relative to the portal
		apply_rotation(camera, PI_2);
		*rot = PI_2;
		if (ray->side == 0)
			diff = (t_v2d_d){diff.y, diff.x};
		else if (ray->side == 1)
			diff = (t_v2d_d){-diff.y, -diff.x};
		camera->pos.x = portals[dest_portal_id].pos.x + 0.5 + diff.x;
		camera->pos.y = portals[dest_portal_id].pos.y + 0.5 + diff.y;
	}
}
