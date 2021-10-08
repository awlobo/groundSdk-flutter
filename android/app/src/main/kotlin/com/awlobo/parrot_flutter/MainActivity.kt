package com.awlobo.parrot_flutter

import android.os.Bundle
import android.util.Log
import com.parrot.drone.groundsdk.GroundSdk
import com.parrot.drone.groundsdk.ManagedGroundSdk
import com.parrot.drone.groundsdk.Ref
import com.parrot.drone.groundsdk.device.DeviceState
import com.parrot.drone.groundsdk.device.Drone
import com.parrot.drone.groundsdk.facility.AutoConnection
import io.flutter.embedding.android.FlutterActivity
import io.flutter.plugin.common.BinaryMessenger
import io.flutter.plugin.common.MethodChannel


class MainActivity : FlutterActivity() {

    companion object {
        const val CHANNEL = "com.awlobo.communication.channel"
        const val TAG = "GroundSDK.Flutter"
        const val DRONE_STATUS = "droneStatus";
    }

    private fun getFlutterView(): BinaryMessenger = flutterEngine!!.dartExecutor.binaryMessenger

    private lateinit var mGroundSdk: GroundSdk
    private lateinit var mAutoConnection: Ref<AutoConnection>
    private var mDrone: Drone? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val channel = MethodChannel(getFlutterView(), CHANNEL)

        mGroundSdk = ManagedGroundSdk.obtainSession(this)

        mAutoConnection =
            mGroundSdk.getFacility(AutoConnection::class.java) { autoConnection: AutoConnection? ->
                assert(autoConnection != null)
                Log.e(
                    TAG,
                    "AUTO CONNECTION STATUS " + autoConnection!!.status.toString()
                )
                channel.invokeMethod("droneStatus", autoConnection.status.toString())
                if (autoConnection.status != AutoConnection.Status.STARTED) {
                    autoConnection.start()
                    channel.invokeMethod(DRONE_STATUS, "Connecting")
                }
                mDrone = autoConnection.drone
                if (mDrone != null) {
                    channel.invokeMethod(DRONE_STATUS, "Drone detected")
                    mDrone?.getState { state: DeviceState? ->
                        assert(state != null)
                        //channel.invokeMethod(DRONE_STATUS, "Drone IS connected")
                        channel.invokeMethod("droneStatus", state.toString())
                        Log.e(TAG, "YES DRONE CONNECTED")
                    }
                } else {
                    channel.invokeMethod(DRONE_STATUS, "NO DRONE")
                    Log.e(TAG, "NO DRONE")
                }
            }
    }
}
