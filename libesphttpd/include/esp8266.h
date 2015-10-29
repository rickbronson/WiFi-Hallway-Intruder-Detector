// Combined include file for esp8266

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <c_types.h>
#include <ip_addr.h>
#include <espconn.h>
#include <ets_sys.h>
#include <gpio.h>
#include <mem.h>
#include <osapi.h>
#include <upgrade.h>
#include <user_interface.h>

#include "espmissingincludes.h"

#ifdef DEBUG
#define debug(fmt,args...)	os_printf(fmt, ##args)
#else
#define debug(fmt,args...)
#endif
