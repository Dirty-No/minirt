/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 01:08:18 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 05:46:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		leave(t_game *game)
{
	destroy_game(game);
	exit(0);
}

int		key_handler(int keycode, t_game *game)
{
	int i;

	i = -1;
	if (keycode == ESC_KEY)
	{
		destroy_game(game);
		exit(0);
	}
	i = -1;
	while (i < K_BUFF_SIZE && (((game->keys)[i]).keycode != -1))
		i++;
	if (((game->keys)[i]).keycode != -1)
		return (0);
	((game->keys)[i]).keycode = keycode;
	while (++i < K_BUFF_SIZE)
		if (((game->keys)[i]).keycode == keycode)
			((game->keys)[i]).keycode = -1;
	return (0);
}

int		release_handler(int keycode, t_game *game)
{
	int				i;

	i = -1;
	while (++i < K_BUFF_SIZE)
	{
		if ((game->keys[i]).keycode == keycode)
		{
			if (i >= K_BUFF_SIZE)
				return (0);
			((game->keys)[i]).keycode = -1;
		}
	}
	return (0);
}

t_keys	*key_chr(t_keys *arr, int keycode, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		if (arr[i].keycode == keycode)
			return (arr + i);
	return (NULL);
}


int		keyboard_handler(t_game *game)
{
	int redraw;

	/*redraw = (int)(forward_handler(game) | backward_handler(game)
					| right_handler(game) | left_handler(game)
					| alt_handler(game) | turn_left_handler(game)
					| turn_right_handler(game));*/
	redraw = 0;
	if (key_chr(game->keys, CTRL_KEY, K_BUFF_SIZE))
	{
		if (key_chr(game->keys, C_KEY, K_BUFF_SIZE))
		{
			destroy_game(game);
			exit(0);
		}
	}
	return (redraw);
}

void
	draw_scene(t_game *game)
{
	do_shitty_raytrace_display(game);
}

int		loop_handler(t_game *game)
{
	//game->redraw |= keyboard_handler(game);
	game->redraw = 1;
	if (game->redraw)
	{
		draw_scene(game);
		refresh(game);
	}
	return (0);
}

void	hooks(t_game *game)
{
	mlx_hook(game->win, KEY_PRESS, KEYPRESS_MASK, key_handler, (void *)game);
	mlx_hook(game->win, KEY_RELEASE, KEYRELEASE_MASK, release_handler,
			(void *)game);
	mlx_hook(game->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, leave, game);
	mlx_loop_hook(game->mlx, loop_handler, (void *)game);
}
