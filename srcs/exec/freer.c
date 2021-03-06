/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:26:57 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 20:40:06 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pfds(t_cmds *cmds)
{
	t_fds	*tmp;

	while (cmds)
	{
		while (cmds->fds)
		{
			tmp = cmds->fds->next;
			free(cmds->fds);
			cmds->fds = tmp;
		}
		free(cmds->lim);
		free(cmds->pfd_in);
		free(cmds->pfd_out);
		cmds = cmds->next;
	}
}

void	free_strs_cmds(t_cmds *tbls)
{
	int	i;

	i = 0;
	if (tbls->delim)
	{
		while (tbls->delim[i])
		{
			free(tbls->delim[i]);
			i++;
		}
		free(tbls->delim);
	}
	if (tbls->cmd)
		free(tbls->cmd);
	if (tbls->path)
		free(tbls->path);
	if (tbls->file_in)
		free(tbls->file_in);
	if (tbls->file_out)
		free(tbls->file_out);
}

void	free_cmds_table(t_cmds *tbls)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	if (!tbls)
		return ;
	if (tbls->cmds)
	{
		while (tbls->cmds[i])
		{
			free(tbls->cmds[i]);
			i++;
		}
		free(tbls->cmds);
	}
	free_strs_cmds(tbls);
	tmp = tbls->next;
	if (tmp)
		free_cmds_table(tmp);
	free(tbls);
}

void	freeer(t_env *envs)
{
	free_pfds(envs->c_tbls);
	free_cmds_table(envs->c_tbls);
}
