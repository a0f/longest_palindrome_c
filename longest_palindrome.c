/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longest_palindrome.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:28:03 by showard           #+#    #+#             */
/*   Updated: 2025/05/10 14:58:10 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putstr_length(char *str, int len)
{
    int		i;

    i = 0;
    while (i < len)
    {
        ft_putchar(str[i]);
        i++;
    }
}

int	ft_strlen(char *str)
{
    int		i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	expand_around_center(char *str, int left, int right, int str_len)
{
    while (left >= 0 && right < str_len && str[left] == str[right])
    {
        left--;
        right++;
    }
    return (right - left - 1);
}

void	find_longest_palindrome(char *str)
{
    int		str_len;
    int		longest_start;
    int		longest_len;
    int		i;
    int		len_if_odd;
    int		len_if_even;
    int		current_max_len;

    if (!str || str[0] == '\0')
    {
        ft_putchar('\n');
        return;
    }
    i = 0;
    str_len = ft_strlen(str);
    longest_start = 0;
    longest_len = 1;
    while (i < str_len)
    {
        len_if_odd = expand_around_center(str, i, i, str_len);
        len_if_even = expand_around_center(str, i, i + 1, str_len);
        if (len_if_odd > len_if_even)
        {
            current_max_len = len_if_odd;
        }
        else
        {
            current_max_len = len_if_even;
        }
        if (current_max_len > longest_len)
        {
            longest_len = current_max_len;
            longest_start = i - (longest_len - 1) / 2;
        }
        if (longest_len == str_len)
        {
            break;
        }
        i++;
    }
    ft_putstr_length(str + longest_start, longest_len);
    ft_putchar('\n');
}

// int	main(void)
// {
//     char	*str1 = "a";
//     char	*str2 = "aa";
//     char	*str3 = "aba";
//     char	*str4 = "racecar";
//     char	*str5 = "abcdeedcba";
//     char	*str6 = "jhsffooflkhasfklhsaflkasfhlkasfhlkasfhkasfhlkasfhracecarasfkhkasfasf";
//     char	*str7 = "";
//     char	*str8 = "babad";
//     char	*str9 = "cbbd";
//     char	*str10 = "madam";
//     char	*str11 = "abacaba";
//     char	*str12 = "zzzaac";
//     char	*str13 = "aaaa";

//     find_longest_palindrome(str1);
//     find_longest_palindrome(str2);
//     find_longest_palindrome(str3);
//     find_longest_palindrome(str4);
//     find_longest_palindrome(str5);
//     find_longest_palindrome(str6);
//     find_longest_palindrome(str7);
//     find_longest_palindrome(str8);
//     find_longest_palindrome(str9);
//     find_longest_palindrome(str10);
//     find_longest_palindrome(str11);
//     find_longest_palindrome(str12);
//     find_longest_palindrome(str13);

//     char long_str[60000];
//     for (int i = 0; i < 60000; i++)
//         long_str[i] = 'a';
//     long_str[60000] = '\0';
//     find_longest_palindrome(long_str);

//     return (0);
// }

