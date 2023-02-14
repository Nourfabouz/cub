/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/15 18:00:25 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

//Check for duplicates
int		check_identifiers(char **s, bool *exist, t_data *mlx)
{
	printf("file name %s\n", s[1]);
	/*int fd = open(s[1], O_RDONLY);
	if (fd < 0)
	{
		printf("make sure you're trying to open the right file\n");
		return (-1);
	}*/
	if (!ft_strcmp(s[0], "NO") && !exist[0])
	{
		printf("\nhere no?!\n");
		exist[0] = 1;
		mlx->north_texture i= s[1];
	}
	else if (!ft_strcmp(s[0], "SO") && !exist[1])
	{
		printf("\nhere so?!\n");
		exist[1] = 1;
		mlx->south_texture = s[1];
	}
	else if (!ft_strcmp(s[0], "WE") && !exist[2])
	{
		printf("\nhere we?!\n");
		exist[2] = 1;
		mlx->west_texture = s[1];
	}
	else if (!ft_strcmp(s[0], "EA") && !exist[3])
	{
		printf("\nhere ea?!\n");
		exist[3] = 1;
		mlx->east_texture = s[1];
	}
	else if (!ft_strcmp(s[0], "F") && !exist[4])
		exist[4] = 1;
	else if (!ft_strcmp(s[0], "C") && !exist[5])
		exist[5] = 1;
	else if (ft_strcmp(s[0], "\n"))
	{
		//printf("\n here?!\n");
		return (1);
	}
	return (0);
}

/*void free_sp(char ***sp)
  {

  size_t len = ft_strlen(*(*sp));
  printf("len is %zu\n", len);
  }*/

int	main(int argc, char **argv)
{
	char	*s;
	t_data	mlx;

	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		if (ft_strchr(argv[1], '.') == ft_strrchr(argv[1], '.'))
		{
			char	*pt = ft_strchr(argv[1], '.');

			if (!pt || ft_strcmp(pt, ".cub"))
				return (printf("Error\nWrong extension!"));
		}
		else
			return (printf("Error\nWrong extension!"));
		int	fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (printf("Error\nCannot open the file!"));
		char	**sp;
		//CHECK IF INDENTIFIER EXIST
		bool	*exist = ft_calloc(sizeof(bool), 6);
		s = get_next_line(fd);
		while (s)
		{
			printf("the string from the file %s", s);
			sp = ft_split(s, ' ');
			if (!sp)
				return (printf("Error\nSomething went wrong in split!"));
			if (check_identifiers(sp, exist, &mlx) == 1)
				return (printf("Error\nWrong or duplicated identifiers!\n"));
			/*else if (check_identifiers(sp, exist, &mlx) == -1)
				return (printf("make sure you're trying to open the right file\n"));*/
			free(s);
			//free_sp(&sp);
			s = get_next_line(fd);
		}
		int i = 0;
		while (i < 6)
		{
			if (exist[i] == 0)
				return (printf("One or more identifiers are missing\n"));
			i++;
		}

		//system("leaks Cub3d");
	}
	return (0);
}
