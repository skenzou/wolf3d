/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:01:05 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/08 11:12:25 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char c;

	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			n = -147483648;
			write(fd, "2", 1);
		}
		n = n * -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = 48 + n % 10;
	write(fd, &c, 1);
}
