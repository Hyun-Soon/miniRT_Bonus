/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:17:38 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/28 16:48:00 by yusekim          ###   ########.fr       */
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

t_color3	get_albedo(t_sphere *sp, t_hit_rec *rec, t_param *par, t_color3 albedo)
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

	if (!par->earth_img.img)
		return (albedo);
	// y_axis = vmult(vec3(0, 1, 0), sp->radius);
	// x_axis = vmult(vec3(1, 0, 0), sp->radius);
	y_axis = vec3(0, 1, 0);//
	x_axis = vec3(1, 0, 0);//
	// if (!par && !par->earth_img.addr)
	// cp = vminus(rec->p, sp->center);
	cp = vunit(vminus(rec->p, sp->center));//
	// cp_xz = vmult(vunit(vec3(cp.x, 0, cp.z)), sp->radius);
	cp_xz = vunit(vec3(cp.x, 0, cp.z)); //
	// int	sign = 1;
	// if (cp_xz.x < 0)
	// 	sign = -1;
	// x_theta = acos(sign * vlength(vec3(cp.x, 0, cp.z)) / cp.x);
	x_theta = acos(vdot(cp_xz, x_axis));
	if (cp.z  > 0)
		x_theta = 2 * M_PI - x_theta;
	y_theta = acos(vdot(cp, y_axis));

	x_theta = x_theta * 180 / M_PI;
	y_theta = y_theta * 180 / M_PI;
	coord_x = (int)(2048.0 / 360.0 * x_theta);
	coord_y = (int)(1024.0 / 180.0 * y_theta);
	dst = par->earth_img.addr + (coord_y * par->earth_img.line_length + coord_x * (par->earth_img.bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (convert(color));
}

t_bool	hit_sp(t_sphere *sp, t_ray *ray, t_hit_rec *rec, t_color3 albedo, t_param *par)
{
	double		discriminant;
	double		sqrtd;
	double		root;
	double		a;
	double		half_b;

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
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	// rec->albedo = albedo;
	// (void)par;
	rec->albedo = get_albedo(sp, rec, par, albedo); //TODO : 좌표설정해서 xpm 색 가져오기
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
