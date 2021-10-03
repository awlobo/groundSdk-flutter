package com.awlobo.parrot_flutter

import android.os.Bundle
import io.flutter.embedding.android.FlutterActivity

import com.parrot.drone.groundsdk.ManagedGroundSdk;
import com.parrot.drone.groundsdk.facility.AutoConnection;
import com.parrot.drone.groundsdk.device.Drone;
import com.parrot.drone.groundsdk.Ref;
import android.widget.Toast
import com.parrot.drone.groundsdk.device.DeviceState
import io.flutter.Log


class MainActivity: FlutterActivity() {

    private val TAG = "GroundSDK.Flutter"
    private lateinit var mGroundSdk: ManagedGroundSdk
    private lateinit var mAutoConnection: Ref<AutoConnection>
    private  var mDrone: Drone? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        Log.i(TAG, "--> STARTING APP")
        Toast.makeText(this, "START APP", Toast.LENGTH_LONG).show()
        mGroundSdk = ManagedGroundSdk.obtainSession(this)
        mAutoConnection = mGroundSdk.getFacility(
            AutoConnection::class.java
        ) { autoconnection: AutoConnection? ->
            assert(autoconnection != null)
            Log.i(
                TAG,
                "AUTO CONNECTION STATUS " + autoconnection!!.status.toString()
            )
            if (autoconnection.status != AutoConnection.Status.STARTED) {
                Toast.makeText(this, "START AUTOCONN", Toast.LENGTH_LONG).show()
                autoconnection.start()
            }
            mDrone = autoconnection.drone
            if (mDrone != null) {
                Toast.makeText(this, "YES DRONE", Toast.LENGTH_LONG).show()
                Log.w(TAG, "YES DRONE")
                mDrone?.getState(Ref.Observer { state: DeviceState? ->
                    assert(state != null)
                    Log.i(TAG, "DRONE CONNECTED")
                    Toast.makeText(this, "Drone Status: " + state.toString(), Toast.LENGTH_LONG)
                        .show()
                    // isConnected("Anafi")
                })
            } else {
                Toast.makeText(this, "NO DRONE", Toast.LENGTH_LONG).show()
                Log.w(TAG, "NO DRONE")
            }
        }

    }


}
