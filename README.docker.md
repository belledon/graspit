This docker image does not support graphical interfaces,
because support for this depends on the locally used
graphics card.

This image installs graspit in the /usr directory of the image.

# Build this image

``sudo docker build -t jenniferbuehler/graspit .``

# Log onto bash of the image

The GRASPIT environment variable is set to 
the folder ``/graspit_home`` on the local image. You can mount
a folder on your computer to it so that you can use yor own robot files.

You will need to connect your display to the docker image,
because even though the graspit code runs in headless mode,
it internally still requires X for Qt.

```
mkdir <your-graspit-home>
xhost +
cp -rf <your-graspit-models-dir> <your-graspit-home>
sudo docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v <your-graspit-home>:/graspit_home jenniferbuehler/grasp_planning_graspit
```

Note that **no soft links** are supported within ``<your-graspit-home>``, you will have to copy
entire files and directories into it.
