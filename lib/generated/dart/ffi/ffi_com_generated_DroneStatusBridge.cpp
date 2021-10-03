
#include "ffi_com_generated_DroneStatusBridge.h"

#include "ConversionBase.h"
#include "InstanceCache.h"
#include "FinalizerData.h"
#include "IsolateContext.h"
#include "com/generated/DroneStatusBridge.h"
#include <cstdint>
#include <memory>
#include <memory>
#include <new>


#ifdef __cplusplus
extern "C" {
#endif




bool
library_com_generated_DroneStatusBridge_isConnected(FfiOpaqueHandle _self, int32_t _isolate_id) {
    ffi::IsolateContext _isolate_context(_isolate_id);
    return ffi::Conversion<bool>::toFfi(
        (*ffi::Conversion<std::shared_ptr<com::generated::DroneStatusBridge>>::toCpp(_self)).is_connected()
    );
}




int32_t
library_com_generated_DroneStatusBridge_favNumber_get(FfiOpaqueHandle _self, int32_t _isolate_id) {
    ffi::IsolateContext _isolate_context(_isolate_id);
    return ffi::Conversion<int32_t>::toFfi(
        (*ffi::Conversion<std::shared_ptr<com::generated::DroneStatusBridge>>::toCpp(_self)).get_fav_number()
    );
}



void
library_com_generated_DroneStatusBridge_favNumber_set__Int(FfiOpaqueHandle _self, int32_t _isolate_id, int32_t value) {
    ffi::IsolateContext _isolate_context(_isolate_id);
            (*ffi::Conversion<std::shared_ptr<com::generated::DroneStatusBridge>>::toCpp(_self)).set_fav_number(
            ffi::Conversion<int32_t>::toCpp(value)
        );
}







// "Private" finalizer, not exposed to be callable from Dart.
void
library_com_generated_DroneStatusBridge_finalizer(FfiOpaqueHandle handle, int32_t isolate_id) {
    auto ptr_ptr = reinterpret_cast<std::shared_ptr<com::generated::DroneStatusBridge>*>(handle);
    library_uncache_dart_handle_by_raw_pointer(ptr_ptr->get(), isolate_id);
    library_com_generated_DroneStatusBridge_release_handle(handle);
}

void
library_com_generated_DroneStatusBridge_register_finalizer(FfiOpaqueHandle ffi_handle, int32_t isolate_id, Dart_Handle dart_handle) {
    FinalizerData* data = new (std::nothrow) FinalizerData{ffi_handle, isolate_id, &library_com_generated_DroneStatusBridge_finalizer};
    Dart_NewFinalizableHandle_DL(dart_handle, data, sizeof data, &library_execute_finalizer);
}

FfiOpaqueHandle
library_com_generated_DroneStatusBridge_copy_handle(FfiOpaqueHandle handle) {
    return reinterpret_cast<FfiOpaqueHandle>(
        new (std::nothrow) std::shared_ptr<com::generated::DroneStatusBridge>(
            *reinterpret_cast<std::shared_ptr<com::generated::DroneStatusBridge>*>(handle)
        )
    );
}

void
library_com_generated_DroneStatusBridge_release_handle(FfiOpaqueHandle handle) {
    delete reinterpret_cast<std::shared_ptr<com::generated::DroneStatusBridge>*>(handle);
}






#ifdef __cplusplus
}
#endif
