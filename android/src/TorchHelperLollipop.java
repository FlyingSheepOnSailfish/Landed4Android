package org.flyingsheep.landed;

import org.qtproject.qt5.android.bindings.QtApplication;
import android.hardware.Camera;
import java.lang.String;
import java.util.List;
import android.util.Log;

public class TorchHelperLollipop implements TorchHelper {

    private Camera cam;
    private Camera.Parameters params;
    private String flashModeTorch;

    public TorchHelperLollipop()
    {
        Log.d(QtApplication.QtTAG, "TorchHelperLollipop constructor!!!");
    }

    public void initTorch(final LandedActivity landed)
    {
    //prepare the camera, establish the supported flash mode for torch use.
        try
        {
            cam = Camera.open();
            params = cam.getParameters();
            List<String> flashModes = params.getSupportedFlashModes();
            if (flashModes != null && flashModes.contains(Camera.Parameters.FLASH_MODE_TORCH)) {
                flashModeTorch = Camera.Parameters.FLASH_MODE_TORCH;
            } else {
                flashModeTorch = Camera.Parameters.FLASH_MODE_ON;
            }
            params.setFlashMode(Camera.Parameters.FLASH_MODE_OFF);
            cam.setParameters(params);
            cam.startPreview();
//TODO: signal back to C++ / QML that the camera has been successfully initiated
        }
        catch (Exception e)
        {
            Log.d(QtApplication.QtTAG, "Torch.initTorch: could not initiate");
        }
    }


    public void on()
    {
//TODO: maybe we should check if torch has been initiated?
        try
        {
            Log.d(QtApplication.QtTAG, "Torch.on");
            params.setFlashMode(flashModeTorch);
            cam.setParameters(params);
        }
        catch (Exception e)
        {
            Log.d(QtApplication.QtTAG, "Torch.on: could not acquire camera");
        }
    }

    public void off()
    {
        try
        {
            params.setFlashMode(Camera.Parameters.FLASH_MODE_OFF);
            cam.setParameters(params);
        }
        catch (Exception e)
        {
            Log.d(QtApplication.QtTAG, "Torch.off: could not stop flash");
        }
    }

    public void releaseTorch()
    {
        try
        {
            params = cam.getParameters();
            params.setFlashMode(Camera.Parameters.FLASH_MODE_OFF);
            cam.setParameters(params);
            cam.stopPreview();
            cam.release();
        }
        catch (Exception e)
        {
            Log.d(QtApplication.QtTAG, "Torch.off: could not release");
        }
    }
}

