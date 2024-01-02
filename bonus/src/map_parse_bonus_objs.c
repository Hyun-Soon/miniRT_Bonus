/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus_objs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:53 by yusekim           #+#    #+#             */
/*   Updated: 2024/01/02 18:00:44 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "scene.h"
#include "map_parse.h"

void	get_maps(t_param *par, t_img *img, char *filepath)
{
	char	*temp;

	printf("%s\n", filepath);
	temp = ft_strchr(filepath, '\n');
	if (temp)
		*temp = '\0';
	if (ft_strcmp(filepath, "none") != 0)
	{
		img->img = mlx_xpm_file_to_image(par->mlx, \
		filepath, &img->width, &img->height);
		if (!img->img)
			exit(13);
		img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->line_length, &img->endian);
		if (!img->addr)
			exit(14);
	}
}

void	parse_light_bulb(char **line, t_param *par)
{
	double		radius;
	t_point3	point;
	t_color3	color;
	int			split_cnt;
	t_object	*sp_obj;

	split_cnt = get_split_cnt(line);
	if (split_cnt != 4 && split_cnt != 6)
		exit(5);
	point = get_tuple(line[1]);
	radius = get_uvalue(line[2]) / 2;
	color = get_color(line[3]);
	sp_obj = object(LB, sphere(point, radius), color);
	if (split_cnt == 6)
	{
		get_maps(par, &sp_obj->texture, line[4]);
		get_maps(par, &sp_obj->bump, line[5]);
	}
	oadd(&par->scene.world, sp_obj);
	oadd(&par->scene.light, object(LIGHT_POINT, \
	light_point(point, 0.1, color), color3(0, 0, 0)));
}
