/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimendes <vimendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:34 by vimendes          #+#    #+#             */
/*   Updated: 2024/08/28 12:59:43 by vimendes         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char c)
{
	int		size;
	int		j;
	char	*str;

	if (s1)
		size = ft_strlen(s1);
	else
		size = 0;
	str = malloc(sizeof(char) * (size + 2));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s1 && s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	str[j++] = c;
	str[j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

void	my_handler(int signum, siginfo_t *s_info, void *context)
{
	static int		bit;
	static int		i;
	static char		*str;
	char			*temp;
	
	(void) context;
	if (!str)
		str = ft_strdup("");
	if (signum == SIGUSR1)
		i |= (1 << bit);
	if (++bit == 8)
	{
		temp = ft_strjoin(str, (char)i);
		str = temp;
		if (i == 0)
		{
			ft_putendl_fd(str, 1);
			free(str);
			str = NULL;
			kill(s_info->si_pid, SIGUSR2);
		}
		i = 0;
		bit = 0;
	}
	kill(s_info->si_pid, SIGUSR1);
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
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
