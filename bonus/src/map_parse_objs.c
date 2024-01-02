/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_objs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:53 by yusekim           #+#    #+#             */
/*   Updated: 2024/01/02 15:37:37 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "scene.h"
#include "map_parse.h"

double	get_uvalue(char *line)
{
	double	diameter;

	diameter = atodb(line);
	if (diameter <= 0)
		exit(4);
	return (diameter);
}

void	get_maps(t_param *par, t_img *img, char *filepath)
{
	char *temp;

	printf("%s\n", filepath);
	temp = ft_strchr(filepath, '\n');
	if (temp)
		*temp = '\0';
	if (ft_strcmp(filepath, "none") != 0)
	{
		img->img = mlx_xpm_file_to_image(par->mlx, filepath, &img->width, &img->height);
		if (!img->img)
			exit(13);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		if (!img->addr)
			exit(14);
	}
}

void	parse_sphere(char **line, t_param *par)
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
	sp_obj = object(SP, sphere(point, radius), color);
	if (split_cnt == 6)
	{
		get_maps(par, &sp_obj->texture, line[4]);
		get_maps(par, &sp_obj->bump, line[5]);
	}
	oadd(&par->scene.object, sp_obj);
}

void	parse_light_bulb(char **line, t_param *par)
{
	double		radius;
	t_point3	point;
	t_color3	color;
	int			split_cnt;
	t_object	*sp_obj;
	double		ratio;

	split_cnt = get_split_cnt(line);
	if (split_cnt != 4 && split_cnt != 6)
		exit(5);
	point = get_tuple(line[1]);
	radius = get_uvalue(line[2]) / 2;
	color = get_color(line[3]);
	ratio = 0.3;
	sp_obj = object(LB, sphere(point, radius), color);
	if (split_cnt == 6)
	{
		get_maps(par, &sp_obj->texture, line[4]);
		get_maps(par, &sp_obj->bump, line[5]);
	}
	oadd(&par->scene.world, sp_obj);
	oadd(&par->scene.light, object(LIGHT_POINT, \
	light_point(point, ratio, color), color3(0, 0, 0)));
}

void	parse_disk(char **line, t_param *par)
{
	double		radius;
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 5)
		exit(6);
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	radius = get_uvalue(line[3]) / 2;
	color = get_color(line[4]);
	oadd(&par->scene.object, object(DK, disk(point, normal, radius), color));
}

void	parse_cylinder(char **line, t_param *par)
{
	double		radius;
	double		height;
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 6)
		exit(6);
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	radius = get_uvalue(line[3]) / 2;
	height = get_uvalue(line[4]);
	color = get_color(line[5]);
	oadd(&par->scene.object, object(CY, \
	cylinder(point, normal, height, radius), color));
	point = vplus(point, vmult(normal, height / 2));
	oadd(&par->scene.object, object(DK, disk(point, normal, radius), color));
	point = vplus(point, vmult(normal, -height));
	oadd(&par->scene.object, object(DK, disk(point, normal, radius), color));
}

void	parse_plane(char **line, t_param *par)
{
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 4)
		exit(7);
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	color = get_color(line[3]);
	oadd(&par->scene.object, object(PL, plane(point, normal), color));
}

void	parse_cb(char **line, t_param *par)
{
	t_point3	point;
	t_vec3		normal;
	t_vec3		direction;
	t_color3	color;

	if (get_split_cnt(line) != 5)
		exit(7);
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	direction = get_tuple(line[3]);
	if (vdot(direction, normal) != 0)
		exit(321);
	color = get_color(line[4]);
	oadd(&par->scene.object, object(CB, checkerboard(point, normal, direction), color));
}

void	parse_cone(char **line, t_param *par)
{
	double		radius;
	double		height;
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 6)
		exit(6);
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	radius = get_uvalue(line[3]);
	height = get_uvalue(line[4]);
	color = get_color(line[5]);
	oadd(&par->scene.object, object(CN, cone(point, normal, radius, height), color));
	oadd(&par->scene.object, object(DK, disk(vplus(point, vmult(normal, height)), normal, radius), color));
}
