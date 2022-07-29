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

