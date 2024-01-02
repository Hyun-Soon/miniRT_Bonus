/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:28:08 by dongseo           #+#    #+#             */
/*   Updated: 2024/01/02 16:39:57 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "map_parse.h"
#include "key_hook.h"

void	parse_bonus(char **split, t_param *par)
{
	if (ft_strcmp(split[0], "cb") == 0)
		parse_cb(split, par);
	else if (ft_strcmp(split[0], "cn") == 0)
		parse_cone(split, par);
	else if (ft_strcmp(split[0], "dk") == 0)
		parse_disk(split, par);
	else if (ft_strcmp(split[0], "lb") == 0)
		parse_light_bulb(split, par);
	else if (get_split_cnt(split) == 1 && ft_strlen(split[0]) == 1)
		;
	else
		exit(100);
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
		else
			parse_bonus(split, par);
		split_free(split);
		free(temp);
		temp = get_next_line(par->fd);
	}
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
