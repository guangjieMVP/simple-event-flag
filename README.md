封装事件标志减少裸机编程中全局标志变量的使用

#### 初始化事件

void event_init(void)；

#### 注册事件

```c
EVENT_EXPORT(event1, ONCE_TYPE, event1)
```

```c
void event1(void)
{
	/* user code */
}
EVENT_EXPORT(event1, ONCE_TYPE, event1);
```

* event1 ——事件的名字(字符串)
* ONCE_TYPE ——事件类型
* event1 ——事件处理函数

#### 发布事件

```c
void publish_event(char *event_name);
```

```c
publish_event(event1);
```

#### 主循环调用

```c
void event_handle_loop(void)
```
```c
int main(void)
{
    while(1)
	{
    	event_handle_loop();		
	}
    
    return 0;
}

```

