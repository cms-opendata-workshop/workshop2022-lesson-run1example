// This macro is use to convert nanoAOD(plus) ntuple to histograms
// that can be compared to Open Data 2010 MuMonitor validation plots
// Usage: root -l MuHistos_eospublic.cxx++

#include <iostream>
#include <iomanip>
#include "TH1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "stdlib.h" 
#include "TStyle.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TFile.h"
#include "string.h"
#include "TChain.h"
#include "TTree.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TBufferFile.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"

void MuHistos_eospublic() {
  
  TH1::SetDefaultSumw2(true);

  gROOT->Reset();
  gStyle->SetOptStat("nemruo");

  // Chain your tree
  TChain *t1 = new TChain("Events");
  
  string inDir = "root://eospublic.cern.ch//eos/opendata/cms/upload/NanoAODRun1/01-Jul-22/";

  // Muon 2010 ntuples
  string infile = "Run2010B_Mu_merged.root";      // version NanoAODRun1_v1

  t1->Add((inDir + infile).c_str());

  // MuMonitor validation example with Muon 2010 dataset
  string outfile = "MuHistos_Mu_eospublic.root";              // version NanoAODRun1_v1

  TFile fout((outfile).c_str(),"RECREATE");

  cout << "reading " << inDir << infile << endl;
  cout << "writing to " << outfile << endl;

////////////////////////////////////////////////////////////////////////////////
///////////////////////// Declare input variables start ////////////////////////
////////////////////////////////////////////////////////////////////////////////
  
  // Variables in the tree
  UInt_t run;
  ULong64_t event;  // use this for newer versions starting from .zerobias
  UInt_t luminosityBlock;
  UInt_t nMuon;
  // should replace 128 by parameter; check whether value is appropriate!
  Float_t Muon_mass[128];
  Float_t Muon_pt[128];
  Float_t Muon_gpt[128];
  Float_t Muon_eta[128];
  Float_t Muon_geta[128];
  Float_t Muon_phi[128];
  Float_t Muon_gphi[128]; 
  Float_t Muon_gChi2[128];
  Int_t Muon_charge[128];
  Bool_t Muon_isTracker[128];
  Bool_t Muon_isGlobal[128];
  Int_t Muon_nValid[128];
  Int_t Muon_gnValid[128];  
  Int_t Muon_gnValidMu[128];  // was nValidMu; documentation says "bug", check!
  Int_t Muon_nPix[128];
  Int_t Muon_gnPix[128];

  // Variables defined in this code
  UInt_t nGlobal;
  TLorentzVector p4mu1, p4mu2, p4dimu;
  TLorentzVector p4gmu1, p4gmu2, p4gdimu;
  Float_t Muon_p1, Muon_p2, Muon_gp1, Muon_gp2; 
  Float_t s, w;
  
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Declare input variables end ////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// Activate branches start ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  // Disable all branches
  t1->SetBranchStatus("*", 0);

  // Read only selected branches
  t1->SetBranchStatus("run", 1);
  t1->SetBranchStatus("event", 1);
  t1->SetBranchStatus("luminosityBlock", 1);
  t1->SetBranchStatus("nMuon", 1);
  t1->SetBranchStatus("Muon_mass", 1);
  t1->SetBranchStatus("Muon_pt", 1);
  t1->SetBranchStatus("Muon_gpt", 1);
  t1->SetBranchStatus("Muon_eta", 1);
  t1->SetBranchStatus("Muon_geta", 1);
  t1->SetBranchStatus("Muon_phi", 1);
  t1->SetBranchStatus("Muon_gphi", 1);
  t1->SetBranchStatus("Muon_gChi2", 1);
  t1->SetBranchStatus("Muon_charge", 1);
  t1->SetBranchStatus("Muon_isTracker", 1);
  t1->SetBranchStatus("Muon_isGlobal", 1);
  t1->SetBranchStatus("Muon_nValid", 1);
  t1->SetBranchStatus("Muon_gnValid", 1);
  t1->SetBranchStatus("Muon_gnValidMu", 1);
  t1->SetBranchStatus("Muon_nPix", 1);
  t1->SetBranchStatus("Muon_gnPix", 1);

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Activate branches end ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////// Get the address of the branch start /////////////////////
////////////////////////////////////////////////////////////////////////////////

  t1->SetBranchAddress("run", &run);
  t1->SetBranchAddress("event", &event);
  t1->SetBranchAddress("luminosityBlock", &luminosityBlock);
  t1->SetBranchAddress("nMuon", &nMuon);
  t1->SetBranchAddress("Muon_mass", Muon_mass);
  t1->SetBranchAddress("Muon_pt", Muon_pt);
  t1->SetBranchAddress("Muon_gpt", Muon_gpt);
  t1->SetBranchAddress("Muon_eta", Muon_eta);
  t1->SetBranchAddress("Muon_geta", Muon_geta);
  t1->SetBranchAddress("Muon_phi", Muon_phi);
  t1->SetBranchAddress("Muon_gphi", Muon_gphi);
  t1->SetBranchAddress("Muon_gChi2", Muon_gChi2);
  t1->SetBranchAddress("Muon_charge", Muon_charge);
  t1->SetBranchAddress("Muon_isTracker", Muon_isTracker);  
  t1->SetBranchAddress("Muon_isGlobal", Muon_isGlobal);
  t1->SetBranchAddress("Muon_nValid", Muon_nValid);
  t1->SetBranchAddress("Muon_gnValid", Muon_gnValid);
  t1->SetBranchAddress("Muon_gnValidMu", Muon_gnValidMu); 
  t1->SetBranchAddress("Muon_nPix", Muon_nPix);
  t1->SetBranchAddress("Muon_gnPix", Muon_gnPix); 

////////////////////////////////////////////////////////////////////////////////
/////////////////////// Get the address of the branch end //////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///////////////////////// Declare your histogram start /////////////////////////
////////////////////////////////////////////////////////////////////////////////
  
  // run nr, event nr, and lumi section for all events that have been analyzed
  TH1D *GM_run = new TH1D("Run number", "Run number", 3100, 146400, 149500);
  TH1D *GM_event = new TH1D("Event number", "Event number", 2000, 0, 2000000000);
  TH1D *GM_luminosityBlock = new TH1D("Lumi section", "Lumi section", 300, 0, 3000);
  
  // global muon multiplicity
  TH1D *GM_multiplicity = new TH1D("GMmultiplicty", "GMmultiplicty", 8, 0, 8);
  GM_multiplicity->GetXaxis()->SetTitle("Number of Global Muons");
  GM_multiplicity->GetYaxis()->SetTitle("Number of Events");

  // global muon momentum
  TH1D *GM_momentum = new TH1D("GMmomentum", "GMmomentum", 240, 0., 120.);
  GM_momentum->GetXaxis()->SetTitle("Momentum of global muons (in GeV/c)");
  GM_momentum->GetYaxis()->SetTitle("Number of Events");

  // global muon transverse momentum
  TH1D *GM_transverse_momentum = new TH1D("GM_Transverse_momentum", "GM_Transverse_momentum", 240, 0., 120.);
  GM_transverse_momentum->GetXaxis()->SetTitle("Transverse Momentum of global muons (in GeV/c)");
  GM_transverse_momentum->GetYaxis()->SetTitle("Number of Events");

  // global muon pseudorapity
  TH1D *GM_eta = new TH1D("GM_eta", "GM_eta", 140, -3.5, 3.5);
  GM_eta->GetXaxis()->SetTitle("Eta of global muons (in radians)");
  GM_eta->GetYaxis()->SetTitle("Number of Events");

  // global muon azimuth angle
  TH1D *GM_phi = new TH1D("GM_phi", "GM_phi", 314, -3.15, 3.15);
  GM_phi->GetXaxis()->SetTitle("Phi of global muons (in radians)");
  GM_phi->GetYaxis()->SetTitle("Number of Events");

  // global muon normalized chi2
  TH1D *GM_chi2 = new TH1D("GM_normalizedchi2", "GM_normalizedchi2", 200, 0., 20.);
  GM_chi2->GetXaxis()->SetTitle("chi2 / ndof of global muons");
  GM_chi2->GetYaxis()->SetTitle("Number of Events");

  // dimuon mass spectrum up to 120 GeV (high mass range: upsilon, Z)
  TH1D *GM_mass_extended = new TH1D("GMmass_extended", "GMmass_extended", 240, 0., 120.);
  GM_mass_extended->GetXaxis()->SetTitle("Invariant Mass for Nmuon>=2 (in GeV/c^2)");
  GM_mass_extended->GetYaxis()->SetTitle("Number of Events");
  
  // dimuon mass spectrum up to 4 GeV (low mass range, rho/omega, phi, psi)
  TH1D *GM_mass = new TH1D("GMmass", "GMmass", 400, 0., 4.);
  GM_mass->GetXaxis()->SetTitle("Invariant Mass for Nmuon>=2 (in GeV/c^2)");
  GM_mass->GetYaxis()->SetTitle("Number of Events");

  // logarithmic dimuon mass spectrum, 
  // binning chosen to correspond to log(0.3) - log(500), 200 bins/log10 unit
  TH1D *GM_mass_log = new TH1D("GM_mass_log", "GM_mass_log", 644, -0.52, 2.7);
  GM_mass_log->GetXaxis()->SetTitle("Invariant Log10(Mass) for Nmuon>=2 (in log10(m/GeV/c^2))");
  GM_mass_log->GetYaxis()->SetTitle("Number of Events/GeV");

  // global muon track, number of valid hits
  TH1D *GM_validhits = new TH1D("GM_validhits", "GM_validhits", 100, 0., 100);
  GM_validhits->GetXaxis()->SetTitle("Number of valid hits");
  GM_validhits->GetYaxis()->SetTitle("Number of Events");

  // global muon track, number of pixel hits
  TH1D *GM_pixelhits = new TH1D("GM_pixelhits", "GM_pixelhits", 14, 0., 14);
  GM_pixelhits->GetXaxis()->SetTitle("Number of pixel hits");
  GM_pixelhits->GetYaxis()->SetTitle("Number of Events");
  
////////////////////////////////////////////////////////////////////////////////
////////////////////////// Declare your histogram end //////////////////////////
////////////////////////////////////////////////////////////////////////////////
  
  Int_t nevent = t1->GetEntries();
  cout << "entries = " << nevent << endl;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Start analyze! //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  
  // Loop over all events
  for (int aa = 0; aa < nevent; aa++) {
 
    if (aa % 1000000 == 0) cout << "event nr " << aa << endl;

    // Get the entry of your event
    t1->GetEntry(aa);

    // fill histograms
    GM_run->Fill(run);
    GM_event->Fill(event);
    GM_luminosityBlock->Fill(luminosityBlock);

    nGlobal = 0;  // global muon counter

    // Loop over nMuon for single muon variables and dimuon mass plot
    for (unsigned int bb = 0; bb < nMuon; bb++) {

      if (!Muon_isGlobal[bb]) continue;
      
      nGlobal++;

      p4gmu1.SetPtEtaPhiM(Muon_gpt[bb], Muon_geta[bb], Muon_gphi[bb], Muon_mass[bb]);
      Muon_gp1 = p4gmu1.P();
      
      // Fill the histogram
      GM_momentum->Fill(Muon_gp1);
      GM_transverse_momentum->Fill(Muon_gpt[bb]);
      GM_eta->Fill(Muon_geta[bb]);
      GM_phi->Fill(Muon_gphi[bb]);
      GM_chi2->Fill(Muon_gChi2[bb]);
      GM_validhits->Fill(Muon_gnValid[bb] + Muon_gnValidMu[bb]);
      GM_pixelhits->Fill(Muon_gnPix[bb]);

      if (nMuon < 2) continue;

      // quality cuts
      if (Muon_gnValid[bb] + Muon_gnValidMu[bb] < 12 
        || Muon_gnPix[bb] < 2
        || Muon_gChi2[bb] >= 4.0) continue;

      // loop over second muon to calculate dimuon invariant mass
      for (unsigned int cc = bb + 1 ; cc < nMuon; cc++) {

        if (!Muon_isGlobal[cc]) continue;
        if (Muon_charge[bb] + Muon_charge[cc] != 0) continue;

        // quality cuts
        if (Muon_gnValid[cc] + Muon_gnValidMu[cc] < 12 
          || Muon_gnPix[cc] < 2
          || Muon_gChi2[cc] >= 4.0) continue;

        p4gmu2.SetPtEtaPhiM(Muon_gpt[cc], Muon_geta[cc], Muon_gphi[cc], Muon_mass[cc]);
        Muon_gp2 = p4gmu2.P();

        // calculate dimuon invariant mass
        p4gdimu = p4gmu1 + p4gmu2;
        s = p4gdimu.M();
        w = 200 / log(10) / s;

        GM_mass_extended->Fill(s);
        GM_mass->Fill(s);
        GM_mass_log->Fill(log10(s), w);

      } // end of loop over second muon
    } // end of loop over first muon

    GM_multiplicity->Fill(nGlobal);

  } // end of loop over all events

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// End analyze! ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  
////////////////////////////////////////////////////////////////////////////////
//////////////////////// write histograms and close file ///////////////////////
////////////////////////////////////////////////////////////////////////////////
  
  // Write out the histograms
  GM_run->Write();
  GM_event->Write();
  GM_luminosityBlock->Write();
  GM_multiplicity->Write(); 
  GM_momentum->Write();
  GM_transverse_momentum->Write();
  GM_eta->Write();
  GM_phi->Write(); 
  GM_chi2->Write(); 
  GM_mass_extended->Write();
  GM_mass->Write();
  GM_mass_log->Write();
  GM_validhits->Write();
  GM_pixelhits->Write();
 
  fout.Close();

  gROOT->ProcessLine(".q");

} // end of script

