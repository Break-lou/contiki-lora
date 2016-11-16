本代码适用于第四代节点的硬件版本、标签硬件。目前集成了SHT25、CO2传感器

2015.08.19
增加BLE数据上传功能，其中修改的地方有：
1. sensor_co2_process.c中的第54行co2_param_init();屏蔽掉
2. sensor_sht25_process.c中的第100行到123屏蔽掉
3. main.c中的第52行屏蔽掉，增加54、55行
4. 温湿度数据通过串口UART0上发数据，数据格式为："Himilit:xx,Temper:xx."，总共20字节


2015.08.21
修改DCDC初始化后设置，修改内容包括如下：
1. minimum_pulse_width 设置为3，原来是0
2. 增加异步模式SI32_DCDC_A_enable_async_mode(SI32_DCDC_0);
经过上述修改，当电池电量降低后，CO2供电的电压波形较之前的稳定


版本修改记录
V0.3版本：
1.增加DA,DB,SFM指令
2.休眠函数中增加工作模式判断，在配置和快速工作模式下直接返回
3.温度采集增加修正函数
4.入网请求的应答中，增加是否父节点是否同步标志判断，以此判断是否同步本地时间
 
2016.5.6
<RTC_config.c>
fun:set_current_time()
根据复位源来决定是否重新标定基准时刻。
增加：看门狗复位不处理标定基准时刻。

2016.5.26
增加：
历史数据发送条数：void at_hdtc(AT_CMD_TYPE* at_item);
	 at+hdtc=n(n>0)
模式切换：void at_sms(AT_CMD_TYPE* at_item);
其中 at+sms=0(停止工作)
	 at+sms=1(正常工作)
	 at+sms=2(配置工作)
	 at+sms=3(快速工作)
	 at+sms=3(重启设备)
ev==SOFTWARE_RESET_EVENT为重启设备事件
格式化flash：void at_fsrc(AT_CMD_TYPE* at_item);
	 at+fsrc>
ev==FORMAT_FLASH_EVENT为清零flash及缓存事件

修改：
在快速工作模式下，接受到广播包不进行闪灯；

2016.6.2
修改：中继同步后不叠加时间片的时间
2016.6.7
广播入网接收包(0x91)增加：判断父节点类型1.若为网关则直接入网；2.若为中继则判断第二强的信号，否则直接监听
发送历史数据判断接收包信息

2016.09.12

在analyst_transmit_sensor_data_payload增加同步信息操作
在analyst_transmit_sensor_history_payload增加同步信息操作
在sensor_sixteen_buffer_put增加缓存满则写FLASH操作





