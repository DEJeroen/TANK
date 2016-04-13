package com.tank.megalania;

import android.bluetooth.BluetoothDevice;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private final static int REQUEST_ENABLE_BT = 1;
    BluetoothConnection btcon = new BluetoothConnection();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void onConnectClick(View view){
        Log.e("Oxygen Bluetooth", "Trying to connect ");


        try {
            ArrayList<BluetoothDevice> pairedDeviceArrayList;
            if(btcon!=null){

                pairedDeviceArrayList = btcon.getDevices();
            }
            //   pairedDeviceArrayList = btcon.getDevices();
            //  mac = btcon.getDevices().get(1).getAddress() ;
            btcon.connect();

        } catch (Exception ex) {
            Log.e("Oxygen Bluetooth", "exception: " + ex);

            //write BluetoothConnectionException to log
            //  Log.e("Oxygen Bluetooth", "exception: " + e);

            //if bluetooth is disabled ask the user to enable it
            //   if (e.getMessage() == "Bluetooth is disabled"){
            //      Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            //      startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
        // }
    }

    public void onLeftClick(View view){
        try {
            btcon.send("L".toString().getBytes());
            btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onRightClick(View view){
        try {
            btcon.send("R".toString().getBytes());
            btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onForwardClick(View view){
        try {
            btcon.send("F".toString().getBytes());
            btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onBackwardClick(View view){
        try {
            btcon.send("B".toString().getBytes());
            btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
}
