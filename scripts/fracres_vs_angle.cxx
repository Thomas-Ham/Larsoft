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

void fracres_vs_angle(){

// get file
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/hit_variables_1.root","read");
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2_oldmethod.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

//TH2D *h_frac_res_vs_thetaXZ       = new TH2D("frac_res_vs_thetaXZ","",36,-180,180,50,-0.3,0.3);
//TH2D *h_frac_res_vs_thetaXZ       = new TH2D("frac_res_vs_thetaXZ","",50,-70,70,50,-0.3,0.3);
TH2D *h_frac_res_vs_thetaXZ       = new TH2D("frac_res_vs_thetaXZ","",1000,-180,180,50,-0.3,0.3);
TH2D *h_frac_res_vs_thetaYZ       = new TH2D("frac_res_vs_thetaYZ","",100,-180,180,50,-0.3,0.3);

TH2D *h_energy_vs_chi2            = new TH2D("energy_vs_chi2","",20,0,50,22,-500,5000);

TProfile *profile                 = new TProfile("p","",100,-180, 180, -1.5, 1.5);
TProfile *profile_w               = new TProfile("p_w","",100,-180, 180, -1.5, 1.5);

std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;
std::vector<double> *reco_hit_charge_vec = 0;
std::vector<double> *reco_hit_goodness_of_fit_vec = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
TBranch *breco_hit_charge = 0;
TBranch *breco_hit_goodness_of_fit = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);
t_reco->SetBranchAddress("hit_charge",&reco_hit_charge_vec,&breco_hit_charge);
t_reco->SetBranchAddress("hit_goodness_of_fit",&reco_hit_goodness_of_fit_vec,&breco_hit_goodness_of_fit);

int n = 1000;

int counter{0};

int nintydeg{0}; int nintyhits{0}; 
int seventydeg{0}; int seventyhits{0};
//for(int i = 0; i < t_truth->GetEntries(); i++){
for(int i = 0; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    double true_hit_energy{0};
    double true_thetaXZ = t_truth->GetLeaf("thetaXZ")->GetValue();
    double true_thetaYZ = t_truth->GetLeaf("thetaYZ")->GetValue();
    
    //for(auto k = 0; k < true_hit_energy_vec->size(); k++){
      //true_hit_energy += true_hit_energy_vec->at(k);
    //}

    //for(int j = 0; j < t_reco->GetEntries(); j++){
    for(int j = 0; j < n; j++){
        t_reco->GetEntry(j);
        //get the variables we want
        double reco_subrun = t_reco->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco->GetLeaf("numhits")->GetValue();
        double reco_energy = t_reco->GetLeaf("energy")->GetValue();
        double reco_hit_energy{0};
        double reco_hit_goodness_of_fit{0};
      
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
            ++counter;
            //h_energy_vs_chi2->Fill(reco_hit_energy_vec->at(k), reco_hit_goodness_of_fit_vec->at(k));
           
            //h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
            //profile_w->Fill(true_thetaXZ, ((reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k))*true_hit_energy_vec->at(k));
          
          }

          h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_hit_energy-true_energy)/true_energy);
          h_frac_res_vs_thetaYZ->Fill(true_thetaYZ, (reco_hit_energy-true_hit_energy)/true_hit_energy);

          profile->Fill(true_thetaXZ, (reco_hit_energy-true_hit_energy)/true_hit_energy);
                   
          if(true_thetaXZ > 87 && true_thetaXZ < 93){
            std::cout << "subrun: "<< true_subrun << std::endl;
            std::cout << "event: " << true_event << std::endl;
            std::cout << "theta: " << true_thetaXZ << std::endl;
            std::cout << "Tot E: " << true_energy << "   Hit E: " << true_hit_energy << "   Reco E: " << reco_energy << std::endl;
            std::cout << "res: " << (reco_energy-true_hit_energy)/true_hit_energy << std::endl;
            nintydeg++;
            nintyhits += reco_hits;
          }
          /*
          if(true_thetaXZ > -3 && true_thetaXZ < 3) {
            std::cout << "subrun: "<< true_subrun << std::endl;
            std::cout << "event: " << true_event << std::endl;
            std::cout << "theta: " << true_thetaXZ << std::endl;
            std::cout << "Tot E: " << true_energy << "   Hit E: " << true_hit_energy << "   Reco E: " << reco_energy <<  std::endl;
            std::cout << "res: " << (reco_energy-true_hit_energy)/true_hit_energy << std::endl;
            seventydeg++;
            seventyhits += reco_hits;
          }
          */   

          break;
        }
    }
}

//std::cout << "90 hits: " << nintyhits/nintydeg << std::endl;
//std::cout << "70 hits: " << seventyhits/seventydeg << std::endl;

std::cout << "counter: " << counter << std::endl;

// plot resolution as function of thetaXZ and thetaYZ
TCanvas *c_thetaXZ = new TCanvas("");  
h_frac_res_vs_thetaXZ->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");
h_frac_res_vs_thetaXZ->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_thetaXZ->Draw("colz");

TCanvas *c_thetaYZ = new TCanvas("");  
h_frac_res_vs_thetaYZ->GetXaxis()->SetTitle("#theta_{YZ} [degrees]");
h_frac_res_vs_thetaYZ->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
h_frac_res_vs_thetaYZ->Draw("colz");

TCanvas *c_profile = new TCanvas("");  
profile->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");
profile->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
profile->SetLineWidth(4);
profile->Draw();
profile_w->SetLineColor(kRed);
profile_w->SetLineWidth(4);
profile_w->Draw("same");

TCanvas *c_energy_vs_chi2 = new TCanvas("");  
//c_energy_vs_chi2->SetLogy();
h_energy_vs_chi2->Draw("colz");
}







