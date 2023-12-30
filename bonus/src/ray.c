/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:48 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/30 14:36:33 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->l_top, vmult(cam->horizontal, u)), \
	vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_rec	record_init(void)
{
	t_hit_rec	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

t_color3	ray_color(t_param *par)
{
	t_scene	*scene;
	double	t;

	scene = &par->scene;
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	else
	{
		t = 0.5 * (scene->ray.dir.y + 1.0);
		return (vplus(vmult(color3(1, 1, 1), 1.0 - t), \
		vmult(color3(0.5, 0.7, 1.0), t)));
	}
}
