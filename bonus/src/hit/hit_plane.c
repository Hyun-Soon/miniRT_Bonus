/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:16:49 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/30 14:28:15 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_pl(t_object *pl_obj, t_ray *ray, t_hit_rec *rec)
{
	double	t;
	t_plane	*pl;

	pl = pl_obj->element;
	t = vdot(vminus(pl->point, ray->orig), pl->normal) / \
	vdot(pl->normal, ray->dir);
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	rec->albedo = pl_obj->albedo;
	return (TRUE);
}
