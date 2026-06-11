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
   FSM_AddTransition(&(transition_t){ S_STOCK_PRODUCTS, E_ACTION_COMPLETED, S_OUT_OF_ORDER});
   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_MAINTENANCE_COMPLETED, S_IDLE});
   FSM_AddTransition(&(transition_t){ S_WAIT_FOR_MONEY, E_MONEY_NOT_ACCEPTED, S_IDLE});
   FSM_AddTransition(&(transition_t){ S_OUT_OF_ORDER, E_RETURN_TO_MAINTENANCE, S_OUT_OF_ORDER});
}

void out_of_order_entry(void)
{
   DCSdebugSystemInfo("System is out of order. Maintenance required.\n");
   //DSPclearDisplay();
   DSPshow(3, "======[MAINTENANCE MODE]======");

   DSPshow(4, "Enter a command code: 0, 1, 2, 3");

   int code = KYBgetint(0);

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
            DSPshow (3, "Maintenance code accepted. Returning to idle state.");
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

void adjust_price_entry(void)
{
    DCSdebugSystemInfo("Adjusting prices.\n");
    DSPclearLine(5);
    DSPshow(5, "Enter a product code and a new price");
    int catagory = KYBgetint(0);
    int price = KYBgetint(0);
    product_manager_price_adjust(catagory, price);
    DSPclearLine(5);
    DSPshow(5, "Price adjusted for category %d to %d cents.", catagory, price);

    FSM_AddEvent(E_ACTION_COMPLETED);
}

void collect_money_entry(void)
{
    DCSdebugSystemInfo("Collecting money from machine.\n");
    int collected_money = money_manager_collect();
    DSPclearLine(5);
    DSPshow(5, "Collected %d cents from machine.", collected_money);
    FSM_AddEvent(E_ACTION_COMPLETED);
}

void stock_products_entry(void)
{
    DCSdebugSystemInfo("Restocking products.\n");
    DSPclearLine(5);
    DSPshow(5, "Enter a product code and the amount restocked");
    int product = KYBgetint(0);
    int count = KYBgetint(0);
    DSPclearLine(5);
    DSPshow(5, "Restocked product %d with %d amount", product, count);
    product_manager_restock(product, count);

    FSM_AddEvent(E_ACTION_COMPLETED);
}
