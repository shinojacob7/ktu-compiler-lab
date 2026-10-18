#include <stdio.h>
int main()
{
int i;
/* 1. Missing ’(’ */
for i = 0; i < 10; i++)
{
printf("%d", i);
}
/* 2. Missing ’)’ */
for(i = 0; i < 10; i++
{
printf("%d", i);
}
/* 3. Missing semicolon */
for(i = 0; i < 10 i++)
{
printf("%d", i);
}
/* 4. Only one semicolon */
for(i = 0; i < 10)
{
printf("%d", i);
}
/* 5. More than two semicolons */
for(i = 0; i < 10; i++; i++)
{
printf("%d", i);
}
/* 6. Correct for loop */
for(i = 0; i < 10; i++)
{
printf("%d", i);
}
return 0;
}