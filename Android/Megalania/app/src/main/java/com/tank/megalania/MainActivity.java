package com.tank.megalania;

import android.bluetooth.BluetoothDevice;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private final static int REQUEST_ENABLE_BT = 1;
    BluetoothConnection btcon = new BluetoothConnection();




    private SeekBar volumeControl = null;
    String  leftspeed = "255";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        volumeControl = (SeekBar) findViewById(R.id.seekBarLeft);
        volumeControl.setMax(510);
        volumeControl.setProgress(255);

        volumeControl.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChanged = 0;

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                leftspeed = Integer.toString(progressChanged);
                try {
                    btcon.send(leftspeed.getBytes());
                    btcon.send(",".getBytes());
                    btcon.send(leftspeed.getBytes());
                    btcon.send("r".getBytes());

                    //btcon.send("255".toString().getBytes());
                    //mOutputView.setText("");

                } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                    Log.e("Oxygen Bluetooth", "exception: " + e);
                }
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                Toast.makeText(MainActivity.this, "seek bar progress:" + progressChanged,
                        Toast.LENGTH_SHORT).show();
            }
        });
    }


    public void onConnectClick(View view){


        Log.e("Oxygen Bluetooth", "Trying to connect ");



        try {
            ArrayList<BluetoothDevice> pairedDeviceArrayList;
            if(btcon!=null){

                pairedDeviceArrayList = btcon.getDevices();
            }
               pairedDeviceArrayList = btcon.getDevices();
              btcon.getDevices().get(1).getAddress() ;
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
            btcon.send("510,0r".toString().getBytes());

            //btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onRightClick(View view){
        try {

            btcon.send("0,510r".toString().getBytes());
            //btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onForwardClick(View view){
        try {
            btcon.send("510,510r".toString().getBytes());

            //btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onBackwardClick(View view) {
        try {
            btcon.send("0,0r".toString().getBytes());

            //btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onStopClick(View view){
        try {
            btcon.send("256,256r".toString().getBytes());
            //btcon.send("255".toString().getBytes());
            //mOutputView.setText("");

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
}
