---
title: "Analyzing Run 1 data"
teaching: 10
exercises: 30
questions:
- "TOBEDONE"
objectives:
- "TOBEDONE"
keypoints:
- "TOBEDONE"
---

## STUFF

From inside your Docker container

~~~
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/dimuonSpectrum_2012_ptcut.C --output dimuonSpectrum_2012_ptcut.C
~~~
{: .language-bash}

You can look to see that the file was downloaded properly by typing

~~~
ls -ltr
~~~
{: .language-bash}

Now launch the script with ROOT.

~~~
root -l dimuonSpectrum_2012_ptcut.C
~~~
{: .language-bash}
