/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:21:10 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/28 16:51:48 by nabouzah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"
# include <stdbool.h>
# define TILE_SIZE 32
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15
# define WIN_WIDTH (TILE_SIZE * MAP_NUM_COLS)
# define WIN_HEIGHT (TILE_SIZE * MAP_NUM_ROWS)
# define MOVE_SPEED 6.0
# define ROTATION_ANGLE M_PI / 2
# define ROTATION_SPEED 2 * (M_PI / 180)

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		line_len;
	int		endian;
	int		bpp;
}	t_img;

typedef struct s_player
{
	int		x;
	int		y;
	int		radius;
	int		turnDirection;
	int		walkDirection;
	double	rotation_angle;
}	t_player;

typedef struct s_data
{
	/*void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_player p;*/
	char *north_texture;
	char *west_texture;
	char *east_texture;
	char *south_texture;
    int floor_color;
    int ceiling_color;
	char **map;
	char **lines;
}	t_data;

char    *ft_strchr(const char *s, int c);
char    *ft_strrchr(const char *s, int c);
int    ft_strcmp(const char *s1,  const char *s);
char	**ft_split(const char *s, char c);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
void    *ft_calloc(size_t count, size_t size);
#endif
