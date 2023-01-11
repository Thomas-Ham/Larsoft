#include <iostream>
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TF1.h"
#include "TGraph.h"
#include "TStyle.h"
#include <tuple>
#include <vector>

void trackIDE(){

// get file
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_norollup.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_norollup_fixed2.root","read");
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/srcs/sbndcode/sbndcode/lowEelectron/low_energy_electron__no_rollup_no_noise_no_roi_reco.list","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH1D *h_electrons_per_hit = new TH1D("electrons_per_hit","",9,1,10);
TH1D *h_electron_contribution = new TH1D("electron_contribution","",100,0,1.001);
TH1D *h_electron_contribution_cut = new TH1D("electron_contribution_cut","",100,0,1.001);
TH1D *h_resolution_1_electron = new TH1D("resolution_1_electron","",50,-1,1);
TH1D *h_resolution_more_than_1_electron = new TH1D("resolution_more_than_1_electron","",50,-1,1);
TH1D *h_resolution_more_than_7_electron = new TH1D("resolution_more_than_7_electron","",50,-1,1);

TH2D *h_electrons_per_hit_vs_energy = new TH2D("electrons_per_hit_vs_energy","",9,1,10,20,0,10);
TH2D *h_electrons_per_hit_vs_resolution = new TH2D("electrons_per_hit_vs_resolution","",9,1,10,50,-3,3);

std::vector<double> *reco_hit_energy_vec = 0;
std::vector<double> *true_hit_energy_vec = 0;
std::vector<std::vector<double>> *true_trackide_id_vec = 0;
std::vector<std::vector<double>> *true_trackide_energy_vec = 0;
std::vector<std::vector<double>> *true_trackide_energyfrac_vec = 0;

TBranch *breco_hit_energy = 0;
TBranch *btrue_hit_energy = 0;
TBranch *btrue_trackide_id = 0;
TBranch *btrue_trackide_energy = 0;
TBranch *btrue_trackide_energyfrac = 0;
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_truth->SetBranchAddress("trackide_id",&true_trackide_id_vec,&btrue_trackide_id);
t_truth->SetBranchAddress("trackide_energy",&true_trackide_energy_vec,&btrue_trackide_energy);
t_truth->SetBranchAddress("trackide_energyfrac",&true_trackide_energyfrac_vec,&btrue_trackide_energyfrac);

int n = 200;

//t_reco->GetEntry(0);
//t_truth->GetEntry(0);
//std::cout << true_hit_energy_vec->size() << std::endl;
//std::cout << true_trackide_id_vec->size() << std::endl;


// loop over truth branch
for(int i = 0; i < t_truth->GetEntries(); i++){
//for(int i = 0; i < n; i++){
  t_truth->GetEntry(i);

  // vector to save the number of electrons per hit
  std::vector<int> electrons_per_hit_vec;
  // Get the event
  double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
  double true_event  = t_truth->GetLeaf("event")->GetValue();

  // Get the contribution of the dominant electron in each hit
  for (const auto& hits : *true_trackide_energyfrac_vec){
    double max_cont = 0;
    double max_cont_2 = 0;
    std::cout << "hit:   ";
    for (const auto& electrons : hits){
      if(electrons > max_cont){
        max_cont = electrons;
      }
      if(electrons > max_cont_2 && electrons < 1){
        max_cont_2 = electrons;
      }
    }
    std::cout << max_cont_2 << std::endl;
    h_electron_contribution->Fill(max_cont);
    if(max_cont_2 > 0){
      h_electron_contribution_cut->Fill(max_cont_2);     
    }
  }

  // Get the number of electrons per hit
  // and get the number of electrons per hit vs energy
  for (const auto& hits : *true_trackide_energy_vec){
    //std::cout << "hit \"ID\": " << i[0];
    int electrons_per_hit = 0;
    double hit_energy = 0;
    for (const auto& electrons : hits){
      //std::cout << "   electron in hit ID :  "  << j << "  ";
      ++electrons_per_hit;
      hit_energy += electrons;
    }
    //std::cout << std::endl;
    //std::cout << "   e per hit: "  << electrons_per_hit << "  hitE: " << hit_energy <<  std::endl;
    electrons_per_hit_vec.push_back(electrons_per_hit);
    h_electrons_per_hit->Fill(electrons_per_hit);
    h_electrons_per_hit_vs_energy->Fill(electrons_per_hit, hit_energy);
  }
  // loop over reco branch
  for(int j = 0; j < t_reco->GetEntries(); j++){
  //for(int j = 0; j < n; j++){
    t_reco->GetEntry(j);
    // Get the event
    double reco_subrun = t_reco->GetLeaf("subrun")->GetValue();
    double reco_event  = t_reco->GetLeaf("event")->GetValue();

    // make sure we're looking at the same true and reco event
    if(true_subrun == reco_subrun && 
       true_event == reco_event &&
       reco_hit_energy_vec->size() == true_hit_energy_vec->size()){
   
      
      for(auto k = 0; k < reco_hit_energy_vec->size(); k++){
        
        double reco_hit_energy = reco_hit_energy_vec->at(k);
        double true_hit_energy = true_hit_energy_vec->at(k);
        double frac_res = (reco_hit_energy - true_hit_energy) / true_hit_energy;
  
        h_electrons_per_hit_vs_resolution->Fill(electrons_per_hit_vec[k], frac_res);

        // 1D resolution plots for X number of electrons per hit
        if(electrons_per_hit_vec[k] == 1){
          h_resolution_1_electron->Fill(frac_res);
        }
         if(electrons_per_hit_vec[k] > 1){
          h_resolution_more_than_1_electron->Fill(frac_res);
        }
         if(electrons_per_hit_vec[k] > 7){
          h_resolution_more_than_7_electron->Fill(frac_res);
        }
      }
    }
  } // reco branch
} // truth branch




TCanvas *c_electrons_per_hit = new TCanvas("");  
//h_true_vs_reco->Scale(1/h_true_vs_reco->Integral());
h_electrons_per_hit->SetLineWidth(3);
h_electrons_per_hit->GetXaxis()->SetTitle("Electrons per hit");
h_electrons_per_hit->Draw();


TCanvas *c_electron_contribution = new TCanvas("");  
//h_true_vs_reco->Scale(1/h_true_vs_reco->Integral());
//h_electron_contribution->SetLineWidth(3);
h_electron_contribution_cut->GetXaxis()->SetTitle("Energy contribution from dominante electron");
h_electron_contribution->Draw();
h_electron_contribution_cut->SetLineColor(kRed);
h_electron_contribution_cut->SetLineWidth(2);
h_electron_contribution_cut->Draw("same");

TLegend *leg = new TLegend();
leg->AddEntry(h_electron_contribution, "1 or more electron per hit", "L");
leg->AddEntry(h_electron_contribution_cut, "more than 1 electron per hit", "L");
leg->SetBorderSize(0);
leg->Draw();


TCanvas *c_electrons_per_hit_vs_energy = new TCanvas(); 

//c_electrons_per_hit_vs_energy->Divide(2,1);

//c_electrons_per_hit_vs_energy->cd(1);
h_electrons_per_hit_vs_energy->SetLineWidth(3);
h_electrons_per_hit_vs_energy->GetYaxis()->SetTitle("Hit Energy [MeV]");
h_electrons_per_hit_vs_energy->GetXaxis()->SetTitle("Electrons per hit");
h_electrons_per_hit_vs_energy->Draw("colz");

TCanvas *c_electrons_per_hit_vs_energy_profile = new TCanvas(); 

//c_electrons_per_hit_vs_energy->cd(2);
h_electrons_per_hit_vs_energy->ProfileX("energy",1,-1,"s")->SetLineWidth(2);
h_electrons_per_hit_vs_energy->ProfileX("energy",1,-1,"s")->GetXaxis()->SetTitle("Electrons per hit");
h_electrons_per_hit_vs_energy->ProfileX("energy",1,-1,"s")->GetYaxis()->SetTitle("Hit Energy [MeV]");
h_electrons_per_hit_vs_energy->ProfileX("energy",1,-1,"s")->Draw();


TCanvas *c_electrons_per_hit_vs_resolution = new TCanvas("");  
//c_electrons_per_hit_vs_resolution->Divide(2,1);

//c_electrons_per_hit_vs_resolution->cd(1);
h_electrons_per_hit_vs_resolution->SetLineWidth(3);
h_electrons_per_hit_vs_resolution->GetYaxis()->SetTitle("#frac{Reco-True}{True} [MeV]");
h_electrons_per_hit_vs_resolution->GetXaxis()->SetTitle("Electrons per hit");
h_electrons_per_hit_vs_resolution->Draw("colz");

TCanvas *c_electrons_per_hit_vs_resolution_profile = new TCanvas("");  
//c_electrons_per_hit_vs_resolution->cd(2);
h_electrons_per_hit_vs_resolution->ProfileX("resolution",1,-1,"s")->SetLineWidth(2);
h_electrons_per_hit_vs_resolution->ProfileX("resolution",1,-1,"s")->GetXaxis()->SetTitle("Electrons per hit");
h_electrons_per_hit_vs_resolution->ProfileX("resolution",1,-1,"s")->GetYaxis()->SetTitle("#frac{Reco-True}{True} [MeV]");
h_electrons_per_hit_vs_resolution->ProfileX("resolution",1,-1,"s")->GetYaxis()->SetTitleOffset(1.2);
h_electrons_per_hit_vs_resolution->ProfileX("resolution",1,-1,"s")->Draw();

/*
TLegend *leg = new TLegend(0.15, 0.7, 0.3, 0.8);
leg->AddEntry(line, "y = x", "L");
leg->SetBorderSize(0);
leg->Draw();
*/

TCanvas *c_resolution = new TCanvas("");  
h_resolution_1_electron->Scale(1/h_resolution_1_electron->Integral());
h_resolution_1_electron->SetLineColor(kBlack);
h_resolution_1_electron->SetLineWidth(3);
h_resolution_1_electron->GetXaxis()->SetTitle("#frac{Reco - True}{True} [MeV]");
h_resolution_1_electron->Draw("histE");

h_resolution_more_than_1_electron->Scale(1/h_resolution_more_than_1_electron->Integral());
h_resolution_more_than_1_electron->SetLineColor(kOrange);
h_resolution_more_than_1_electron->SetLineWidth(3);
h_resolution_more_than_1_electron->Draw("histE,same");

h_resolution_more_than_7_electron->Scale(1/h_resolution_more_than_7_electron->Integral());
h_resolution_more_than_7_electron->SetLineColor(kRed);
h_resolution_more_than_7_electron->SetLineWidth(3);
h_resolution_more_than_7_electron->Draw("histE,same");

TLegend *l_res = new TLegend();
l_res->AddEntry(h_resolution_1_electron, "1 electron per hit", "L");
l_res->AddEntry(h_resolution_more_than_1_electron, "> 1 electron per hit", "L");
l_res->AddEntry(h_resolution_more_than_7_electron, "> 7 electron per hit", "L");
l_res->Draw("same");


}







