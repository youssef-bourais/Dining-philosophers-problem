# include <stdio.h>

int ft_len(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

int main()
{
	char *str;
	printf("%d\n", ft_len(str));
}