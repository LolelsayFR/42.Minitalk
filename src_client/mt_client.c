/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:39:54 by emaillet          #+#    #+#             */
/*   Updated: 2024/11/21 21:54:30 by emaillet         ###   ########.fr       */
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

	i = 0;
	ft_printf("String : %s\n", str);
	if (kill(server_pid, SIGUSR2) == -1)
		ft_printf(RED"[Error] : Invalid server pid");
	while (str[i])
	{
		chatosi(server_pid, str[i]);
		usleep(35);
		i++;
	}
}

void	chatosi(pid_t server_pid, char c)
{
	int	d;
	int	u;

	u = c % 10;
	d = (((c % 100) - u) / 10);
	if (c >= 100)
		mt_sigsend(server_pid, 1);
	mt_sigsend(server_pid, 2);
	while (d)
	{
		mt_sigsend(server_pid, 1);
		d--;
	}
	mt_sigsend(server_pid, 2);
	while (u)
	{
		mt_sigsend(server_pid, 1);
		u--;
	}
	mt_sigsend(server_pid, 2);
}

void	mt_sigsend(pid_t server_pid, int sig)
{
	const int	cooldown = 15;

	if (sig == 1)
		kill(server_pid, SIGUSR1);
	else if (sig == 2)
	{
		kill(server_pid, SIGUSR2);
		usleep(5);
	}
	usleep(cooldown);
}
