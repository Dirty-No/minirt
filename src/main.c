/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 00:26:34 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 04:38:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_keys_buffer(t_keys *keys)
{
	int	i;

	i = -1;
	while (++i < K_BUFF_SIZE)
		keys[i] = (t_keys){-1};
}

int
	init_img(t_img *img_struct, void *mlx, int w, int h)
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	
	if (!img_struct)
		return (1);
	img = mlx_new_image(mlx, w, h);
	if (!img)
		return (1);
	addr = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!addr)
	{
		mlx_destroy_image(mlx, img);
		return (1);
	}
	*img_struct = (t_img){img, addr, bits_per_pixel, size_line, endian, w, h};
	return (0);
}

int
	init_game(t_game *game, int w, int h)
{
	void	*mlx;
	void	*win;

	if (!game)
		return (1);
	mlx = mlx_init();
	if (!mlx)
	{
		printf("Error: Could not init mlx\n");
		return (1);
	}
	win = mlx_new_window(mlx, w, h, W_TITLE);
	if (!win)
	{
		printf("Error: Could not create a new window\n");
		free(mlx);
		return (1);
	}
	if (init_img(&(game->img), mlx, w, h))
	{
		printf("Error: Could not create a new image\n");
		mlx_destroy_window(mlx, win);
		return (1);
	}
	*game = (t_game){.mlx = mlx, .win = win, .img = game->img};
	init_keys_buffer(game->keys);
	return (0);
}

int
	destroy_game(t_game *game)
{
	int	ret;

	if (!game)
		return (1);
	ret = 0; 
	ret |= mlx_destroy_image(game->mlx, (game->img).img);
	ret |= mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
	return (ret);
}

void
	refresh(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, (game->img).img, 0, 0);
}

size_t
	img_byte_size(t_img *img)
{
	return (img->width * img->height * (img->bits_per_pixel / 8));
}	

size_t
	img_size(t_img *img)
{
	return (img->width * img->height);
}	

void
	fill_img(t_img *img, unsigned int color)
{
	size_t			i;
	size_t			size;
	unsigned int	*bytes;

	i = 0;
	size = img_size(img);
	bytes = img->addr;
	while (i < size)
	{
		bytes[i] = color;
		i++;
	}
}

void
	do_test_display(t_game *game)
{

	fill_img(&(game->img), 0xFF);
	refresh(game);
}

void
	do_tuto_display(t_game *game)
{
	double			r;
	double			g;
	double			b;
	unsigned int	color;
	
	b = 0.2;
	for (size_t y = 0; y < W_HEIGHT; y++)
	{
		for (size_t x = 0; x < W_WIDTH; x++)
		{
			r = (double)x / (double)W_WIDTH;
			g = (double)(W_HEIGHT - y) / (double)W_HEIGHT;
			color = rgb(255.99 * r, 255.99 * g, 255.99 * b);
			my_mlx_pixel_put(&(game->img), x,  y, color);
		}
	}
	refresh(game);
}

void
	do_vect3_display(t_game *game)
{
	t_vect3			col;
	unsigned int	color;
	
	for (size_t y = 0; y < W_HEIGHT; y++)
	{
		for (size_t x = 0; x < W_WIDTH; x++)
		{
			col = (t_vect3)
			{
				(double)x / (double)W_WIDTH,
				(double)(W_HEIGHT - y) / (double)W_HEIGHT,
				0.2
			};
			color = rgb(255.99 * col.x, 255.99 * col.y, 255.99 * col.z);
			my_mlx_pixel_put(&(game->img), x,  y, color);
		}
	}
	refresh(game);
}

t_vect3
	ray_color(t_ray *r)
{
	t_vect3	unit_dir;
	double	t;

	unit_dir = vect3_unit(r->dir);
	t = 0.5 * (unit_dir.y + 1.0);
	return (
		vect3_add
		(
			vect3_mult_scalar((t_vect3){1.0, 1.0, 1.0}, 1.0 - t),
			vect3_mult_scalar((t_vect3){0.5, 0.7, 1.0}, t)
		)
	);
}

void
	do_shitty_raytrace_display(t_game *game)
{
	t_vect3	lower_left_corner;
	t_vect3	horizontal;
	t_vect3	vertical;
	t_vect3	origin;
	t_ray	ray;
	int		color;
	t_vect3	col;
	double	u;
	double	v;

	lower_left_corner = (t_vect3){-2.0, -1.0, -1.0};
	horizontal = (t_vect3){4.0, 0.0, 0.0};
	vertical = (t_vect3){0.0, 2.0, 0.0};
	origin = (t_vect3){0.0, 0.0, 0.0};
	//printf("P3\n%d %d\n%d\n", W_WIDTH, W_HEIGHT, 255);
	for (size_t y = 0; y < W_HEIGHT; y++)
	{
		for (size_t x = 0; x < W_WIDTH; x++)
		{
			u = (double)x / (double)W_WIDTH;
			v = (double)(W_HEIGHT - y) / (double)W_HEIGHT;
			ray = (t_ray)
			{
				origin,
				vect3_add
				(
					lower_left_corner,
					vect3_add
					(
						vect3_mult_scalar(horizontal, u),
						vect3_mult_scalar(vertical, v)
					)
				)
			};
			col = ray_color(&ray);
			color = rgb(255.99 * col.x, 255.99 * col.y, 255.99 * col.z);
			(void)color;
		//	printf("%u %u %u\n", (unsigned char)(255.99 * col.x), (unsigned char)(255.99 * col.y),
		//	 (unsigned char)(255.99 * col.z));
			my_mlx_pixel_put(&(game->img), x,  y, color);
		}
	}
	refresh(game);
}

int main(void)
{
	t_game	game[1];

	if (init_game(game, W_WIDTH, W_HEIGHT))
		return (1);
	do_shitty_raytrace_display(game);
	hooks(game);
	mlx_loop(game->mlx);
	return (destroy_game(game));
}