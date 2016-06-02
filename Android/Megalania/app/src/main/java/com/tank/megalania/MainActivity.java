package com.tank.megalania;

import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class MainActivity extends AppCompatActivity {

    private final static int REQUEST_ENABLE_BT = 1;
    BluetoothConnection btcon = new BluetoothConnection(this);


    Button buttonForward;
    Button btnLeft;
    Button buttonStop;
    Button btnRight;
    Button buttonBackwards;
    Button connectButton;
    Button buttonAutomatic;
    Button buttonManual;

    TextView textViewforward1;
    TextView textViewforward2;
    TextView textViewLeft;
    TextView textViewRight;
    boolean automaticDrive = true;


    String first;
    String second;
    String third;
    String fourth;


    private SeekBar leftControl = null;
    String  leftspeed = "0";

    private SeekBar rightControl = null;
    String  rightspeed = "0";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BroadcastReceiver resultReceiver;
        resultReceiver = createBroadcastReceiver();
        LocalBroadcastManager.getInstance(this).registerReceiver(resultReceiver, new IntentFilter("com.tank.megalania"));

        buttonForward = (Button) findViewById(R.id.buttonForward);
        btnLeft = (Button) findViewById(R.id.btnLeft);
        buttonStop = (Button) findViewById(R.id.buttonStop);
        btnRight = (Button) findViewById(R.id.btnRight);
        buttonBackwards = (Button) findViewById(R.id.buttonBackwards);
        connectButton = (Button) findViewById(R.id.connectButton);
        buttonAutomatic = (Button) findViewById(R.id.buttonAutomatic);
        buttonManual = (Button) findViewById(R.id.buttonManual);

        textViewforward1 = (TextView) findViewById(R.id.textViewforward1);
        textViewforward2 = (TextView) findViewById(R.id.textViewforward2);
        textViewLeft = (TextView) findViewById(R.id.textViewleft);
        textViewRight = (TextView) findViewById(R.id.textViewRight);


        leftControl = (SeekBar) findViewById(R.id.seekBarLeft);
        leftControl.setMax(510);
        leftControl.setProgress(256);
        rightControl = (SeekBar) findViewById(R.id.seekBarRight);
        rightControl.setMax(510);
        rightControl.setProgress(256);



        buttonForward.setVisibility(View.GONE);
        btnLeft.setVisibility(View.GONE);
        buttonStop.setVisibility(View.GONE);
        btnRight.setVisibility(View.GONE);
        buttonBackwards.setVisibility(View.GONE);
        buttonAutomatic.setVisibility(View.GONE);
        buttonManual.setVisibility(View.GONE);
        leftControl.setVisibility(View.GONE);
        rightControl.setVisibility(View.GONE);








        rightControl.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener(){
            int progressChanged = 0;
            public void onProgressChanged(SeekBar seekBarLeft, int progress, boolean fromUser) {
                progressChanged = progress;
                leftspeed = Integer.toString(progressChanged);
                try {
                    btcon.send("r".getBytes());
                    btcon.send(leftspeed.getBytes());
                    btcon.send(",".getBytes());
                    btcon.send(leftspeed.getBytes());
                    btcon.send(",".getBytes());


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


        leftControl.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChanged = 0;

            public void onProgressChanged(SeekBar seekBarLeft, int progress, boolean fromUser) {
                progressChanged = progress;
                leftspeed = Integer.toString(progressChanged);
                try {
                    btcon.send("r".getBytes());
                    btcon.send(leftspeed.getBytes());
                    btcon.send(",".getBytes());
                    btcon.send(leftspeed.getBytes());
                    btcon.send(",".getBytes());


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

    public void onManualClick(View view){
        try {
            btcon.send("m".toString().getBytes());
            buttonManual.setVisibility(View.GONE);
            buttonAutomatic.setVisibility(View.VISIBLE);
            automaticDrive = false;


            buttonForward.setVisibility(View.VISIBLE);
            btnLeft.setVisibility(View.VISIBLE);
            buttonStop.setVisibility(View.VISIBLE);
            btnRight.setVisibility(View.VISIBLE);
            buttonBackwards.setVisibility(View.VISIBLE);
            leftControl.setVisibility(View.VISIBLE);
            rightControl.setVisibility(View.VISIBLE);


        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }

    public void onAutomaticClick(View view){
        try {
            btcon.send("a".toString().getBytes());
            buttonManual.setVisibility(View.VISIBLE);
            buttonAutomatic.setVisibility(View.GONE);
            automaticDrive = true;


            buttonForward.setVisibility(View.GONE);
            btnLeft.setVisibility(View.GONE);
            buttonStop.setVisibility(View.GONE);
            btnRight.setVisibility(View.GONE);
            buttonBackwards.setVisibility(View.GONE);
            leftControl.setVisibility(View.GONE);
            rightControl.setVisibility(View.GONE);


        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }

    public void onLeftClick(View view){
        try {
            btcon.send("510,255,".toString().getBytes());

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onRightClick(View view){
        try {

            btcon.send("255,510,".toString().getBytes());

        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onForwardClick(View view){
        try {
            btcon.send("510,510,".toString().getBytes());


        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onBackwardClick(View view) {
        try {
            btcon.send("255,255,".toString().getBytes());


        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
    public void onStopClick(View view){
        try {
            btcon.send("256,256,".toString().getBytes());


        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }


    protected void onActivityResult(int requestCode, int resultCode,
                                    Intent data) {
        Context context = getApplicationContext();

        //Respond to the user allowing or denying the enable request
        if (requestCode == REQUEST_ENABLE_BT) {
            if (resultCode == RESULT_OK) {
                Toast.makeText(context, "Enabled Bluetooth and will try to connect",
                        Toast.LENGTH_LONG).show();

                try {
                    btcon.connect();
                } catch (BluetoothConnection.BluetoothConnectionException e) {

                    //write BluetoothConnectionException to log
                    Log.e("Oxygen Bluetooth", "exception: " + e);
                }

            }
            else {
                Toast.makeText(context, "Cannot connect without Bluetooth",
                        Toast.LENGTH_LONG).show();
            }
        }
    }

    private BroadcastReceiver createBroadcastReceiver() {
        return new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                updateResults(BluetoothConnection.heartRate);


            }
        };
    }

    private void updateResults(String test) {


        StringTokenizer tokens = new StringTokenizer(test, ",");
        first = tokens.nextToken();
        textViewforward1.setText(first);
        if(tokens.hasMoreElements())
            second = tokens.nextToken();

        if (tokens.hasMoreElements())
        third = tokens.nextToken();
        if (tokens.hasMoreElements())
        fourth = tokens.nextToken();



        textViewforward2.setText(second);
        textViewLeft.setText(third);
        textViewRight.setText(fourth);
        Log.e("second deel late zien" , "sec");
      //  saveData(second);

        if (BluetoothConnection.globalConnected) {
            connectButton.setVisibility(View.GONE);


            if (automaticDrive == false) {
                buttonForward.setVisibility(View.VISIBLE);
                btnLeft.setVisibility(View.VISIBLE);
                buttonStop.setVisibility(View.VISIBLE);
                btnRight.setVisibility(View.VISIBLE);
                buttonBackwards.setVisibility(View.VISIBLE);
            }

            if (automaticDrive == true)
            buttonManual.setVisibility(View.VISIBLE);





            // saveData();

        }
        else {
            connectButton.setVisibility(View.VISIBLE);




        }

    }
}
