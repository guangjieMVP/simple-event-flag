#ifndef _EVENT_DRV_H_
#define _EVENT_DRV_H_

#define EVENT_ON   1
#define EVENT_OFF  0

typedef enum{
    CONTINUE_TYPE = 0,            //持续运行
    ONCE_TYPE     = 1             //产生一次事件运行一次
}event_type_t;

typedef void (*event_handle_func)(void); 

typedef struct __event_drv{
    unsigned char  event_flag : 1;                     /* Must not be equal to zero */ 
    event_type_t   event_type;                                       
    event_handle_func _event_handle_func;  
    struct __event_drv *next;
}event_drv_t;

void event_handle_loop(void);
char event_init(event_drv_t *event_handle, event_type_t event_type, event_handle_func __handle_func);
void post_event(event_drv_t *event_handle);


#endif

