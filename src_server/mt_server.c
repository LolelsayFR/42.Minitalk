/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:40:04 by emaillet          #+#    #+#             */
/*   Updated: 2024/11/21 21:58:48 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mt_server.h"

int	g_sig[2];

int	main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_printf(GRN"Server PID : %i\n"RES, getpid());
	while (1)
	{
		pause();
	}
	ft_printf(RED"Stop"RES);
	return (0);
}

void	signal_handler(int sig)
{
	if (sig == 10)
		g_sig[0] += 1;
	else
	{
		g_sig[1] += 1;
		if (g_sig[1] <= 3 && ft_isascii(g_sig[0] * 10))
			g_sig[0] *= 10;
		else
		{
			ft_printf("%c", g_sig[0]);
			g_sig[1] = 0;
			g_sig[0] = 0;
		}
	}
}
