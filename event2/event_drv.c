#include "event_drv.h"
#include "string.h"


static event_drv_t event_drv_list_head = {0,ONCE_TYPE,(void *)0,(void *)0};

/**
  * @brief:         
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ      
  * @version:       v1.0.0
*/
static unsigned char  is_event_list_empty(void)
{
	if(event_drv_list_head.next == NULL)
		return 1;
	else
		return 0;
}

/**
  * @brief:         Insert the software timer node into the linked list
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ      
  * @version:       v1.0.0
*/
static void insert_event_handle(event_drv_t *event_handle)
{
    event_drv_t *tmp;
    event_drv_t *list_head = &event_drv_list_head;

    if(is_event_list_empty())
    {
        list_head->next = event_handle;
    }
    else
    {
        tmp = list_head->next;
        while(tmp->next)
        {
			if(event_handle == tmp)    
			{
				printf("The timer already exists\r\n");
				return;
			}
            tmp = tmp->next; 
        }
        tmp->next = event_handle;
    }
}

/**
  * @brief:         Removes the software timer node from the list
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ       
  * @version:       v1.0.0
*/
static void remove_event_handle(event_drv_t *event_handle)
{
    event_drv_t *list_head = &event_drv_list_head;
    event_drv_t *tmp = list_head;
	
	if(is_event_list_empty())
		return;
	
    while(tmp && tmp->next != event_handle)
    {
        tmp = tmp->next;
    }
	
	if(tmp == NULL)
		return;
	
	tmp->next          = event_handle->next;
	event_handle->next = NULL;	
}

/**
  * @brief:         Traverse the software timer list
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ             
*/
static void traverse_list(void)
{
	event_drv_t *tmp = &event_drv_list_head;
	tmp = tmp->next;
	while(tmp)
	{
		tmp->_event_handle_func();
		tmp = tmp->next;
	}
}

/**
  * @brief:         initialize event 
  * @param[in]:     event_handle  event data struct handle
  * @param[in]:     event_number  event number,Must not be equal to zero,numbering between events can be equal
  * @param[in]:     event_type event type
  *                 CONTINUE_TYPE   continuous running
  *                 ONCE_TYPE       once running after post event
  * @param[in]:     __handle_func   event handled fuction
  * @retval[out]:   true : initialize finish
  *                 false : intialize fail
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/guangjieSuper            
*/
char event_init(event_drv_t *event_handle, event_type_t event_type, event_handle_func __handle_func)
{
	event_handle->event_flag         = EVENT_OFF;
	event_handle->event_type         = event_type;
	event_handle->_event_handle_func = __handle_func;
	event_handle->next               = NULL;
	insert_event_handle(event_handle);   
    return 0;
}

/**
  * @brief:         
  * @param[in]:     
  * @retval[out]:   
  * @note:            
  * @author:        
  * @github:              
*/
void post_event(event_drv_t *event_handle)
{
    event_handle->event_flag = EVENT_ON;
}

void event_handle_loop(void)
{
    event_drv_t *event_handle;
    
    for(event_handle = event_drv_list_head.next; event_handle; event_handle = event_handle->next)
    {
        if(event_handle->event_type == CONTINUE_TYPE)      //Continuous running event
        {
            event_handle->_event_handle_func();
        }
        else                                               //once running event
        {
            if(event_handle->event_flag == EVENT_ON)
            {
                event_handle->_event_handle_func();
                event_handle->event_flag = EVENT_OFF;
            }
        }
    }
}



