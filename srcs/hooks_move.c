/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:20:30 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/20 19:27:06 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_data *data, t_player *plr)
{
	double	pos_x;
	double	pos_y;

	pos_x = plr->pos_x + plr->dir_x * MOVE_SPEED;
	pos_y = plr->pos_y + plr->dir_y * MOVE_SPEED;
	if (data->map[(int)(plr->pos_y)][(int)(pos_x + plr->dir_x
			* COLLISION_MARGIN)] == '0')
		plr->pos_x = pos_x;
	if (data->map[(int)(pos_y + plr->dir_y
			* COLLISION_MARGIN)][(int)(plr->pos_x)] == '0')
		plr->pos_y = pos_y;
}

void	move_backward(t_data *data, t_player *plr)
{
	double	pos_x;
	double	pos_y;

	pos_x = plr->pos_x - plr->dir_x * MOVE_SPEED;
	pos_y = plr->pos_y - plr->dir_y * MOVE_SPEED;
	if (data->map[(int)(plr->pos_y)][(int)(pos_x - plr->dir_x
			* COLLISION_MARGIN)] == '0')
		plr->pos_x = pos_x;
	if (data->map[(int)(pos_y - plr->dir_y
			* COLLISION_MARGIN)][(int)(plr->pos_x)] == '0')
		plr->pos_y = pos_y;
}

void	move_left(t_data *data, t_player *plr)
{
	double	pos_x;
	double	pos_y;

	pos_x = plr->pos_x - plr->plane_x * MOVE_SPEED;
	pos_y = plr->pos_y - plr->plane_y * MOVE_SPEED;
	if (data->map[(int)(plr->pos_y)][(int)(pos_x - plr->plane_x
			* COLLISION_MARGIN)] == '0')
		plr->pos_x = pos_x;
	if (data->map[(int)(pos_y - plr->plane_y
			* COLLISION_MARGIN)][(int)(plr->pos_x)] == '0')
		plr->pos_y = pos_y;
}

void	move_right(t_data *data, t_player *plr)
{
	double	pos_x;
	double	pos_y;

	pos_x = plr->pos_x + plr->plane_x * MOVE_SPEED;
	pos_y = plr->pos_y + plr->plane_y * MOVE_SPEED;
	if (data->map[(int)(plr->pos_y)][(int)(pos_x + plr->plane_x
			* COLLISION_MARGIN)] == '0')
		plr->pos_x = pos_x;
	if (data->map[(int)(pos_y + plr->plane_y
			* COLLISION_MARGIN)][(int)(plr->pos_x)] == '0')
		plr->pos_y = pos_y;
}
