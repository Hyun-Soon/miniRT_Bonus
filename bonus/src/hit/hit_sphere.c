/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:17:38 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/30 17:34:36 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

double	sp_discriminant(t_ray *ray, t_sphere *sp, double *a, double *half_b);

t_color3	convert(int color)
{
	double	r;
	double	g;
	double	b;

	r = ((color / 65536) % 256) / 255.0;
	g = ((color / 256) % 256) / 255.0;
	b = ((color % 256)) / 255.0;
	return (color3(r, g, b));
}

t_color3	get_albedo(t_sphere *sp, t_img *img, t_hit_rec *rec, t_color3 albedo)
{
	t_vec3	cp;
	t_vec3	cp_xz;
	t_vec3	y_axis;
	t_vec3	x_axis;
	int		coord_x;
	int		coord_y;
	double	x_theta;
	double	y_theta;
	char	*dst;
	int		color;

	if (!img->addr)
		return (albedo);
	y_axis = vec3(0, 1, 0);
	x_axis = vec3(1, 0, 0);
	cp = vunit(vminus(rec->p, sp->center));
	cp = rotate_x(cp, 23 * M_PI / 180);
	cp_xz = vunit(vec3(cp.x, 0, cp.z)); 

	x_theta = acos(vdot(cp_xz, x_axis));
	if (cp.z > 0)
		x_theta = 2 * M_PI - x_theta;
	y_theta = acos(vdot(cp, y_axis));

	x_theta = x_theta * 180 / M_PI;
	y_theta = y_theta * 180 / M_PI;
	coord_x = (int)((double)img->width / 360.0 * x_theta);
	coord_y = (int)((double)img->height / 180.0 * y_theta);
	dst = img->addr + (coord_y * img->line_length + coord_x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (convert(color));
}

t_vec3	get_bump(t_sphere *sp, t_img *img, t_hit_rec *rec)
{
	t_vec3	cp;
	t_vec3	cp_xz;
	t_vec3	y_axis;
	t_vec3	x_axis;
	t_vec3	normal;
	int		coord_x;
	int		coord_y;
	double	x_theta;
	double	y_theta;
	char	*dst;
	int		normal_int;

	if (!img->addr)
		return (vdivide(vminus(rec->p, sp->center), sp->radius));
	y_axis = vec3(0, 1, 0);
	x_axis = vec3(1, 0, 0);
	cp = vunit(vminus(rec->p, sp->center));
	cp = rotate_x(cp, 23 * M_PI / 180);
	cp_xz = vunit(vec3(cp.x, 0, cp.z)); 

	x_theta = acos(vdot(cp_xz, x_axis));
	if (cp.z > 0)
		x_theta = 2 * M_PI - x_theta;
	y_theta = acos(vdot(cp, y_axis));

	x_theta = x_theta * 180 / M_PI;
	y_theta = y_theta * 180 / M_PI;
	coord_x = (int)((double)img->width / 360.0 * x_theta);
	coord_y = (int)((double)img->height / 180.0 * y_theta);
	dst = img->addr + (coord_y * img->line_length + coord_x * (img->bits_per_pixel / 8));
	normal_int = *(unsigned int *)dst;
	normal = vunit(convert(normal_int));
	normal = vmult(vminus(normal, vec3(0.5, 0.5, 0.5)), 1);
	normal = rotate_x(normal, (90 - y_theta) * M_PI / 180);
	normal = rotate_y(normal, x_theta * M_PI / 180);
	normal.y *= -1;
	normal.z *= -1;
	return (normal);
}

t_bool	hit_sp(t_object *sp_obj, t_ray *ray, t_hit_rec *rec)
{
	double		discriminant;
	double		sqrtd;
	double		root;
	double		a;
	double		half_b;
	t_sphere	*sp;

	sp = sp_obj->element;
	discriminant = sp_discriminant(ray, sp, &a, &half_b);
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	// rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	rec->normal = get_bump(sp, &sp_obj->bump, rec);
	set_face_normal(ray, rec);
	rec->albedo = get_albedo(sp, &sp_obj->texture, rec, sp_obj->albedo);
	return (TRUE);
}

double	sp_discriminant(t_ray *ray, t_sphere *sp, double *a, double *half_b)
{
	t_vec3		oc;
	double		c;

	oc = vminus(ray->orig, sp->center);
	*a = vlength2(ray->dir);
	*half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	return ((*half_b) * (*half_b) - *a * c);
}
