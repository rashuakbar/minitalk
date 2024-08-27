/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimendes <vimendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:34 by vimendes          #+#    #+#             */
/*   Updated: 2024/08/27 21:59:21 by vimendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (0);
	while (str[i] != 0)
	{
		dup[i] = (char)str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	my_handler(int signum, siginfo_t *s_info, void *context)
{
	static	int		bit;
	static int		i;
	static char		*str;
	char	*temp;
	int pid = s_info->si_pid;
	(void) context;

	if (!str)
		str = ft_strdup("");
	if (signum == SIGUSR1)
			i |= (1 << bit);
	if(++bit == 8)
	{
		temp = ft_strjoin(str, (char)i);
		str = temp;
		if (i == 0)
		{
			ft_putstr_fd(str,1);
			free(str);
			str = NULL;
		}
		i = 0;
		bit = 0;
	}
	pid = 0;
}

int	main(void)
{
	struct sigaction	sa_sig;
	
	sigemptyset(&sa_sig.sa_mask);
	sigaddset(&sa_sig.sa_mask, SIGINT);
	sigaddset(&sa_sig.sa_mask, SIGQUIT);
	sa_sig.sa_handler = 0;
	sa_sig.sa_flags = SA_SIGINFO;
	sa_sig.sa_sigaction = my_handler;
	sigaction(SIGUSR1, &sa_sig, NULL);
	sigaction(SIGUSR2, &sa_sig, NULL);
	ft_putstr_fd("PID: ",1);
	ft_putnbr_fd(getpid(),1);
	ft_putchar_fd('\n',1);
	while(1)
		pause();
	return (0);
}
