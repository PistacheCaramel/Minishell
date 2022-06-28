/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:09:26 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 00:10:37 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_null(t_env *data)
{
	data->lexed = NULL;
	data->parsed = NULL;
	data->error = NULL;
	data->temp = NULL;
	data->nb_token = 0;
	data->nb_parsed = 0;
	data->error = NULL;
	data->temp = NULL;
	data->c_tbls = NULL;
}
/*
int	set_env_i(t_env *data)
{
	char	**ret;
	int	i;
	ret = ft_calloc((sizeof(char *) * 4));
	if (!ret)
		return (-1);
	i = 0;
	ret[i] = PWD;
	i++;
	ret[i] = ft_cpy2("SHLVL=1");
	if (!ret[i])
		return (-1);
	i++;
	ret[i] = _ {chemin absolu pour l env};
	return (0);
}*/

int	env_init(t_env *data, char **env)
{
	int	i;

	i = 0;
//	if (!data->env[i])
//		return (set_env_i(data));
	while (env[i])
		i++;
	data->env = ft_calloc((sizeof(char *) * (i + 1)));
	if (!data->env)
		return (-1);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (-1);
		if (!ft_strncmp("SHLVL=", data->env[i], 5))
			data->env[i][6] = data->env[i][6] + 1;
		i++;
	}
	return (0);
}

int	ft_init(t_env *data, char **env)
{
	int	ret;

	data->tab = NULL;
	set_null(data);
	if (env_init(data, env))
		return (-1);
	if (token_init(data) == -1)
		return (-1);
	ret = signal_init();
	if (ret)
		printf("sigerror, ret = %d\n", ret);
	return (0);
}
