#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
/// Finite State Machine Library
#include "fsm_functions/fsm.h"
#include "states.h"
#include "events.h"
/// Development Console Library
#include "keyboard.h"
#include "display.h"
#include "console.h"

#include "maintenance_mode.h"
#include "product_manager.h"
#include "money_manager.h"

void maintenance_mode_register()
{
   FSM_AddState(S_OUT_OF_ORDER, &(state_funcs_t){ out_of_order_entry, out_of_order_exit});
   FSM_AddState(S_ADJUST_PRICE, &(state_funcs_t){ adjust_price_entry, NULL});
   FSM_AddState(S_COLLECT_MONEY, &(state_funcs_t){ collect_money_entry, NULL});
   FSM_AddState(S_STOCK_PRODUCTS, &(state_funcs_t){ stock_products_entry, NULL});

   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_AJUST_PRICE, S_ADJUST_PRICE});
   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_COLLECT_MONEY, S_COLLECT_MONEY});
   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_STOCK_PRODUCTS, S_STOCK_PRODUCTS});
   FSM_AddTransition(&(transition_t){ S_COLLECT_MONEY, E_ACTION_COMPLETED, S_OUT_OF_ORDER});
   FSM_AddTransition(&(transition_t){ S_ADJUST_PRICE, E_ACTION_COMPLETED, S_OUT_OF_ORDER});
   FSM_AddTransition(&(transition_t){ S_ADJUST_PRICE, E_AJUST_PRICE, S_ADJUST_PRICE});
   FSM_AddTransition(&(transition_t){ S_STOCK_PRODUCTS, E_ACTION_COMPLETED, S_OUT_OF_ORDER});
   FSM_AddTransition(&(transition_t){ S_STOCK_PRODUCTS, E_STOCK_PRODUCTS, S_STOCK_PRODUCTS});
   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_MAINTENANCE_COMPLETED, S_IDLE});
   FSM_AddTransition(&(transition_t){ S_WAIT_FOR_MONEY, E_MONEY_NOT_ACCEPTED, S_IDLE});
   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_RETURN_TO_MAINTENANCE, S_OUT_OF_ORDER});
}

void out_of_order_entry(void)
{
    DCSdebugSystemInfo("System is out of order. Maintenance required.\n");
    //DSPclearDisplay();
    DSPshow(0, "[MAINTENANCE MODE]");

    DSPshow(3, "cmd: 0, 1, 2, 3");

    int code = KYBgetint(0);
    printf("cmd: %d\n", code);

    switch (code)
    {
        case 0:
            FSM_AddEvent(E_AJUST_PRICE);
            break;
        case 1:
            FSM_AddEvent(E_COLLECT_MONEY);
            break;
        case 2:
            FSM_AddEvent(E_STOCK_PRODUCTS);
            break;
        case 3:
            FSM_AddEvent(E_MAINTENANCE_COMPLETED);
            DSPshow(3, "Maintenance accept.");
            break;
        default: 
            FSM_AddEvent(E_RETURN_TO_MAINTENANCE);
            break;
    }
}

void out_of_order_exit(void)
{
    DCSdebugSystemInfo("Exiting out of order state.\n");
}

static int product_code = -1;
void adjust_price_entry(void)
{
    DCSdebugSystemInfo("Adjusting prices.\n");
    DSPshow(3, "Price adjust.");
    DSPclearLine(1);
    DSPshow(1, "Entr pcode, price.");
    int value = KYBgetint(0);
    if (value == -1) {
        return FSM_AddEvent(E_AJUST_PRICE);
    }
    if (product_code == -1) {
        product_code = value;
        return FSM_AddEvent(E_AJUST_PRICE);
    }

    product_manager_price_adjust(product_code, value);
    DSPclearLine(1);
    DSPshow(1, "%d c to %d c.", product_code, value);
    product_code = -1;
    FSM_AddEvent(E_ACTION_COMPLETED);
}

void collect_money_entry(void)
{
    DCSdebugSystemInfo("Collecting money from machine.\n");
    DSPshow(3, "Collecting money.");
    int collected_money = money_manager_collect();
    DSPclearLine(1);
    DSPshow(1, "Collected %d cents.", collected_money);
    FSM_AddEvent(E_ACTION_COMPLETED);
}

void stock_products_entry(void)
{
    DCSdebugSystemInfo("Restocking products.\n");
    DSPshow(3, "Restocking product.");
    DSPclearLine(1);
    DSPshow(1, "Entr pcode, amount.");
    int value = KYBgetint(0);
    if (value == -1) {
        return FSM_AddEvent(E_STOCK_PRODUCTS);
    }
    if (product_code == -1) {
        product_code = value;
        return FSM_AddEvent(E_STOCK_PRODUCTS);
    }
    
    DSPclearLine(1);
    DSPshow(1, "Rest. %d to %d", product_code, value);
    product_manager_restock(product_code, value);

    FSM_AddEvent(E_ACTION_COMPLETED);
}
