/******************************************************************************
* @file    main.c
* @brief   Blinky/Button demo using uC/OS-II and the uC/AO Active Object layer
* @board   EK-TM4C123GXL
* @author  Alexandre Panhaleux
*******************************************************************************

                Blinky/Button with uC/OS-II RTOS

******************************************************************************/


#include <qassert_mini.h>    /* embedded-system-friendly assertions */
#include "uc_ao.h"      /* uC/OS-II API, port and compile-time configuration */
#include "bsp.h"        /* Board Support Package */
#include <stdbool.h>    /* For standard boolean types */

/* Module name for Q_ASSERT() diagnostics */
Q_DEFINE_THIS_MODULE("main") /* this module name for Q_ASSERT() */

/* The BlinkyButton AO =========================================================*/
enum { INITIAL_BLINK_TIME = (OS_TICKS_PER_SEC / 4) };

typedef struct{
    Active super; /* inherit active base class, Active Object from uC/AO */


    enum {OFF_STATE, ON_STATE}state;/* state variable */

    TimeEvent te;                   /* Time event for periodic blinking */
    uint32_t blink_time;            /* Current blink interval in ticks */
} BlinkyButton;

/* Static function prototype =========================================================*/
static void BlinkyButton_dispatch(BlinkyButton * const me,
                                  Event const * const e);

/* BlinkyButton implementation =========================================================*/
static void BlinkyButton_dispatch(BlinkyButton * const me, Event const * const e) {

    /* One-time initialization signal */
    if (e->sig == INIT_SIG){
        BSP_ledBlueOff();
        BSP_ledGreenOff();
        TimeEvent_arm(&me->te, me->blink_time * 3U, 0U); /* First timeout */
        me->state = OFF_STATE;
        return;
    }

    /* Main state machine */
    switch (me->state){
        case OFF_STATE:{
            switch(e->sig){
                case TIMEOUT_SIG:{
                    /* Turn OFF green LED, prepare next ON cycle */
                    BSP_ledGreenOff();
                    TimeEvent_arm(&me->te, me->blink_time * 3U, 0U);
                    me->state = ON_STATE;
                    break;
                }
                case BUTTON_PRESSED_SIG:{
                    BSP_ledBlueOn();
                    /* update the blink time for the 'blink' thread */
                    me->blink_time >>= 1U; /* shorten the blink time by factor of 2 */
                    if (me->blink_time == 0U) {
                        me->blink_time = INITIAL_BLINK_TIME;
                    }
                    break;
                }
                case BUTTON_RELEASED_SIG:{
                    BSP_ledBlueOff();
                    break;
                    }
            }
            break;
        }

        case ON_STATE:{
            switch(e->sig){
                case TIMEOUT_SIG:{
                    /* Turn ON green LED and schedule next OFF cycle */
                    BSP_ledGreenOn();
                    TimeEvent_arm(&me->te, me->blink_time, 0U);
                    me->state = OFF_STATE;
                    break;
                }
                case BUTTON_PRESSED_SIG:{
                    BSP_ledBlueOn();

                    /* update the blink time for the 'blink' thread */
                    me->blink_time >>= 1U; /* shorten the blink time by factor of 2 */
                    if (me->blink_time == 0U) {
                        me->blink_time = INITIAL_BLINK_TIME;
                    }
                    break;
                }
                case BUTTON_RELEASED_SIG:{
                    BSP_ledBlueOff();
                    break;
                }
            }
            break;
        }
        default:{
            Q_ASSERT(0); /* invalid state */
            break;
        }
    }
}

/* BlinkyButton AO constructor */
void BlinkyButton_ctor(BlinkyButton * const me) {
    Active_ctor(&me->super, (DispatchHandler)&BlinkyButton_dispatch);
    TimeEvent_ctor(&me->te, TIMEOUT_SIG, &me->super);
    me->state = OFF_STATE;
    me->blink_time = INITIAL_BLINK_TIME;
}

/* AO instance and RTOS resources declaration =========================================================*/
OS_STK stack_blinkyButton[100]; /* task stack */
static Event *blinkyButton_queue[10];
static BlinkyButton blinkyButton;
Active *AO_blinkyButton = &blinkyButton.super;

/* the main function =========================================================*/
int main() {

    BSP_init(); /* initialize the BSP */
    OSInit();   /* initialize uC/OS-II */


    /* create AO and start it */
    BlinkyButton_ctor(&blinkyButton);
    Active_start(AO_blinkyButton,
                      2U,       /* priority (1-based) */
                      blinkyButton_queue,
                      sizeof(blinkyButton_queue)/sizeof(blinkyButton_queue[0]),
                      stack_blinkyButton,
                      sizeof(stack_blinkyButton),
                      0U);

    BSP_start(); /* configure and start the interrupts */

    OSStart(); /* start the uC/OS-II scheduler... */
    return 0; /* NOTE: the scheduler does NOT return */
}

/*******************************************************************************
* NOTE1:
* The call to uC/OS-II API OSTaskCreateExt() assumes that the pointer to the
* top-of-stack (ptos) is at the end of the provided stack memory. This is
* correct only for CPUs with downward-growing stack, but must be changed for
* CPUs with upward-growing stack.
*/
