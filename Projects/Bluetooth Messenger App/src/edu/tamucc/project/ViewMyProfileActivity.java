package edu.tamucc.project;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class ViewMyProfileActivity extends Activity {

	private TextView usernameTextView;
	private TextView emailTextView;
	private ImageView profilePicImageView;
	private String username;
	private String email;
	private String imagePath;
	private Bitmap image;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{	
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.view_profile);
		
		usernameTextView = (TextView) findViewById(R.id.viewProfileUnTextView);
		emailTextView = (TextView) findViewById(R.id.viewProfileEmailTextView);
		
		profilePicImageView = (ImageView) findViewById(R.id.viewProfileImageView);
		
		SharedPreferences prefs = getSharedPreferences("profile", 0);
		
		username = prefs.getString("username", "");
		email = prefs.getString("email", "");
		imagePath = prefs.getString("image_path", "");
		
		usernameTextView.setText(username);
		emailTextView.setText(email);
	
		File imageFile = new File(imagePath);
		
		image = decodeFile(imageFile);
		
		profilePicImageView.setImageBitmap(image);
		
		Button editProfileButton = (Button) findViewById(R.id.editProfileButton);
		editProfileButton.setOnClickListener(editProfileButtonListener);
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
	    } catch (FileNotFoundException e) {}
	    return null;
	}

	
	@Override
	protected void onDestroy() 
	{
		// TODO Auto-generated method stub
		super.onDestroy();
		image.recycle();
	}

	public OnClickListener editProfileButtonListener = new OnClickListener()
	{

		@Override
		public void onClick(View v) 
		{
			// TODO Auto-generated method stub
			Intent newIntent = new Intent(ViewMyProfileActivity.this, CreateProfileActivity.class);
			ViewMyProfileActivity.this.startActivity(newIntent);
			ViewMyProfileActivity.this.finish();
		}
		
	};
}
