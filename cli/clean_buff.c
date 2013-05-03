/*
** clean_buff.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<ctype.h>
#include	"client.h"

void		clean_buff(char *buff, int nb_read)
{
  int		i;

  for (i = nb_read - 1; isspace((int)buff[i]) && i != 0; i--)
      buff[i] = '\0';
}
