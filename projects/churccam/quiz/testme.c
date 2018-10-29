/*
 * Random Testing Quiz
 * Cameron Church
 * SEII
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // TODO: rewrite this function
  // Note on rand() format ------ num = (rand() % (upper – lower + 1))
  int charInt = (rand() % (126 - 32 + 1)) + 32;
  char randomChar = (char) charInt;

  return randomChar;
}

char *inputString()
{
  // TODO: rewrite this function
  char rand_string[6]; //char array - stores random chars

  int i;
  //fill array
  for(i = 0; i < 5; i++){
      int charInt = (rand() % (116 - 101 + 1)) + 101; //random ASCII value from 'e' to 't'
      char randomChar = (char) charInt; //convert int to char
      rand_string[i] = randomChar; // add char to array
  }
   //append closing char to array
  rand_string[5] = '\0';
  char *randomString = rand_string;
  return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
