/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:25:21 by abonnel           #+#    #+#             */
/*   Updated: 2021/03/26 10:59:13 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

size_t		ft_strlen(const char *s);
char 		*ft_strcpy(char * dst, const char * src);
ssize_t		ft_write(int fildes, const void *buf, size_t nbyte);
ssize_t		ft_read(int fildes, void *buf, size_t nbyte);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
ssize_t		testerror(int fildes, const void *buf, size_t nbyte);

int main()
{
	dprintf(1, "STRLEN TESTS\n");
	dprintf(1, "=========================\n");
	dprintf(1, "My output\t| strlen output\n");
	dprintf(1, "%zu \t\t| ", ft_strlen("bonjo0uuuuur"));
	dprintf(1, "%zu", strlen("bonjo0uuuuur"));
	dprintf(1, "\n");
	dprintf(1, "%zu \t\t| ", ft_strlen("bonjou\tur"));
	dprintf(1, "%zu", strlen("bonjou\tur"));
	dprintf(1, "\n");
	dprintf(1, "%zu \t\t| ", ft_strlen("bonjou  128uuuur"));
	dprintf(1, "%zu", strlen("bonjou  128uuuur"));
	dprintf(1, "\n");
	dprintf(1, "%zu \t\t| ", ft_strlen("bonj\0our"));
	dprintf(1, "%zu", strlen("bonj\0our"));
	dprintf(1, "\n");
	dprintf(1, "%zu \t\t| ", ft_strlen(""));
	dprintf(1, "%zu", strlen(""));
	dprintf(1, "\n");


	char		dst[150];
	dprintf(1, "\nSTRCPY TESTS\n");
	dprintf(1, "=========================\n");
	dprintf(1, "%s\tft_strcpy\n", ft_strcpy(dst, "bonjour miaou"));
	dprintf(1, "dst:%s|\n", dst);
	dst[0] = '\0';
	dprintf(1, "%s\tstrcpy\n", strcpy(dst, "bonjour miaou"));
	dprintf(1, "dst:%s|\n\n\n", dst);
	dst[0] = '\0';

	dprintf(1, "%s\tft_strcpy\n", ft_strcpy(dst, "hihihi"));
	dprintf(1, "dst:%s|\n", dst);
	dst[0] = '\0';
	dprintf(1, "%s\tstrcpy\n", strcpy(dst, "hihihi"));
	dprintf(1, "dst:%s|\n\n\n", dst);
	dst[0] = '\0';

	dprintf(1, "%s\tft_strcpy\n", ft_strcpy(dst, "\t\t\to\t\to"));
	dst[0] = '\0';
	dprintf(1, "%s\tstrcpy\n", strcpy(dst, "\t\t\to\t\to"));
	dst[0] = '\0';

	dprintf(1, "%s\tft_strcpy\n", ft_strcpy(dst, "MINOUCHE LOVE"));
	dst[0] = '\0';
	dprintf(1, "%s\tstrcpy\n", strcpy(dst, "MINOUCHE LOVE"));
	dst[0] = '\0';

	dprintf(1, "\nWRITE TESTS\n");
	dprintf(1, "=========================\n");
	dprintf(1, "first comes my output, then the actual write function output \n");
	dprintf(1, "Initiate errno = %d\n", errno);
	dprintf(1, "\n%zd\n", ft_write(1, "bonjour", -1));
	dprintf(1, "%s\n", strerror(errno));
	dprintf(1, "%d\n", errno);
	dprintf(1, "\n");
	dprintf(1, "\n%zd\n", write(1, "bonjour", -1));
	dprintf(1, "%s\n", strerror(errno));
	dprintf(1, "%d\n", errno);
	dprintf(1, "\n");


	dprintf(1, "\n%zu\n", ft_write(1, "bonjour", 0));
	dprintf(1, "\n");
	dprintf(1, "\n%zu\n", write(1, "bonjour", 0));
	dprintf(1, "\n");

	dprintf(1, "\n%zu\n", ft_write(1, "bonjour", 7));
	dprintf(1, "\n");
	dprintf(1, "\n%zu\n", write(1, "bonjour", 7));
	dprintf(1, "\n");

	dprintf(1, "\n%zu\n", ft_write(1, "bonjour", 4));
	dprintf(1, "\n");
	dprintf(1, "\n%zu\n", write(1, "bonjour", 4));
	dprintf(1, "\n");

	dprintf(1, "\n%zu\n", ft_write(1, "", 7));
	dprintf(1, "\n");
	dprintf(1, "\n%zu\n", write(1, "", 7));
	dprintf(1, "\n");

	dprintf(1, "STRCMP TESTS\n");
	dprintf(1, "=========================\n");
	dprintf(1, "My output\t| strcmp output\n");
	dprintf(1, "%d\t\t|", strcmp("Bonjour", "Bonjou"));
	dprintf(1, " %d\n", ft_strcmp("Bonjour", "Bonjou"));

	dprintf(1, "%d\t\t|", strcmp("", "Bonjou"));
	dprintf(1, "%d\n", ft_strcmp("", "Bonjou"));

	dprintf(1, "%d\t\t|", strcmp("", ""));
	dprintf(1, "%d\n", ft_strcmp("", ""));

	dprintf(1, "%d\t\t|", strcmp(" 1 6 8 9\xff\xff", " 1 6 8 0\xff "));
	dprintf(1, "%d\n", ft_strcmp(" 1 6 8 9\xff\xff ", " 1 6 8 0\xff "));

	dprintf(1, "\nSTRDUP TESTS\n");
	dprintf(1, "=========================\n");

	dprintf(1, "%s\t\tft_strdup\n", ft_strdup("bonjour")); 
	dprintf(1, "%s\t\tstrdup\n", strdup("bonjour")); 
	dprintf(1, "\n");

	dprintf(1, "%s\t\tft_strdup\n", ft_strdup("")); 
	dprintf(1, "%s\t\tstrdup\n", strdup("")); 
	dprintf(1, "\n");

	dprintf(1, "%s\t\tft_strdup\n", ft_strdup("000")); 
	dprintf(1, "%s\t\tstrdup\n", strdup("000")); 
	dprintf(1, "\n");

	dprintf(1, "%s\t\tft_strdup\n", ft_strdup("\t\t\t|")); 
	dprintf(1, "%s\t\tstrdup\n", strdup("\t\t\t|")); 
	dprintf(1, "\n");

	dprintf(1, "%s\t\tft_strdup\n", ft_strdup("\0|")); 
	dprintf(1, "%s\t\tstrdup\n", strdup("\0|")); 
	dprintf(1, "\n");

	dprintf(1, "%s\t\tft_strdup\n", ft_strdup("Trois petits chats")); 
	dprintf(1, "%s\t\tstrdup\n", strdup("Trois petits chats")); 
	dprintf(1, "\n");

	//real strdup function segfaults with NULL as param
	//dprintf(1, "%s\t\tft_strdup\n", ft_strdup(NULL)); 
	//dprintf(1, "%s\t\tstrdup\n", strdup(NULL)); 
	//dprintf(1, "\n");

	char		buf[1000];
	dprintf(1, "READ TESTS\n");
	dprintf(1, "=========================\n");
	dprintf(1, "input same number of char two times from keyboard and press enter -> first output is read function, second one is my ft_read output\n");
	dprintf(1, "%zu\n", read(0, buf, 30));	
	dprintf(1, "%zu\n", ft_read(0, buf, 30));	

	return (0);
}
