<!--
 * @file:     xxx.c
 * @author:   guangjieMVP
 * @github:               
 * @version:  v1.0.0
 * @date:     2020-xx-xx
 * @brief:               
-->
封装事件标志减少裸机编程中全局标志变量的使用

#### 初始化事件标志机制
void doge_event_init(void);

#### 注册事件

```c
void event1(void)
{
	/* user code */
}
DOGE_EVENT_EXPORT(event1, ONCE_TYPE, event1);
```

* event1 ——事件的名字(字符串)
* ONCE_TYPE ——事件类型
* event1 ——事件处理函数

#### 发布事件

```c
doge_publish_event(event1);
```

#### 主循环调用

```c
int main(void)
{
    while(1)
	{
    	doge_event_handle_loop();	  //循环调用处理事件标志	
	}
    
    return 0;
}

```

