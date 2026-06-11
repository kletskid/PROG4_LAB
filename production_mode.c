
#include <unistd.h>
#include <time.h>

/// Finite State Machine Library
#include "fsm_functions/fsm.h"
#include "states.h"
#include "events.h"
/// Development Console Library
#include "keyboard.h"
#include "display.h"
#include "console.h"

#include "production_mode.h"
#include "product_manager.h"
#include "money_manager.h"




void production_mode_register()
{
   FSM_AddState(S_WAIT_FOR_MONEY, &(state_funcs_t){ wait_for_money_entry, wait_for_money_exit});
   FSM_AddState(S_PROCESS_50C, &(state_funcs_t){ process_50c_entry, process_50c_exit});
   FSM_AddState(S_PROCESS_20C, &(state_funcs_t){ process_20c_entry, process_20c_exit});
   FSM_AddState(S_END_INTERACTION, &(state_funcs_t){ end_interaction_entry, end_interaction_exit});

   FSM_AddTransition(&(transition_t){ S_WAIT_FOR_MONEY, E_20C, S_PROCESS_20C});
   FSM_AddTransition(&(transition_t){ S_WAIT_FOR_MONEY, E_50C, S_PROCESS_50C});
   FSM_AddTransition(&(transition_t){ S_WAIT_FOR_MONEY, E_MONEY_NOT_ACCEPTED, S_WAIT_FOR_MONEY});
   FSM_AddTransition(&(transition_t){ S_PROCESS_50C, E_MONEY_ENOUGH, S_END_INTERACTION});
   FSM_AddTransition(&(transition_t){ S_PROCESS_50C, E_MONEY_NOT_ENOUGH, S_WAIT_FOR_MONEY});
   FSM_AddTransition(&(transition_t){ S_PROCESS_20C, E_MONEY_ENOUGH, S_END_INTERACTION});
   FSM_AddTransition(&(transition_t){ S_PROCESS_20C, E_MONEY_NOT_ENOUGH, S_WAIT_FOR_MONEY});
   FSM_AddTransition(&(transition_t){ S_END_INTERACTION, E_INTERACTION_ENDED, S_IDLE});
   FSM_AddTransition(&(transition_t){ S_END_INTERACTION, E_MONEY_ENOUGH, S_END_INTERACTION});
}


event_t get_coin() {
   
   int coin = KYBgetint(0);
   
   switch (coin) {
      case 50:
         return E_50C; 
         break;
      case 20:
         return E_20C;
      default:
         return E_MONEY_NOT_ACCEPTED;
   }
}


void wait_for_money_entry()
{

   DCSdebugSystemInfo("in wait_for_money_entry\n");
   
   DSPclearDisplay();
   DSPshow(3, "Insert %d cents", product_manager_get_current_price());


   event_t money_event = get_coin();

   FSM_AddEvent(money_event);
}

void wait_for_money_exit()
{
   // do nothing
}


void process_50c_entry()
{
   DCSdebugSystemInfo("processing 50c\n");
   money_manager_add_money(50);
   event_t money_enough = money_manager_check_count();
   FSM_AddEvent(money_enough);
}

void process_50c_exit()
{

}


void process_20c_entry()
{
   DCSdebugSystemInfo("processing 20c\n");
   money_manager_add_money(20);
   event_t money_enough = money_manager_check_count();
   FSM_AddEvent(money_enough);
}

void process_20c_exit()
{

}

static struct timespec lastTime;

void end_interaction_entry()
{
   DCSdebugSystemInfo("finalising interaction\n");

   struct timespec current;
   clock_gettime(CLOCK_MONOTONIC, &current);
   if (lastTime.tv_sec == 0) {
      //DSPclearDisplay();
      product_manager_dispence_product();
      money_manager_finalize_transaction();

      lastTime = current;
   }

   if ((current.tv_sec - lastTime.tv_sec) > 3) {
      lastTime.tv_sec = 0;
      
      FSM_AddEvent(E_INTERACTION_ENDED);
   } else {
      FSM_AddEvent(E_MONEY_ENOUGH);
   }
}

void end_interaction_exit()
{

}


