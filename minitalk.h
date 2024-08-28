/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimendes <vimendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:22:26 by vimendes          #+#    #+#             */
/*   Updated: 2024/08/27 17:09:48 by vimendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_atoi(const char *nptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	my_handler(int signum, siginfo_t *s_info, void *context);
void	send_bit(int pid, char c, size_t len);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char c);
size_t	ft_strlen(const char *src);
size_t	time_sleep(size_t size);

#endif
