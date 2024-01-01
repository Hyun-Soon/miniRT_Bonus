/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:36:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/27 11:58:35 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "scene.h"

t_cb	*checkerboard(t_point3 point, t_vec3 normal, t_vec3 dir)
{
	t_cb	*cb;

	cb = (t_cb *)malloc(sizeof(t_cb));
	if (!cb)
		return (NULL);
	cb->point = point;
	cb->normal = vunit(normal);
	cb->dir = vunit(dir);
	return (cb);
}

t_cone *cone(t_point3 center, t_vec3 normal, double radius, double h)
{
	t_cone *cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	
	cone->center = center;
	cone->normal = vunit(normal);
	cone->radius = radius;
	cone->height = h;
	return (cone);
}
