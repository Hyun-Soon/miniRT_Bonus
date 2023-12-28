/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:28:08 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/28 15:03:52 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "map_parse.h"
#include "key_hook.h"

void	get_map(t_param *par)
{
	int		width;
	int		height;

	par->earth_img.img = mlx_xpm_file_to_image(par->mlx, "./earth.xpm", &width, &height);
	par->earth_img.addr = mlx_get_data_addr(par->earth_img.img, &par->earth_img.bits_per_pixel, &par->earth_img.line_length, &par->earth_img.endian);
	if (!par->earth_img.addr)
		exit(8);
}

void	scene_parse(t_param *par)
{
	char	*temp;
	char	**split;

	temp = get_next_line(par->fd);
	while (temp)
	{
		split = ft_split(temp, ' ');
		if (ft_strcmp(split[0], "A") == 0)
			parse_ambient(split, &par->scene);
		else if (ft_strcmp(split[0], "C") == 0)
			parse_camera(split, &par->scene);
		else if (ft_strcmp(split[0], "L") == 0)
			parse_light(split, &par->scene);
		else if (ft_strcmp(split[0], "sp") == 0)
		{
			get_map(par);
			parse_sphere(split, &par->scene);
		}
		else if (ft_strcmp(split[0], "pl") == 0)
			parse_plane(split, &par->scene);
		else if (ft_strcmp(split[0], "cy") == 0)
			parse_cylinder(split, &par->scene);
		else if (ft_strcmp(split[0], "cb") == 0)
			parse_cb(split, &par->scene);
		else if (ft_strcmp(split[0], "cn") == 0)
			parse_cone(split, &par->scene);
		else
			exit(100);
		split_free(split);
		free(temp);
		temp = get_next_line(par->fd);
	}
}

void	init_image(t_param *par)
{
	par->img.img = mlx_new_image(par->mlx, WIDTH, HEIGHT);
	if (!par->img.img)
		exit(1);
	par->img.addr = mlx_get_data_addr(par->img.img, &par->img.bits_per_pixel,
			&par->img.line_length, &par->img.endian);
	if (!par->img.addr)
		exit(1);
}

void	init(t_param *par, char *file_name)
{
	par->fd = open(file_name, O_RDONLY);
	if (par->fd < 0)
	{
		perror("miniRT");
		exit(1);
	}
	par->mlx = mlx_init();
	par->win = mlx_new_window(par->mlx, WIDTH, HEIGHT, "miniRT");
	init_image(par);
	ft_memset(&par->scene, 0, sizeof(t_scene));
	par->scene.canvas.width = WIDTH;
	par->scene.canvas.height = HEIGHT;
	par->scene.canvas.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scene_parse(par);
}

int	main(int argc, char *argv[])
{
	t_param	par;

	if (argc != 2)
	{
		printf("miniRT: not enough arguments!\n");
		return (1);
	}
	init(&par, argv[1]);
	snapshot(&par);
	mlx_key_hook(par.win, key_hook, &par);
	mlx_loop(par.mlx);
}
