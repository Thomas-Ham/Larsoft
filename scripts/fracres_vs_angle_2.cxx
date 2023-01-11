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

void fracres_vs_angle_2(){

// get file
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/hit_variables_1.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2_oldmethod.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH2D *h_frac_res_vs_thetaXZ       = new TH2D("frac_res_vs_thetaXZ","",50,-70,70,50,-0.3,0.3);
TH2D *h_frac_res_vs_thetaXZ_showering_particle       = new TH2D("frac_res_vs_thetaXZ_showering_particle","",50,-70,70,50,-0.5,0);


std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;
std::vector<double> *reco_hit_charge_vec = 0;
std::vector<double> *reco_hit_goodness_of_fit_vec = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);

int n = 2000;

int counter{0};

for(int i = 0; i < t_truth->GetEntries(); i++){
//for(int i = 0; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    double true_hit_energy{0};
    double true_thetaXZ = t_truth->GetLeaf("thetaXZ")->GetValue();
    

    for(int j = 0; j < t_reco->GetEntries(); j++){
    //for(int j = 0; j < n; j++){
        t_reco->GetEntry(j);
        //get the variables we want
        double reco_subrun = t_reco->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco->GetLeaf("numhits")->GetValue();
        double reco_energy = t_reco->GetLeaf("energy")->GetValue();
        double reco_hit_energy{0};
      
        if(true_subrun == reco_subrun && 
           true_event == reco_event){

          for(auto k = 0; k < true_hit_energy_vec->size(); k++){
            //if(reco_hit_charge_vec->at(k) < 10E3 && true_thetaXZ > 80 && true_thetaXZ < 100){
              //std::cout << (reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k) << std::endl;}
            //if(reco_hit_charge_vec->at(k) < 20E3 && true_thetaXZ < -80 && true_thetaXZ > -100){continue;}
            //if(reco_hit_goodness_of_fit_vec->at(k) == -1 || reco_hit_goodness_of_fit_vec->at(k) > 1.5 || reco_hit_goodness_of_fit_vec->at(k) < 0.5){continue;}
            //h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
            //h_frac_res_vs_thetaYZ->Fill(true_thetaYZ, (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
            true_hit_energy += true_hit_energy_vec->at(k);   
            reco_hit_energy += reco_hit_energy_vec->at(k);   
            //h_energy_vs_chi2->Fill(reco_hit_energy_vec->at(k), reco_hit_goodness_of_fit_vec->at(k));
          
            //h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
           
          }

          h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_hit_energy-true_hit_energy)/true_hit_energy);
          h_frac_res_vs_thetaXZ_showering_particle->Fill(true_thetaXZ, (reco_hit_energy-true_energy)/true_energy);

                   
          break;
        }
    }
}

TLine *nom_line = new TLine(-70,0,70,0);

// plot resolution as function of thetaXZ 
TCanvas *c_thetaXZ = new TCanvas("");  
h_frac_res_vs_thetaXZ->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");
h_frac_res_vs_thetaXZ->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_thetaXZ->Draw("colz");

TCanvas *c_profile = new TCanvas("");  
c_profile->SetLeftMargin(0.12);
h_frac_res_vs_thetaXZ->ProfileX("hits",1,-1,"s")->SetLineWidth(2);
h_frac_res_vs_thetaXZ->ProfileX("hits",1,-1,"s")->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_thetaXZ->ProfileX("hits",1,-1,"s")->GetYaxis()->SetRangeUser(-0.15,0.15);
h_frac_res_vs_thetaXZ->ProfileX("hits",1,-1,"s")->Draw();
nom_line->Draw("same");

TCanvas *c_thetaXZ_showering_particle = new TCanvas("");  
c_thetaXZ_showering_particle->SetLeftMargin(0.12);
h_frac_res_vs_thetaXZ_showering_particle->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");
h_frac_res_vs_thetaXZ_showering_particle->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_thetaXZ_showering_particle->Draw("colz");

TCanvas *c_profile_showering_particle = new TCanvas("");  
c_profile_showering_particle->SetLeftMargin(0.12);
h_frac_res_vs_thetaXZ_showering_particle->ProfileX("showeringE",1,-1,"s")->SetLineWidth(2);
h_frac_res_vs_thetaXZ_showering_particle->ProfileX("showeringE",1,-1,"s")->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_thetaXZ_showering_particle->ProfileX("showeringE",1,-1,"s")->GetYaxis()->SetRangeUser(-0.35,0.05);
h_frac_res_vs_thetaXZ_showering_particle->ProfileX("showeringE",1,-1,"s")->Draw();
nom_line->Draw("same");

}







