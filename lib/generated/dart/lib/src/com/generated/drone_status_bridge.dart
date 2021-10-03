

import 'dart:ffi';
import 'package:library/src/_library_context.dart' as __lib;
import 'package:library/src/_native_base.dart' as __lib;
import 'package:library/src/_token_cache.dart' as __lib;
import 'package:library/src/builtin_types__conversion.dart';

abstract class DroneStatusBridge {

  /// @nodoc
  @Deprecated("Does nothing")
  void release();


  bool isConnected();
  int get favNumber;
  set favNumber(int value);

}


// DroneStatusBridge "private" section, not exported.

final _comGeneratedDronestatusbridgeRegisterFinalizer = __lib.catchArgumentError(() => __lib.nativeLibrary.lookupFunction<
    Void Function(Pointer<Void>, Int32, Handle),
    void Function(Pointer<Void>, int, Object)
  >('library_com_generated_DroneStatusBridge_register_finalizer'));
final _comGeneratedDronestatusbridgeCopyHandle = __lib.catchArgumentError(() => __lib.nativeLibrary.lookupFunction<
    Pointer<Void> Function(Pointer<Void>),
    Pointer<Void> Function(Pointer<Void>)
  >('library_com_generated_DroneStatusBridge_copy_handle'));
final _comGeneratedDronestatusbridgeReleaseHandle = __lib.catchArgumentError(() => __lib.nativeLibrary.lookupFunction<
    Void Function(Pointer<Void>),
    void Function(Pointer<Void>)
  >('library_com_generated_DroneStatusBridge_release_handle'));



class DroneStatusBridge$Impl extends __lib.NativeBase implements DroneStatusBridge {

  DroneStatusBridge$Impl(Pointer<Void> handle) : super(handle);

  @override
  void release() {}

  @override
  bool isConnected() {
    final _isConnectedFfi = __lib.catchArgumentError(() => __lib.nativeLibrary.lookupFunction<Uint8 Function(Pointer<Void>, Int32), int Function(Pointer<Void>, int)>('library_com_generated_DroneStatusBridge_isConnected'));
    final _handle = this.handle;
    final __resultHandle = _isConnectedFfi(_handle, __lib.LibraryContext.isolateId);
    try {
      return booleanFromFfi(__resultHandle);
    } finally {
      booleanReleaseFfiHandle(__resultHandle);

    }

  }

  @override
  int get favNumber {
    final _getFfi = __lib.catchArgumentError(() => __lib.nativeLibrary.lookupFunction<Int32 Function(Pointer<Void>, Int32), int Function(Pointer<Void>, int)>('library_com_generated_DroneStatusBridge_favNumber_get'));
    final _handle = this.handle;
    final __resultHandle = _getFfi(_handle, __lib.LibraryContext.isolateId);
    try {
      return (__resultHandle);
    } finally {


    }

  }

  @override
  set favNumber(int value) {
    final _setFfi = __lib.catchArgumentError(() => __lib.nativeLibrary.lookupFunction<Void Function(Pointer<Void>, Int32, Int32), void Function(Pointer<Void>, int, int)>('library_com_generated_DroneStatusBridge_favNumber_set__Int'));
    final _valueHandle = (value);
    final _handle = this.handle;
    _setFfi(_handle, __lib.LibraryContext.isolateId, _valueHandle);


  }



}

Pointer<Void> comGeneratedDronestatusbridgeToFfi(DroneStatusBridge value) =>
  _comGeneratedDronestatusbridgeCopyHandle((value as __lib.NativeBase).handle);

DroneStatusBridge comGeneratedDronestatusbridgeFromFfi(Pointer<Void> handle) {
  final instance = __lib.getCachedInstance(handle);
  if (instance != null && instance is DroneStatusBridge) return instance;

  final _copiedHandle = _comGeneratedDronestatusbridgeCopyHandle(handle);
  final result = DroneStatusBridge$Impl(_copiedHandle);
  __lib.cacheInstance(_copiedHandle, result);
  _comGeneratedDronestatusbridgeRegisterFinalizer(_copiedHandle, __lib.LibraryContext.isolateId, result);
  return result;
}

void comGeneratedDronestatusbridgeReleaseFfiHandle(Pointer<Void> handle) =>
  _comGeneratedDronestatusbridgeReleaseHandle(handle);

Pointer<Void> comGeneratedDronestatusbridgeToFfiNullable(DroneStatusBridge? value) =>
  value != null ? comGeneratedDronestatusbridgeToFfi(value) : Pointer<Void>.fromAddress(0);

DroneStatusBridge? comGeneratedDronestatusbridgeFromFfiNullable(Pointer<Void> handle) =>
  handle.address != 0 ? comGeneratedDronestatusbridgeFromFfi(handle) : null;

void comGeneratedDronestatusbridgeReleaseFfiHandleNullable(Pointer<Void> handle) =>
  _comGeneratedDronestatusbridgeReleaseHandle(handle);

// End of DroneStatusBridge "private" section.

