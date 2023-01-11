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

void fracres_vs_angle_temp(){

// get file
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2.root","read");
  TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/hit_variables_1.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH2D *h_frac_res_vs_thetaXZ       = new TH2D("frac_res_vs_thetaXZ","",36,-180,180,50,-30,30);
TH2D *h_frac_res_vs_thetaYZ       = new TH2D("frac_res_vs_thetaYZ","",100,-180,180,50,-0.3,0.3);

TH1D *h_chi2_m1_hits              = new TH1D("chi2 == -1 hits","",25,-180,180);
TH1D *h_chi2_less01_hits          = new TH1D("chi2 < 0.1 hits","",25,-180,180);
TH1D *h_chi2_more100_hits         = new TH1D("chi2 > 100 hits","",25,-180,180);
TH1D *h_chi2_more1000_hits        = new TH1D("chi2 > 1000 hits","",25,-180,180);
TH1D *h_chi2_less01_res           = new TH1D("chi2 < 0.1","",50,-1,1);
TH1D *h_chi2_more100_res          = new TH1D("chi2 > 100","",50,-1,1);
TH1D *h_chi2_more1000_res         = new TH1D("chi2 > 1000","",50,-1,1);
TH1D *h_chi2_m1_res               = new TH1D("chi2 == -1","",50,-1,1);

TProfile *h_frac_E_chi_m1             = new TProfile("frac_energy_m1","",36,-180,180,0,100);
TProfile *h_frac_E_chi_1_100          = new TProfile("frac_energy_1_100","",36,-180,180,0,100);
TProfile *h_frac_E_chi_100_1000       = new TProfile("frac_energy_100_1000","",36,-180,180,0,100);
TProfile *h_frac_E_chi_more_1000      = new TProfile("100 < frac_energy < 1000","",36,-180,180,0,100);
TProfile *h_frac_E_chi_less_1         = new TProfile("frac_energy_less_1","",36,-180,180,0,100);
THStack *hs = new THStack("hs","");


TProfile *profile_hit_E_vs_chi2   = new TProfile("p","",16,-100, 1500, 0, 100);
TProfile *profile_hit_E_vs_chi2_low  = new TProfile("p_low","",16,0, 1, 0, 100);

TProfile *profile_chi2_vs_res     = new TProfile("p_res","",51,-100, 5000, -3, 3);
TProfile *profile_thetaXZ_vs_chi2 = new TProfile("p_angle_res","",20,-180, 180, -1, 5000);

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

//int n = 1000;

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
    double true_thetaYZ = t_truth->GetLeaf("thetaYZ")->GetValue();
    
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
        double reco_hit_energy{0};
        double reco_hit_goodness_of_fit{0};
      
        if(true_subrun == reco_subrun && 
           true_event == reco_event){
  
          double E_m1 = 0, E_1_100 = 0, E_100_1000 = 0, E_more_1000 = 0, E_less_1 = 0;
          //if(true_thetaXZ > 80 && true_thetaXZ < 100){
            for(auto k = 0; k < reco_hit_energy_vec->size(); k++){
              reco_hit_energy += reco_hit_energy_vec->at(k);
              if(reco_hit_goodness_of_fit_vec->at(k) == -1){
                E_m1 += reco_hit_energy_vec->at(k);
              }
              if(reco_hit_goodness_of_fit_vec->at(k) > 1 && reco_hit_goodness_of_fit_vec->at(k) < 100){
                E_1_100 += reco_hit_energy_vec->at(k);
              }
              if(reco_hit_goodness_of_fit_vec->at(k) > 100 && reco_hit_goodness_of_fit_vec->at(k) < 1000){
                E_100_1000 += reco_hit_energy_vec->at(k);
              }
              if(reco_hit_goodness_of_fit_vec->at(k) > 1000){
                E_more_1000 += reco_hit_energy_vec->at(k);
              }
              if(reco_hit_goodness_of_fit_vec->at(k) < 1 && reco_hit_goodness_of_fit_vec->at(k) > 0){
                E_less_1 += reco_hit_energy_vec->at(k);
              }
              
           //}
            //std::cout << reco_hit_goodness_of_fit_vec->at(k) << std::endl;
            //std::cout << j << " " << E_m1/reco_energy << "  " << true_thetaXZ << std::endl;
            h_frac_E_chi_m1->Fill(true_thetaXZ,(E_m1/reco_hit_energy) * 100);
            h_frac_E_chi_less_1->Fill(true_thetaXZ,(E_less_1/reco_hit_energy) * 100);
            h_frac_E_chi_1_100->Fill(true_thetaXZ,(E_1_100/reco_hit_energy) * 100);
            h_frac_E_chi_100_1000->Fill(true_thetaXZ,(E_100_1000/reco_hit_energy) * 100);
            h_frac_E_chi_more_1000->Fill(true_thetaXZ,(E_more_1000/reco_hit_energy) * 100);
          }

          h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, ((reco_hit_energy-true_hit_energy)/true_hit_energy)*100);               

          for(auto k = 0; k < true_hit_energy_vec->size(); k++){

            if(reco_hit_goodness_of_fit_vec->at(k) > 1 || reco_hit_goodness_of_fit_vec->at(k) == -1){
              profile_hit_E_vs_chi2->Fill(reco_hit_goodness_of_fit_vec->at(k), reco_hit_energy_vec->at(k));
              profile_chi2_vs_res->Fill(reco_hit_goodness_of_fit_vec->at(k), (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
            }
            if(reco_hit_goodness_of_fit_vec->at(k) < 1 && reco_hit_goodness_of_fit_vec->at(k) > 0){
              profile_hit_E_vs_chi2_low->Fill(reco_hit_goodness_of_fit_vec->at(k), reco_hit_energy_vec->at(k));
            }

            if(reco_hit_goodness_of_fit_vec->at(k) < 0.1 && reco_hit_goodness_of_fit_vec->at(k) != -1){

              h_chi2_less01_res->Fill((reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/ true_hit_energy_vec->at(k));
              h_chi2_less01_hits->Fill(true_thetaXZ);
            }

            if(reco_hit_goodness_of_fit_vec->at(k) > 100){
            
              profile_thetaXZ_vs_chi2->Fill(true_thetaXZ, reco_hit_goodness_of_fit_vec->at(k));
              h_chi2_more100_res->Fill((reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/ true_hit_energy_vec->at(k));
              h_chi2_more100_hits->Fill(true_thetaXZ);
            }

            if(reco_hit_goodness_of_fit_vec->at(k) > 1000){
            
              h_chi2_more1000_res->Fill((reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/ true_hit_energy_vec->at(k));
              h_chi2_more1000_hits->Fill(true_thetaXZ);
            }

            if(reco_hit_goodness_of_fit_vec->at(k) == -1){

              h_chi2_m1_res->Fill((reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/ true_hit_energy_vec->at(k));
              true_hit_energy += true_hit_energy_vec->at(k);
              reco_hit_energy += reco_hit_energy_vec->at(k);

              h_chi2_m1_hits->Fill(true_thetaXZ);         
            }
          }


         double bad_hit_energy_frac = reco_hit_energy/reco_energy;
         double frac_res = (reco_hit_energy - true_hit_energy)/true_hit_energy;
         //h_bad_fits_frac_res->Fill(frac_res);
         if(bad_hit_energy_frac > 0){
           //h_bad_fits_energy_frac->Fill(bad_hit_energy_frac);
          }

         break;
        }
    }
}

TCanvas *c_chi2_m1_hits = new TCanvas("");  
h_chi2_m1_hits->Scale(1/h_chi2_m1_hits->Integral());
h_chi2_m1_hits->SetLineWidth(4);
h_chi2_m1_hits->SetLineColor(kRed);
h_chi2_m1_hits->GetXaxis()->SetTitle("#theta_{xz} [Degrees]");
h_chi2_m1_hits->GetYaxis()->SetTitle("Normalised Hit Number");
h_chi2_m1_hits->Draw("hist, E");

h_chi2_less01_hits->Scale(1/h_chi2_less01_hits->Integral());
h_chi2_less01_hits->SetLineWidth(4);
h_chi2_less01_hits->SetLineColor(kBlue);
h_chi2_less01_hits->Draw("same, hist, E");

h_chi2_more100_hits->Scale(1/h_chi2_more100_hits->Integral());
h_chi2_more100_hits->SetLineWidth(4);
h_chi2_more100_hits->SetLineColor(kOrange);
h_chi2_more100_hits->Draw("same, hist, E");

h_chi2_more1000_hits->Scale(1/h_chi2_more1000_hits->Integral());
h_chi2_more1000_hits->SetLineWidth(4);
h_chi2_more1000_hits->SetLineColor(kRed);
//h_chi2_more1000_hits->Draw("same, hist");

TLegend *leg_hits = new TLegend();
leg_hits->SetBorderSize(0);
leg_hits->AddEntry(h_chi2_less01_hits, "chi2 < 0.1", "L");
leg_hits->AddEntry(h_chi2_more100_hits, "chi2 > 100", "L");
//leg_hits->AddEntry(h_chi2_more1000_hits, "chi2 > 1000", "L");
leg_hits->AddEntry(h_chi2_m1_hits, "chi2 == -1", "L");
leg_hits->Draw();


TCanvas *frac_res = new TCanvas("");
h_chi2_less01_res->Scale(1/h_chi2_less01_res->Integral());
h_chi2_less01_res->SetLineWidth(4);
h_chi2_less01_res->SetLineColor(kBlue);
h_chi2_less01_res->GetXaxis()->SetTitle("(Reco-True)/True [Hit Energy]");
h_chi2_less01_res->GetYaxis()->SetTitle("Normalised Hit Number");
h_chi2_less01_res->Draw();

h_chi2_more100_res->Scale(1/h_chi2_more100_res->Integral());
h_chi2_more100_res->SetLineWidth(4);
h_chi2_more100_res->SetLineColor(kOrange);
h_chi2_more100_res->Draw("same");

h_chi2_more1000_res->Scale(1/h_chi2_more1000_res->Integral());
h_chi2_more1000_res->SetLineWidth(4);
h_chi2_more1000_res->SetLineColor(kRed);
//h_chi2_more1000_res->Draw("same");

h_chi2_m1_res->Scale(1/h_chi2_m1_res->Integral());
h_chi2_m1_res->SetLineWidth(4);
h_chi2_m1_res->SetLineColor(kRed);
h_chi2_m1_res->Draw("same");

TLegend *leg = new TLegend();
leg->SetBorderSize(0);
leg->AddEntry(h_chi2_less01_res, "chi2 < 0.1", "L");
leg->AddEntry(h_chi2_more100_res, "chi2 > 100", "L");
//leg->AddEntry(h_chi2_more1000_res, "chi2 > 1000", "L");
leg->AddEntry(h_chi2_m1_res, "chi2 == -1", "L");
leg->Draw();


//TCanvas *c_bad_hits_frac_res = new TCanvas("");  
//h_bad_fits_frac_res->Draw();

//TCanvas *c_bad_hits_energy_frac = new TCanvas("");  
//h_bad_fits_energy_frac->Draw();


TCanvas *c_profile = new TCanvas("");  
profile_hit_E_vs_chi2->GetYaxis()->SetTitle("Reco Hit Energy [MeV]");
profile_hit_E_vs_chi2->GetXaxis()->SetTitle("GoodnessOfFit");
profile_hit_E_vs_chi2->SetLineWidth(4);
profile_hit_E_vs_chi2->Draw();


TCanvas *c_profile_low = new TCanvas("");  
profile_hit_E_vs_chi2_low->GetYaxis()->SetTitle("Reco Hit Energy [MeV]");
profile_hit_E_vs_chi2_low->GetXaxis()->SetTitle("GoodnessOfFit");
profile_hit_E_vs_chi2_low->SetLineWidth(4);
profile_hit_E_vs_chi2_low->Draw();


TCanvas *c_profile_res = new TCanvas("");  
profile_chi2_vs_res->GetYaxis()->SetTitle("(reco-true)/true [MeV]");
profile_chi2_vs_res->GetXaxis()->SetTitle("chi2");
profile_chi2_vs_res->SetLineWidth(4);
profile_chi2_vs_res->Draw();


TCanvas *c_profile_angle_vs_chi2 = new TCanvas("");  
profile_thetaXZ_vs_chi2->GetXaxis()->SetTitle("#theta_{xz}");
profile_thetaXZ_vs_chi2->GetYaxis()->SetTitle("chi2");
profile_thetaXZ_vs_chi2->SetLineWidth(4);
profile_thetaXZ_vs_chi2->Draw();




TCanvas *c_energy_frac = new TCanvas("");  
//h_frac_E_chi_m1->Scale(1/h_frac_E_chi_m1->Integral());
h_frac_E_chi_m1->SetLineWidth(4);
h_frac_E_chi_m1->GetYaxis()->SetRangeUser(0,100);
h_frac_E_chi_m1->GetYaxis()->SetTitle("Reco Hit Energy %");
h_frac_E_chi_m1->GetXaxis()->SetTitle("#theta_{xz} [Degrees]");
h_frac_E_chi_m1->SetLineColor(kRed);
h_frac_E_chi_m1->Draw();

//h_frac_E_chi_more_100->Scale(1/h_frac_E_chi_more_100->Integral());
h_frac_E_chi_1_100->SetLineWidth(4);
h_frac_E_chi_1_100->SetLineColor(kGreen+2);
h_frac_E_chi_1_100->Draw("same");

h_frac_E_chi_100_1000->SetLineWidth(4);
h_frac_E_chi_100_1000->SetLineColor(kOrange);
h_frac_E_chi_100_1000->Draw("same");

//h_frac_E_chi_more_1000->Scale(1/h_frac_E_chi_more_1000->Integral());
h_frac_E_chi_more_1000->SetLineWidth(4);
//h_frac_E_chi_more_1000->SetLineColor(kCyan);
//h_frac_E_chi_more_1000->Draw("same");

//h_frac_E_chi_less_1->Scale(1/h_frac_E_chi_less_1->Integral());
h_frac_E_chi_less_1->SetLineWidth(4);
h_frac_E_chi_less_1->SetLineColor(kBlue);
h_frac_E_chi_less_1->Draw("same");

TLegend *leg2 = new TLegend();
leg2->SetBorderSize(0);
leg2->AddEntry(h_frac_E_chi_m1, "GoodnessOfFit == -1", "L");
leg2->AddEntry(h_frac_E_chi_1_100, "1 < GoodnessOfFit < 100", "L");
leg2->AddEntry(h_frac_E_chi_100_1000, "100 < GoodnessOfFit < 1000", "L");
//leg2->AddEntry(h_frac_E_chi_more_1000, "chi2 > 1000", "L");
leg2->AddEntry(h_frac_E_chi_less_1, "GoodnessOfFit < 1 (and not == -1)", "L");
leg2->Draw();

//TCanvas *c_stack = new TCanvas("");  
//hs->Add(h_frac_E_chi_m1);
//hs->Add(h_frac_E_chi_more_100);
//hs->Add(h_frac_E_chi_more_1000);
//hs->Add(h_frac_E_chi_less_1);
//hs->SetMaximum(10);
//hs->Draw();




TCanvas *c_final = new TCanvas("");  

h_frac_E_chi_m1->SetLineWidth(4);
//h_frac_E_chi_m1->GetYaxis()->SetRangeUser(0,100);
h_frac_E_chi_m1->SetLineColor(kRed);
h_frac_E_chi_m1->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");                                                                                                                   
h_frac_E_chi_m1->GetYaxis()->SetTitle("Arbitrary Values");    

h_frac_E_chi_m1->Draw();

h_frac_res_vs_thetaXZ->Draw("same, colz");

h_frac_E_chi_m1->Draw("same");
}



