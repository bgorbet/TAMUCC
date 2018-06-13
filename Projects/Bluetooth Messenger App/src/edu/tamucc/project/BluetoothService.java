package edu.tamucc.project;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Base64;

public class BluetoothService 
{
    final String NAME = "BluetoothMessenger";

    // Unique UUID for this application
    final UUID MY_UUID = UUID.fromString("9421cb50-d0bb-11e1-9b23-0800200c9a66");

    // Member fields
    private final BluetoothAdapter btAdapter;
    private final Handler handler;
    private AcceptThread acceptThread;
    private ConnectThread connectThread;
    private ConnectedThread connectedThread;
    private int state;

    // Constants that indicate the current connection state
    public static final int STATE_NONE = 0;       // doing nothing
    public static final int STATE_LISTEN = 1;     // now listening for incoming connections
    public static final int STATE_CONNECTING = 2; // now initiating an outgoing connection
    public static final int STATE_CONNECTED = 3;  // now connected to a remote device


    public BluetoothService(Context context, Handler MessageHandler) 
    {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        state = STATE_NONE;
        handler = MessageHandler;
    }

    
    // Set the current state of the connection
    private synchronized void setState(int State) 
    {
        state = State;

        // Give the new state to the Handler so the UI Activity can update
        handler.obtainMessage(MessengerActivity.MESSAGE_STATE_CHANGE, state, -1).sendToTarget();
    }

    // Return the current connection state
    public synchronized int getState() 
    {
        return state;
    }

    // Start the accept thread listening for incoming connections
    public synchronized void start() 
    {
        // Cancel any thread attempting to make a connection
        if (connectThread != null) 
        {
        	connectThread.cancel(); connectThread = null;
        }

        // Cancel any thread currently running a connection
        if (connectedThread != null) 
        {
        	connectedThread.cancel(); connectedThread = null;
        }

        // Start the thread to listen on a BluetoothServerSocket
        if (acceptThread == null) 
        {
            acceptThread = new AcceptThread();
            acceptThread.start();
        }
        setState(STATE_LISTEN);
    }

    // Attempt to connect to a device
    public synchronized void connect(BluetoothDevice device) 
    {
        // Cancel any thread attempting to make a connection
        if (state == STATE_CONNECTING) 
        {
            if (connectThread != null) 
            {
            	connectThread.cancel(); 
            	connectThread = null;
            }
        }

        // Cancel any thread currently running a connection
        if (connectedThread != null) 
        {
        	connectedThread.cancel(); 
        	connectedThread = null;
        }

        // Start the thread to connect with the given device
        connectThread = new ConnectThread(device);
        connectThread.start();
        setState(STATE_CONNECTING);
    }

    //Start the ConnectedThread to begin managing a Bluetooth connection
    public synchronized void connected(BluetoothSocket socket, BluetoothDevice device) 
    {
        // Cancel the thread that completed the connection
        if (connectThread != null) 
        {
        	connectThread.cancel(); 
        	connectThread = null;
        }

        // Cancel any thread currently running a connection
        if (connectedThread != null) 
        {
        	
        	connectedThread.cancel(); 
        	connectedThread = null;
        }

        // Cancel the accept thread (only want to connect to one device)
        if (acceptThread != null) 
        {
        	acceptThread.cancel(); 
        	acceptThread = null;
        }

        // Start the thread to manage the connection and perform transmissions
        connectedThread = new ConnectedThread(socket);
        connectedThread.start();

        // Send the name of the connected device back to the UI Activity
        Message msg = handler.obtainMessage(MessengerActivity.MESSAGE_DEVICE_NAME);
        Bundle bundle = new Bundle();
        bundle.putString(MessengerActivity.DEVICE_NAME, device.getName());
        msg.setData(bundle);
        handler.sendMessage(msg);

        setState(STATE_CONNECTED);
    }

    // Stop all threads
    public synchronized void stop() 
    {
        if (connectThread != null) {connectThread.cancel(); connectThread = null;}
        if (connectedThread != null) {connectedThread.cancel(); connectedThread = null;}
        if (acceptThread != null) {acceptThread.cancel(); acceptThread = null;}
        setState(STATE_NONE);
    }

    public void write(byte[] out) 
    {
        // Create temporary object
        ConnectedThread r;
        // Synchronize a copy of the ConnectedThread
        synchronized (this) 
        {
            if (state != STATE_CONNECTED) return;
            r = connectedThread;
        }
        // Perform the write 
        r.write(out);
    }

    // Indicate that the connection attempt failed and notify the UI Activity.
    private void connectionFailed() 
    {
        setState(STATE_LISTEN);

        // Send a failure message back to the Activity
        Message msg = handler.obtainMessage(MessengerActivity.MESSAGE_TOAST);
        Bundle bundle = new Bundle();
        bundle.putString(MessengerActivity.TOAST, "Unable to connect device");
        msg.setData(bundle);
        handler.sendMessage(msg);
    }

