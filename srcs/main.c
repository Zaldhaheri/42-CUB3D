/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:03:05 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/21 16:00:42 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_all(t_data *data)
{
	if (data->plr)
		free(data->plr);
	if (data->line)
		free(data->line);
	if (data->map)
		free_darray(data->map);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3d_parser <path_to_cub_file>\n"), 1);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (printf("Error\nIncorrect file name\n"), 2);
	ft_memset(&data, 0, sizeof(data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (printf("Error\nMLX failed\n"), -1);
	if (parse(argv[1], &data) == -1)
		return (free(data.mlx), -1);
	init(&data);
	game_start(&data);
	free_all(&data);
	return (0);
}
