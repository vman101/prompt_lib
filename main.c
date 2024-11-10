#include "prompt.h"

int main()
{
	char *bless = prompt_get(">");

	ft_printf("%s\n", bless);
}
