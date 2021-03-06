/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:26:46 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 18:35:49 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_mini_atoi(char *str)
{
	long long int	ret;
	int				i;

	ret = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret);
}

void	numeric_required(t_env *data, char *str, int in, int out)
{
	write(2, "exit\nbash: exit: ", 18);
	write(2, str, ft_strlen(str));
	write(2, " : numeric argument required\n", 29);
	close_fds(data->c_tbls);
	free_all_env(data);
	exit_fd(in, out);
	exit(2);
}

long long int	ft_get_status(char *str, t_env *data, int in, int out)
{
	unsigned int			i;
	char					mark;

	i = 0;
	mark = 1;
	if ((str[i] == '-' || str[i] == '+')
		&& (str[i + 1] >= 48 && str[i + 1] <= 67))
	{
		if (str[i] == '-')
			mark = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 67)
		i++;
	if (i != ft_strlen(str) || ft_cmp(str, "") || i > 19)
		numeric_required(data, str, in, out);
	return (ft_mini_atoi(str) * mark);
}

int	too_many(void)
{
	write(2, "bash: exit: too many arguments\n", 32);
	return (127);
}

int	ft_exit(t_env *data, char **strs, int in, int out)
{
	long long int	nb;

	if (!strs)
		return (0);
	nb = 0;
	if (strs)
	{
		if (strs[1])
			nb = ft_get_status(strs[1], data, in, out);
	}
	if (nb < -9223372036854775807)
		numeric_required(data, strs[1], in, out);
	if (strs[1] && strs[2])
		return (too_many());
	exit_write(data);
	close_fds(data->c_tbls);
	free_all_env(data);
	exit_fd(in, out);
	exit(nb);
	return (0);
}
