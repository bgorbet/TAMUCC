package edu.tamucc.project;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;
import android.view.View.OnClickListener;

public class WelcomeActivity extends Activity {
	
	private Button button;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.first_time_welcome);
		
		button = (Button) findViewById(R.id.welcomeButton);
		button.setOnClickListener(buttonListener);
		
	}
	
	public OnClickListener buttonListener = new OnClickListener()
	{

		@Override
		public void onClick(View v) 
		{
			// TODO Auto-generated method stub
			

			Intent intent = new Intent(WelcomeActivity.this, CreateProfileActivity.class);
			startActivity(intent);
			WelcomeActivity.this.finish();
		}
		
	};

}
