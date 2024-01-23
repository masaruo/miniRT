/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:20:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/01/22 15:23:42 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_list.h"
#include <stdio.h>
#include "t_shape.h"
#include "t_light.h"
#include "t_vec3.h"

void	print_tshape(t_list *head)
{
	t_list	*crnt;
	t_shape	*shape;
	t_material material;

	crnt = head->next;
	while (crnt)
	{
		shape = crnt->content;
		material = shape->material;
		if (shape->type == sphere_type)
		{
			t_sphere sphere;
			sphere = shape->u_data.sphere;
			printf("sphere's r [%lf]\n", sphere.r);
		}
		else if (shape->type == plane_type)
		{
			t_plane plane;
			plane = shape->u_data.plane;
			vec3_print(&plane.position);
			printf(" <= position / normal =>\n");
			vec3_print(&plane.normal);
			printf("plane\n");
		}
		else
		{
			;
		}
		crnt = crnt->next;
	}
}

void	print_tlight(t_list *head)
{
	t_list *crnt;
	t_light *light;

	crnt = head->next;
	while (crnt)
	{
		light = crnt->content;
		printf("light vector: ");
		vec3_print(&light->vector);
		crnt = crnt->next;
	}
}
