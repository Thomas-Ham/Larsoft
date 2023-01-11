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

void fractional_resolution(){

// get file
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_oldmethod.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_norollup_fixed.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/TEST.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

//TH1D *h_frac_res = new TH1D("frac_res","",41,-1.025,1.025);
TH1D *h_frac_res = new TH1D("frac_res","",41,-1.033,1.017);
TH1D *h_frac_res_hit_level = new TH1D("frac_res_hit_level","",41,-1.025,1.025);
//TH1D *h_frac_res_showering_e = new TH1D("frac_res_showering_e","",41,-1.025,1.025); // linear
//TH1D *h_frac_res_showering_e = new TH1D("frac_res_showering_e","",41,-1.0,1.05); // oldmethod
TH1D *h_frac_res_showering_e = new TH1D("frac_res_showering_e","",41,-0.998,1.052); // estar

std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
//t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);

int n = 6000;

for(int i = 0; i < t_truth->GetEntries(); i++){
//for(int i = 1000; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    double true_hit_energy{0};

    for(int j = 0; j < t_reco->GetEntries(); j++){
    //for(int j = 1000; j < n; j++){
        t_reco->GetEntry(j);
        //get the variables we want
        double reco_subrun = t_reco->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco->GetLeaf("numhits")->GetValue();
        double reco_energy = t_reco->GetLeaf("energy")->GetValue();
        //double reco_hit_energy{0};

        if(true_subrun == reco_subrun && 
           true_event == reco_event) {
 
          for(auto k = 0; k < true_hit_energy_vec->size(); k++){
            true_hit_energy += true_hit_energy_vec->at(k);

            //h_frac_res_hit_level->Fill((reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));

          }
 
          h_frac_res->Fill((reco_energy - true_hit_energy)/true_hit_energy);
          
          h_frac_res_showering_e->Fill((reco_energy - true_energy)/true_energy);

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
h_frac_res->GetXaxis()->SetTitle("#frac{Reco - True}{True} [Hit Energy]");

h_frac_res->Fit("gaus");
//h_frac_res->GetFunction("gaus")->SetLineColor(kBlue);
//TF1 *g1 = new TF1("m1","gaus",-0.1,0.1);
//h_frac_res->Fit(g1, "R");

h_frac_res->Draw("histE,same");
y_line->Draw("same");

TCanvas *c2 = new TCanvas("");  
std::cout << h_frac_res_hit_level->Integral() << std::endl;
h_frac_res_hit_level->Scale(1/h_frac_res_hit_level->Integral());
h_frac_res_hit_level->SetLineWidth(3);
h_frac_res_hit_level->GetYaxis()->SetTitleSize(0.035);
h_frac_res_hit_level->GetXaxis()->SetTitleOffset(1.75);
h_frac_res_hit_level->GetXaxis()->SetTitleSize(0.025);
h_frac_res_hit_level->GetYaxis()->SetTitle("Normalised Events");
h_frac_res_hit_level->GetXaxis()->SetTitle("#frac{Reco - True}{True} [Hit Energy]");
h_frac_res_hit_level->Draw("histE");

y_line->Draw("same");


TCanvas *c3 = new TCanvas("");  
std::cout << h_frac_res_showering_e->Integral() << std::endl;
h_frac_res_showering_e->Scale(1/h_frac_res_showering_e->Integral());
h_frac_res_showering_e->SetLineWidth(3);
h_frac_res_showering_e->GetYaxis()->SetTitleSize(0.035);
h_frac_res_showering_e->GetXaxis()->SetTitleOffset(1.75);
h_frac_res_showering_e->GetXaxis()->SetTitleSize(0.025);
h_frac_res_showering_e->GetYaxis()->SetTitle("Normalised Events");
h_frac_res_showering_e->GetXaxis()->SetTitle("#frac{Reco - True}{True} [Hit Energy]");
TF1 *g1 = new TF1("m1","gaus",-0.25,-0.05);
h_frac_res_showering_e->Fit(g1, "R");
//h_frac_res_showering_e->Fit("gaus");
h_frac_res_showering_e->Draw("histE,same");

std::cout << h_frac_res_showering_e->GetMaximumBin() << std::endl;


y_line->Draw("same");

double xmax[n_points] = {h_frac_res_showering_e->GetBinCenter(h_frac_res_showering_e->GetMaximumBin()), h_frac_res_showering_e->GetBinCenter(h_frac_res_showering_e->GetMaximumBin())};
//double xmax[n_points] = {h_frac_res_showering_e->GetBinCenter(17), h_frac_res_showering_e->GetBinCenter(17)};
double ymax[n_points] = {0, 1};
TGraph *max_line = new TGraph(n_points,xmax,ymax);

//max_line->Draw("same");

}







