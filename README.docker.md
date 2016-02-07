This docker image does not support graphical interfaces with OpenGL,
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
cp -rf <your-graspit-models-dir> <your-graspit-home>
xhost +
sudo docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v <your-graspit-home>:/graspit_home jenniferbuehler/grasp_planning_graspit
```

You can find the graspit sources on /usr.

Note that **no soft links** are supported within ``<your-graspit-home>``, you will have to copy
entire files and directories into it.

This image alone is not very useful by itself at this stage, due to the limited support of graphical interfaces. But you can base other images on this, which access the GraspIt! code in headless mode.
For example, check out the docker image jenniferbuehler/grasp_planning_graspit.
