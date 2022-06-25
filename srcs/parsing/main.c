#include "minishell.h"

int	ft_cmp(char *s1, char *s2)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (ft_strlen(s1) == i && ft_strlen(s2) == i)
		return (1);
	return (0);
}

int	handle_buff(t_env *data, char **buff, char **env)
{
	int	ret;

	ret = ft_cmp(*buff, "exit");
	if (ret == -1)

	if (ret == 1)
	{
		free(*buff);
		*buff = NULL;
		return (ft_return(1, data));
	}
	ret = lexer(*buff, data);
	if (ret)
	{
		free(*buff);
		*buff = NULL;
		return (ft_return(ret, data));
	}
	free(*buff);
	*buff = NULL;
	ret = init_parser(data, env);
	if (ret)
		return (ft_return(ret, data));
	return (0);
}

void	reset(t_env *data)
{
	set_null(data);	
}
	
int	main(int ac, char **av, char **env)
{
	t_env	data;
	char	*buff;
	int		ret;

	(void)ac;
	(void)av;
	if (ft_init(&data))
		ft_return(1, &data);
	data.env = env;
	data.status_code = 0;
	while (7)
	{
		buff = readline(0);
		if (!buff)
			data.status_code = ft_return(1, &data);
		data.status_code = handle_buff(&data, &buff, env);
		if (!data.status_code)
		{
		//test
			unsigned int i = 0;
			printf("/°\\_/°\\_/°\\_/°\\ Parser Output /°\\_/°\\_/°\\_/°\\\n\n");
			while (i < data.nb_parsed)
			{
				printf("%d = %d %d %s\n", i, data.parsed[i].type, data.parsed[i].size, data.parsed[i].token);
				i++;
			}
			printf("______________________________________________________\n");
		//end-test
			ret = parsing(&data);
		//	if (ret)
		//		return (ret);
		//test	
			t_cmds	*tmp;
			i = 0;
			tmp = data.c_tbls;
			if (tmp)
			{
				while (tmp)
				{
					i = 0;
					if (tmp->cmds)
					{
						while (tmp->cmds[i])
						{
							printf("cmds:%s\n", tmp->cmds[i]);
							i++;
						}
					}
				if (tmp->cmd)
					printf("cmd:%s\n", tmp->cmd);
				printf("in:%d\nout:%d\n", tmp->in, tmp->out);
					tmp = tmp->next;
				}
			}
		//end-test
			data.status_code = execution(&data);
			freeer(&data);
		}
		else
		{
			freeer(&data);
			free_lexed(&data);
			free_parsed(&data);
		}
		printf("status_code:%d\n", data.status_code);
		
		reset(&data);
	}
	return(0);
}
