/*
** itoa.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>
#include	"ftp.h"

char		*itoa(int nb)
{
  int		diviseur;
  int		i;
  char		*str;

  diviseur = 1;
  for (i = 0; nb / diviseur > 9; i++)
    diviseur *= 10;
  str = malloc((i + 2) * sizeof (char));
  for (i = 0; diviseur; i++)
    {
      str[i] = ((nb / diviseur) % 10) + '0';
      diviseur /= 10;
    }
  str[i] = 0;
  return (str);
}
