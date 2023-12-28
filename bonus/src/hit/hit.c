/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:04:34 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/28 12:03:55 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit(t_object *world, t_ray *ray, t_hit_rec *rec, t_param *par)
{
	t_bool		hit_anything;
	t_hit_rec	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec, par))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}

t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_rec *rec, t_param *par)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sp(world->element, ray, rec, world->albedo, par);
	else if (world->type == PL)
		hit_result = hit_pl(world->element, ray, rec, world->albedo);
	else if (world->type == CY)
		hit_result = hit_cy(world->element, ray, rec, world->albedo);
	else if (world->type == DK)
		hit_result = hit_disk(world->element, ray, rec, world->albedo);
	else if (world->type == CN)
		hit_result = hit_cone(world->element, ray, rec, world->albedo);
	else if (world->type == CB)
		hit_result = hit_cb(world->element, ray, rec, world->albedo);
	return (hit_result);
}
