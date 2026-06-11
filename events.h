#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
   E_NO,                ///< Used for initialisation of an event variable
   E_INITIALIZE,
   E_READY,
   E_SELECT_PRODUCT,
   E_MONEY_ENOUGH,
   E_MONEY_NOT_ENOUGH,
   E_50C,
   E_20C,
   E_MAINTENANCE,
   E_PRODUCT_INVALID,
   E_INTERACTION_ENDED,
   E_MONEY_NOT_ACCEPTED,
   E_AJUST_PRICE,
   E_COLLECT_MONEY,
   E_STOCK_PRODUCTS,
   E_MAINTENANCE_COMPLETED,
   E_ACTION_COMPLETED,
   E_RETURN_TO_MAINTENANCE,
   E_ENTERED_PCODE
} event_t;

#endif
