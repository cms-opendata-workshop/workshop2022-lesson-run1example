---
title: "Analyzing Run 1 data"
teaching: 10
exercises: 50
questions:
- "How can I analyze larger ROOT files?"
objectives:
- "Demonstrate examples of accessing ROOT files remotely"
- "To compare and contrast using standard ROOT approaches and newer ROOT objects like RDataFrame"
keypoints:
- "Making use of RDataFrame can speed up your analysis"
---

# Analyzying the dimuon samples

This lesson will be primarily following the material found [here](https://twiki.cern.ch/twiki/bin/view/CMSPublic/NanoAODRun1Examples)
about using the NanoAOD format in an analysis of the dimuon samples.

> ## Potential pitfalls!
> We'll be running over some larger ROOT files in this lesson and for some of you, memory issues may cause some errors
> or crashes of the code. If that happens, it is primarily restricted to this exercise and you should feel free to simply 
> follow along with the instructor. 
{: .callout}

## Download the code and scripts

Launch your Docker container, as per the previous episode.
From inside your Docker container, we're going to execute a series of `curl` commands. 
[`curl`](https://curl.se/) is a widely used utility to download files from remote locations. 
Simply highlight the commands below and cut-and-paste them into your Docker terminal. 

~~~
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/Dimuon2011_eospublic.C --output Dimuon2011_eospublic.C      
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/dimuonSpectrum2012_local.py --output dimuonSpectrum2012_local.py     
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/dimuonSpectrum_2012_ptcut.C --output dimuonSpectrum_2012_ptcut.C
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/Dimuon2011_local.C --output Dimuon2011_local.C          
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/dimuonSpectrum2012_outreach.C --output dimuonSpectrum2012_outreach.C   
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/MuHistos_eospublic.cxx --output MuHistos_eospublic.cxx
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/dimuonSpectrum2012_local.C --output dimuonSpectrum2012_local.C  
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/dimuonSpectrum2012_outreach.py --output dimuonSpectrum2012_outreach.py  
curl https://raw.githubusercontent.com/cms-opendata-workshop/workshop2022-lesson-run1example/gh-pages/data/MuHistos_local.cxx --output MuHistos_local.cxx
~~~
{: .language-bash}

You can look to see that the files were downloaded properly by typing

~~~
ls -ltr
~~~
{: .language-bash}

## Run some of the commands

Your instructor will be executing most of these commands, some of which might take a few minutes to run. 

In most cases, these scripts produce an output `.pdf` file with a name similar to that of the script itself. 
If you have any issues with ROOT displaying the plots as they are made, you can view the `.pdf` files 
on your *local* system by looking in the `cms_open_data_run1` directory that you created. 

### First example 

Let's run the first command making use of ROOT's ability to compile and execute a file in one step. 
This might take 5 minutes for local participants at CERN, but longer for remote participants. 

~~~
root -l MuHistos_eospublic.cxx++ 
~~~
{: .language-bash}

~~~
root [0]
Processing MuHistos_eospublic.cxx++...
Info in <TUnixSystem::ACLiC>: creating shared library /code/./MuHistos_eospublic_cxx.so
reading root://eospublic.cern.ch//eos/opendata/cms/upload/NanoAODRun1/01-Jul-22/Run2010B_Mu_merged.root
writing to MuHistos_Mu_eospublic.root
entries = 26718043
event nr 0
event nr 1000000
event nr 2000000
event nr 3000000
event nr 4000000
event nr 5000000
event nr 6000000
event nr 7000000
event nr 8000000
event nr 9000000
event nr 10000000
event nr 11000000
event nr 12000000
event nr 13000000
event nr 14000000
event nr 15000000
event nr 16000000
event nr 17000000
event nr 18000000
event nr 19000000
event nr 20000000
event nr 21000000
event nr 22000000
event nr 23000000
event nr 24000000
event nr 25000000
event nr 26000000
~~~
{: .output}

After the above output, the program will finish and will return the command-line prompt. 
The program should have produced an output file called `MuHistos_Mu_eospublic.root`. You can check this by typing

~~~
ls -l MuHistos_Mu_eospublic.root
~~~
{: .language-bash}

~~~
-rw-r--r-- 1 cmsusr cmsusr 31625 Jul 31 22:57 MuHistos_Mu_eospublic.root
~~~
{: .output}

You can open this file in ROOT and inspect it with a `TBrowser`. First type

~~~
root -l MuHistos_Mu_eospublic.root
~~~
{: .language-bash}

This will put you into the ROOT environment, from which you can then launch the `TBrowser`
from the prompt (you needn't type the `root [0]`). 

~~~
root [0] TBrowser b;
~~~
{: .code}

You can then click on the file name in the window and then click on the various 
histograms to view them.

## Example 2 (`RDataFrame`)

A different example runs over a smaller (2 Gb) file, primarily used for
outreach, and makes use of ROOT's relatively 
newer `RDataFrame` object. You can run this example by launching ROOT from the commandline.

~~~
root -l dimuonSpectrum2012_outreach.C
~~~
{: .language-bash}

It should only take a few minutes to run and if X-forwarding is working for you, you 
should see a ROOT window pop up that looks like this.

> ## CMS dimuon spectrum
> Invariant mass of a select sample of oppositely charged dimuon pairs.
> ![](../assets/img/dimuon_spectrum.png)
{: .callout}
> 

## Example 3 (2011 data)

This example runs over 2011 data that was used for more "real" analysis. 
Takes about 15 minutes at CERN.

~~~
root -l Dimuon2011_eospublic_RDF.C
~~~
{: .language-bash}

> ## CMS dimuon spectrum - 2011 data sample
> Invariant mass of a select sample of oppositely charged dimuon pairs.
> Derived from 2011 data.
> ![](../assets/img/dimuon_spectrum_2011.png)
{: .callout}

