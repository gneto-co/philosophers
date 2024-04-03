#include <unistd.h>

// 0 - normal
// 1 - red
// 2 - green
// 3 - yellow
// 4 - blue
// 5 - magenta
// 6 - cyan
// 7 - white
// 8 - orange
void	ft_color(int nb)
{
	if (nb == 0) // normal
		write(1, &"\033[0m", 4);
	else if (nb == 1) // red
		write(1, &"\033[0;31m", 7);
	else if (nb == 2) // green
		write(1, &"\033[0;32m", 7);
	else if (nb == 3) // yellow
		write(1, &"\033[0;33m", 7);
	else if (nb == 4) // blue
		write(1, &"\033[0;34m", 7);
	else if (nb == 5) // magenta
		write(1, &"\033[0;35m", 7);
	else if (nb == 6) // cyan
		write(1, &"\033[0;36m", 7);
	else if (nb == 7) // white
		write(1, &"\033[0;37m", 7);
	else if (nb == 8) // orange
		write(1, &"\033[31m\033[33m", 10);
}
