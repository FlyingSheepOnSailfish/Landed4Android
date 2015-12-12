package org.flyingsheep.landed.landed29;

import org.qtproject.qt5.android.bindings.QtApplication;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCharacteristics;
import java.lang.String;
import java.util.List;
import android.util.Log;
import android.content.Context;

public class TorchHelperMarshmallow implements TorchHelper {

    private CameraManager manager;
    private String cameraId;
    private boolean flashFound;


    public TorchHelperMarshmallow()
    {
        Log.d(QtApplication.QtTAG, "TorchHelperMarshmallow constructor!!!");
    }

    public void initTorch(final LandedActivity landed)
    {
        try
        {
            Log.d(QtApplication.QtTAG, "TorchHelperMarshmallow initTorch!!!");
            manager = (CameraManager) landed.getSystemService(Context.CAMERA_SERVICE);
            for (String id : manager.getCameraIdList()) {
                // Turn on the flash if camera has one
                if (manager.getCameraCharacteristics(id) .get(CameraCharacteristics.FLASH_INFO_AVAILABLE)) {
                    flashFound = true;
                    cameraId = id;
                    //manager.setTorchMode(id, true);
                }
            }

        }
        catch (Exception e)
        {
            flashFound = false;
            Log.d(QtApplication.QtTAG, "Torch.initTorch: could not initiate");
        }
    }

    public void on()
    {
//TODO: maybe we should check if torch has been initiated?
        try
        {
            if (flashFound) {
                manager.setTorchMode(cameraId, true);
            }
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
            if (flashFound) {
                manager.setTorchMode(cameraId, false);
            }
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
            off();
        }
        catch (Exception e)
        {
            Log.d(QtApplication.QtTAG, "Torch.off: could not release");
        }
    }

}

