---
title: "Introduction"
teaching: 5
exercises: 5
questions:
- "How can we set up an environment to run over Run I simplified files."
objectives:
- "Remind ourselves of how to set up Docker to use ROOT."
keypoints:
- "Docker can reduce the overhead in setting up a ROOT environment."
---

The first thing you will want to do is start your ROOT Docker container.
Ideally, you have already downloaded it and tested it out when you 
completed the [Docker pre-exercise](https://cms-opendata-workshop.github.io/workshop2022-lesson-docker/)
for this workshop. 

The specific episode is 
[Using Docker with CMS Open Data](https://cms-opendata-workshop.github.io/workshop2022-lesson-docker/03-docker-for-cms-opendata/index.html).
You will want to scroll down to 
**Download the docker images for ROOT and python tools and start container** and then just below that, 
**ROOT container**. Please make sure you have gone through that lesson, as we will be following
most of the instructions about how to launch the container, with some minimal modifications. 

## Create a local directory to store your work

Before you start up the Docker container, create a local directory where we will store
files. Let's call it `cms_open_data_run1`. If you were on Linux or in a Mac terminal, 
    you would type something like

~~~
mkdir cms_open_data_run1
~~~
{: .language-bash}

## Launch Docker

We'll follow the instructions from the previous lesson on Docker except that
* We will call this new instance of the container `my_run1`
* We will mount a new `volume` which is our `cms_open_data_run1` directory

If you are on native Linux and want to use X11-forwarding, use

~~~
docker run -it --name my_run1 --net=host --env="DISPLAY" -v $HOME/.Xauthority:/home/cmsusr/.Xauthority:rw -v ${HOME}/cms_open_data_run1:/code gitlab-registry.cern.ch/cms-cloud/root-vnc:latest
~~~
{: .language-bash}

On MacOS and Windows WSL2 (and on native Linux if you do not want to use X11-forwarding), use

~~~
docker run -it --name my_run1 -P -p 5901:5901 -p 6080:6080 -v ${HOME}/cms_open_data_run1:/code gitlab-registry.cern.ch/cms-cloud/root-vnc:latest
~~~
{: .language-bash}


This opens a bash shell where you can type your commands. Edit files in the `cms_open_data_run1` directory on your local computer, but run the commands in the container.

For graphics, on native Linux, use X11-forwarding. On other systems, use VNC that is installed in the container and start the graphics windows with `vnc_start`. Open the browser window in the address given at the start message ([http://127.0.0.1:6080/vnc.html](http://127.0.0.1:6080/vnc.html)) with the default VNC password is `cms.cern`. It shows an empty screen to start with and all graphics will pop up there.

Type `exit` to leave the container, and if you have started VNC, stop it first:

~~~
stop_vnc
exit
~~~
{: .language-bash}







{% include links.md %}

