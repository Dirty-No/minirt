/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 02:54:38 by user42            #+#    #+#             */
/*   Updated: 2021/05/16 05:29:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect3 vect3_minus(t_vect3 vect)
{
	return ((t_vect3){-vect.x, -vect.y, -vect.z});
}

double
	vect3_squared_lenght(t_vect3 vect3)
{
	return (vect3.x * vect3.x + vect3.y * vect3.y + vect3.z * vect3.z);
}

double
	vect3_lenght(t_vect3 vect3)
{
	return (sqrt(vect3_squared_lenght(vect3)));
}


void
	vect3_make_unit(t_vect3	*vect3)
{
	double	k;

	k = 1.0 / sqrt(vect3_squared_lenght(*vect3));
	vect3->x *= k;
	vect3->y *= k;
	vect3->z *= k;
}

t_vect3 vect3_add(t_vect3 r, t_vect3 l)
{
	return ((t_vect3){r.x + l.x, r.y + l.y, r.z + l.z});
}

t_vect3 vect3_sub(t_vect3 r, t_vect3 l)
{
	return ((t_vect3){r.x - l.x, r.y - l.y, r.z - l.z});
}

t_vect3 vect3_mult(t_vect3 r, t_vect3 l)
{
	return ((t_vect3){r.x * l.x, r.y * l.y, r.z * l.z});
}

t_vect3 vect3_div(t_vect3 r, t_vect3 l)
{
	return ((t_vect3){r.x / l.x, r.y / l.y, r.z / l.z});
}

t_vect3	vect3_mult_scalar(t_vect3 v, double s)
{
	return ((t_vect3){v.x * s, v.y * s, v.z * s});
}

t_vect3	vect3_div_scalar(t_vect3 v, double s)
{
	return ((t_vect3){v.x / s, v.y / s, v.z / s});
}

double	vect3_dot(t_vect3 r, t_vect3 l)
{
	return (r.x * l.x + r.y * l.y + r.z * l.z);
}

t_vect3	vect3_cross(t_vect3 r, t_vect3 l)
{
	return ((t_vect3)
	{
		r.y * l.z - r.z * l.y,
		-(r.x * l.z - r.z * l.x),
		r.x * l.y - r.y * r.x
	});
}

t_vect3	vect3_unit(t_vect3 v)
{
	return (vect3_div_scalar(v, vect3_lenght(v)));
}

t_vect3
	point_at_parameter(t_ray ray, double t)
{
	return (vect3_add(ray.ori, vect3_mult_scalar(ray.dir, t)));
}
