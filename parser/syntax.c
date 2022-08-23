#include "../minishell.h"

int	put_syntaxerr_msg(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (0);
}

int	init_syntax(t_info *info)
{
	t_dlist	*curr;

	curr = info->dlist;
	while (curr)
	{
		if (!ft_strncmp(curr->token, "&&", 3) || !ft_strncmp(curr->token, "||", 3))
			curr->type = LINE;
		else if (!ft_strncmp(curr->token, "|", 2))
			curr->type = PIPE;
		else if (!ft_strncmp(curr->token, "<", 1) || !ft_strncmp(curr->token, ">", 1))
			curr->type = REDIR;
		else if (curr->token[0] == '(')
			curr->type = BRACKET;
		else
			curr->type = WORD;
		curr = curr->next;
	}
	return (1);
}

int	check_redir(t_dlist *curr)
{
	if (curr->next->type == PIPE)
		return (put_syntaxerr_msg(curr->next->token));
	if (curr->next->type == LINE)
		return (put_syntaxerr_msg(curr->next->token));
	if (curr->next->type == BRACKET)
		return (put_syntaxerr_msg("("));
	if (curr->next->type == REDIR)
		return (put_syntaxerr_msg(curr->next->token));
	return (1);
}

int	check_pipe(t_dlist *curr)
{
	if (curr->next->type == PIPE)
		return (put_syntaxerr_msg(curr->next->token));
	if (curr->next->type == LINE)
		return (put_syntaxerr_msg(curr->next->token));
	return (1);
}

int	check_word(t_dlist *curr)
{
	if (curr->next->type == BRACKET)
		return (put_syntaxerr_msg("("));
	return (1);
}

int	check_line(t_dlist *curr)
{
	if (curr->next->type == PIPE)
		return (put_syntaxerr_msg(curr->next->token));
	if (curr->next->type == LINE)
		return (put_syntaxerr_msg(curr->next->token));
	return (1);
}

int	check_bracket(t_dlist *curr)
{
	if (curr->next->type == BRACKET)
		return (put_syntaxerr_msg("("));
	if (curr->next->type == WORD)
		return (put_syntaxerr_msg(curr->next->token));
	return (1);
}

int	check_last(t_dlist *curr)
{
	if (curr->type != WORD && curr->type != BRACKET)
	{
		if (curr->type == REDIR)
			return (put_syntaxerr_msg("newline"));
		else
			return (put_syntaxerr_msg(curr->token));
	}
	return (1);
}

int	check_syntax(t_info *info)
{
	t_dlist	*curr;
	int		ret;

	curr = info->dlist;
	init_syntax(info);
	ret = 1;
	while (curr->next)
	{
		if (curr->type == LINE)
			ret = check_line(curr);
		else if (curr->type == PIPE)
			ret = check_pipe(curr);
		else if (curr->type == REDIR)
			ret = check_redir(curr);
		else if (curr->type == WORD)
			ret = check_word(curr);
		else if (curr->type == BRACKET)
			ret = check_bracket(curr);
		if (!ret)
			break ;
		curr = curr->next;
	}
	ret = check_last(curr);
	return (ret);
}