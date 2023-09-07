package com.example.bootlegarkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Rect;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.WindowMetrics;

import com.example.bootlegarkanoid.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'bootlegarkanoid' library on application startup.
    static {
        System.loadLibrary("bootlegarkanoid");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Rect windowSize = getWindowManager().getCurrentWindowMetrics().getBounds();
        boolean res = Launch(windowSize.bottom, windowSize.right);
        // TODO: handle failure to launch/intialize
    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction();
        float x = event.getX();
        float y = event.getY();
        
        return SignalInputEvent(action, x, y);
    }
    public native boolean Launch(int sizeVertical, int sizeHorizontal);
    public native boolean SignalInputEvent(int action, float x, float y);
}
