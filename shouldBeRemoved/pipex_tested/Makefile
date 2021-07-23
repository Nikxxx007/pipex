NAME					=	pipex

MAIN_OBJ_DIR			=	main_objs/
BONUS_OBJ_DIR			=	bonus_objs/
SHARED_OBJ_DIR			=	shared_objs/

all:			main_Makefile
				@$(MAKE) -f main_Makefile

bonus:			bonus_Makefile
				@$(MAKE) -f bonus_Makefile

clean:
				rm -rf $(MAIN_OBJ_DIR) $(BONUS_OBJ_DIR) $(SHARED_OBJ_DIR)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

bonusre:		fclean bonus

.PHONY:			bonus clean fclean re bonusre
