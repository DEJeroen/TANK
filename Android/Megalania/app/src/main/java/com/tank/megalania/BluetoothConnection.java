package com.tank.megalania;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.support.annotation.MainThread;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;
import android.util.Xml;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

/**
 * Created by DEJeroen on 2/26/16.
 */


public class BluetoothConnection {



    public static String heartRate = " ";
    private OutputStream mOutputStream;
    private InputStream mInputStream;
    private BluetoothAdapter mBluetoothAdapter;
    BluetoothSocket socket;
    BluetoothDevice device = null;
    final String macAddress = "20:15:12:07:24:18";



   // String kappa = "8";
    ArrayList<BluetoothDevice> pairedDeviceArrayList;
    boolean connected = false;
    static boolean globalConnected = false;
    byte[] received = new byte[128];
    private static Context context;
    //TextView ConnectedTextview = (TextView) findViewById(R.id.ConnectedTextview);
    public BluetoothConnection(Context c) {
        context = c;
    }
    public static void showToastMethod(String text) {
        Toast.makeText(context, text, Toast.LENGTH_SHORT).show();
    }


    //Enable emulated RS-232 serial port via Bluetooth
    public void connect() throws BluetoothConnectionException {


        // Assign the Bluetooth adapter to mBluetoothAdapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        device = mBluetoothAdapter.getRemoteDevice(macAddress);


        //If Bluetooth adapter does not exists throw exception
        if (mBluetoothAdapter == null)
            throw new BluetoothConnectionException("Device does not support Bluetooth");

        // Check if Bluetooth is disabled
        if (!mBluetoothAdapter.isEnabled()) {
            showToastMethod("Bluetooth is disabled");
            throw new BluetoothConnectionException("Bluetooth is disabled");

        }


        new Thread(new Runnable() {
            @Override
            public void run(){


                if(connected)
                    Log.e("Oxygen Bluetooth","already connected");


                try {
                    if(!connected) {
                        // ConnectedTextview.setTextColor(Color.RED);
                        //ConnectedTextview.setText("Not Connected");
                        socket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
                        socket.connect();
                        Log.e("Oxygen Bluetooth", "connected");
                    }

                    connected = true;
                    BluetoothConnection.globalConnected = true;

                    Intent intent = new Intent("com.tank.megalania");
                    intent.putExtra("result", "connected");
                    LocalBroadcastManager.getInstance(context).sendBroadcast(intent);

                }catch (IOException e){

                    Log.e("Oxygen Bluetooth", "error" + e);
                }


                try {
                    if(connected){

                        // ConnectedTextview.setTextColor(Color.GREEN);
                        while(true)
                        {
                            mOutputStream = socket.getOutputStream();
                            mInputStream = socket.getInputStream();
                            mInputStream.read(received, 0, received.length);
                            try {
                           //     mOutputStream.write(kappa.getBytes(), 0, kappa.length());
                                ShowData(received);

                                Intent intent = new Intent("com.tank.megalania");
                                intent.putExtra("result", received);
                                LocalBroadcastManager.getInstance(context).sendBroadcast(intent);

                                String textmessage = new String(received, "US-ASCII");
                                heartRate = textmessage.replace("\0", "");

                                //  Log.e("text aangekregen",heartRate);


                            }
                            catch (IOException | BluetoothConnectionException e) {
                                Log.e("Oxygen Bluetooth", "exception: " + e);
                            }

                        }
                    }
                }
                catch (IOException e)
                {
                    Log.e("Oxygen Bluetooth", "Connection Lost" + e);
                    connected = false;
                    BluetoothConnection.globalConnected = false;

                    Intent intent = new Intent("com.tank.megalania");
                    intent.putExtra("result", "false");
                    LocalBroadcastManager.getInstance(context).sendBroadcast(intent);

                }
            }}).start();
    }

    public void ShowData(byte[] message)throws BluetoothConnectionException, IOException{
        if (mInputStream == null)

            throw new BluetoothConnectionException("Socket not connected");
        String textmessage = new String(message, "US-ASCII");
        String sProper = textmessage.replace("\0", "");


        Log.v("Ontvangen", sProper);



    }

    public void send(byte[] data) throws BluetoothConnectionException, IOException {
        if (mOutputStream == null)
            throw new BluetoothConnectionException("Socket not connected");

        mOutputStream.write(data, 0, data.length);
    }


    //Define Bluetooth Exception
    public static class BluetoothConnectionException extends Exception {
        public BluetoothConnectionException(String message) {
            super(message);
        }
    }

    public ArrayList<BluetoothDevice> getDevices() throws BluetoothConnectionException {

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if (pairedDevices.size() > 0) {
            pairedDeviceArrayList = new ArrayList<>();

            for (BluetoothDevice device : pairedDevices) {
                pairedDeviceArrayList.add(device);
            }


        }
        return pairedDeviceArrayList;

    }

}