package edu.tamucc.project;

import java.util.Set;
import java.util.UUID;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

public class FindDeviceActivity extends Activity 
{
    // Return Intent extra
    public static String EXTRA_DEVICE_ADDRESS = "device_address";
   
    private BluetoothAdapter btAdapter = null;
	private ArrayAdapter<String> pairedDevicesAdapter;
    private ArrayAdapter<String> newDevicesAdapter;
    public UUID uuid;

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        // Request progress bar feature
        requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
        setContentView(R.layout.device_list);
        
        // Set result CANCELED in case the user backs out
        setResult(Activity.RESULT_CANCELED);
        
        Button refreshButton = (Button)findViewById(R.id.RefreshButton);
        refreshButton.setOnClickListener(refreshButtonListener);

        // Initialize array adapters for new devices and paired devices
        pairedDevicesAdapter = new ArrayAdapter<String>(this, R.layout.message_user_buttons, 
        		R.id.userAliasButton);
        newDevicesAdapter = new ArrayAdapter<String>(this, R.layout.message_user_buttons, 
        		R.id.userAliasButton);
       
        // Find and set up the ListView for paired devices
        ListView pairedListView = (ListView) findViewById(R.id.pairedDevicesListView);
        pairedListView.setAdapter(pairedDevicesAdapter);

        // Find and set up the ListView for newly discovered devices
        ListView newDevicesListView = (ListView) findViewById(R.id.newDevicesListView);
        newDevicesListView.setAdapter(newDevicesAdapter);
        
        // Register for broadcasts when a device is discovered
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        this.registerReceiver(receiver, filter);
        
        // Register for broadcasts when discovery has finished
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        this.registerReceiver(receiver, filter);
        
        // Get local Bluetooth adapter
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        
        // Get a set of currently paired devices
        Set<BluetoothDevice> pairedDevices = btAdapter.getBondedDevices();

        // If there are paired devices, add each one to the ArrayAdapter
        if (pairedDevices.size() > 0) 
        {
            for (BluetoothDevice device : pairedDevices) 
            {
            	pairedDevicesAdapter.add(device.getName() + "\n" + device.getAddress());
            }
        } 
    }
    
    @Override
    protected void onDestroy() 
    {
        super.onDestroy();

        // If still discovering, cancel
        if (btAdapter != null) 
        {
            btAdapter.cancelDiscovery();
        }

        // Unregister broadcast listeners
        this.unregisterReceiver(receiver);
    }
    
    public OnClickListener refreshButtonListener = new OnClickListener()
    {

		@Override
		public void onClick(View v) 
		{
			// TODO Auto-generated method stub
			discover();
			v.setVisibility(View.GONE);
		}
    	
    };
    
    public void myClickHandler(View v) 
    {
    	Button b = (Button) v;
    	String info = b.getText().toString();
    	String address = info.substring(info.length() - 17);
    	
    	// Create the result Intent and include the MAC address
        Intent intent = new Intent();
        intent.putExtra(EXTRA_DEVICE_ADDRESS, address);

        // Set result and finish this Activity
        setResult(Activity.RESULT_OK, intent);
        finish();
    }
    
    private void discover()
    {
    	// Indicate scanning in the title
        setProgressBarIndeterminateVisibility(true);
        setTitle(R.string.scanning);
        
        // If already discovering, cancel
        if (btAdapter.isDiscovering()) 
        {
        	btAdapter.cancelDiscovery();
        }

        btAdapter.startDiscovery();
    }
    

	private final BroadcastReceiver receiver = new BroadcastReceiver() 
	{
        @Override
        public void onReceive(Context context, Intent intent) 
        {
            String action = intent.getAction();

            // When discovery finds a device
            if (BluetoothDevice.ACTION_FOUND.equals(action)) 
            {
                // Get the BluetoothDevice object from the Intent
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                // If it's already paired, skip it, because it's been listed already
                if (device.getBondState() != BluetoothDevice.BOND_BONDED) 
                {
                    newDevicesAdapter.add(device.getName() + "\n" + device.getAddress());
                }
            // When discovery is finished, change the Activity title
            } 
            else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) 
            {
                setProgressBarIndeterminateVisibility(false);
                setTitle(R.string.select_device);
                if (newDevicesAdapter.getCount() == 0) 
                {
                    Toast.makeText(FindDeviceActivity.this, "no unpaired devices found", Toast.LENGTH_LONG).show();
                }
            }
        }
    };

}