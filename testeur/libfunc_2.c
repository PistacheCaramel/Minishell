#include "tester.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && (i + j) < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
			{
				res = (char *)&big[i];
				return (res);
			}
			j++;
		}
		i++;
	}
	res = NULL;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (0);
	dest = (char *)ft_calloc(sizeof(char),
			(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	return (dest);
}