#include <stdio.h>
#include <string.h>

int main(void)
{
		int pos;
		char s[] = "Self-trust is the first secret of success.";
		char t[] = "secret";
		char *test;

		test = strstr(s, t);
		pos = strlen(s)-strlen(test);
		printf("%d\n",pos);

		return 0;    
}
