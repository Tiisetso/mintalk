/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:05:21 by timurray          #+#    #+#             */
/*   Updated: 2025/09/07 12:28:00 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>

# ifndef MSG_BUFFER_SIZE
#  define MSG_BUFFER_SIZE 4096
# endif

typedef struct sigaction	t_sigaction;

pid_t						get_pid(const char *pid);

#endif
