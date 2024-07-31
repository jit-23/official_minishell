/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:07:45 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/30 04:18:53 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int ft_substrr(char ***str, char *s, int start, int len, int j)
{
	int	i;

	i = 0;
	while (i < len)
	{
		(*str)[j][i] = s[start + i];
		i++;
	}
	(*str)[j][i] = '\0';
	return (0);
}

int	ft_splitt(char ***strs, char *s, char c)
{
	int		i;
	int		word;
	int		size;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	word = ft_count_word(s, c);
	*strs = (char **)malloc((word + 1) * sizeof(char *));
	if (!strs)
		return (1);
	while (j < word)
	{
		while (s[i] == c && s[i])
			i++;
		size = ft_size_word(s, c, i);
		strs[0][j] = (char *)malloc((size + 1) * sizeof(char));
		ft_substrr(strs, s, i, size, j);
		if (!strs[0][j])
			ft_free(*strs, j);
		i += size;
		j++;
	}
	strs[0][j] = NULL;
	return (0);
}