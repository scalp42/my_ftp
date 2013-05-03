##
## Makefile for make in  /Users/scalp/projs/my_ftp
##
## Made by anthony scalisi
## <scalisia@gmail.com>
##
## Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
## Last update Fri May 03 14:25:37 2013 anthony scalisi
##

NAME	= serveur
NAMECLI	= client
SRV	= srv
CLI	= cli
COM	= com
SRC	=	$(SRV)/create_real_mess.c \
	  	$(SRV)/fct_cd.c \
		$(SRV)/fct_epsv.c \
		$(SRV)/fct_feat.c \
		$(SRV)/fct_ls.c \
		$(SRV)/fct_pass.c \
		$(SRV)/fct_pasv.c \
		$(SRV)/fct_pwd.c \
		$(SRV)/fct_retr.c \
		$(SRV)/fct_stor.c \
		$(SRV)/fct_syst.c \
		$(SRV)/fct_type.c \
		$(SRV)/fct_quit.c \
		$(SRV)/fct_user.c \
		$(SRV)/init_pwd.c \
		$(SRV)/init_transfert.c \
		$(SRV)/itoa.c \
		$(SRV)/open_new_socket.c \
		$(SRV)/seek_addr.c \
		$(SRV)/serveur.c \
		$(SRV)/stick_addr.c

SRC2	=	$(CLI)/client.c \
		$(CLI)/init_userpass.c \
		$(CLI)/init_client_connection.c \
		$(CLI)/check_line.c \
		$(CLI)/check_option.c \
		$(CLI)/receiv_ls.c \
		$(CLI)/retr_opt.c \
		$(CLI)/stor_opt.c \
		$(CLI)/open_data_connection.c \
		$(CLI)/init_pwd.c \
		$(CLI)/clean_buff.c \
		$(CLI)/open_new_data_connection.c

SRC3	=	$(COM)/get_next_line.c \
		$(COM)/xmalloc.c \
		$(COM)/xread.c \
		$(COM)/xrecv.c \
		$(COM)/xsend.c

OBJ	=	$(SRC:.c=.o)

OBJ2	=	$(SRC2:.c=.o)

OBJ3	=	$(SRC3:.c=.o)

CC	=	gcc

RM	=	rm -rf

#CFLAGS	= -O3 -W -Wall -ansi -pedantic -D${HOSTTYPE}
CFLAGS	= -O3 -W -Wall -ansi

LDFLAGS_sun4	=	-lsocket -lnsl

LDFLAGS		=	$(LDFLAGS_$(HOSTTYPE))

all		:	$(NAME) $(NAMECLI)

$(NAME)		:	$(OBJ) $(OBJ3)
			$(CC) -o $(NAME) $(OBJ) $(OBJ3) $(LDFLAGS)

$(NAMECLI)	:	$(OBJ2) $(OBJ3)
			$(CC) -o $(NAMECLI) $(OBJ2) $(OBJ3) $(LDFLAGS)

.c.o		:
			$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

clean		:
			$(RM) $(OBJ) $(OBJ2) $(OBJ3) *~ *#

fclean		:	clean
			$(RM) $(NAME) $(NAMECLI)

re		:	fclean all
