#include "../include/cub3d.h"

int	count_lines(char *path)
{
	int		fd;
	char	*line;
	int		total_lines;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	return (-1);
	total_lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		total_lines++;
	}
	close(fd);
	return (total_lines);
}

char	**extract_content(char *path)
{
	int		fd;
	char	**content;
	char	*line;
	int		index;
	int		line_count;
	
	line_count = count_lines(path) + 1;
	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = (char **)ft_calloc(line_count, 8);
	if (content == NULL)
		return (NULL);
	index = 0;
	line = get_next_line(fd);
	while (line)
	{
		content[index] = line;
		line = get_next_line(fd);
		index++;
	}
	content[index] = NULL;
	close(fd);
	return (content);
}

int	check_indents(int *identifier_count)
{
	if (identifier_count[0] != 1)
		return (write(1, "Error\nInvalid floor identifiers\n", 42), 0);
	if (identifier_count[1] != 1)
		return (write(1, "Error\nInvalid ceiling identifiers\n", 44), 0);
	if (identifier_count[2] != 1)
		return (write(1, "Error\nInvalid number of NO identifiers\n", 39), 0);
	if (identifier_count[3] != 1)
		return (write(1, "Error\nInvalid number of SO identifiers\n", 39), 0);
	if (identifier_count[4] != 1)
		return (write(1, "Error\nInvalid number of WE identifiers\n", 39), 0);
	if (identifier_count[5] != 1)
		return (write(1, "Error\nInvalid number of EA identifiers\n", 39), 0);
	return (1);
}

int	validate_idents(char *line, int *identifier_count)
{
	if (line[0] == 'F' && line[1] == ' ')
		identifier_count[0]++;
	else if (line[0] == 'C' && line[1] == ' ')
		identifier_count[1]++;
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		identifier_count[2]++;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		identifier_count[3]++;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		identifier_count[4]++;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		identifier_count[5]++;
	else
		return (0);
	return (1);
}

int	check_content(char **content)
{
	int		index;
	char	*line;
	int		identifier_count[6];

	index = 0;
	if (content[0] == NULL)
		return (write(1, "Error\nEmpty file\n", 17), 0); //Error here when file not even empty
	ft_memset(identifier_count, 0, sizeof(int) * 6);
	while (content[index] != NULL)
	{
		line = ft_strtrim(content[index], " \t\n");
		if (line[0] && validate_idents(line, identifier_count) == 0)
			return (write(1, "Error\nInvalid identifier\n", 25), free(line), 0);
		free(line);
	}
	if (check_indents(identifier_count) == 0)
		return (0);
	return (1);
}
