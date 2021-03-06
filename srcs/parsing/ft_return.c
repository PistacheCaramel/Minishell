/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:48:19 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 23:01:14 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexed(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_token)
	{
		if (data->lexed[i].token)
		{
			free(data->lexed[i].token);
			data->lexed[i].token = NULL;
		}
		i++;
	}
	if (data->lexed)
	{
		free(data->lexed);
		data->lexed = NULL;
	}
	data->nb_token = 0;
}

void	free_parsed(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_parsed)
	{
		if (data->parsed[i].token)
		{
			free(data->parsed[i].token);
			data->parsed[i].token = NULL;
		}
		i++;
	}
	if (data->parsed)
	{	
		free(data->parsed);
		data->parsed = NULL;
	}
	data->nb_parsed = 0;
}

void	free_env(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	if (data->env)
	{
		free(data->env);
		data->env = NULL;
	}
}

void	cases_neg_ret(int ret, t_env *data)
{	
	if (ret == -1)
	{
		freeer(data);
		free_parsed(data);
		free_lexed(data);
		write(2, "Malloc error.\n", 14);
	}
	if (ret == -2)
		write(1, "Lone quote.\n", 12);
	if (ret == -3)
		printf("bash : syntax error near unexpected token `%s'\n", data->error);
	if (ret == -5)
		printf("bash : syntax error near unexpected token `newline'\n");
}

int	ft_return(int ret, t_env *data)
{
	if (ret == 2)
	{
		free_parsed(data);
		return (2);
	}
	if (ret < 0)
		cases_neg_ret(ret, data);
	if (ret < -2)
		free_parsed(data);
	if (ret < 0 && ret > -4)
		free_lexed(data);
	if (ret == 1)
	{
		rl_clear_history();
		free_all(data);
		write(1, "exit\n", 5);
		exit(0);
	}
	if (ret == -2 || ret == -3 || ret == -5)
		ret = 2;
	set_null(data);
	return (ret);
}
