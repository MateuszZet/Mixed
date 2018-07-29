package com.example.mateusz.animation;

import android.graphics.drawable.AnimationDrawable;
import android.graphics.drawable.Drawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.lang.reflect.Field;

import static android.R.attr.button;
import static android.R.attr.drawable;

public class MainActivity extends AppCompatActivity {

    ImageView image;
    Button button, next, prev;
    int frameNumber, i;
    boolean showingFirst = true;
    Drawable currentFrame, checkFrame;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        image = (ImageView)findViewById(R.id.imageView);
        image.setBackgroundResource(R.drawable.trans);

        button = (Button)findViewById(R.id.button);
        next = (Button)findViewById(R.id.next);
        prev = (Button)findViewById(R.id.prev);



        button.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
               AnimationDrawable frameAnimation = (AnimationDrawable) image.getBackground();
                if(showingFirst == true){
                frameAnimation.start();
                showingFirst = false;
                }
                else{frameAnimation.stop();
                showingFirst = true;
                }

            }

        });

        next.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                AnimationDrawable frameAnimation = (AnimationDrawable) image.getBackground();
                currentFrame = frameAnimation.getCurrent();

                for (int i = 0; i < frameAnimation.getNumberOfFrames(); i++) {
                    checkFrame = frameAnimation.getFrame(i);
                    if (checkFrame == currentFrame) {
                        frameNumber = i;
                        break;
                    }
                }
                frameAnimation.selectDrawable(frameNumber+1);





            }

        });

        prev.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                AnimationDrawable frameAnimation = (AnimationDrawable) image.getBackground();
                currentFrame = frameAnimation.getCurrent();

                for (int i = 0; i < frameAnimation.getNumberOfFrames(); i++) {
                    checkFrame = frameAnimation.getFrame(i);
                    if (checkFrame == currentFrame) {
                        frameNumber = i;
                        break;
                    }
                }
                frameAnimation.selectDrawable(frameNumber-1);




            }

        });

    }



    private int getCurFrameFromAnimationDrawable(AnimationDrawable drawable){
        try {
            Field mCurFrame = drawable.getClass().getDeclaredField("mCurFrame");
            mCurFrame.setAccessible(true);
            return  mCurFrame.getInt(drawable);
        }catch (Exception ex){
            Log.e(MainActivity.class.getName(), "getCurFrameFromAnimationDrawable: Exception");
            return 0;
        }
    }



}



