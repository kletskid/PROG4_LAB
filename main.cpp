#include <QApplication>
#include "mainwindow.hpp"

extern "C" {
/// Finite State Machine Library
#include "fsm_functions/fsm.h"
#include "events.h"
#include "states.h"

#include "main.h"
#include "idle_mode.h"
#include "production_mode.h"
#include "product_manager.h"
#include "money_manager.h"
#include "maintenance_mode.h"

}

event_t event;
state_t state;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    
    idle_mode_register();
    production_mode_register();
    maintenance_mode_register();

    FSM_FlushEnexpectedEvents(true);
    

    MainWindow w;
    w.show();

    return app.exec();
}



