// Referenced https://www.acmicpc.net/source/7075347 

#include <stdio.h>
#include <string.h>

char s[1001], buf[10000];

int cmp(int* a, int* b) { return strcmp(s + *a, s + *b); }

int main()
{
  int a[1000], i = 0;

  gets(s);
  setvbuf(stdout, buf, _IOFBF, 10000);
  for(i = 0; s[i]; i++) a[i] = i;
  qsort(a, i, 4, cmp);
  for(i = 0; s[i]; i++) puts(s + a[i]);
}