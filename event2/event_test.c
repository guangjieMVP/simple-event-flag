/**
  * @file:     xxx.c
  * @author:   guangjieSuper
  * @github:   https://github.com/guangjieSuper
  * @version:  v1.0.0
  * @date:     2020-xx-xx
  * @brief:               
*/
/**
  * @file:     xxx.c
  * @author:   AresXu
  * @github:              
  * @version:  v1.0.0
  * @date:     2020-01-xx
  * @brief:               
*/
#include "event_drv.h"
#include "sys_init.h"

void event1(void)
{
	printf("event1 Ares>>\r\n");
}

void event2(void)
{
	printf("event2 Sola>>\r\n");
}

void event3(void)
{
	printf("event3 Pzibang>>\r\n");
}

event_drv_t event1_handle;
event_drv_t event2_handle;
event_drv_t event3_handle;

void MyEventInit(void)
{
	event_init(&event1_handle, ONCE_TYPE, event1);
	event_init(&event2_handle, ONCE_TYPE, event2);
	event_init(&event3_handle, ONCE_TYPE, event3);
}


