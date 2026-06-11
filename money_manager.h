#pragma once

void money_manager_init();
uint32_t money_manager_get_count();
void money_manager_add_money(uint32_t money); 
event_t money_manager_check_count(); 
void money_manager_finalize_transaction();
uint32_t money_manager_collect();
