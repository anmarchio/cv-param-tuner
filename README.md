# CV Parameter Tuner

Optimising CV parameter for a given operator pipeline and segmentation area.

## Add OpenCV Reference

If OpenCV references have not been added to your solution file, then manually add OpenCV properties:

* in VS, right click on project explorer, select `Properties`
* then select `VC++ Directories`
* to Include Directories add: `$(OPENCVDIR)\opencv\build\install\include`
* to Library Directories add: `$(OPENCVDIR)\opencv\build\install\x64\<YOUR_VS_VERSION>\lib`
* in `Linker > Input > Additional Dependencies` add the following string: `opencvXXXd-world.lib`; `XXX` should be replaced with your custom opencv version
