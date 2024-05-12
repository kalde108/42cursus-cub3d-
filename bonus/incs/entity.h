#ifndef ENTITY_H
# define ENTITY_H

# include "ft_math.h"

# define MONSTER_MOVEMENT_SPEED 2.5
# define MONSTER_ROTATION_SPEED 1.5
# define MONSTER_SIZE 0.1

typedef struct s_entity
{
	t_v2d_d	pos;	// entity position
	t_v2d_d	dir;	// entity orientation
	t_v2d_d	plane;	// camera plane
	double	mv_speed;
	double	rt_speed;
}	t_entity;

#endif