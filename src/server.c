/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:15 by timurray          #+#    #+#             */
/*   Updated: 2025/09/02 14:10:42 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int main(void)
{
	pid_t pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);

	//infinite loop to receive signal
	return(0);
}

//wait for signals
//process signal? Unicode?
//show the result unicode?
//send signal back. Read receipt?
