/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:52:37 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/27 12:15:22 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_cone(t_cone *cn, t_ray *ray, t_hit_rec *rec, t_color3 albedo)
{
	t_vec3 oc;
	double a;
	double half_b;
	double c;
	double sqrtd;
	double h2;
	double r2;
	double root;
	double discriminant;

	h2 = cn->height * cn->height;
	r2 = cn->radius * cn->radius;
	oc = vminus(ray->orig, cn->center);
	a = (h2 * vlength2(vcross(cn->normal, ray->dir))) - (r2 * pow(vdot(cn->normal, ray->dir), 2));
	half_b = (h2 * vdot(vcross(cn->normal, ray->dir), vcross(cn->normal, oc))) - (r2 * vdot(cn->normal, ray->dir) * vdot(oc, cn->normal));
	c = (h2 * vlength2(vcross(cn->normal, oc))) - (r2 * pow(vdot(oc, cn->normal), 2));
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return(FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	h2 = vdot(vminus(ray_at(ray, root), cn->center), cn->normal);
	if (root < rec->tmin || rec->tmax < root || (h2 > cn->height) || h2 < 0)
	{
		root = (-half_b + sqrtd) / a;
		h2 = vdot(vminus(ray_at(ray, root), cn->center), cn->normal);
		if (root < rec->tmin || root > rec->tmax || (h2 > cn->height) || h2 < 0)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vminus(rec->p, vplus(cn->center, vmult(cn->normal, (vdot(vminus(rec->p, cn->center), cn->normal) + (((cn->radius * cn->radius) * vdot(vminus(rec->p, cn->center), cn->normal)) / (cn->height * cn->height)))))));
	set_face_normal(ray, rec);
	rec->albedo = albedo;
	return (TRUE);
}