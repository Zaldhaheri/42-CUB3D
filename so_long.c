/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:32:57 by mbabayan          #+#    #+#             */
/*   Updated: 2024/05/23 04:59:26 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	map_parsing(char *path, t_game *game)
{
	init_map(&game->map);
	path_validation(path, &game->map);
	retrieve_map(path, &game->map);
	check_map_size(&game->map);
	check_map_borders(&game->map);
	check_map_elements(&game->map);
	check_element_amount(&game->map);
	path_finder(&game->map, game->map->map_copy, game->map->x, game->map->y);
	check_path_finder_result(&game->map);
	free_maps(NULL, game->map->map_copy, NULL);
}

int	main(int argc, char **argv)
{
	t_parsemap	game;
]
	image_check();
	game.map = malloc(sizeof(t_parsemap));
	if (argc != 2)
		(write(1, "Error\nInvalid number of arguments\n", 35), exit(EF));
	map_parsing(argv[1], &game);
	return (0);
}
