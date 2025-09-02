/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:13 by timurray          #+#    #+#             */
/*   Updated: 2025/09/02 16:39:44 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"



int main(int ac, char **av)
{
	pid_t pid;

	if (ac != 3)
		ft_putendl_fd("Enter PID and message string.", 2);
	else
	{
		ft_printf("av: %s\n", av[2]);
		pid = ft_atoi(av[1]);
		ft_printf("pid: %d\n", pid);
	}
	return(0);
}

//get server PID and message string
//Error check
//use SIGSUR1 and SIGSUR2
// -1 exception?