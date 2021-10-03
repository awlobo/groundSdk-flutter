
#pragma once

#include "Export.h"
#include "OpaqueHandle.h"
#include "dart_api_dl.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif




_GLUECODIUM_FFI_EXPORT bool library_com_generated_DroneStatusBridge_isConnected(FfiOpaqueHandle _self, int32_t _isolate_id);




_GLUECODIUM_FFI_EXPORT int32_t library_com_generated_DroneStatusBridge_favNumber_get(FfiOpaqueHandle _self, int32_t _isolate_id);



_GLUECODIUM_FFI_EXPORT void library_com_generated_DroneStatusBridge_favNumber_set__Int(FfiOpaqueHandle _self, int32_t _isolate_id, int32_t value);







_GLUECODIUM_FFI_EXPORT void library_com_generated_DroneStatusBridge_register_finalizer(
    FfiOpaqueHandle ffi_handle, int32_t isolate_id, Dart_Handle dart_handle);
_GLUECODIUM_FFI_EXPORT FfiOpaqueHandle library_com_generated_DroneStatusBridge_copy_handle(FfiOpaqueHandle handle);
_GLUECODIUM_FFI_EXPORT void library_com_generated_DroneStatusBridge_release_handle(FfiOpaqueHandle handle);





#ifdef __cplusplus
}
#endif
