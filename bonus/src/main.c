/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:28:08 by dongseo           #+#    #+#             */
/*   Updated: 2024/01/02 12:24:02 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "map_parse.h"
#include "key_hook.h"

void	scene_parse(t_param *par)
{
	char	*temp;
	char	**split;

	temp = get_next_line(par->fd);
	while (temp)
	{
		split = ft_split(temp, ' ');
		if (ft_strcmp(split[0], "A") == 0)
			parse_ambient(split, par);
		else if (ft_strcmp(split[0], "C") == 0)
			parse_camera(split, par);
		else if (ft_strcmp(split[0], "L") == 0)
			parse_light(split, par);
		else if (ft_strcmp(split[0], "sp") == 0)
			parse_sphere(split, par);
		else if (ft_strcmp(split[0], "pl") == 0)
			parse_plane(split, par);
		else if (ft_strcmp(split[0], "cy") == 0)
			parse_cylinder(split, par);
		else if (ft_strcmp(split[0], "cb") == 0)
			parse_cb(split, par);
		else if (ft_strcmp(split[0], "cn") == 0)
			parse_cone(split, par);
		else if (ft_strcmp(split[0], "dk") == 0)
			parse_disk(split, par);
		else if (get_split_cnt(split) == 1 && ft_strlen(split[0]) == 1)
			;
		else
			exit(100);
		split_free(split);
		free(temp);
		temp = get_next_line(par->fd);
	}
}

void	init_image(t_param *par, t_bool flag)
{
	t_img	*tar_img;

	if (flag == AA)
		tar_img = &par->aa_img;
	else
		tar_img = &par->img;
	tar_img->height = HEIGHT;
	tar_img->width = WIDTH;
	tar_img->img = mlx_new_image(par->mlx, tar_img->width, tar_img->height);
	if (!tar_img->img)
		exit(1);
	tar_img->addr = mlx_get_data_addr(tar_img->img, &tar_img->bits_per_pixel,
			&tar_img->line_length, &tar_img->endian);
	if (!tar_img->addr)
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
	par->aa_flag = FALSE;
	init_image(par, NAA);
	init_image(par, AA);
	ft_memset(&par->scene, 0, sizeof(t_scene));
	par->scene.canvas.width = WIDTH;
	par->scene.canvas.height = HEIGHT;
	par->scene.canvas.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scene_parse(par);
}

int	win_close(t_param *par)
{
	mlx_destroy_window(par->mlx, par->win);
	exit(0);
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
	snapshot(&par, &par.img);
	mlx_key_hook(par.win, key_hook, &par);
	mlx_hook(par.win, 17, 0, win_close, &par);
	mlx_loop(par.mlx);
}
