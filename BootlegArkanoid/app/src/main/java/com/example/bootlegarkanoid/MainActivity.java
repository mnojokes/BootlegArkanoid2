package com.example.bootlegarkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;

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

        boolean res = Launch();
        // TODO: handle failure to launch/intialize
    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction();
        float x = event.getX();
        float y = event.getY();
        
        return SignalInputEvent(action, x, y);
    }
    public native boolean Launch();
    public native boolean SignalInputEvent(int action, float x, float y);
}
