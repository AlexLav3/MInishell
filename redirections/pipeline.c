#include <../Minishell.h>

//pipeline.c

/*
 * Used by piped command execution.
 * - Initializes `t_cmd` structs and tokenizes subcommands
 * - Parses args and redirections for each command
 * - Executes all via `execute_piped_commands`
 * - Cleans up tokens and memory
 */
static void process_and_execute(int cmd_count, char **cmd_strs, t_shell *shell, t_cmd *cmds)
{	
	int		i;
	t_shell	px;
	t_token	*subtokens;

	i = -1;
	while (++i < cmd_count)
	{
		init_cmd(&cmds[i]);
		subtokens = tokenize_command(cmd_strs[i]);
		if (!subtokens)
			continue ;
		cmds[i].args = parse_args_and_redirs(subtokens, &cmds[i], shell);
		strip_redirection_tokens(&subtokens);
		deallocate(&subtokens);
	}
	init_pipex(&px, shell);
	execute_piped_commands(&px, cmds, cmd_count, shell);
	free_array(cmd_strs);
}

/*
 * Entry point for handling a full pipeline (commands with `|`).
 * Splits into individual commands, initializes `t_cmd` array,
 * processes and executes all using `process_and_execute`.
 */
void	pipe_cmds_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	t_cmd	*cmds;
	char	**cmd_strs;
	int		cmd_count;
	int		i;

	(void)command;
	cmd_strs = make_args_pipes(*tokens);
	if (!cmd_strs)
		return ;
	cmd_count = cmd_counter(cmd_strs);
	cmds = malloc(sizeof(t_cmd) * cmd_count);
	if (!cmds)
	{
		free_array(cmd_strs);
		return ;
	}
	process_and_execute(cmd_count, cmd_strs, shell, cmds);
	i = -1;
	while (++i < cmd_count)
	{
		free_array(cmds[i].args);
		reset_redirection(&cmds[i]);
	}
	free(cmds);
}
