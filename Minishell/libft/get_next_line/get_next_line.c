/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:39:18 by elavrich          #+#    #+#             */
/*   Updated: 2024/11/22 18:12:31 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Ensures read_line is initialized as an empty string if it is NULL
char	*norm(char *read_line)
{
	if (!read_line)
	{
		read_line = malloc(1);
		if (!read_line)
			return (NULL);
		read_line[0] = '\0';
	}
	return (read_line);
}

// Reads from the file descriptor until a newline or EOF is encountered
char	*read_from_f(int fd, char *read_line)
{
	char	*storage_l;
	int		bytes_read;

	storage_l = malloc(BUFFER_SIZE + 1);
	if (!storage_l)
		return (free(read_line), NULL);
	read_line = norm(read_line);
	if (!read_line)
		return (free(storage_l), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, storage_l, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(storage_l), free(read_line), NULL);
		storage_l[bytes_read] = '\0';
		read_line = ft_strjoin_g(read_line, storage_l);
		if (!read_line)
			return (free(storage_l), free(read_line), NULL);
		if (ft_strchr_g(storage_l, '\n'))
			break ;
	}
	return (free(storage_l), read_line);
}

// Extracts the first line (up to and including the newline if present)
char	*cut_line(char *str)
{
	int		i;
	char	*fin_line;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	fin_line = malloc(i + 1);
	if (!fin_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		fin_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		fin_line[i++] = '\n';
	fin_line[i] = '\0';
	return (fin_line);
}

// Retrieves the remainder of the string after the newline
char	*get_rest(char *str)
{
	int		i;
	int		j;
	char	*remainder;

	j = 0;
	i = 0;
	while (str[j] && str[j] != '\n')
		j++;
	if (!str[j])
		return ((free(str)), NULL);
	j++;
	if (!str[j])
		return ((free(str)), NULL);
	remainder = malloc(ft_strlen_g(str) - j + 1);
	if (!remainder)
		return (free(str), NULL);
	while (str[j])
		remainder[i++] = str[j++];
	remainder[i] = '\0';
	free(str);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*st_line;
	char		*f_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	st_line = read_from_f(fd, st_line);
	if (!st_line)
		return (free(st_line), NULL);
	f_line = cut_line(st_line);
	if (!f_line)
	{
		free(st_line);
		st_line = NULL;
		return (NULL);
	}
	st_line = get_rest(st_line);
	if (!st_line)
	{
		free(st_line);
		st_line = NULL;
	}
	return (f_line);
}
// int	main(void)
// {
// 	int		fd;
// 	char	a;
// 	char	*next_line;

// 	a = 0;
// 	fd = open("example.txt",
// 			O_RDONLY);
// 	next_line = get_next_line(fd);
// 	printf("1-%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("2 %s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("3 %s", next_line);
// 	// printf("%zd", read(fd, &a, 1));
// 	// write(1, &a, 1);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("4 %s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("5 %s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("6 %s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("7 %s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("8 %s", next_line);
// 	free(next_line);
// 	//next_line = get_next_line(fd);
// 	// printf("9 %s", next_line);
// 	// free(next_line);
// 	// next_line = get_next_line(fd);
// 	// printf("10 %s", next_line);
// 	// free(next_line);
// 	// next_line = get_next_line(fd);
// 	// printf("11 %s", next_line);
// 	// free(next_line);
// 	// next_line = get_next_line(fd);
// 	// printf("12 %s", next_line);
// 	// free(next_line);
// 	// next_line = get_next_line(fd);
// 	// printf("13 %s", next_line);
// 	// free(next_line);
// 	// next_line = get_next_line(fd);
// 	// printf("14 %s", next_line);
// 	// free(next_line);
// 	// 	close(fd);
// 	// 	return (0)
// }
