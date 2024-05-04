#include <stdio.h>

#include "cubscene.h"

void	DEBUG_print(t_cubscene *ptr)
{
	printf("\t---------------------------------------------\n");
	printf("\t                 SCENE INFOS\n");
	printf("\t---------------------------------------------\n");
	printf("\tTEXTURE NORTH: %s\n", ptr->texture[NO].filepath);
	printf("\tTEXTURE SOUTH: %s\n", ptr->texture[SO].filepath);
	printf("\t TEXTURE EAST: %s\n", ptr->texture[EA].filepath);
	printf("\t TEXTURE WEST: %s\n", ptr->texture[WE].filepath);
	printf("\t---------------------------------------------\n");
	printf("\t        FLOOR: %d,%d,%d\n", ptr->floor.r, ptr->floor.g, ptr->floor.b);
	printf("\t     CEILLING: %d,%d,%d\n", ptr->ceilling.r, ptr->ceilling.g, ptr->ceilling.b);
	printf("\t---------------------------------------------\n");

}
