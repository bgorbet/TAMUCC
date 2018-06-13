package edu.tamucc.project;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

public class CreateProfileActivity extends Activity {
	private static final int SELECT_PICTURE = 1;
	private EditText usernameEditText;
	private EditText emailEditText;
	private String selectedImagePath;
	private Uri selectedImageUri;
	private ImageView profilePicImageView;

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.create_profile);
		
		usernameEditText = (EditText) findViewById(R.id.enterUnEditText);
		emailEditText = (EditText) findViewById(R.id.enterEmailEditText);
		
		profilePicImageView = (ImageView) findViewById(R.id.createProfileImageView);
		
		Button uploadImageButton = (Button) findViewById(R.id.uploadButton);
		uploadImageButton.setOnClickListener(uploadImageButtonListener);
		
		Button createButton = (Button) findViewById(R.id.createButton);
		createButton.setOnClickListener(createButtonListener);
	}
	
	@Override
	protected void onDestroy() 
	{
		// TODO Auto-generated method stub
		super.onDestroy();
		// "destroy" the drawable to free up memory
		profilePicImageView.getDrawable().setCallback(null);
	}

	@Override
	protected void onPause() 
	{
		// TODO Auto-generated method stub
		super.onPause();
		profilePicImageView.getDrawable().setCallback(null);
	}

	public OnClickListener uploadImageButtonListener = new OnClickListener()
	{

		@Override
		public void onClick(View v) 
		{
			// Start the gallery picture chooser
			// TODO Auto-generated method stub
			Intent intent = new Intent();
            intent.setType("image/*");
            intent.setAction(Intent.ACTION_GET_CONTENT);
            startActivityForResult(Intent.createChooser(intent,
                    "Select Picture"), SELECT_PICTURE);
		}
	};
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent imageReturnedIntent) 
	{ 
	    super.onActivityResult(requestCode, resultCode, imageReturnedIntent); 

	    switch(requestCode) 
	    {
	    case SELECT_PICTURE:
	        if(resultCode == RESULT_OK)
	        {
	        	// Get the selected image's Uri and path
	            selectedImageUri = imageReturnedIntent.getData();
	            selectedImagePath = getPath(selectedImageUri);
                
	            // Set the profile pic image view
	    		profilePicImageView.setImageURI(selectedImageUri);
	            
	    		// Save the image path
	            SharedPreferences prefs = getSharedPreferences("profile", 0);
	            Editor edit = prefs.edit();
	            edit.putString("image_path", selectedImagePath);
	            edit.commit();
	           
	        }
	    }
	}
	
	public String getPath(Uri uri) 
	{
        String[] projection = { MediaStore.Images.Media.DATA };
        Cursor cursor = managedQuery(uri, projection, null, null, null);
        if(cursor!=null)
        {
            int column_index = cursor
            .getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            cursor.moveToFirst();
            return cursor.getString(column_index);
        }
        else return null;
    }

	// Make sure all fields have been filled, save the info and exit the activity
	public OnClickListener createButtonListener = new OnClickListener()
	{

		@Override
		public void onClick(View v) 
		{
			// TODO Auto-generated method stub
			
			SharedPreferences prefs = getSharedPreferences("profile", MODE_PRIVATE);
			Editor edit = prefs.edit();
			
			String username = usernameEditText.getText().toString();
			if (username.matches("")) 
			{
			    Toast.makeText(CreateProfileActivity.this, "You did not enter a username", Toast.LENGTH_SHORT).show();
			    return;
			}
			else
			{
				edit.putString("username", username);
			}
			
			String email = emailEditText.getText().toString();
			if(email.matches(""))
			{
				Toast.makeText(CreateProfileActivity.this, "You did not enter an email address", Toast.LENGTH_SHORT).show();
			    return;
			}
			else
			{
				edit.putString("email", email);
			}
			
			if(prefs.getString("image_path", "").matches(""))
			{
				Toast.makeText(CreateProfileActivity.this, "You did not select an image", Toast.LENGTH_SHORT).show();
			    return;
			}
			
			if(!(username.matches("") && email.matches("") && prefs.getString("image_path", "").matches("")))
			{
				edit.putBoolean("isfirstLaunch", false);
				edit.commit();
				CreateProfileActivity.this.finish();
			}
		}
	};
}
