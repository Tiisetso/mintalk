/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:15 by timurray          #+#    #+#             */
/*   Updated: 2025/09/06 13:30:32 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void signal_detect(int sig, siginfo_t *info, void *context)
{
	static unsigned char c = 0;
	static int bit = 7;
	static int i = 0;
	static int size = 4096;
	static char *buffer;
	
	(void)context;

	if (!buffer)
	{
		buffer = (char *)malloc(size * sizeof(char) + 1);
		if (!buffer)
			exit(1);
	}
	if (i + 1 == size)
	{
		char *temp;
		size *=  2;
		temp = (char *)malloc(size * sizeof(char) + 1);
		if (!temp)
			exit(1);
		temp = ft_memcpy(temp, buffer, i);
		free(buffer);
		buffer = temp;
	}

	if(sig == SIGUSR2)
		c = c | ((unsigned int)1 << bit);

	if (--bit < 0)
	{
		if (c == '\0')
		{
			buffer[i] = '\0';
			ft_putendl_fd(buffer,1);
			i = 0;
			free(buffer);
			buffer = NULL;
			size = 200;
			i = 0;
		}
		else
			buffer[i++] = c;
		c = 0;
		bit = 7;
	}
	if (info)
		kill(info-> si_pid, SIGUSR1);
}

static void    init_sigact(void)
{
    struct sigaction    sigact;

    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = signal_detect;
    sigemptyset(&sigact.sa_mask);
    sigaddset(&sigact.sa_mask, SIGUSR1);
    sigaddset(&sigact.sa_mask, SIGUSR2);
    if (sigaction(SIGUSR1, &sigact, 0) == -1)
        ft_putendl_fd("fail",2);
    if (sigaction(SIGUSR2, &sigact, 0) == -1)
        ft_putendl_fd("fail",2);
}

int main(void)
{
	pid_t pid;

	init_sigact();

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	
	while (1)
        pause();
		
	return(0);
}


//Error cascading handling