    // Indicate that the connection was lost and notify the UI Activity.
    private void connectionLost() 
    {
        setState(STATE_LISTEN);

        // Send a failure message back to the Activity
        Message msg = handler.obtainMessage(MessengerActivity.MESSAGE_TOAST);
        Bundle bundle = new Bundle();
        bundle.putString(MessengerActivity.TOAST, "Device connection was lost");
        msg.setData(bundle);
        handler.sendMessage(msg);
    }

    /*
    / This thread runs while listening for incoming connections. It behaves
    / like a server-side client. It runs until a connection is accepted
    / (or until cancelled).*/
    private class AcceptThread extends Thread 
    {
        // The local server socket
        private final BluetoothServerSocket btServerSocket;

        public AcceptThread() 
        {
            BluetoothServerSocket tmp = null;

            // Create a new listening server socket
            try 
            {
                tmp = btAdapter.listenUsingRfcommWithServiceRecord(NAME, MY_UUID);
            } catch (IOException e) {
            }
            btServerSocket = tmp;
        }

        public void run() 
        {
            setName("AcceptThread");
            BluetoothSocket socket = null;

            // Listen to the server socket if we're not connected
            while (state != STATE_CONNECTED) 
            {
                try 
                {
                    socket = btServerSocket.accept();
                } catch (IOException e) {
                    break;
                }

                // If a connection was accepted
                if (socket != null) 
                {
                    synchronized (BluetoothService.this) 
                    {
                        switch (state) 
                        {
                        case STATE_LISTEN:
                        case STATE_CONNECTING:
                            // Situation normal. Start the connected thread.
                            connected(socket, socket.getRemoteDevice());
                            break;
                        case STATE_NONE:
                        case STATE_CONNECTED:
                            // Either not ready or already connected. Terminate new socket.
                            try 
                            {
                                socket.close();
                            } catch (IOException e) {
                            }
                            break;
                        }
                    }
                }
            }
        }

        public void cancel() {
            try {
                btServerSocket.close();
            } catch (IOException e) {
            }
        }
    }


    /*
    / This thread runs while attempting to make an outgoing connection
    / with a device */
    private class ConnectThread extends Thread 
    {
        private final BluetoothSocket btSocket;
        private final BluetoothDevice btDevice;

        public ConnectThread(BluetoothDevice device) 
        {
            btDevice = device;
            BluetoothSocket tmp = null;

            // Get a BluetoothSocket for a connection with the
            // given BluetoothDevice
            try 
            {
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) {
            }
            btSocket = tmp;
        }

        public void run() 
        {
            setName("ConnectThread");

            // Cancel discovery because it will slow down a connection
            btAdapter.cancelDiscovery();

            // Make a connection to the BluetoothSocket
            try 
            {
                btSocket.connect();
            } 
            catch (IOException e)
            {
                connectionFailed();
                // Close the socket
                try 
                {
                    btSocket.close();
                } catch (IOException e2) {
                }
                // Start the service over to restart listening mode
                BluetoothService.this.start();
                return;
            }

            // Reset the ConnectThread when done
            synchronized (BluetoothService.this) 
            {
                connectThread = null;
            }

            // Start the connected thread
            connected(btSocket, btDevice);
        }

        public void cancel() 
        {
            try 
            {
                btSocket.close();
            } catch (IOException e) {
            }
        }
    }

    /*
    / This thread runs during a connection with a remote device.
    / It handles all incoming and outgoing transmissions */
    private class ConnectedThread extends Thread 
    {
        private final BluetoothSocket btSocket;
        private final InputStream InStream;
        private final OutputStream OutStream;

        public ConnectedThread(BluetoothSocket socket) 
        {
            btSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            // Get the BluetoothSocket input and output streams
            try 
            {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
            }

            InStream = tmpIn;
            OutStream = tmpOut;
        }

        public void run() 
        {
            byte[] bArray = new byte[1024*100];
            byte[] buffer = new byte[1024*1024];
            int pos = 0;
            int bytes;

            // Keep listening to the InputStream while connected
            while (true) 
            {
                try 
                {
                	pos = 0;
                	/* Use do while loop to get bytes from the stream, otherwise long
                	/ messages (images) will be broken up, making it impossible to 
                	/ reconstruct an image from the byte array */
                	do 
                	{
                        bytes = InStream.read(bArray,0,1008);
                        System.arraycopy(bArray,0,buffer,pos,bytes);
                        pos += bytes;
                    } while (bytes==1008);
                	// Encode the string to Base64 to preserve the data
                	String msg = Base64.encodeToString(buffer, Base64.DEFAULT);
                	handler.obtainMessage(MessengerActivity.MESSAGE_READ, pos, -1, msg)
                    	.sendToTarget();
                } catch (IOException e) {
                    connectionLost();
                    break;
                }
            }
        }

        
        // Write to the connected OutStream
        public void write(byte[] buffer) 
        {
            try 
            {
                OutStream.write(buffer);
                OutStream.flush();

                // Share the sent message back to the UI Activity
                handler.obtainMessage(MessengerActivity.MESSAGE_WRITE, -1, -1, buffer)
                        .sendToTarget();
            } catch (IOException e) {
            }
        }

        public void cancel() 
        {
            try 
            {
                btSocket.close();
            } catch (IOException e) {
            }
        }
    }
}
