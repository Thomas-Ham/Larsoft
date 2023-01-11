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

void fracres_vs_energy_2(){

// get file
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_oldmethod.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH2D *h_frac_res_vs_hit_energy       = new TH2D("frac_res_vs_hit_energy","",25,20,1100,25,-0.3,0.3);
//TH2D *h_frac_res_vs_hit_energy       = new TH2D("frac_res_vs_hit_energy","",50,50,1100,25,-0.3,0.3);
TH2D *h_frac_res_vs_showering_energy = new TH2D("frac_res_vs_showering_energy","",25,20,1100,25,-1,0.3);

std::vector<double> *true_hit_energy_vec = 0;

TBranch *btrue_hit_energy = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);

int n = 2000;

for(int i = 0; i < t_truth->GetEntries(); i++){
//for(int i = 0; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    double true_hit_energy{0};
    for(auto k = 0; k < true_hit_energy_vec->size(); k++){
      true_hit_energy += true_hit_energy_vec->at(k);
    }

    for(int j = 0; j < t_reco->GetEntries(); j++){
    //for(int j = 0; j < n; j++){
        t_reco->GetEntry(j);
        //get the variables we want
        double reco_subrun = t_reco->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco->GetLeaf("numhits")->GetValue();
        double reco_energy = t_reco->GetLeaf("energy")->GetValue();

        if(true_subrun == reco_subrun && 
           true_event == reco_event) {

          h_frac_res_vs_hit_energy->Fill(true_hit_energy, (reco_energy-true_hit_energy)/true_hit_energy);
          h_frac_res_vs_showering_energy->Fill(true_energy, (reco_energy-true_energy)/true_energy);

          break;
        }
    }
}


TCanvas *c = new TCanvas("");  


h_frac_res_vs_hit_energy->GetXaxis()->SetTitle("Energy [MeV]");
h_frac_res_vs_hit_energy->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_hit_energy->Draw("colz");

TCanvas *c_profile = new TCanvas("");  
c_profile->SetLeftMargin(0.12);
h_frac_res_vs_hit_energy->ProfileX("a",1,-1,"s")->SetLineWidth(2);
h_frac_res_vs_hit_energy->ProfileX("a",1,-1,"s")->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_hit_energy->ProfileX("a",1,-1,"s")->Draw();


TCanvas *c2 = new TCanvas("");  

h_frac_res_vs_showering_energy->GetXaxis()->SetTitle("Energy [MeV]");
h_frac_res_vs_showering_energy->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_showering_energy->Draw("colz");

TCanvas *c2_profile = new TCanvas(""); 
c2_profile->SetLeftMargin(0.12);
h_frac_res_vs_showering_energy->ProfileX("b",1,-1,"s")->SetLineWidth(2);
h_frac_res_vs_showering_energy->ProfileX("b",1,-1,"s")->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_showering_energy->ProfileX("b",1,-1,"s")->Draw();


/*
std::cout << h_frac_res_vs_energy->Integral() << std::endl;
//h_frac_res_vs_energy->Scale(1/h_frac_res->Integral());
h_frac_res_vs_energy->SetLineWidth(3);
h_frac_res_vs_energy->GetYaxis()->SetTitleSize(0.035);
h_frac_res_vs_energy->GetXaxis()->SetTitleOffset(1.75);
h_frac_res_vs_energy->GetXaxis()->SetTitleSize(0.025);
h_frac_res_vs_energy->GetYaxis()->SetTitle("Normalised Events");
h_frac_res_vs_energy->GetXaxis()->SetTitle("#frac{True - Reco}{True} [Energy]");
h_frac_res_vs_energy->Draw("histE");
*/

TLegend *leg = new TLegend();
//leg->SetHeader("True Hit Energy", "C");
leg->SetBorderSize(0);
//leg->Draw();


}







