/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 05:27:25 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 05:34:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char
	hit_sphere(t_vect3 center, double radius, t_ray *ray)
{
	t_vect3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vect3_sub(ray->ori, center);
	a = vect3_dot(ray->dir, ray->dir);
	b = 2.0 * vect3_dot(oc, ray->dir);
	c = vect3_dot(oc, oc) - radius * radius;
	discriminant = b*b - 4 * a *c;
	return (discriminant > 0);
}

t_vect3
	ray_color(t_ray *r)
{
	t_vect3	unit_dir;
	double	t;

	if (hit_sphere((t_vect3){0, 0, -1}, 0.5, r))
		return ((t_vect3){1, 0, 0});
	unit_dir = vect3_unit(r->dir);
	t = 0.5 * (unit_dir.y + 1.0);
	return (
		vect3_add
		(
			vect3_mult_scalar((t_vect3){1.0, 1.0, 1.0}, 1.0 - t),
			vect3_mult_scalar((t_vect3){0.5, 0.7, 1.0}, t)
		)
	);
}
