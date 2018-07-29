package com.example.mateusz.myapplication;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void changeText(View view){
        EditText editText=(EditText)findViewById(R.id.editText);
        editText.setHint("Tu wpisz jakiś tekst");
        String Text = editText.getText().toString();
        TextView textView=(TextView) findViewById(R.id.textView);
        textView.setText(Text);

        if(Text.equals("gugle")){
            Uri uri=Uri.parse("http://google.pl");
            Intent e = new Intent(Intent.ACTION_VIEW, uri);
            startActivity(e);
        }
    }

    public void clearText(View view){
        TextView textView=(TextView) findViewById(R.id.textView);
        textView.setText("");
        EditText editText=(EditText)findViewById(R.id.editText);
        editText.setText("");
        Toast.makeText(getApplicationContext(), "Usunięto tekst!!!", Toast.LENGTH_LONG).show();
    }

    public void gugle(View view){
        EditText editText2=(EditText)findViewById(R.id.editText2);
        Uri uri=Uri.parse("http://"+editText2.getText());
        Intent i = new Intent(Intent.ACTION_VIEW, uri);
        startActivity(i);
    }
}

