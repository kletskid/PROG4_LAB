#include "keyboard.h"

int lastPressed;

int KYBgetint(int a)
{
   int key = lastPressed;
   lastPressed = -1;
   return key;
}


