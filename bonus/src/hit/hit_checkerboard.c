/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_checkerboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:37:15 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/27 11:37:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_color3	get_cb_color(t_cb *cb, t_vec3 vec, t_color3 albedo)
{
	t_vec3	u;
	t_vec3	v;

	u = cb->dir;
	v = vcross(cb->normal, u);
	if (((unsigned int)round(vdot(vec, u)) + (unsigned int)round(vdot(vec, v))) % 2 == 1)
		return (color3(1, 1, 1));
	else
		return (albedo);
}

t_bool	hit_cb(t_cb *cb, t_ray *ray, t_hit_rec *rec, t_color3 albedo)
{
	double	t;

	t = vdot(vminus(cb->point, ray->orig), cb->normal) / \
	vdot(cb->normal, ray->dir);
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = cb->normal;
	set_face_normal(ray, rec);
	rec->albedo = get_cb_color(cb, vminus(rec->p, cb->point), albedo);
	return (TRUE);
}