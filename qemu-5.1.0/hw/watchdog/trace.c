/* This file is autogenerated by tracetool, do not edit. */

#include "qemu/osdep.h"
#include "qemu/module.h"
#include "trace.h"

uint16_t _TRACE_CMSDK_APB_WATCHDOG_READ_DSTATE;
uint16_t _TRACE_CMSDK_APB_WATCHDOG_WRITE_DSTATE;
uint16_t _TRACE_CMSDK_APB_WATCHDOG_RESET_DSTATE;
uint16_t _TRACE_CMSDK_APB_WATCHDOG_LOCK_DSTATE;
TraceEvent _TRACE_CMSDK_APB_WATCHDOG_READ_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "cmsdk_apb_watchdog_read",
    .sstate = TRACE_CMSDK_APB_WATCHDOG_READ_ENABLED,
    .dstate = &_TRACE_CMSDK_APB_WATCHDOG_READ_DSTATE 
};
TraceEvent _TRACE_CMSDK_APB_WATCHDOG_WRITE_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "cmsdk_apb_watchdog_write",
    .sstate = TRACE_CMSDK_APB_WATCHDOG_WRITE_ENABLED,
    .dstate = &_TRACE_CMSDK_APB_WATCHDOG_WRITE_DSTATE 
};
TraceEvent _TRACE_CMSDK_APB_WATCHDOG_RESET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "cmsdk_apb_watchdog_reset",
    .sstate = TRACE_CMSDK_APB_WATCHDOG_RESET_ENABLED,
    .dstate = &_TRACE_CMSDK_APB_WATCHDOG_RESET_DSTATE 
};
TraceEvent _TRACE_CMSDK_APB_WATCHDOG_LOCK_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "cmsdk_apb_watchdog_lock",
    .sstate = TRACE_CMSDK_APB_WATCHDOG_LOCK_ENABLED,
    .dstate = &_TRACE_CMSDK_APB_WATCHDOG_LOCK_DSTATE 
};
TraceEvent *hw_watchdog_trace_events[] = {
    &_TRACE_CMSDK_APB_WATCHDOG_READ_EVENT,
    &_TRACE_CMSDK_APB_WATCHDOG_WRITE_EVENT,
    &_TRACE_CMSDK_APB_WATCHDOG_RESET_EVENT,
    &_TRACE_CMSDK_APB_WATCHDOG_LOCK_EVENT,
  NULL,
};

static void trace_hw_watchdog_register_events(void)
{
    trace_event_register_group(hw_watchdog_trace_events);
}
trace_init(trace_hw_watchdog_register_events)
