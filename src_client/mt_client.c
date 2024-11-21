/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:39:54 by emaillet          #+#    #+#             */
/*   Updated: 2024/11/21 01:54:41 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mt_client.h"
#include <signal.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	ft_printf("Client PID : %i\n", getpid());
	if (argc == 3 && ft_atoi(argv[1]) != 0)
	{
		ft_printf(GRN"[Info] : Initialization\n"RES);
		client_init((pid_t)ft_atoi(argv[1]), argv[2]);
	}
	else
	{
		ft_printf(RED"[Error] : Invalid arguments !\n"RES);
		ft_printf(YEL"[Usage] : ./client `server_pid` `string_message`\n"RES);
	}
	return (0);
}

void	client_init(pid_t server_pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("String : %s\n", str);
	if (kill(server_pid, SIGUSR2) == -1)
		ft_printf(RED"[Error] : Invalid server pid");
	while (str[i] != 0)
	{
		j = (int)str[i];
		while (j)
		{
			kill(server_pid, SIGUSR1);
			usleep(2);
			j--;
		}
		kill(server_pid, SIGUSR2);
		usleep(1);
		i++;
	}
}
