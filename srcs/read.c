/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 04:12:09 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/21 19:33:47 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int		check_line(char *str, int fd)
{
	char	**words;
	int		i;
	int		j;

	if (!(words = ft_strsplit(str, ' ')))
		end(ANSI_RED "malloc fail", fd);
	j = -1;
	while (words[++j])
	{
		if (!(i = 0) && words[j][i] == '-')
			i++;
		while (ft_isdigit(words[j][i]))
			i++;
		if (words[j][i])
			end(ANSI_RED "map error", fd);
	}
	ft_splitdel(words);
	return (j);
}

static	int		create_list(int fd, t_list **begin)
{
	char		*str;
	int			ret;
	t_list		*lst;
	int			words;
	int			lines;

	words = -1;
	lines = 0;
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		if (words == -1)
			words = check_line(str, fd);
		if (words != check_line(str, fd))
			return (ft_lstdestroy(begin));
		if (!(lst = ft_lstnew((void *)str, ft_strlen(str) + 1)))
			return (ft_lstdestroy(begin));
		ft_lstadd(begin, lst);
		ft_strdel(&str);
		lines++;
	}
	if (ret)
		return (ft_lstdestroy(begin));
	ft_lstrev(begin);
	return (lines);
}

static	int		*create_row(char *str, int fd)
{
	char	**words;
	int		*row;
	int		j;

	row = (int *)ft_memalloc(sizeof(int) * (ft_count_words(str, ' ') + 2));
	if (!(words = ft_strsplit(str, ' ')) || !row)
		end(ANSI_RED "malloc fail", fd);
	j = 0;
	row[0] = 1;
	while (words[j])
	{
		row[j + 1] = ft_atoi(words[j]);
		j++;
	}
	row[j + 1] = 1;
	ft_splitdel(words);
	return (row);
}

void			add_edge(t_map *map)
{
	int i;
	int linesize;

	linesize = sizeof(int) * map->w;
	map->board[0] = (int *)ft_memalloc(linesize);
	map->board[0] == NULL ? exit(1) : 0;
	i = 0;
	while (i < map->w)
		map->board[0][i++] = 1;
	map->board[map->h] = (int *)ft_memalloc(linesize);
	map->board[map->h] == NULL ? exit(1) : 0;
	ft_memcpy((void *)map->board[map->h++], map->board[0], linesize);
}

t_map			*create_map(int fd)
{
	t_list		*list;
	t_list		*begin;
	char		*str;
	int			lines;
	t_map		*map;

	begin = NULL;
	lines = create_list(fd, &begin);
	map = (t_map *)malloc(sizeof(t_map));
	map ? map->board = (int **)malloc(sizeof(int *) * (lines + 2)) : 0;
	if (!(list = begin) || !lines)
		end(ANSI_RED "map error", fd);
	if (!map || !(map->board))
		end(ANSI_RED "malloc fail", fd);
	map->w = ft_count_words((char *)list->content, ' ') + 2;
	map->h = 1;
	while (map->h <= lines)
	{
		str = (char *)list->content;
		map->board[(map->h)++] = create_row(str, fd);
		list = list->next;
	}
	add_edge(map);
	ft_lstdestroy(&begin);
	return (map);
}
