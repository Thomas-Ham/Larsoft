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

void fractional_resolution_overlay(){

// get file
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2.root","read");
//TFile *f_oldmethod        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_oldmethod.root","read");

TFile *f               = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_plane2.root","read");
TFile *f_oldmethod     = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_plane2_oldmethod.root","read");
TFile *f_linear        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_plane2_linear.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_reco_oldmethod   = (TTree*)f_oldmethod->Get("TriggerResults/Reco_LS");
TTree *t_reco_linear   = (TTree*)f_linear->Get("TriggerResults/recoenergy_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH1D *h_frac_res = new TH1D("frac_res","",41,-1.025,1.025);
TH1D *h_frac_res_oldmethod = new TH1D("frac_res_oldmethod","",41,-1.025,1.025);
TH1D *h_frac_res_linear = new TH1D("frac_res_linear","",41,-1.025,1.025);

TH1D *h_frac_res_hit_level = new TH1D("frac_res_hit_level","",40,-1,1);
TH1D *h_frac_res_hit_level_oldmethod = new TH1D("frac_res_hit_level_oldmethod","",40,-1,1);

std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec_oldmethod = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
TBranch *breco_hit_energy_oldmethod = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);
t_reco_oldmethod->SetBranchAddress("hit_energy",&reco_hit_energy_vec_oldmethod,&breco_hit_energy_oldmethod);


int n = 500;

//for(int i = 0; i < t_truth->GetEntries(); i++){
for(int i = 0; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    double true_hit_energy{0};

    //for(int j = 0; j < t_reco->GetEntries(); j++){
    for(int j = 0; j < n; j++){
        t_reco->GetEntry(j);
        //get the variables we want
        double reco_subrun = t_reco->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco->GetLeaf("numhits")->GetValue();
        double reco_energy = t_reco->GetLeaf("energy")->GetValue();

        if(true_subrun == reco_subrun && 
           true_event == reco_event) {
 
          
          for(auto k = 0; k < true_hit_energy_vec->size(); k++){
            true_hit_energy += true_hit_energy_vec->at(k);
            
            h_frac_res_hit_level->Fill((reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
          }
          
          h_frac_res->Fill((reco_energy - true_hit_energy)/true_hit_energy);

          break;
        }
    }
    //for(int k = 0; k < t_reco->GetEntries(); k++){
    for(int k = 0; k < n; k++){
        t_reco_oldmethod->GetEntry(k);
        //get the variables we want
        double reco_subrun_oldmethod = t_reco_oldmethod->GetLeaf("subrun")->GetValue();
        double reco_event_oldmethod  = t_reco_oldmethod->GetLeaf("event")->GetValue();
        double reco_hits_oldmethod   = t_reco_oldmethod->GetLeaf("numhits")->GetValue();
        double reco_energy_oldmethod = t_reco_oldmethod->GetLeaf("energy")->GetValue();

        if(true_subrun == reco_subrun_oldmethod &&
           true_event == reco_event_oldmethod) {
 
          
          for(auto k = 0; k < true_hit_energy_vec->size(); k++){
            std::cout << reco_hit_energy_vec_oldmethod->at(k) << std::endl;
            std::cout << true_hit_energy_vec->at(k) << std::endl;
            h_frac_res_hit_level_oldmethod->Fill((reco_hit_energy_vec_oldmethod->at(k) - true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
          }
          

          h_frac_res_oldmethod->Fill((reco_energy_oldmethod - true_hit_energy)/true_hit_energy);

          break;
        }
    }
    
    //for(int k = 0; k < t_reco_linear->GetEntries(); k++){
    for(int k = 0; k < n; k++){
      t_reco_linear->GetEntry(k);
      double reco_subrun_linear = t_reco_linear->GetLeaf("subrun")->GetValue();
      double reco_event_linear  = t_reco_linear->GetLeaf("event")->GetValue();
      double reco_hits_linear   = t_reco_linear->GetLeaf("numhits")->GetValue();
      double reco_energy_linear = t_reco_linear->GetLeaf("energy")->GetValue();

      if(true_subrun == reco_subrun_linear &&
           true_event == reco_event_linear) {

        h_frac_res_linear->Fill((reco_energy_linear - true_hit_energy)/true_hit_energy);
        break;
      }
   }

}


const int n_points = 2;
int x[n_points] = {0, 0};
int y[n_points] = {0, 1};
TGraph *y_line = new TGraph(n_points,x,y);



TCanvas *c = new TCanvas("");  
std::cout << h_frac_res->Integral() << std::endl;
h_frac_res->Scale(1/h_frac_res->Integral());
h_frac_res->SetLineWidth(3);
h_frac_res->GetYaxis()->SetTitleSize(0.035);
h_frac_res->GetXaxis()->SetTitleOffset(1.75);
h_frac_res->GetXaxis()->SetTitleSize(0.025);
h_frac_res->GetYaxis()->SetTitle("Normalised Events");
h_frac_res->GetXaxis()->SetTitle("#frac{Reco - True}{True} [Energy]");

//TF1 *gaus_fit = new TF1("gaus_fit","gaus");
//TF1 *gaus_fit2 = new TF1("gaus_fit2","gaus");
//h_frac_res->Fit(gaus_fit,"+");
//h_frac_res->GetFunction("gaus")->SetLineColor(kBlue);
h_frac_res->Draw("histE,same");

h_frac_res_oldmethod->Scale(1/h_frac_res_oldmethod->Integral());
h_frac_res_oldmethod->SetLineWidth(3);
h_frac_res_oldmethod->SetLineColor(kRed);
//h_frac_res_oldmethod->Fit(gaus_fit2,"+");
//h_frac_res_oldmethod->GetFunction("gaus")->SetLineColor(kRed);
h_frac_res_oldmethod->Draw("histE, same");

h_frac_res_linear->Scale(1/h_frac_res_linear->Integral());
h_frac_res_linear->SetLineWidth(3);
h_frac_res_linear->SetLineColor(kGreen+2);
//h_frac_res_linear->Fit("gaus");
//h_frac_res_linear->GetFunction("gaus")->SetLineColor(kGreen+2);
h_frac_res_linear->Draw("histE, same");


y_line->Draw("same");

TLegend *l = new TLegend(0.15,0.6,0.4,0.8);
l->SetBorderSize(0);
l->AddEntry(h_frac_res, "ESTAR", "L");
l->AddEntry(h_frac_res_oldmethod, "Num of Electrons", "L");
l->AddEntry(h_frac_res_linear, "Linear", "L");
l->Draw();




TCanvas *c_hit_level = new TCanvas("");  
std::cout << h_frac_res_hit_level->Integral() << std::endl;
h_frac_res_hit_level->Scale(1/h_frac_res_hit_level->Integral());
h_frac_res_hit_level->SetLineWidth(3);
h_frac_res_hit_level->GetYaxis()->SetTitleSize(0.035);
h_frac_res_hit_level->GetXaxis()->SetTitleOffset(1.75);
h_frac_res_hit_level->GetXaxis()->SetTitleSize(0.025);
h_frac_res_hit_level->GetYaxis()->SetTitle("Normalised Events");
h_frac_res_hit_level->GetXaxis()->SetTitle("#frac{Reco - True}{True} [Energy]");
h_frac_res_hit_level->Draw("histE");

h_frac_res_hit_level_oldmethod->Scale(1/h_frac_res_hit_level_oldmethod->Integral());
h_frac_res_hit_level_oldmethod->SetLineWidth(3);
h_frac_res_hit_level_oldmethod->SetLineColor(kRed);
h_frac_res_hit_level_oldmethod->Draw("histE, same");

y_line->Draw("same");

TLegend *l2 = new TLegend(0.15,0.6,0.4,0.8);
l2->SetBorderSize(0);
l2->AddEntry(h_frac_res_hit_level, "ESTAR", "L");
l2->AddEntry(h_frac_res_hit_level_oldmethod, "kGeVToElectrons", "L");
l2->Draw();



}







