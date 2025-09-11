/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:38:19 by timurray          #+#    #+#             */
/*   Updated: 2025/09/07 12:20:38 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static int	pid_value_check(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			ft_putendl_fd("PID must have decimal digits.", 2);
			return (0);
		}
		i++;
	}
	if (s[0] == '0' && s[1] != '\0')
	{
		ft_putendl_fd("PID cannot have leading zeroes.", 2);
		return (0);
	}
	return (1);
}

pid_t	get_pid(const char *s)
{
	long	pid;

	if (!s || !s[0])
	{
		ft_putendl_fd("PID required.", 2);
		return (0);
	}
	if (!pid_value_check(s))
		return (0);
	pid = ft_atol(s);
	if (!(pid > 0 && pid <= 4194304))
	{
		ft_putendl_fd("Valid PID integers (range 1 - 4194304) only.", 2);
		return (0);
	}
	if (kill(pid, 0) == -1)
	{
		ft_putendl_fd("PID does not exist or can not be accessed.", 2);
		return (0);
	}
	return ((pid_t)(pid));
}
