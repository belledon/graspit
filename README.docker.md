# UNDER CONSTRUCTION

The graspit simulator cannot be run yet with the current graphics card sharing.
Looking into this.

# Build this image

sudo docker build -t jenniferbuehler/graspit .

# Log onto bash

sudo docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix jenniferbuehler/graspit

# Run simulator

sudo docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix jenniferbuehler/graspit graspit_simulator


