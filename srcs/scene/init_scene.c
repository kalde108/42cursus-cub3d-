/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:29:16 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/04 02:16:11 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubscene.h"

void	init_img(t_img *img)
{
	img->filepath = NULL;
	img->ptr = NULL;
}

void	init_scene(t_cubscene *ptr)
{
	init_img(&ptr->texture.no);
	init_img(&ptr->texture.so);
	init_img(&ptr->texture.ea);
	init_img(&ptr->texture.we);
	ptr->floor.a = 255;
	ptr->ceilling.a = 255;
}
