package com.tank.megalania;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.support.annotation.MainThread;
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


    private OutputStream mOutputStream;
    private InputStream mInputStream;
    private BluetoothAdapter mBluetoothAdapter;
    BluetoothSocket socket;
    BluetoothDevice device = null;
    final String macAddress = "20:15:12:07:24:18";
    ArrayList<BluetoothDevice> pairedDeviceArrayList;
    boolean connected = false;
    byte[] received = new byte[128];


    //Enable emulated RS-232 serial port via Bluetooth
    public void connect() throws BluetoothConnectionException {

        // Assign the Bluetooth adapter to mBluetoothAdapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        //If Bluetooth adapter does not exists throw exception
        if (mBluetoothAdapter == null)
            throw new BluetoothConnectionException("Device does not support Bluetooth");

        // Check if Bluetooth is disabled
        if (!mBluetoothAdapter.isEnabled()) {
            throw new BluetoothConnectionException("Bluetooth is disabled");
        }

        new Thread(new Runnable() {
            @Override
            public void run(){
                //Device to connect with
                device = mBluetoothAdapter.getRemoteDevice(macAddress);
                if(connected)Log.e("Oxygen Bluetooth","already connected");


                try {
                    if(!connected) {
                        socket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
                        socket.connect();
                        Log.e("Oxygen Bluetooth", "connected");
                    }
                    mOutputStream = socket.getOutputStream();
                    connected = true;
                }catch (IOException e){
                    Log.e("Oxygen Bluetooth", "error" + e);
                }

                try {
                    if(connected)
                    {

                        while(true)
                        {
                            mInputStream = socket.getInputStream();
                            mInputStream.read(received, 0, received.length);
                            try {
                                ShowData(received);
                            }
                            catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                                Log.e("Oxygen Bluetooth", "exception: " + e);
                            }

                        }
                    }
                }
                catch (IOException e)
                {
                    Log.e("Oxygen Bluetooth", "Connection Lost" + e);
                    connected = false;

                }
            }}).start();
    }

    public void ShowData(byte[] message)throws BluetoothConnectionException, IOException{
        if (mOutputStream == null)
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
            pairedDeviceArrayList = new ArrayList<BluetoothDevice>();

            for (BluetoothDevice device : pairedDevices) {
                pairedDeviceArrayList.add(device);
            }


        }
        return pairedDeviceArrayList;

    }
}





