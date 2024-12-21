/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:55:28 by emaillet          #+#    #+#             */
/*   Updated: 2024/12/22 00:17:28 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mt_client.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	set_status(int i)
{
	static int	check = 0;

	if (i >= 0)
		check = i;
	return (check);
}

void	sig_handle(int signal)
{
	if (signal == SIGUSR1)
		set_status(1);
	else
	{
		while (!set_status(-1))
			usleep(10);
		set_status(0);
	}
}

void	ft_send_char(unsigned char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		sig_handle(0);
		i++;
	}
}

void	ft_send_strlen(int len, int pid)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (len & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		sig_handle(0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	int		len;
	int		pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_printf(RED"[ERROR] Usage: %s <server_pid> <string>\n"RES, argv[0]);
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (EXIT_FAILURE);
	str = argv[2];
	len = ft_strlen(str);
	signal(SIGUSR1, sig_handle);
	ft_send_strlen(len, pid);
	while (str[i])
		ft_send_char(str[i++], pid);
	ft_send_char('\0', pid);
	return (EXIT_SUCCESS);
}
