/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:40:09 by emaillet          #+#    #+#             */
/*   Updated: 2024/11/21 00:59:46 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MT_SERVER_H
# define MT_SERVER_H
# include <signal.h>
# include "../src_shared/ft_printf/func/ft_printf.h"
# include "../src_shared/libft/libft.h"
# include <unistd.h>

# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define RES  "\x1B[0m"

void	signal_handler(int sig);

#endif
