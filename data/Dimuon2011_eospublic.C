{
// the opening parenthesis is important!
// the following code can also be typed by hand on the root command line 
// (or copy-pasted into it one by one or in blocks).
// To run it as a script, start interactive root and type .x Dimuon2011_public.C
// (takes about 10 minutes locally from interactive DESY workgroup server)
// if access to eospublic doesn't work, try 
// source /cvmfs/sft.cern.ch/lcg/views/LCG_98/x86_64-centos7-gcc8-opt/setup.sh
//
// enable implicit multithreading
//ROOT::EnableImplicitMT();
//
// chain t1 is 2011 DoubleMu Run A in NanoAODRun1 format
TChain *t1 = new TChain("Events");
t1->Add("root://eospublic.cern.ch//eos/opendata/cms/upload/NanoAODRun1/01-Jul-22/Run2011A_DoubleMu_merged.root");
//
// define a canvas with log y scale
TCanvas *c1=new TCanvas("c1","c1",1);
c1->SetLogy();                                                // set log scale
gStyle->SetOptStat(0);                                        // remove box

// book the histogram
TH1D *h_dimulog = new TH1D("h_dimulog", "h_dimulog", 620,-0.4, 2.7);
gROOT->cd();
cout << "high pt dimuon" << endl;
// fill the histogram from the ntuple ("high pt" = 13/8 or larger, see threshold "bump")
// the factor in the second argument acts as a weight
t1->Draw("log10(Dimu_mass)>>h_dimulog","2./log(10.)/Dimu_mass*(run<170000 && Trig_DoubleMuThresh>12 && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>6. && Muon_pt[Dimu_t2muIdx]>6. && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])");
// clone the histogram and set to no directory such that it does not get deleted
TH1D *h_dimulog1 = (TH1D*)h_dimulog->Clone(); 
h_dimulog1->SetDirectory(0);
//
// chain t2 is 2011 MuOnia Run A in NanoAODRun1 format
TChain *t2 = new TChain("Events");
t2->Add("root://eospublic.cern.ch//eos/opendata/cms/upload/NanoAODRun1/01-Jul-22/Run2011A_MuOnia_merged.root");
//
// explicit rebooking is necessary for name labels to be picked up by Draw
TH1D *h_dimulog2 = new TH1D("h_dimulog2", "h_dimulog2", 620,-0.4, 2.7);
TH1D *h_dimulog4 = new TH1D("h_dimulog4", "h_dimulog4", 620,-0.4, 2.7);
TH1D *h_dimulog6 = new TH1D("h_dimulog6", "h_dimulog6", 620,-0.4, 2.7);
TH1D *h_dimulog7 = new TH1D("h_dimulog7", "h_dimulog7", 620,-0.4, 2.7);
TH1D *h_dimulog8 = new TH1D("h_dimulog8", "h_dimulog8", 620,-0.4, 2.7);
TH1D *h_dimulog12 = new TH1D("h_dimulog12", "h_dimulog12", 620,-0.4, 2.7);
TH1D *h_dimulog3 = (TH1D*)h_dimulog2->Clone(); 
TH1D *h_dimulog5 = (TH1D*)h_dimulog4->Clone(); 
TH1D *h_dimulog9 = (TH1D*)h_dimulog4->Clone(); 
TH1D *h_dimulog10 = (TH1D*)h_dimulog4->Clone(); 
TH1D *h_dimulog11 = (TH1D*)h_dimulog4->Clone(); 
TH1D *h_dimulog13 = (TH1D*)h_dimulog4->Clone(); 
cout << "all MuOnia" << endl;
// all except displaced, trimuon, and 0 threshold triggers (and events already treated from DoubleMuon)
t2->Draw("log10(Dimu_mass)>>h_dimulog4","2./log(10.)/Dimu_mass*(run<170000 && !(Alsoon_DoubleMu && Trig_DoubleMuThresh>12) && Trig_JpsiThresh !=0 && (!HLT_DoubleMu4_LowMass_Displaced && !HLT_DoubleMu4p5_LowMass_Displaced && !HLT_DoubleMu5_LowMass_Displaced && !HLT_Dimuon6p5_LowMass_Displaced && !HLT_Dimuon7_LowMass_Displaced) && (!HLT_DoubleMu4_Jpsi_Displaced && !HLT_DoubleMu5_Jpsi_Displaced && !HLT_Dimuon6p5_Jpsi_Displaced && !HLT_Dimuon7_Jpsi_Displaced) && !HLT_Mu5_L2Mu2 && Dimu_mass>2. && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>3. && Muon_pt[Dimu_t2muIdx]>3. && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])");
// early 2011A Quarkonium trigger only
cout << "Quarkonium/Low pT dimuon only" << endl;
// was cut offline at m>2
t2->Draw("log10(Dimu_mass)>>h_dimulog2","2./log(10.)/Dimu_mass*(run<170000 && !(Alsoon_DoubleMu && Trig_DoubleMuThresh>12) && HLT_DoubleMu3_Quarkonium && Dimu_mass>2. && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>2. && Muon_pt[Dimu_t2muIdx]>2. && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])");
// early quarkonium and Upsilon
cout << "Quarkonium and Upsilon" << endl;
// to take care of the tails, Upsilon should have cuts 7<m<14
t2->Draw("log10(Dimu_mass)>>h_dimulog6","2./log(10.)/Dimu_mass*(run<170000 && !(Alsoon_DoubleMu && Trig_DoubleMuThresh>12) && (HLT_DoubleMu3_Quarkonium || ((HLT_Dimuon0_Upsilon || HLT_Dimuon0_Barrel_Upsilon || HLT_DoubleMu3_Upsilon || HLT_Dimuon5_Upsilon_Barrel || HLT_Dimuon7_Upsilon_Barrel) && Dimu_mass>7. && Dimu_mass<14.)) && Dimu_mass>2. && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>2. && Muon_pt[Dimu_t2muIdx]>2. && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])");
// early quarkonium and B0
cout << "Quarkonium and B0" << endl;
// to take care of the tails, B0 should have cuts 4<m<7
 t2->Draw("log10(Dimu_mass)>>h_dimulog7","2./log(10.)/Dimu_mass*(run<170000 && !(Alsoon_DoubleMu && Trig_DoubleMuThresh>12) && ((HLT_DoubleMu3_Quarkonium && Muon_pt[Dimu_t1muIdx]>2. && Muon_pt[Dimu_t2muIdx]>2.) || ((HLT_Dimuon6_Bs || HLT_Dimuon4_Bs_Barrel || HLT_DoubleMu4_Dimuon6_Bs || HLT_DoubleMu4_Dimuon4_Bs_Barrel || HLT_DoubleMu3_Bs || HLT_DoubleMu2_Bs) && Dimu_mass>4. && Dimu_mass<7.)) && Dimu_mass>2. && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>2. && Muon_pt[Dimu_t2muIdx]>2. && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])"); // 
// early quarkonium and Jpsi
cout << "Quarkonium and Jpsi" << endl;
// to take care of the tails, Dimuon0 and Dimuon6p5 should have cuts 2.8<m<3.4, Dimuon10/13 should have cuts 2.5<m<4.3
t2->Draw("log10(Dimu_mass)>>h_dimulog8","2./log(10.)/Dimu_mass*(run<170000 && !(Alsoon_DoubleMu && Trig_DoubleMuThresh>12) && ((HLT_DoubleMu3_Quarkonium && Muon_pt[Dimu_t1muIdx]>3. && Muon_pt[Dimu_t2muIdx]>3.) || ((HLT_Dimuon6p5_Jpsi || HLT_Dimuon6p5_Barrel_Jpsi) && Dimu_mass>2.5 && Dimu_mass<4.3) || ((HLT_Dimuon0_Jpsi || HLT_Dimuon13_Jpsi_Barrel || HLT_Dimuon10_Jpsi_Barrel) && Dimu_mass>2.8 && Dimu_mass<3.4)) && Dimu_mass>2. && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>1.5 && Muon_pt[Dimu_t2muIdx]>1.5 && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])"); // HLT_Dimuon0_Jpsi? -> not culprit for tail, HLT_Dimuon10/13_Jpsi_Barrel is?
// early quarkonium and Jpsi/psiprime
cout << "Quarkonium and Jpsi/psiprime" << endl;
// to take care of the tails, the psiprime triggers should have cuts 3.4<m<4.3
t2->Draw("log10(Dimu_mass)>>h_dimulog12","2./log(10.)/Dimu_mass*(run<170000 && !(Alsoon_DoubleMu && Trig_DoubleMuThresh>12) && ((HLT_DoubleMu3_Quarkonium && Muon_pt[Dimu_t1muIdx]>3. && Muon_pt[Dimu_t2muIdx]>3.) || ((HLT_Dimuon6p5_Jpsi || HLT_Dimuon6p5_Barrel_Jpsi) && Dimu_mass>2.5 && Dimu_mass<4.3) || ((HLT_Dimuon0_Jpsi || HLT_Dimuon13_Jpsi_Barrel || HLT_Dimuon10_Jpsi_Barrel) && Dimu_mass>2.8 && Dimu_mass<3.4) || ((HLT_Dimuon11_PsiPrime || HLT_Dimuon9_PsiPrime || HLT_Dimuon7_PsiPrime) && Dimu_mass>3.4 && Dimu_mass<4.3)) && Dimu_mass>2. && Dimu_charge==0 && Muon_pt[Dimu_t1muIdx]>1.5 && Muon_pt[Dimu_t2muIdx]>1.5 && Muon_mediumId[Dimu_t1muIdx] && Muon_mediumId[Dimu_t2muIdx])"); 
h_dimulog3->Add(h_dimulog1,h_dimulog2,1,1);
h_dimulog5->Add(h_dimulog1,h_dimulog4,1,1);
h_dimulog9->Add(h_dimulog1,h_dimulog6,1,1);
h_dimulog10->Add(h_dimulog1,h_dimulog7,1,1);
h_dimulog11->Add(h_dimulog1,h_dimulog8,1,1);
h_dimulog13->Add(h_dimulog1,h_dimulog12,1,1);
// draw histogram
//h_dimulog5->SetFillColor(5); // yellow
//h_dimulog5->GetXaxis()->SetTitle("Invariant Log10(Mass) for Nmuon>=2 (in log10(m/GeV/c^2))");
//h_dimulog5->GetYaxis()->SetTitle("Number of Events/10 MeV");
//h_dimulog5->SetMinimum(0.02);
//h_dimulog5->SetMaximum(3.E6);
//h_dimulog5->Draw("hist");
h_dimulog9->SetTitle("Dimuon mass spectrum 2011 7 TeV (1.2 fb-1)");  // set histogram title
h_dimulog9->SetFillColor(8); // Green
h_dimulog9->GetXaxis()->SetTitle("Invariant Log10(Mass) for Nmuon>=2 (in log10(m/GeV/c^2))");
h_dimulog9->GetYaxis()->SetTitle("Number of Events/10 MeV");
h_dimulog9->SetMinimum(0.02);
h_dimulog9->SetMaximum(3.E6);
h_dimulog9->Draw("hist");
// draw others on top
//h_dimulog9->Draw("hist same");
h_dimulog10->SetFillColor(29); // blue_green
h_dimulog10->Draw("hist same");
h_dimulog13->SetFillColor(9); // dark blue
h_dimulog13->Draw("hist same");
h_dimulog11->SetFillColor(2); // red
h_dimulog11->Draw("hist same");
h_dimulog3->SetFillColor(38); // dark grey
h_dimulog3->Draw("hist same");
h_dimulog1->SetFillColor(18); // light grey
h_dimulog1->Draw("hist same");
// regenerate ticks 
gPad->RedrawAxis();
//
// produce output picture file 
c1->Print("Dimuon2011_eospublic.png");
// write out histograms (will delete previous file, if any!)
TFile Dimuon2011("Dimuon2011_eospublic.root","RECREATE"); 
h_dimulog1->Write();
h_dimulog2->Write();
h_dimulog3->Write();
h_dimulog4->Write();
h_dimulog5->Write();
h_dimulog6->Write();
h_dimulog7->Write();
h_dimulog8->Write();
h_dimulog9->Write();
h_dimulog10->Write();
h_dimulog11->Write();
h_dimulog12->Write();
h_dimulog13->Write();
// output root file will be closed automatically when session is closed
//
// the closing parenthesis is important!
}
