#include <unistd.h>

#include "idle_mode.h"
#include "fsm_functions/fsm.h"
#include "events.h"
#include "states.h"
#include "main.h"
#include "money_manager.h"
#include "product_manager.h"
#include "display.h"
#include "console.h"
#include "keyboard.h"


void idle_mode_register()
{
   FSM_AddState(S_IDLE, &(state_funcs_t){ idle_entry, idle_exit });
   
   FSM_AddTransition(&(transition_t){ S_IDLE, E_INITIALIZE, S_IDLE});
   FSM_AddTransition(&(transition_t){ S_IDLE, E_SELECT_PRODUCT, S_WAIT_FOR_MONEY});
   FSM_AddTransition(&(transition_t){ S_IDLE, E_MAINTENANCE, S_OUT_OF_ORDER});
}

void idle_entry()
{
   if (event == E_INITIALIZE) {
      money_manager_init();
      product_manager_init(); 

      DSPclearDisplay();
      DSPshow(3, "Initialising system...");
   }
   DCSdebugSystemInfo("in state idle\n");
   DSPclearDisplay();
   DSPshow(3, "Enter product code");
   int product_code = KYBgetint(0);

   event_t mode_event = product_manager_set_product((enum product_code_e) product_code);
   FSM_AddEvent(mode_event);
}

void idle_exit()
{
   
}

