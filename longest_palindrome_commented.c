/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longest_palindrome_commented.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:28:03 by showard           #+#    #+#             */
/*   Updated: 2025/05/10 14:56:29 by showard          ###   ########.fr       */
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
	/*  We hand the string and the index of the left and right character

		It will then keep expanding outwards and check if if the next character 
		to the left is the same as the next character to the right */
    while (left >= 0 && right < str_len && str[left] == str[right])
    {
        left--;
        right++;
    }
    // When the loop terminates, 'left' and 'right' have moved one step
    // *outside* the boundaries of the actual palindrome.
    // The actual palindrome starts at 'left + 1' and ends at 'right - 1'.
    // The length is (right - 1) - (left + 1) + 1, which simplifies to:
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

	// i dont know specific exam instructions so i just assumed on empty print newline
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
		// paldriomes can be even or odd length
		// ie. "aba" or "abba"
		// in one case we need to expand around "b", in the other "bb"
		// so we need to check both cases
        len_if_odd = expand_around_center(str, i, i, str_len);
        len_if_even = expand_around_center(str, i, i + 1, str_len);
		// check if it was odd or even length palindrome
        if (len_if_odd > len_if_even)
        {
            current_max_len = len_if_odd;
        }
        else
        {
            current_max_len = len_if_even;
        }
		// check if we found a new longest palindrome
        if (current_max_len > longest_len)
        {
            longest_len = current_max_len;
			 /*
            	we are indexed at the center of the palindrome right now
            	so we need to calculate the start index of the palindrome
            	if we subtract 1 the length will be correct in even and odd
            	integer division handles both cases correctly.
            	e.g. (odd): str="aba", i=1 (center 'b'), longest_len=3
            	  (3 - 1) / 2 = 1
            	  longest_start = 1 - 1 = 0 (index of 'a')
			
            	e.g. (even): str="abba", i=1 (first 'b'), longest_len=4
            	  (4 - 1) / 2 = 3 / 2 = 1 (integer division)
            	  longest_start = 1 - 1 = 0 (index of 'a')
            */
            longest_start = i - (longest_len - 1) / 2;
        }
		//***optimization if the whole string is 60000 of the same character***
		// If we already found the longest palindrome is the entire string, DONT KEEP CHECKING 
		// instead break out of loop early
        if (longest_len == str_len)
        {
            break;
        }
        i++;
    }
    ft_putstr_length(str + longest_start, longest_len);
    ft_putchar('\n');
}


int	main(void)
{
    char	*str1 = "a";
    char	*str2 = "aa";
    char	*str3 = "aba";
    char	*str4 = "racecar";
    char	*str5 = "abcdeedcba"; // Longest: "deed" or "cdeedc" or "abcdeedcba"
    char	*str6 = "jhsffooflkhasfklhsaflkasfhlkasfhlkasfhkasfhlkasfhracecarasfkhkasfasf"; // Longest: "racecar"
    char	*str7 = "";
    char	*str8 = "babad"; // Longest: "bab" or "aba"
    char	*str9 = "cbbd";  // Longest: "bb"
    char	*str10 = "madam";
    char	*str11 = "abacaba";
    char	*str12 = "zzzaac"; // Longest: zzz
    char	*str13 = "aaaa"; // Longest: aaaa

    find_longest_palindrome(str1);  // Expected: a
    find_longest_palindrome(str2);  // Expected: aa
    find_longest_palindrome(str3);  // Expected: aba
    find_longest_palindrome(str4);  // Expected: racecar
    find_longest_palindrome(str5);  // Expected: abcdeedcba
    find_longest_palindrome(str6);  // Expected: racecar
    find_longest_palindrome(str7);  // Expected: (newline)
    find_longest_palindrome(str8);  // Expected: bab (or aba)
    find_longest_palindrome(str9);  // Expected: bb
    find_longest_palindrome(str10); // Expected: madam
    find_longest_palindrome(str11); // Expected: abacaba
    find_longest_palindrome(str12); // Expected: zzz
    find_longest_palindrome(str13); // Expected: aaaa

	/* 	Uncomment the following lines to test with a long string
			Note: This takes like 4 seconds to run. If if times out on exam (that would be crazy) you either 
			need to make an edge case that checks for long single char string shenanigans
			or use a better algorithm. */
    char long_str[60000];
    for (int i = 0; i < 60000; i++)
        long_str[i] = 'a';
    long_str[60000] = '\0';
    find_longest_palindrome(long_str);

    return (0);
}

// main for argc argva if needed
// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		write(1, "you fucked up, congrats\n", 24);
// 		return (1);
// 	}
// 	find_longest_palindrome(argv[1]);
// 	return (0);
// }

