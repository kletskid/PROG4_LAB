#pragma once

#define PRODUCT_LEN 3
enum product_code_e {
   CLASSIC,
   ZERO,
   DIET,
   NONE,
   MAGIC_CODE = 6767
};

typedef struct {
   char name[16];
   uint32_t price;
   int count;
} product_t;

void product_manager_init();

event_t product_manager_set_product(enum product_code_e product);

uint32_t product_manager_get_current_price();

void product_manager_dispence_product();

void product_manager_price_adjust(enum product_code_e product, uint32_t newprice);

void product_manager_restock(enum product_code_e product, uint32_t amount);

