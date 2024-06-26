/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:53:11 by ibertran          #+#    #+#             */
/*   Updated: 2024/05/17 18:38:18 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keyup_hook(int keycode, t_c3_env *env)
{
	int	keyindex;

	keyindex = get_keyindex(keycode);
	if (keyindex != -1)
		env->key_state[keyindex] = 0;
	return (0);
}
