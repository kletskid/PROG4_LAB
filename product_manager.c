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

enum product_code_e current_product;

product_t product_list[PRODUCT_LEN] = {
   {
      .name = "cola classic",
      .price = 125
   },
   {
      .name = "cola zero",
      .price = 160
   },
   {
      .name = "diet coke",
      .price = 200
   }
};

void product_manager_init()
{
   for (int product = 0; product < PRODUCT_LEN; product++) {
      product_list[product].count = 20;
   }
   current_product = NONE;
}

event_t product_manager_set_product(enum product_code_e product) {
   if (product == MAGIC_CODE) {
      return E_MAINTENANCE;
   } else if (product > DIET) {
      return E_PRODUCT_INVALID;
   }
   current_product = product;
   return E_SELECT_PRODUCT;
}

uint32_t product_manager_get_current_price() {
   return product_list[current_product].price;
}

void product_manager_price_adjust(enum product_code_e product, uint32_t newprice) {
   if (product > DIET) {
      return;
   }

   product_list[product].price = newprice;
}

void product_manager_restock(enum product_code_e product, uint32_t amount) {
   if (amount <= 20) {
      product_list[product].count = amount;
   }
}

void product_manager_dispence_product() {
   if (product_list[current_product].count <= 0) {
      DSPshow(2, "%s sold out", product_list[current_product].name);
      DSPshow(3, "Returned: %d c", money_manager_get_count());
   } else {
      product_list[current_product].count--; 
      int change = money_manager_get_count() - product_manager_get_current_price();
      DSPshow(2, "Disp. %s", product_list[current_product].name);
      DSPshow(3, "ret: %d c", change);
   }
}


