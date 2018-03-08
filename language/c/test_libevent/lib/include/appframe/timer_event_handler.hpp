#ifndef  _TIMER_EVENT_HANDLER_HPP_
#define _TIMER_EVENT_HANDLER_HPP_



namespace std
{
    class TimerEventHandler
    {
    public:
        virtual ~TimerEventHandler() {}
    public:
        virtual void handle_timeout(void* param)=0;
    };
}


#endif
