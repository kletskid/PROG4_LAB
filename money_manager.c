#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
/// Finite State Machine Library
#include "fsm_functions/fsm.h"
/// Development Console Library
#include "keyboard.h"
#include "display.h"
#include "console.h"

#include "product_manager.h"
#include "money_manager.h"

uint32_t money_count;
uint32_t money_total;

void money_manager_init()
{
   money_count = 0;
   money_total = 0;
}

uint32_t money_manager_get_count() {
   return money_count;
}

void money_manager_add_money(uint32_t money) {
   money_count += money;
}

void money_manager_finalize_transaction() {
   money_total += product_manager_get_current_price();
   money_count = 0;
}

uint32_t money_manager_collect() {
   uint32_t tmp = money_total;
   money_total = 0;
   return tmp;
}

event_t money_manager_check_count() {
   if (money_count >= product_manager_get_current_price()) {
      return E_MONEY_ENOUGH;
   } else {
      return E_MONEY_NOT_ENOUGH;
   }
}




