/* This file is autogenerated by tracetool, do not edit. */

#include "qemu/osdep.h"
#include "qemu/module.h"
#include "trace.h"

uint16_t _TRACE_KVM_FAILED_SPR_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_SPR_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_FPSCR_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_FP_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_VSCR_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_VR_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_FPSCR_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_FP_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_VSCR_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_VR_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_VPA_ADDR_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_SLB_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_DTL_GET_DSTATE;
uint16_t _TRACE_KVM_FAILED_VPA_ADDR_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_SLB_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_DTL_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_NULL_VPA_ADDR_SET_DSTATE;
uint16_t _TRACE_KVM_FAILED_PUT_VPA_DSTATE;
uint16_t _TRACE_KVM_FAILED_GET_VPA_DSTATE;
uint16_t _TRACE_KVM_INJECTED_INTERRUPT_DSTATE;
uint16_t _TRACE_KVM_HANDLE_DCR_WRITE_DSTATE;
uint16_t _TRACE_KVM_HANDLE_DCR_READ_DSTATE;
uint16_t _TRACE_KVM_HANDLE_HALT_DSTATE;
uint16_t _TRACE_KVM_HANDLE_PAPR_HCALL_DSTATE;
uint16_t _TRACE_KVM_HANDLE_EPR_DSTATE;
uint16_t _TRACE_KVM_HANDLE_WATCHDOG_EXPIRY_DSTATE;
uint16_t _TRACE_KVM_HANDLE_DEBUG_EXCEPTION_DSTATE;
uint16_t _TRACE_KVM_HANDLE_NMI_EXCEPTION_DSTATE;
TraceEvent _TRACE_KVM_FAILED_SPR_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_spr_set",
    .sstate = TRACE_KVM_FAILED_SPR_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_SPR_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_SPR_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_spr_get",
    .sstate = TRACE_KVM_FAILED_SPR_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_SPR_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_FPSCR_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_fpscr_set",
    .sstate = TRACE_KVM_FAILED_FPSCR_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_FPSCR_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_FP_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_fp_set",
    .sstate = TRACE_KVM_FAILED_FP_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_FP_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_VSCR_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_vscr_set",
    .sstate = TRACE_KVM_FAILED_VSCR_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_VSCR_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_VR_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_vr_set",
    .sstate = TRACE_KVM_FAILED_VR_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_VR_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_FPSCR_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_fpscr_get",
    .sstate = TRACE_KVM_FAILED_FPSCR_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_FPSCR_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_FP_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_fp_get",
    .sstate = TRACE_KVM_FAILED_FP_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_FP_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_VSCR_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_vscr_get",
    .sstate = TRACE_KVM_FAILED_VSCR_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_VSCR_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_VR_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_vr_get",
    .sstate = TRACE_KVM_FAILED_VR_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_VR_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_VPA_ADDR_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_vpa_addr_get",
    .sstate = TRACE_KVM_FAILED_VPA_ADDR_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_VPA_ADDR_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_SLB_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_slb_get",
    .sstate = TRACE_KVM_FAILED_SLB_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_SLB_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_DTL_GET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_dtl_get",
    .sstate = TRACE_KVM_FAILED_DTL_GET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_DTL_GET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_VPA_ADDR_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_vpa_addr_set",
    .sstate = TRACE_KVM_FAILED_VPA_ADDR_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_VPA_ADDR_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_SLB_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_slb_set",
    .sstate = TRACE_KVM_FAILED_SLB_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_SLB_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_DTL_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_dtl_set",
    .sstate = TRACE_KVM_FAILED_DTL_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_DTL_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_NULL_VPA_ADDR_SET_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_null_vpa_addr_set",
    .sstate = TRACE_KVM_FAILED_NULL_VPA_ADDR_SET_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_NULL_VPA_ADDR_SET_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_PUT_VPA_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_put_vpa",
    .sstate = TRACE_KVM_FAILED_PUT_VPA_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_PUT_VPA_DSTATE 
};
TraceEvent _TRACE_KVM_FAILED_GET_VPA_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_failed_get_vpa",
    .sstate = TRACE_KVM_FAILED_GET_VPA_ENABLED,
    .dstate = &_TRACE_KVM_FAILED_GET_VPA_DSTATE 
};
TraceEvent _TRACE_KVM_INJECTED_INTERRUPT_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_injected_interrupt",
    .sstate = TRACE_KVM_INJECTED_INTERRUPT_ENABLED,
    .dstate = &_TRACE_KVM_INJECTED_INTERRUPT_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_DCR_WRITE_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_dcr_write",
    .sstate = TRACE_KVM_HANDLE_DCR_WRITE_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_DCR_WRITE_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_DCR_READ_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_dcr_read",
    .sstate = TRACE_KVM_HANDLE_DCR_READ_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_DCR_READ_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_HALT_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_halt",
    .sstate = TRACE_KVM_HANDLE_HALT_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_HALT_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_PAPR_HCALL_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_papr_hcall",
    .sstate = TRACE_KVM_HANDLE_PAPR_HCALL_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_PAPR_HCALL_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_EPR_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_epr",
    .sstate = TRACE_KVM_HANDLE_EPR_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_EPR_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_WATCHDOG_EXPIRY_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_watchdog_expiry",
    .sstate = TRACE_KVM_HANDLE_WATCHDOG_EXPIRY_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_WATCHDOG_EXPIRY_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_DEBUG_EXCEPTION_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_debug_exception",
    .sstate = TRACE_KVM_HANDLE_DEBUG_EXCEPTION_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_DEBUG_EXCEPTION_DSTATE 
};
TraceEvent _TRACE_KVM_HANDLE_NMI_EXCEPTION_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "kvm_handle_nmi_exception",
    .sstate = TRACE_KVM_HANDLE_NMI_EXCEPTION_ENABLED,
    .dstate = &_TRACE_KVM_HANDLE_NMI_EXCEPTION_DSTATE 
};
TraceEvent *target_ppc_trace_events[] = {
    &_TRACE_KVM_FAILED_SPR_SET_EVENT,
    &_TRACE_KVM_FAILED_SPR_GET_EVENT,
    &_TRACE_KVM_FAILED_FPSCR_SET_EVENT,
    &_TRACE_KVM_FAILED_FP_SET_EVENT,
    &_TRACE_KVM_FAILED_VSCR_SET_EVENT,
    &_TRACE_KVM_FAILED_VR_SET_EVENT,
    &_TRACE_KVM_FAILED_FPSCR_GET_EVENT,
    &_TRACE_KVM_FAILED_FP_GET_EVENT,
    &_TRACE_KVM_FAILED_VSCR_GET_EVENT,
    &_TRACE_KVM_FAILED_VR_GET_EVENT,
    &_TRACE_KVM_FAILED_VPA_ADDR_GET_EVENT,
    &_TRACE_KVM_FAILED_SLB_GET_EVENT,
    &_TRACE_KVM_FAILED_DTL_GET_EVENT,
    &_TRACE_KVM_FAILED_VPA_ADDR_SET_EVENT,
    &_TRACE_KVM_FAILED_SLB_SET_EVENT,
    &_TRACE_KVM_FAILED_DTL_SET_EVENT,
    &_TRACE_KVM_FAILED_NULL_VPA_ADDR_SET_EVENT,
    &_TRACE_KVM_FAILED_PUT_VPA_EVENT,
    &_TRACE_KVM_FAILED_GET_VPA_EVENT,
    &_TRACE_KVM_INJECTED_INTERRUPT_EVENT,
    &_TRACE_KVM_HANDLE_DCR_WRITE_EVENT,
    &_TRACE_KVM_HANDLE_DCR_READ_EVENT,
    &_TRACE_KVM_HANDLE_HALT_EVENT,
    &_TRACE_KVM_HANDLE_PAPR_HCALL_EVENT,
    &_TRACE_KVM_HANDLE_EPR_EVENT,
    &_TRACE_KVM_HANDLE_WATCHDOG_EXPIRY_EVENT,
    &_TRACE_KVM_HANDLE_DEBUG_EXCEPTION_EVENT,
    &_TRACE_KVM_HANDLE_NMI_EXCEPTION_EVENT,
  NULL,
};

static void trace_target_ppc_register_events(void)
{
    trace_event_register_group(target_ppc_trace_events);
}
trace_init(trace_target_ppc_register_events)
