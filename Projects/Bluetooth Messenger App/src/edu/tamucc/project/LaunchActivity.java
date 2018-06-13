package edu.tamucc.project;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class LaunchActivity extends Activity {
	
	private Handler handler;

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.launch);
		
		handler = new Handler();
		handler.postDelayed(
				new Runnable()
				{
					@Override
					public void run() 
					{
						// TODO Auto-generated method stub
						
						Intent intentObj = new Intent(LaunchActivity.this, MessengerActivity.class);
						startActivity(intentObj);
						LaunchActivity.this.finish();
					}
					
				}, 3000);
		
	}
}
