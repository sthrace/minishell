#include "minishell.h"

int	main()
{
	char	str[1];
	struct	termios term;

	tcgetattr(0,&term);
	term.c_lflag &= ~ECHO;			// отключаем вывод служебных символов
	term.c_lflag &= ~ICANON;		// переходим в неканонический посимвольный режим ввода
	tcsetattr(0, TCSANOW, &term);	// применяем настройки

	str[0] = '0';
	while (ft_strcmp(str, "\n"))
	{
		read(0, str, 1);
		write(1, str, 1);
	}
	
	return(0);
}
