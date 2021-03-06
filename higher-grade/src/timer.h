
/** 
 * @brief The three types of timers causes different signals.
 * @param type type of timer, one of ITIMER_REAL, ITIMER_VIRTUAL, or ITIMER_PROF.
 * @return The signal generated by the timer.
 */
int timer_signal(int timer_type);

/** 
 * @brief Set a timer and a handler for the timer.
 * @param type type of timer, one of ITIMER_REAL, ITIMER_VIRTUAL, or ITIMER_PROF.
 * @param handler timer signal handler
 * @param ms time in ms for the timer
 */
void set_timer(int type, void (*handler)(int), int ms);



void timer_handler (int signum);