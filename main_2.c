/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:18:54 by fabou-za          #+#    #+#             */
/*   Updated: 2023/02/14 19:05:12 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

int ft_strlenew(char *s);
size_t ft_maplen(char **s);
void    clear_splited(char **s);

void	init_mlx(t_data *mlx)
{
	mlx->north_texture = NULL;
	mlx->west_texture = NULL;
	mlx->east_texture = NULL;
	mlx->south_texture = NULL;
	mlx->floor_color = 0;
	mlx->ceiling_color = 0;
}

void	free_mlx(t_data *mlx)
{
	char *temp;
	int j;

	j = 0;
	while (mlx->lines[j])
	{
		temp = mlx->lines[j];
		mlx->lines[j] = mlx->lines[j + 1];
		free(temp);
		j++;
	}
	free(mlx->lines);
	if (mlx->north_texture)
		free(mlx->north_texture);
	if (mlx->west_texture)
		free(mlx->west_texture);
	if (mlx->east_texture)
		free(mlx->east_texture);
	if (mlx->south_texture)
		free(mlx->south_texture);
}

void read_file(int fd, t_data *mlx)
{
	char *s;
	char **temp;
	int i;
	int j;

	i = 1;
	temp = NULL;
	while((s = get_next_line(fd)))
	{
		temp = mlx->lines;
		mlx->lines = malloc((i + 1) * sizeof(char *));
		j = 0;
		if (temp)
		{
			while (temp[j])
			{
				mlx->lines[j] = temp[j];
				j++;
			}
		}
		free(temp);
		mlx->lines[j++] = s;
		mlx->lines[j] = 0;
		i++;
	}
}

int read_textures(char *texture, char identif, t_data *mlx)
{
	int len;

	if (texture == NULL)
		return (-1);
	len = ft_strlenew(texture);
	texture[len] = '\0';
	if (ft_strchr(texture, '.') == ft_strrchr(texture, '.'))
	{
		char    *pt = ft_strchr(texture, '.');
		if (!pt || ft_strcmp(pt, ".xpm"))
			return (-1);
	}
	else
		return (-1);
	if (identif == 'N')
		mlx->north_texture = strdup(texture);
	else if (identif == 'S')
		mlx->south_texture = strdup(texture);
	else if (identif == 'E')
		mlx->east_texture = strdup(texture);
	else if (identif == 'W')
		mlx->west_texture = strdup(texture);
	return (0);
}

int to_color(char **str)
{
	int i;
	int color;
	int tmp;

	i = 0;
	color = 0;
	while(str[i])
	{
		tmp = atoi(str[i]);//
		printf("the number %d\n", tmp);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ * 8)));
	}
	return (color);
}

int check_color(char **str)
{
	int len;
	int i;

	len = ft_strlenew(*str);
	(*str)[len] = '\0';
	i = 0;
	while ((*str)[i])
	{
		if (ft_strchr(" ,0123456789", (*str)[i++]) == NULL)
			return (-1);
	}
	return (0);
}

int color_stock(char c, char *str, t_data *mlx)
{
	char **splited;
	char **split;
	int color;

	if (check_color(&str) == -1)
		return (-1);
	splited = ft_split(str, ',');
	split = ft_split(str, ' ');
	if (!splited || !split || ft_maplen(splited) != 3 || ft_maplen(split) != 3)
	{
		clear_splited(splited);
		clear_splited(split);
		return (-1);
	}
	clear_splited(split);
	color = to_color(&splited[0]);
	clear_splited(splited);
	if (color == -1)
		return (-1);
	if (c == 'F')
		mlx->floor_color = color;
	else
		mlx->ceiling_color = color;
	return (0);
}

int parse_color(char **splited, char *str, bool *exist, t_data *mlx)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (str[i] == ' ')
		i++;
	if (!strcmp(splited[0], "F") && !exist[5])
	{
		exist[5] = 1;
		if (str[i] && str[i] == 'F')
			i++;
		status = color_stock('F', &str[i], mlx);
	}
	else if (!exist[4])
	{
		exist[4] = 1;
		if (str[i] && str[i] == 'C')
			i++;
		status = color_stock('C', &str[i], mlx);
	}
	else
		return (-1);
	return (status);
}

int fill_identif(bool *exist, char *str, t_data *mlx, char c)
{
	int status;

	status = 0;
	(*exist) = 1;
	status = read_textures(str, c, mlx);
	return (status);
}

int check_identifiers(char **str, bool *exist, t_data *mlx)
{
	int status;

	status = 0;
	if(!ft_strcmp("NO", str[0]) && !exist[0])
		status = fill_identif(&exist[0], str[1], mlx, 'N');
	else if (!ft_strcmp("SO", str[0]) && !exist[1])
		status = fill_identif(&exist[1], str[1], mlx, 'S');
	else if (!ft_strcmp("EA", str[0]) && !exist[2])
		status = fill_identif(&exist[2], str[1], mlx, 'E');
	else if (!ft_strcmp("WE", str[0]) && !exist[3])
		status = fill_identif(&exist[3], str[1], mlx, 'W');
	else
		return (-1);
	if (status == -1)
		return (-1);
	return (0);
}

void	clear_splited(char **s)
{
	char *temp;
	int j;

	j = 0;
	while(s[j])
	{
		temp = s[j];
		s[j] = s[j + 1];
		free(temp);
		j++;
	}
	free(s);
}

size_t	ft_maplen(char **s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strlenew(char *s)
{
	size_t i;

	i = 0;
	while (s[i] && (s[i] != '\n'))
		i++;
	return (i);
}

int check_map(char **str)
{
	int len_first;
	int len_last;
	int len_map;
	int j;
	int i;
	int tmp;

	len_first = ft_strlenew(str[0]);
	len_map = ft_maplen(str);
	len_last = ft_strlenew(str[len_map - 1]);
	//printf("last char len_map is '%c'\n", str[len_map - 1][len_last - 1]);
	j = 0;
	while ((str[0][j] && j <= len_first - 1))
	{
		if ((str[0][j] != '1' && str[0][j] != ' '))
			return (1);
		j++;
	}
	j = 0;
	while (str[len_map - 1][j] && j <= len_last - 1)
	{
		if (str[len_map - 1][j] != '1' && str[len_map - 1][j] != ' ')
			return (1);
		j++;
	}
	j = 1;
	//printf("len_map %d\n", len_map - 2);
	while (str[j] && (j <= len_map - 1))
	{
		len_first = ft_strlenew(str[j]);
		str[j][len_first] = '\0';
		//printf("here the char at the end of the string %c\n", str[j][len_first - 1]);
		i = 0;
		while (str[j][i]== ' ')
			i++;
		while (str[j][len_first - 1] == ' ')
			len_first--;
		//printf("\nhere the char at the end of the string %c\n", str[j][len_first - 1]);
		if (str[j][i] != '1' || str[j][len_first - 1] != '1')
			return (1);
		i++;
		while (str[j][i] && i < len_first - 1)
		{
			if (str[j][i] != '1' && str[j][i] != '0' && str[j][i] != ' ' && str[j][i] != 'N' && str[j][i] != 'S' \
					&& str[j][i] != 'W' && str[j][i] != 'E')
				return (1);
			if (str[j][i] == ' ' && str[j][i + 1] != ' ' && str[j][i + 1] != '\0')
			{
				tmp = j;
				while (str[j][i] == ' ' && str[j][i + 1] != '\0')
				{
					if (str[j][i - 1] != '1' || str[j][i + 1] != '1')
					{
						printf("A problem here, char before '%c' and char after '%c'\n", str[j][i - 1], str[j][i + 1]);
						return (1);
					}
					j--;
				}
				if (str[j][i] != '1')
				{
					printf("another problem here with '%c'\n", str[j][i]);
					return (1);
				}
				j = tmp;
			}
			i++;
		}
		j++;
	}
	return (0);
}

int check_dup(bool *exist)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (exist[i++] == 0)
		{
			free(exist);
			return (-1);
		}
	}
	return (0);
}

int check_fun(char *line, bool *exist, t_data *mlx)
{
	int if_error;
	char **splited;

	if_error = 0;
	splited = ft_split(line, ' ');
	if (!ft_strcmp(splited[0], "F") || !strcmp(splited[0], "C"))
		if_error = parse_color(splited, line, exist, mlx);
	else if (splited[0][0] == '1' || splited[0][0] == '0')
		if_error = 2;
	else if (!ft_strcmp("\n", splited[0]))
		if_error = 0;
	else
		if_error = check_identifiers(splited, exist, mlx);
	clear_splited(splited);
	if (if_error == -1)
		free(exist);
	return (if_error);
}

int identif_loop(char **lines, int *j, bool *exist, t_data *mlx)
{
	int if_error;

	if_error = 0;
	while (lines[*j])
	{
		if_error = check_fun(lines[*j], &exist[0], mlx);
		if (if_error == 2)
			break;
		if (if_error == -1)
			return (-1);
		(*j)++;
	}
	return (if_error);
}

int	check_function(t_data *mlx)
{
	int j;
	int	 if_error;
	bool *exist;
	int if_dup;

	exist = ft_calloc(6, 1);
	if_dup = 0;
	j = 0;
	/*while (mlx->lines[j])
	{
		if_error = check_fun(mlx->lines[j], &exist[0], mlx);
		if (if_error == 2)
			break;
		if (if_error == -1)
			return (-1);
		j++;
	}*/
	if_error = identif_loop(mlx->lines, &j, &exist[0], mlx);
	if (if_error == -1)
		return (-1);
	if ((if_dup = check_dup(&exist[0])) == -1)
		return (-1);
	free(exist);
	if (if_error == 2)
	{
		if (check_map(&mlx->lines[j]) == 1)
			return (-1);
	}
	else
		return (3);
	return (0);
}

int check_file_extension(char *s)
{
	char *pt;

	pt = NULL;
	if (ft_strchr(s, '.') == ft_strchr(s, '.'))
	{
		pt = ft_strchr(s, '.');
		if (!pt || ft_strcmp(pt, ".cub"))
		{
			printf("ERROR\nWrong extension!");
			return (1);
		}
	}
	else
	{
		printf("ERROR\nWrong extension!");
		return (1);
	}
	return (0);
}

void    display_message_error(int if_error)
{
	if (if_error == -1)
		printf("ERROR\nParse error\n");
	else if (if_error == 3)
		printf("ERROR\nNo map found\n");
}

int	main(int argc, char **argv)
{
	t_data	mlx;
	int if_error;

	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		if ((if_error = check_file_extension(argv[1])) == 1)
			return (1);
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (printf("ERROR\ncannot open the file"));
		mlx.lines = NULL;
		init_mlx(&mlx);
		read_file(fd, &mlx);
		if_error = check_function(&mlx);
		display_message_error(if_error);
		//printf("the floor color is %d\n", mlx.floor_color);
		//printf("the ceiling color is %d\n", mlx.ceiling_color);
		free_mlx(&mlx);
		//system("leaks Cub3d");
	}
}
