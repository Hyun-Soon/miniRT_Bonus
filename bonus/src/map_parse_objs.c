/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_objs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:53 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/28 14:49:09 by yusekim          ###   ########.fr       */
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

void	parse_sphere(char **line, t_scene *scene)
{
	double		radius;
	t_point3	point;
	t_color3	color;

	if (get_split_cnt(line) != 4)
		exit(5);
	point = get_tuple(line[1]);
	radius = get_uvalue(line[2]) / 2;
	color = get_color(line[3]);
	oadd(&scene->world, object(SP, sphere(point, radius), color));
}

void	parse_cylinder(char **line, t_scene *scene)
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
	oadd(&scene->world, object(CY, \
	cylinder(point, normal, height, radius), color));
	point = vplus(point, vmult(normal, height / 2));
	oadd(&scene->world, object(DK, disk(point, normal, radius), color));
	point = vplus(point, vmult(normal, -height));
	oadd(&scene->world, object(DK, disk(point, normal, radius), color));
}

void	parse_plane(char **line, t_scene *scene)
{
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 4)
		exit(7);
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	color = get_color(line[3]);
	oadd(&scene->world, object(PL, plane(point, normal), color));
}

void	parse_cb(char **line, t_scene *scene)
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
	oadd(&scene->world, object(CB, checkerboard(point, normal, direction), color));
}

void	parse_cone(char **line, t_scene *scene)
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
	oadd(&scene->world, object(CN, cone(point, normal, radius, height), color));
	oadd(&scene->world, object(DK, disk(vplus(point, vmult(normal, height)), normal, radius), color));


	//oadd(&scene->world, object(CN, \
	//cone(point, normal, height, radius), color));
	//point = vplus(point, vmult(normal, -height));
	//oadd(&scene->world, object(DK, disk(point, normal, radius), color));
}
