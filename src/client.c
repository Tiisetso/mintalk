/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:13 by timurray          #+#    #+#             */
/*   Updated: 2025/09/03 15:01:54 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


int send_char(pid_t pid, unsigned char c)
{
	int i;
	int bit;

	i = 8;
	while(i > 0)
	{
		i--;
		bit  = (c >> i) & 1;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
	}
	return (0);
}

int send_string(pid_t pid, char *msg)
{
	int i;

	i = 0;
	while(msg[i])
	{
		send_char(pid, msg[i]);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	pid_t pid;


	if (ac != 3)
	{
		ft_putendl_fd("Enter PID and message string.", 2);
		return (1);
	}
	else
	{
		pid = ft_atoi(av[1]);
		ft_printf("pid: %d\n", pid);
		ft_printf("msg: %s\n", av[2]);
		send_string(pid, av[2]);
	}
	return(0);
}

//Error check
// -1 exception? Edge cases?