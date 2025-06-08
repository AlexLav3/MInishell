/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:21:24 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/25 21:28:35 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//cat test.txt | grep "42" | sort | wc -l (testing)
char	**make_args(t_token *tokens, t_shell *shell)
{
	char	**cmd;
	char	*pos;
	int		i;
	char	*expanded;

	i = 0;
	cmd = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmd || !tokens)
		return (NULL);
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
		{
			cmd[i] = toks_to_args(tokens, *cmd, shell);
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i++] = NULL;
	return (cmd);
}

char	*toks_to_args(t_token *tokens, char *cmd, t_shell *shell)
{
	char	*pos;
	char	*exp;
	char 	*res = ft_strdup("");	
	int 	i = 0;
	int 	in_single = 0;
	int 	start = 0;

	while (tokens->com[i])
	{
		if (tokens->com[i] == '\'')
		{
			in_single = 1;
			i++;
			start = i;
			while (tokens->com[i] && tokens->com[i] != '\'')
				i++;
			res = join_and_free(res, ft_substr(tokens->com, start, i - start));
			if (tokens->com[i] == '\'')
			{
				in_single = 0;
				i++;
			}
		}
		if (tokens->com[i] == '$' && !in_single)
		{
			printf("I am here\n");
			pos = &tokens->com[i];
			exp = handle_dollar(pos, shell); //need to check single quotes in this function as well
			if (exp)
			{
				return (ft_strjoin(strndup(res, pos -res),
					exp));
			}
		}
		else 
			res = join_and_free(res, char_to_str(tokens->com[i]));
		i++;
	}
	return (res);
}

char	*handle_dollar(char *cmd, t_shell *shell)
{
	int		idx;
	char	*env;
	char	*value;
	char 	*suf;
	int		i;
	char	*prefix;
	
	i = 0;
	if (!cmd || cmd[1] == '?')
		return (ft_strdup(cmd));
	while(cmd[i])
	{
		if(cmd[i] == '$')
			break;
		i++;
	}
	prefix = ft_substr(cmd, 0, i);
	idx = search_env(shell, cmd + (i + 1));
	if (idx >= 0)
	{
		env = shell->env_var[idx];
		value = ft_strchr(env, '=') + 1;
		if (!value)
			return (ft_strdup(""));
		suf = ft_strdup(cmd + (i + 1) + shell->var_len);
		if(ft_strchr(suf, '$') != NULL)
			suf = handle_dollar(suf, shell);
		return (join_and_free(prefix, join_and_free(ft_strdup(value), suf)));
	}
	else
		return (ft_strdup(""));
}

