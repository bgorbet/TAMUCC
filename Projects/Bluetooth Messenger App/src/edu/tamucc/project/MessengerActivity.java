package edu.tamucc.project;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import edu.tamucc.project.BluetoothService;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Base64;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.MeasureSpec;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.view.inputmethod.EditorInfo;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MessengerActivity extends Activity 
{
	// Message types sent from the BluetoothService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    public static final int IMAGE_READ = 6;
    
    // Indicates the first time the application is launched
    private static final String FIRST_LAUNCH = "isfirstLaunch";

    // Key names received from the BluetoothService Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";

    // Intent request codes
    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;

    // Layout Views
    private ListView messagesView;
    private EditText messageOutEditText;
    private Button sendButton;

    // Name of the connected device
    private String connectedDeviceName = null;
    // Array adapter for the message thread
    private ArrayAdapter<String> arrayAdapter;
    // String buffer for outgoing messages
    private StringBuffer messageOutStringBuffer;
    // Local Bluetooth adapter
    private BluetoothAdapter btAdapter = null;
    // Member object for the bluetooth services
    private BluetoothService btService = null;


    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        // Get local Bluetooth adapter
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        
        // If this is first launch, start welcome activity 
        if(isFirstLaunch())
        {
        	Intent welcomeIntent = new Intent(this, WelcomeActivity.class);
        	this.startActivity(welcomeIntent);
        }
        
        // Check that the device supports bluetooth
        if (btAdapter == null) 
        {
            Toast msg = Toast.makeText(this, "Device does not support Bluetooth", Toast.LENGTH_LONG);
            msg.setGravity(Gravity.CENTER, msg.getXOffset() / 2, msg.getYOffset() / 2);
			msg.show();
			this.finish();
        }
    }
    
    private Boolean isFirstLaunch()
	{
    	SharedPreferences prefs = getSharedPreferences("profile", MODE_PRIVATE);
		boolean isfirstLaunch = prefs.getBoolean(FIRST_LAUNCH, true);
		return isfirstLaunch;
	}

    @Override
    public void onStart() 
    {
        super.onStart();

        // If BT is not on, request that it be enabled.
        if (!btAdapter.isEnabled()) 
        {
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
        // Otherwise, setup the session
        } 
        else 
        {
            if (btService == null) 
            	setup();
        }
    }

    @Override
    public synchronized void onResume() 
    {
        super.onResume();

        // This check covers the case in which BT was not enabled
        // during onStart()
        if (btService != null) 
        {
            // If the state is STATE_NONE, then bluetooth service hasn't started
            if (btService.getState() == BluetoothService.STATE_NONE) 
            {
              // Start the Bluetooth services
              btService.start();
            }
        }
    }

    private void setup() 
    {

        // Initialize the array adapter for the message thread
        arrayAdapter = new ArrayAdapter<String>(this, R.layout.single_message);
        messagesView = (ListView) findViewById(R.id.messagesListView);
        messagesView.setAdapter(arrayAdapter);

        // Initialize the message out field with a listener for the return key
        messageOutEditText = (EditText) findViewById(R.id.sendMessageEditText);
        messageOutEditText.setOnEditorActionListener(writeListener);

        // Initialize the send button with a listener for click events
        sendButton = (Button) findViewById(R.id.sendButton);
        sendButton.setOnClickListener(new OnClickListener() 
        {
            public void onClick(View v) 
            {
                // Send a message using content of the edit text 
                TextView view = (TextView) findViewById(R.id.sendMessageEditText);
                String message = view.getText().toString();
                sendMessage(message);
            }
        });

        // Initialize the BluetoothService to perform connections
        btService = new BluetoothService(this, handler);
        btService.start();

        // Initialize the buffer for outgoing messages
        messageOutStringBuffer = new StringBuffer("");
    }

    @Override
    public synchronized void onPause() 
    {
        super.onPause();
    }

    @Override
    public void onStop() 
    {
        super.onStop();
    }

    @Override
    public void onDestroy() 
    {
        super.onDestroy();
        // Stop the Bluetooth services
        if (btService != null) btService.stop();
    }


    private void sendMessage(String message) 
    {
        // Check connection first
        if (btService.getState() != BluetoothService.STATE_CONNECTED) 
        {
            Toast.makeText(this, "Not connected.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Check that there's actually something to send and that it's not too long
        if (message.length() > 0 && message.length() < 300) 
        {
            // Get the message bytes and tell the BluetoothService to write
            byte[] send = message.getBytes();
            btService.write(send);

            // Reset out string buffer to zero and clear the edit text field
            messageOutStringBuffer.setLength(0);
            messageOutEditText.setText(messageOutStringBuffer);
        }
    }
    
    
    private void ensureDiscoverable() 
    {
        if (btAdapter.getScanMode() !=
            BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE) 
        {
            Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
            discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
            startActivity(discoverableIntent);
        }
    }

    // The action listener for the message out EditText, to listen for the return key
    private TextView.OnEditorActionListener writeListener =
        new TextView.OnEditorActionListener() 
    {
        public boolean onEditorAction(TextView view, int actionId, KeyEvent event) 
        {
            // If the action is a key-up event on the return key, send the message
            if (actionId == EditorInfo.IME_NULL && event.getAction() == KeyEvent.ACTION_UP) 
            {
                String message = view.getText().toString();
                sendMessage(message);
            }
            return true;
        }
    };

    // The Handler that gets information back from the BluetoothService
    private final Handler handler = new Handler() 
    {
        @Override
        public void handleMessage(Message msg) 
        {
            switch (msg.what) 
            {
            case MESSAGE_STATE_CHANGE:
                if (msg.arg1 == BluetoothService.STATE_CONNECTED) 
                {
                	// clear old messages when a new connection is made
                    arrayAdapter.clear();
                }
                break;
            case MESSAGE_WRITE:
                byte[] writeBuf = (byte[]) msg.obj;
                // construct a string from the buffer
                String writeMessage = new String(writeBuf);
                // if the message is very long, it is an image (send profile action)
                if(writeMessage.length()>500)
                	arrayAdapter.add("Profile Sent");
                else
                	arrayAdapter.add("Me:  " + writeMessage);
                break;
            case MESSAGE_READ:
            	String readBuf = (String) msg.obj;
            	// decode the message
            	byte[] b = Base64.decode(readBuf, Base64.DEFAULT);
            	// Try to construct an image
            	Bitmap image = BitmapFactory.decodeByteArray(b, 0, msg.arg1);
            	// If the message was an image, display it in custom alert dialog
                if(image != null)
                {
                	AlertDialog.Builder builder;
                	AlertDialog alertDialog;

                	//Context mContext = getApplicationContext();
                	LayoutInflater inflater = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);
                	View layout = inflater.inflate(R.layout.view_image, null);

                	ImageView imageView = (ImageView) layout.findViewById(R.id.view_imageImageView);
                	imageView.setImageBitmap(image);

                	builder = new AlertDialog.Builder(MessengerActivity.this);
                	builder.setView(layout);
                	alertDialog = builder.create();
                	alertDialog.show();
                }
                else
                {
                // If the image was null, construct a string from the valid bytes in the buffer
                String readMessage = new String(b, 0, msg.arg1);
                arrayAdapter.add(connectedDeviceName+":  " + readMessage);
                }
                break;
            case MESSAGE_DEVICE_NAME:
                // Save the connected device's name
                connectedDeviceName = msg.getData().getString(DEVICE_NAME);
                Toast.makeText(getApplicationContext(), "Connected to "
                               + connectedDeviceName, Toast.LENGTH_SHORT).show();
                break;
            case MESSAGE_TOAST:
            	// If connection was lost or failed
                Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                               Toast.LENGTH_SHORT).show();
                break;
            }
        }
    };
    
    public void onActivityResult(int requestCode, int resultCode, Intent data) 
    {
        switch (requestCode) 
        {
        case REQUEST_CONNECT_DEVICE:
            // When FindDeviceActivity returns with a device to connect
            if (resultCode == Activity.RESULT_OK) 
            {
                // Get the device MAC address
                String address = data.getExtras()
                                     .getString(FindDeviceActivity.EXTRA_DEVICE_ADDRESS);
                // Get the BLuetoothDevice object
                BluetoothDevice device = btAdapter.getRemoteDevice(address);
                // Attempt to connect to the device
                btService.connect(device);
            }
            break;
        case REQUEST_ENABLE_BT:
            // When the request to enable Bluetooth returns
            if (resultCode == Activity.RESULT_OK) 
            {
                // Bluetooth is now enabled, so set up a session
                setup();
            } 
            else 
            {
                // User did not enable Bluetooth or an error occured
                Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_LONG).show();
                finish();
            }
        }
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.option_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) 
    {
        switch (item.getItemId()) 
        {
        case R.id.scan:
            // Launch the FindDeviceActivity to see devices and do scan
            Intent serverIntent = new Intent(this, FindDeviceActivity.class);
            startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
            return true;
        case R.id.discoverable:
            // Ensure this device is discoverable by others
            ensureDiscoverable();
            return true;
        case R.id.view_my_profile:
        	// Launch the ViewMyProfile Activity
        	Intent intentObj = new Intent(this, ViewMyProfileActivity.class);
        	startActivity(intentObj);
        	return true;
        case R.id.send_my_profile:
        	// Get the profile from shared preferences
        	SharedPreferences prefs = getSharedPreferences("profile", MODE_PRIVATE);
        	String imagePath = prefs.getString("image_path", ""); //get image
        	File imageFile = new File(imagePath);
        	Bitmap image = decodeFile(imageFile); //reduce image size

        	// Inflate the profile GUI
        	Context mContext = MessengerActivity.this;
        	View layout = ((LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE)).inflate(R.layout.profile, null);
        	
        	// Set the TextView and ImageView to the username and profile picture
        	TextView usernameTextView = (TextView)layout.findViewById(R.id.profileTextView);
        	usernameTextView.setText(prefs.getString("username", ""));
        	ImageView profileImageView = (ImageView)layout.findViewById(R.id.profileImageView);
        	profileImageView.setImageBitmap(image);
        	
        	// Set layout parameters, get display metrics, get measure specs, and assign a size to the GUI
        	layout.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
        	DisplayMetrics displayMetrics = new DisplayMetrics();
            ((Activity)mContext).getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
            layout.measure((MeasureSpec.makeMeasureSpec(displayMetrics.widthPixels, MeasureSpec.AT_MOST)), 
            		 (MeasureSpec.makeMeasureSpec(displayMetrics.heightPixels, MeasureSpec.AT_MOST)));
            layout.layout(0, 0, displayMetrics.widthPixels, displayMetrics.heightPixels);

            // Create a new bitmap and draw the layout to it using a canvas object
            Bitmap returnedBitmap = Bitmap.createBitmap(layout.getMeasuredWidth(), layout.getMeasuredHeight(), Bitmap.Config.ARGB_8888);
            Canvas canvas = new Canvas(returnedBitmap);
            layout.draw(canvas);
        	
			// Convert bitmap to byte array
			ByteArrayOutputStream stream = new ByteArrayOutputStream();
			returnedBitmap.compress(Bitmap.CompressFormat.PNG, 100, stream);
			byte[] byteArray = stream.toByteArray();
			
			// If connected, send the image
			if (btService.getState() != BluetoothService.STATE_CONNECTED) 
	        {
	            Toast.makeText(this, "Not connected.", Toast.LENGTH_SHORT).show();
	        }
			else
			{
				btService.write(byteArray);
			}
			return true;
        case R.id.close_application:
        	Intent intent = new Intent(Intent.ACTION_MAIN);
        	intent.addCategory(Intent.CATEGORY_HOME);
        	intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        	startActivity(intent);
        	return true;
        case R.id.close_connection:
        	btService.stop();
        	return true;
        }
        return false;
    }
    
    // This scales down an image to reduce memory cost
    private Bitmap decodeFile(File f)
	{
	    try 
	    {
	        //Decode image size
	        BitmapFactory.Options o = new BitmapFactory.Options();
	        o.inJustDecodeBounds = true;
	        BitmapFactory.decodeStream(new FileInputStream(f),null,o);

	        //The new size to scale to
	        final int REQUIRED_SIZE=100;

	        //Find the correct scale value
	        int scale=1;
	        while(o.outWidth/scale/2>=REQUIRED_SIZE && o.outHeight/scale/2>=REQUIRED_SIZE)
	            scale*=2;

	        //Decode with inSampleSize
	        BitmapFactory.Options o2 = new BitmapFactory.Options();
	        o2.inSampleSize=scale;
	        return BitmapFactory.decodeStream(new FileInputStream(f), null, o2);
	    } 
	    catch (FileNotFoundException e) {}
	    return null;
	}

}