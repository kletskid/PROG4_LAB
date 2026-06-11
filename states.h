#ifndef STATES_H
#define STATES_H

typedef enum {
   S_NO,               ///< Used for initialisation if state is not yet known
   S_IDLE,
   S_WAIT_FOR_MONEY,
   S_PROCESS_50C,
   S_PROCESS_20C,
   S_END_INTERACTION,
   S_OUT_OF_ORDER,
   S_ADJUST_PRICE,
   S_COLLECT_MONEY,
   S_STOCK_PRODUCTS
} state_t;

#endif

