package com.example.bootlegarkanoid;

import androidx.appcompat.app.AppCompatActivity;

import android.app.NativeActivity;
import android.graphics.Rect;
import android.os.Bundle;
import android.view.MotionEvent;
import android.opengl.GLES20;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.Window;
import android.view.WindowManager;

import com.example.bootlegarkanoid.databinding.ActivityMainBinding;

import java.util.Objects;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'bootlegarkanoid' library on application startup.
    static {
        System.loadLibrary("bootlegarkanoid");
    }

    private ActivityMainBinding binding;
    private SurfaceView m_surfaceView;
    private Surface m_surface;

   @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        m_surfaceView = findViewById(R.id.surfaceView);
        m_surface = m_surfaceView.getHolder().getSurface();

        float refreshRate = Objects.requireNonNull(getDisplay()).getRefreshRate();
        boolean res = Launch(m_surface, refreshRate);
        // TODO: handle failure to launch/initialize
    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction();
        float x = event.getX();
        float y = event.getY();
        
        return SignalInputEvent(action, x, y);
    }
    public native boolean Launch(Object surface, float refreshRate);
    public native boolean SignalInputEvent(int action, float x, float y);
}
