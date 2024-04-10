/* AUTOMATICALLY GENERATED, DO NOT MODIFY */

/*
 * Schema-defined QAPI visitors
 *
 * Copyright IBM, Corp. 2011
 * Copyright (C) 2014-2018 Red Hat, Inc.
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qapi/qmp/qerror.h"
#include "qapi-visit-misc.h"

bool visit_type_LostTickPolicy(Visitor *v, const char *name, LostTickPolicy *obj, Error **errp)
{
    int value = *obj;
    bool ok = visit_type_enum(v, name, &value, &LostTickPolicy_lookup, errp);
    *obj = value;
    return ok;
}

bool visit_type_q_obj_add_client_arg_members(Visitor *v, q_obj_add_client_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "protocol", &obj->protocol, errp)) {
        return false;
    }
    if (!visit_type_str(v, "fdname", &obj->fdname, errp)) {
        return false;
    }
    if (visit_optional(v, "skipauth", &obj->has_skipauth)) {
        if (!visit_type_bool(v, "skipauth", &obj->skipauth, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "tls", &obj->has_tls)) {
        if (!visit_type_bool(v, "tls", &obj->tls, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_NameInfo_members(Visitor *v, NameInfo *obj, Error **errp)
{
    if (visit_optional(v, "name", &obj->has_name)) {
        if (!visit_type_str(v, "name", &obj->name, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_NameInfo(Visitor *v, const char *name, NameInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(NameInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_NameInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_NameInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_KvmInfo_members(Visitor *v, KvmInfo *obj, Error **errp)
{
    if (!visit_type_bool(v, "enabled", &obj->enabled, errp)) {
        return false;
    }
    if (!visit_type_bool(v, "present", &obj->present, errp)) {
        return false;
    }
    return true;
}

bool visit_type_KvmInfo(Visitor *v, const char *name, KvmInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(KvmInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_KvmInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_KvmInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_UuidInfo_members(Visitor *v, UuidInfo *obj, Error **errp)
{
    if (!visit_type_str(v, "UUID", &obj->UUID, errp)) {
        return false;
    }
    return true;
}

bool visit_type_UuidInfo(Visitor *v, const char *name, UuidInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(UuidInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_UuidInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_UuidInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_IOThreadInfo_members(Visitor *v, IOThreadInfo *obj, Error **errp)
{
    if (!visit_type_str(v, "id", &obj->id, errp)) {
        return false;
    }
    if (!visit_type_int(v, "thread-id", &obj->thread_id, errp)) {
        return false;
    }
    if (!visit_type_int(v, "poll-max-ns", &obj->poll_max_ns, errp)) {
        return false;
    }
    if (!visit_type_int(v, "poll-grow", &obj->poll_grow, errp)) {
        return false;
    }
    if (!visit_type_int(v, "poll-shrink", &obj->poll_shrink, errp)) {
        return false;
    }
    return true;
}

bool visit_type_IOThreadInfo(Visitor *v, const char *name, IOThreadInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(IOThreadInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_IOThreadInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_IOThreadInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_IOThreadInfoList(Visitor *v, const char *name, IOThreadInfoList **obj, Error **errp)
{
    bool ok = false;
    IOThreadInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (IOThreadInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_IOThreadInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_IOThreadInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_BalloonInfo_members(Visitor *v, BalloonInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "actual", &obj->actual, errp)) {
        return false;
    }
    return true;
}

bool visit_type_BalloonInfo(Visitor *v, const char *name, BalloonInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(BalloonInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_BalloonInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_BalloonInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_BALLOON_CHANGE_arg_members(Visitor *v, q_obj_BALLOON_CHANGE_arg *obj, Error **errp)
{
    if (!visit_type_int(v, "actual", &obj->actual, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PciMemoryRange_members(Visitor *v, PciMemoryRange *obj, Error **errp)
{
    if (!visit_type_int(v, "base", &obj->base, errp)) {
        return false;
    }
    if (!visit_type_int(v, "limit", &obj->limit, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PciMemoryRange(Visitor *v, const char *name, PciMemoryRange **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciMemoryRange), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciMemoryRange_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciMemoryRange(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciMemoryRegion_members(Visitor *v, PciMemoryRegion *obj, Error **errp)
{
    if (!visit_type_int(v, "bar", &obj->bar, errp)) {
        return false;
    }
    if (!visit_type_str(v, "type", &obj->type, errp)) {
        return false;
    }
    if (!visit_type_int(v, "address", &obj->address, errp)) {
        return false;
    }
    if (!visit_type_int(v, "size", &obj->size, errp)) {
        return false;
    }
    if (visit_optional(v, "prefetch", &obj->has_prefetch)) {
        if (!visit_type_bool(v, "prefetch", &obj->prefetch, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "mem_type_64", &obj->has_mem_type_64)) {
        if (!visit_type_bool(v, "mem_type_64", &obj->mem_type_64, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_PciMemoryRegion(Visitor *v, const char *name, PciMemoryRegion **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciMemoryRegion), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciMemoryRegion_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciMemoryRegion(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciBusInfo_members(Visitor *v, PciBusInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "number", &obj->number, errp)) {
        return false;
    }
    if (!visit_type_int(v, "secondary", &obj->secondary, errp)) {
        return false;
    }
    if (!visit_type_int(v, "subordinate", &obj->subordinate, errp)) {
        return false;
    }
    if (!visit_type_PciMemoryRange(v, "io_range", &obj->io_range, errp)) {
        return false;
    }
    if (!visit_type_PciMemoryRange(v, "memory_range", &obj->memory_range, errp)) {
        return false;
    }
    if (!visit_type_PciMemoryRange(v, "prefetchable_range", &obj->prefetchable_range, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PciBusInfo(Visitor *v, const char *name, PciBusInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciBusInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciBusInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciBusInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciDeviceInfoList(Visitor *v, const char *name, PciDeviceInfoList **obj, Error **errp)
{
    bool ok = false;
    PciDeviceInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (PciDeviceInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_PciDeviceInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciDeviceInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciBridgeInfo_members(Visitor *v, PciBridgeInfo *obj, Error **errp)
{
    if (!visit_type_PciBusInfo(v, "bus", &obj->bus, errp)) {
        return false;
    }
    if (visit_optional(v, "devices", &obj->has_devices)) {
        if (!visit_type_PciDeviceInfoList(v, "devices", &obj->devices, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_PciBridgeInfo(Visitor *v, const char *name, PciBridgeInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciBridgeInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciBridgeInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciBridgeInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciDeviceClass_members(Visitor *v, PciDeviceClass *obj, Error **errp)
{
    if (visit_optional(v, "desc", &obj->has_desc)) {
        if (!visit_type_str(v, "desc", &obj->desc, errp)) {
            return false;
        }
    }
    if (!visit_type_int(v, "class", &obj->q_class, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PciDeviceClass(Visitor *v, const char *name, PciDeviceClass **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciDeviceClass), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciDeviceClass_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciDeviceClass(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciDeviceId_members(Visitor *v, PciDeviceId *obj, Error **errp)
{
    if (!visit_type_int(v, "device", &obj->device, errp)) {
        return false;
    }
    if (!visit_type_int(v, "vendor", &obj->vendor, errp)) {
        return false;
    }
    if (visit_optional(v, "subsystem", &obj->has_subsystem)) {
        if (!visit_type_int(v, "subsystem", &obj->subsystem, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "subsystem-vendor", &obj->has_subsystem_vendor)) {
        if (!visit_type_int(v, "subsystem-vendor", &obj->subsystem_vendor, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_PciDeviceId(Visitor *v, const char *name, PciDeviceId **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciDeviceId), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciDeviceId_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciDeviceId(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciMemoryRegionList(Visitor *v, const char *name, PciMemoryRegionList **obj, Error **errp)
{
    bool ok = false;
    PciMemoryRegionList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (PciMemoryRegionList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_PciMemoryRegion(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciMemoryRegionList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciDeviceInfo_members(Visitor *v, PciDeviceInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "bus", &obj->bus, errp)) {
        return false;
    }
    if (!visit_type_int(v, "slot", &obj->slot, errp)) {
        return false;
    }
    if (!visit_type_int(v, "function", &obj->function, errp)) {
        return false;
    }
    if (!visit_type_PciDeviceClass(v, "class_info", &obj->class_info, errp)) {
        return false;
    }
    if (!visit_type_PciDeviceId(v, "id", &obj->id, errp)) {
        return false;
    }
    if (visit_optional(v, "irq", &obj->has_irq)) {
        if (!visit_type_int(v, "irq", &obj->irq, errp)) {
            return false;
        }
    }
    if (!visit_type_int(v, "irq_pin", &obj->irq_pin, errp)) {
        return false;
    }
    if (!visit_type_str(v, "qdev_id", &obj->qdev_id, errp)) {
        return false;
    }
    if (visit_optional(v, "pci_bridge", &obj->has_pci_bridge)) {
        if (!visit_type_PciBridgeInfo(v, "pci_bridge", &obj->pci_bridge, errp)) {
            return false;
        }
    }
    if (!visit_type_PciMemoryRegionList(v, "regions", &obj->regions, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PciDeviceInfo(Visitor *v, const char *name, PciDeviceInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciDeviceInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciDeviceInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciDeviceInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciInfo_members(Visitor *v, PciInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "bus", &obj->bus, errp)) {
        return false;
    }
    if (!visit_type_PciDeviceInfoList(v, "devices", &obj->devices, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PciInfo(Visitor *v, const char *name, PciInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PciInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PciInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PciInfoList(Visitor *v, const char *name, PciInfoList **obj, Error **errp)
{
    bool ok = false;
    PciInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (PciInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_PciInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PciInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_memsave_arg_members(Visitor *v, q_obj_memsave_arg *obj, Error **errp)
{
    if (!visit_type_int(v, "val", &obj->val, errp)) {
        return false;
    }
    if (!visit_type_int(v, "size", &obj->size, errp)) {
        return false;
    }
    if (!visit_type_str(v, "filename", &obj->filename, errp)) {
        return false;
    }
    if (visit_optional(v, "cpu-index", &obj->has_cpu_index)) {
        if (!visit_type_int(v, "cpu-index", &obj->cpu_index, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_q_obj_pmemsave_arg_members(Visitor *v, q_obj_pmemsave_arg *obj, Error **errp)
{
    if (!visit_type_int(v, "val", &obj->val, errp)) {
        return false;
    }
    if (!visit_type_int(v, "size", &obj->size, errp)) {
        return false;
    }
    if (!visit_type_str(v, "filename", &obj->filename, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_balloon_arg_members(Visitor *v, q_obj_balloon_arg *obj, Error **errp)
{
    if (!visit_type_int(v, "value", &obj->value, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_human_monitor_command_arg_members(Visitor *v, q_obj_human_monitor_command_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "command-line", &obj->command_line, errp)) {
        return false;
    }
    if (visit_optional(v, "cpu-index", &obj->has_cpu_index)) {
        if (!visit_type_int(v, "cpu-index", &obj->cpu_index, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_q_obj_change_arg_members(Visitor *v, q_obj_change_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "device", &obj->device, errp)) {
        return false;
    }
    if (!visit_type_str(v, "target", &obj->target, errp)) {
        return false;
    }
    if (visit_optional(v, "arg", &obj->has_arg)) {
        if (!visit_type_str(v, "arg", &obj->arg, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_q_obj_xen_set_global_dirty_log_arg_members(Visitor *v, q_obj_xen_set_global_dirty_log_arg *obj, Error **errp)
{
    if (!visit_type_bool(v, "enable", &obj->enable, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_getfd_arg_members(Visitor *v, q_obj_getfd_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "fdname", &obj->fdname, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_closefd_arg_members(Visitor *v, q_obj_closefd_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "fdname", &obj->fdname, errp)) {
        return false;
    }
    return true;
}

bool visit_type_MemoryInfo_members(Visitor *v, MemoryInfo *obj, Error **errp)
{
    if (!visit_type_size(v, "base-memory", &obj->base_memory, errp)) {
        return false;
    }
    if (visit_optional(v, "plugged-memory", &obj->has_plugged_memory)) {
        if (!visit_type_size(v, "plugged-memory", &obj->plugged_memory, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_MemoryInfo(Visitor *v, const char *name, MemoryInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(MemoryInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_MemoryInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_MemoryInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_AddfdInfo_members(Visitor *v, AddfdInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "fdset-id", &obj->fdset_id, errp)) {
        return false;
    }
    if (!visit_type_int(v, "fd", &obj->fd, errp)) {
        return false;
    }
    return true;
}

bool visit_type_AddfdInfo(Visitor *v, const char *name, AddfdInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(AddfdInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_AddfdInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_AddfdInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_add_fd_arg_members(Visitor *v, q_obj_add_fd_arg *obj, Error **errp)
{
    if (visit_optional(v, "fdset-id", &obj->has_fdset_id)) {
        if (!visit_type_int(v, "fdset-id", &obj->fdset_id, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "opaque", &obj->has_opaque)) {
        if (!visit_type_str(v, "opaque", &obj->opaque, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_q_obj_remove_fd_arg_members(Visitor *v, q_obj_remove_fd_arg *obj, Error **errp)
{
    if (!visit_type_int(v, "fdset-id", &obj->fdset_id, errp)) {
        return false;
    }
    if (visit_optional(v, "fd", &obj->has_fd)) {
        if (!visit_type_int(v, "fd", &obj->fd, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_FdsetFdInfo_members(Visitor *v, FdsetFdInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "fd", &obj->fd, errp)) {
        return false;
    }
    if (visit_optional(v, "opaque", &obj->has_opaque)) {
        if (!visit_type_str(v, "opaque", &obj->opaque, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_FdsetFdInfo(Visitor *v, const char *name, FdsetFdInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(FdsetFdInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_FdsetFdInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_FdsetFdInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_FdsetFdInfoList(Visitor *v, const char *name, FdsetFdInfoList **obj, Error **errp)
{
    bool ok = false;
    FdsetFdInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (FdsetFdInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_FdsetFdInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_FdsetFdInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_FdsetInfo_members(Visitor *v, FdsetInfo *obj, Error **errp)
{
    if (!visit_type_int(v, "fdset-id", &obj->fdset_id, errp)) {
        return false;
    }
    if (!visit_type_FdsetFdInfoList(v, "fds", &obj->fds, errp)) {
        return false;
    }
    return true;
}

bool visit_type_FdsetInfo(Visitor *v, const char *name, FdsetInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(FdsetInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_FdsetInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_FdsetInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_FdsetInfoList(Visitor *v, const char *name, FdsetInfoList **obj, Error **errp)
{
    bool ok = false;
    FdsetInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (FdsetInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_FdsetInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_FdsetInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_AcpiTableOptions_members(Visitor *v, AcpiTableOptions *obj, Error **errp)
{
    if (visit_optional(v, "sig", &obj->has_sig)) {
        if (!visit_type_str(v, "sig", &obj->sig, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "rev", &obj->has_rev)) {
        if (!visit_type_uint8(v, "rev", &obj->rev, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "oem_id", &obj->has_oem_id)) {
        if (!visit_type_str(v, "oem_id", &obj->oem_id, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "oem_table_id", &obj->has_oem_table_id)) {
        if (!visit_type_str(v, "oem_table_id", &obj->oem_table_id, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "oem_rev", &obj->has_oem_rev)) {
        if (!visit_type_uint32(v, "oem_rev", &obj->oem_rev, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "asl_compiler_id", &obj->has_asl_compiler_id)) {
        if (!visit_type_str(v, "asl_compiler_id", &obj->asl_compiler_id, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "asl_compiler_rev", &obj->has_asl_compiler_rev)) {
        if (!visit_type_uint32(v, "asl_compiler_rev", &obj->asl_compiler_rev, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "file", &obj->has_file)) {
        if (!visit_type_str(v, "file", &obj->file, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "data", &obj->has_data)) {
        if (!visit_type_str(v, "data", &obj->data, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_AcpiTableOptions(Visitor *v, const char *name, AcpiTableOptions **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(AcpiTableOptions), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_AcpiTableOptions_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_AcpiTableOptions(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_CommandLineParameterType(Visitor *v, const char *name, CommandLineParameterType *obj, Error **errp)
{
    int value = *obj;
    bool ok = visit_type_enum(v, name, &value, &CommandLineParameterType_lookup, errp);
    *obj = value;
    return ok;
}

bool visit_type_CommandLineParameterInfo_members(Visitor *v, CommandLineParameterInfo *obj, Error **errp)
{
    if (!visit_type_str(v, "name", &obj->name, errp)) {
        return false;
    }
    if (!visit_type_CommandLineParameterType(v, "type", &obj->type, errp)) {
        return false;
    }
    if (visit_optional(v, "help", &obj->has_help)) {
        if (!visit_type_str(v, "help", &obj->help, errp)) {
            return false;
        }
    }
    if (visit_optional(v, "default", &obj->has_q_default)) {
        if (!visit_type_str(v, "default", &obj->q_default, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_CommandLineParameterInfo(Visitor *v, const char *name, CommandLineParameterInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(CommandLineParameterInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_CommandLineParameterInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_CommandLineParameterInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_CommandLineParameterInfoList(Visitor *v, const char *name, CommandLineParameterInfoList **obj, Error **errp)
{
    bool ok = false;
    CommandLineParameterInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (CommandLineParameterInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_CommandLineParameterInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_CommandLineParameterInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_CommandLineOptionInfo_members(Visitor *v, CommandLineOptionInfo *obj, Error **errp)
{
    if (!visit_type_str(v, "option", &obj->option, errp)) {
        return false;
    }
    if (!visit_type_CommandLineParameterInfoList(v, "parameters", &obj->parameters, errp)) {
        return false;
    }
    return true;
}

bool visit_type_CommandLineOptionInfo(Visitor *v, const char *name, CommandLineOptionInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(CommandLineOptionInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_CommandLineOptionInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_CommandLineOptionInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_query_command_line_options_arg_members(Visitor *v, q_obj_query_command_line_options_arg *obj, Error **errp)
{
    if (visit_optional(v, "option", &obj->has_option)) {
        if (!visit_type_str(v, "option", &obj->option, errp)) {
            return false;
        }
    }
    return true;
}

bool visit_type_CommandLineOptionInfoList(Visitor *v, const char *name, CommandLineOptionInfoList **obj, Error **errp)
{
    bool ok = false;
    CommandLineOptionInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (CommandLineOptionInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_CommandLineOptionInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_CommandLineOptionInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_PCDIMMDeviceInfo_members(Visitor *v, PCDIMMDeviceInfo *obj, Error **errp)
{
    if (visit_optional(v, "id", &obj->has_id)) {
        if (!visit_type_str(v, "id", &obj->id, errp)) {
            return false;
        }
    }
    if (!visit_type_int(v, "addr", &obj->addr, errp)) {
        return false;
    }
    if (!visit_type_int(v, "size", &obj->size, errp)) {
        return false;
    }
    if (!visit_type_int(v, "slot", &obj->slot, errp)) {
        return false;
    }
    if (!visit_type_int(v, "node", &obj->node, errp)) {
        return false;
    }
    if (!visit_type_str(v, "memdev", &obj->memdev, errp)) {
        return false;
    }
    if (!visit_type_bool(v, "hotplugged", &obj->hotplugged, errp)) {
        return false;
    }
    if (!visit_type_bool(v, "hotpluggable", &obj->hotpluggable, errp)) {
        return false;
    }
    return true;
}

bool visit_type_PCDIMMDeviceInfo(Visitor *v, const char *name, PCDIMMDeviceInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(PCDIMMDeviceInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_PCDIMMDeviceInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_PCDIMMDeviceInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_VirtioPMEMDeviceInfo_members(Visitor *v, VirtioPMEMDeviceInfo *obj, Error **errp)
{
    if (visit_optional(v, "id", &obj->has_id)) {
        if (!visit_type_str(v, "id", &obj->id, errp)) {
            return false;
        }
    }
    if (!visit_type_size(v, "memaddr", &obj->memaddr, errp)) {
        return false;
    }
    if (!visit_type_size(v, "size", &obj->size, errp)) {
        return false;
    }
    if (!visit_type_str(v, "memdev", &obj->memdev, errp)) {
        return false;
    }
    return true;
}

bool visit_type_VirtioPMEMDeviceInfo(Visitor *v, const char *name, VirtioPMEMDeviceInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(VirtioPMEMDeviceInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_VirtioPMEMDeviceInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_VirtioPMEMDeviceInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_VirtioMEMDeviceInfo_members(Visitor *v, VirtioMEMDeviceInfo *obj, Error **errp)
{
    if (visit_optional(v, "id", &obj->has_id)) {
        if (!visit_type_str(v, "id", &obj->id, errp)) {
            return false;
        }
    }
    if (!visit_type_size(v, "memaddr", &obj->memaddr, errp)) {
        return false;
    }
    if (!visit_type_size(v, "requested-size", &obj->requested_size, errp)) {
        return false;
    }
    if (!visit_type_size(v, "size", &obj->size, errp)) {
        return false;
    }
    if (!visit_type_size(v, "max-size", &obj->max_size, errp)) {
        return false;
    }
    if (!visit_type_size(v, "block-size", &obj->block_size, errp)) {
        return false;
    }
    if (!visit_type_int(v, "node", &obj->node, errp)) {
        return false;
    }
    if (!visit_type_str(v, "memdev", &obj->memdev, errp)) {
        return false;
    }
    return true;
}

bool visit_type_VirtioMEMDeviceInfo(Visitor *v, const char *name, VirtioMEMDeviceInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(VirtioMEMDeviceInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_VirtioMEMDeviceInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_VirtioMEMDeviceInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_PCDIMMDeviceInfo_wrapper_members(Visitor *v, q_obj_PCDIMMDeviceInfo_wrapper *obj, Error **errp)
{
    if (!visit_type_PCDIMMDeviceInfo(v, "data", &obj->data, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_VirtioPMEMDeviceInfo_wrapper_members(Visitor *v, q_obj_VirtioPMEMDeviceInfo_wrapper *obj, Error **errp)
{
    if (!visit_type_VirtioPMEMDeviceInfo(v, "data", &obj->data, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_VirtioMEMDeviceInfo_wrapper_members(Visitor *v, q_obj_VirtioMEMDeviceInfo_wrapper *obj, Error **errp)
{
    if (!visit_type_VirtioMEMDeviceInfo(v, "data", &obj->data, errp)) {
        return false;
    }
    return true;
}

bool visit_type_MemoryDeviceInfoKind(Visitor *v, const char *name, MemoryDeviceInfoKind *obj, Error **errp)
{
    int value = *obj;
    bool ok = visit_type_enum(v, name, &value, &MemoryDeviceInfoKind_lookup, errp);
    *obj = value;
    return ok;
}

bool visit_type_MemoryDeviceInfo_members(Visitor *v, MemoryDeviceInfo *obj, Error **errp)
{
    if (!visit_type_MemoryDeviceInfoKind(v, "type", &obj->type, errp)) {
        return false;
    }
    switch (obj->type) {
    case MEMORY_DEVICE_INFO_KIND_DIMM:
        return visit_type_q_obj_PCDIMMDeviceInfo_wrapper_members(v, &obj->u.dimm, errp);
    case MEMORY_DEVICE_INFO_KIND_NVDIMM:
        return visit_type_q_obj_PCDIMMDeviceInfo_wrapper_members(v, &obj->u.nvdimm, errp);
    case MEMORY_DEVICE_INFO_KIND_VIRTIO_PMEM:
        return visit_type_q_obj_VirtioPMEMDeviceInfo_wrapper_members(v, &obj->u.virtio_pmem, errp);
    case MEMORY_DEVICE_INFO_KIND_VIRTIO_MEM:
        return visit_type_q_obj_VirtioMEMDeviceInfo_wrapper_members(v, &obj->u.virtio_mem, errp);
    default:
        abort();
    }
    return true;
}

bool visit_type_MemoryDeviceInfo(Visitor *v, const char *name, MemoryDeviceInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(MemoryDeviceInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_MemoryDeviceInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_MemoryDeviceInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_MemoryDeviceInfoList(Visitor *v, const char *name, MemoryDeviceInfoList **obj, Error **errp)
{
    bool ok = false;
    MemoryDeviceInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (MemoryDeviceInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_MemoryDeviceInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_MemoryDeviceInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_MEMORY_DEVICE_SIZE_CHANGE_arg_members(Visitor *v, q_obj_MEMORY_DEVICE_SIZE_CHANGE_arg *obj, Error **errp)
{
    if (visit_optional(v, "id", &obj->has_id)) {
        if (!visit_type_str(v, "id", &obj->id, errp)) {
            return false;
        }
    }
    if (!visit_type_size(v, "size", &obj->size, errp)) {
        return false;
    }
    return true;
}

bool visit_type_q_obj_MEM_UNPLUG_ERROR_arg_members(Visitor *v, q_obj_MEM_UNPLUG_ERROR_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "device", &obj->device, errp)) {
        return false;
    }
    if (!visit_type_str(v, "msg", &obj->msg, errp)) {
        return false;
    }
    return true;
}

bool visit_type_ACPISlotType(Visitor *v, const char *name, ACPISlotType *obj, Error **errp)
{
    int value = *obj;
    bool ok = visit_type_enum(v, name, &value, &ACPISlotType_lookup, errp);
    *obj = value;
    return ok;
}

bool visit_type_ACPIOSTInfo_members(Visitor *v, ACPIOSTInfo *obj, Error **errp)
{
    if (visit_optional(v, "device", &obj->has_device)) {
        if (!visit_type_str(v, "device", &obj->device, errp)) {
            return false;
        }
    }
    if (!visit_type_str(v, "slot", &obj->slot, errp)) {
        return false;
    }
    if (!visit_type_ACPISlotType(v, "slot-type", &obj->slot_type, errp)) {
        return false;
    }
    if (!visit_type_int(v, "source", &obj->source, errp)) {
        return false;
    }
    if (!visit_type_int(v, "status", &obj->status, errp)) {
        return false;
    }
    return true;
}

bool visit_type_ACPIOSTInfo(Visitor *v, const char *name, ACPIOSTInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(ACPIOSTInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_ACPIOSTInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_ACPIOSTInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_ACPIOSTInfoList(Visitor *v, const char *name, ACPIOSTInfoList **obj, Error **errp)
{
    bool ok = false;
    ACPIOSTInfoList *tail;
    size_t size = sizeof(**obj);

    if (!visit_start_list(v, name, (GenericList **)obj, size, errp)) {
        return false;
    }

    for (tail = *obj; tail;
         tail = (ACPIOSTInfoList *)visit_next_list(v, (GenericList *)tail, size)) {
        if (!visit_type_ACPIOSTInfo(v, NULL, &tail->value, errp)) {
            goto out_obj;
        }
    }

    ok = visit_check_list(v, errp);
out_obj:
    visit_end_list(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_ACPIOSTInfoList(*obj);
        *obj = NULL;
    }
    return ok;
}

bool visit_type_q_obj_ACPI_DEVICE_OST_arg_members(Visitor *v, q_obj_ACPI_DEVICE_OST_arg *obj, Error **errp)
{
    if (!visit_type_ACPIOSTInfo(v, "info", &obj->info, errp)) {
        return false;
    }
    return true;
}

bool visit_type_ReplayMode(Visitor *v, const char *name, ReplayMode *obj, Error **errp)
{
    int value = *obj;
    bool ok = visit_type_enum(v, name, &value, &ReplayMode_lookup, errp);
    *obj = value;
    return ok;
}

bool visit_type_q_obj_xen_load_devices_state_arg_members(Visitor *v, q_obj_xen_load_devices_state_arg *obj, Error **errp)
{
    if (!visit_type_str(v, "filename", &obj->filename, errp)) {
        return false;
    }
    return true;
}

bool visit_type_GuidInfo_members(Visitor *v, GuidInfo *obj, Error **errp)
{
    if (!visit_type_str(v, "guid", &obj->guid, errp)) {
        return false;
    }
    return true;
}

bool visit_type_GuidInfo(Visitor *v, const char *name, GuidInfo **obj, Error **errp)
{
    bool ok = false;

    if (!visit_start_struct(v, name, (void **)obj, sizeof(GuidInfo), errp)) {
        return false;
    }
    if (!*obj) {
        /* incomplete */
        assert(visit_is_dealloc(v));
        ok = true;
        goto out_obj;
    }
    if (!visit_type_GuidInfo_members(v, *obj, errp)) {
        goto out_obj;
    }
    ok = visit_check_struct(v, errp);
out_obj:
    visit_end_struct(v, (void **)obj);
    if (!ok && visit_is_input(v)) {
        qapi_free_GuidInfo(*obj);
        *obj = NULL;
    }
    return ok;
}

/* Dummy declaration to prevent empty .o file */
char qapi_dummy_qapi_visit_misc_c;
