/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:03:05 by zaldhahe          #+#    #+#             */
/*   Updated: 2025/05/20 19:27:11 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	return (0);
}
