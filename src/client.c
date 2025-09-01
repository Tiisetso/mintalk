/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:13 by timurray          #+#    #+#             */
/*   Updated: 2025/09/01 20:11:20 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"



int main(int ac, char **av)
{
	if (ac != 3)
		ft_putendl_fd("Enter PID and message string.", 2);
	else
	{
		ft_printf("av: %s", av[2]);
	}
	return(0);
}

//get server PID and message string
//Error check
//use SIGSUR1 and SIGSUR2
