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

void true_vs_reco_energy(){

// get file
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_plane1.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/TEST.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cheat_plane2_oldmethod.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH2D *h_true_vs_reco = new TH2D("true_vs_reco","",50,0,1200,50,0,1200);
TH2D *h_true_vs_reco_hitlevel = new TH2D("true_vs_reco_hitlevel","",50,0,50,50,0,50);
TH2D *h_true_vs_reco_hitlevel_zoom = new TH2D("true_vs_reco_hitlevel_zoom","",50,0,10,50,0,10);

TH2D *h_true_vs_reco_oldmethod = new TH2D("true_vs_reco_old_method","",50,0,1200,50,0,1200);
TH2D *h_true_vs_reco_hitlevel_oldemethod = new TH2D("true_vs_reco_hitlevel_old_method","",50,0,50,50,0,50);


// Make x=y line
const int n_points = 2;
int x[n_points] = {0, 2000};
int y[n_points] = {0, 2000};
TGraph *line = new TGraph(n_points,x,y);


std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;
std::vector<double> *reco_hit_goodness_of_fit_vec = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
TBranch *breco_hit_goodness_of_fit = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);
//t_reco->SetBranchAddress("hit_goodness_of_fit",&reco_hit_goodness_of_fit_vec,&breco_hit_goodness_of_fit);

int n = 1000;

for(int i = 0; i < t_truth->GetEntries(); i++){
//for(int i = 0; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    double true_hit_energy{0};

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
           true_event == reco_event) {
       
                   
          // Hit level stuff
          for(auto k = 0; k < true_hit_energy_vec->size(); k++){
            //if(reco_hit_goodness_of_fit_vec->at(k) > 200 || reco_hit_goodness_of_fit_vec->at(k) < 0){continue;}
            true_hit_energy += true_hit_energy_vec->at(k);
            //reco_hit_energy += reco_hit_energy_vec->at(k);

            //h_true_vs_reco_hitlevel->Fill(true_hit_energy_vec->at(k), reco_hit_energy_vec->at(k));
            //h_true_vs_reco_hitlevel_zoom->Fill(true_hit_energy_vec->at(k), reco_hit_energy_vec->at(k));

          }
          
          h_true_vs_reco->Fill(true_hit_energy, reco_energy);
          //std::cout << "reco E: " << reco_hit_energy << std::endl;
          //std::cout << "true E: " << true_hit_energy << std::endl;

          break;
        }
    }
}



TCanvas *c = new TCanvas("");  
//std::cout << h_true_vs_reco->Integral() << std::endl;
//h_true_vs_reco->Scale(1/h_true_vs_reco->Integral());
h_true_vs_reco->SetLineWidth(3);
h_true_vs_reco->GetYaxis()->SetTitleSize(0.035);
h_true_vs_reco->GetXaxis()->SetTitleOffset(1.1);
h_true_vs_reco->GetXaxis()->SetTitleSize(0.035);
h_true_vs_reco->GetYaxis()->SetTitle("Reco Energy [MeV]");
h_true_vs_reco->GetXaxis()->SetTitle("True Energy [MeV]");
h_true_vs_reco->Draw("colz");

line->SetLineColor(kRed);
line->SetLineWidth(2);
line->Draw("same");


TLegend *leg = new TLegend(0.15, 0.7, 0.3, 0.8);
leg->AddEntry(line, "y = x", "L");
leg->SetBorderSize(0);
leg->Draw();

TCanvas *c_hit_level = new TCanvas(""); 
//c_hit_level->SetLogz();
//std::cout << h_true_vs_reco->Integral() << std::endl;
//h_true_vs_reco->Scale(1/h_true_vs_reco->Integral());
h_true_vs_reco_hitlevel->SetLineWidth(3);
h_true_vs_reco_hitlevel->GetYaxis()->SetTitleSize(0.035);
h_true_vs_reco_hitlevel->GetXaxis()->SetTitleOffset(1.1);
h_true_vs_reco_hitlevel->GetXaxis()->SetTitleSize(0.035);
h_true_vs_reco_hitlevel->GetYaxis()->SetTitle("Reco Energy [MeV]");
h_true_vs_reco_hitlevel->GetXaxis()->SetTitle("True Energy [MeV]");
h_true_vs_reco_hitlevel->Draw("colz");

line->SetLineColor(kRed);
line->SetLineWidth(2);
line->Draw("same");


TLegend *leg2 = new TLegend(0.15, 0.7, 0.3, 0.8);
leg2->AddEntry(line, "y = x", "L");
leg2->SetBorderSize(0);
leg2->Draw();

TCanvas *c_hit_level_zoom = new TCanvas(""); 
c_hit_level_zoom->SetLogz();
//std::cout << h_true_vs_reco->Integral() << std::endl;
//h_true_vs_reco->Scale(1/h_true_vs_reco->Integral());
h_true_vs_reco_hitlevel_zoom->SetLineWidth(3);
h_true_vs_reco_hitlevel_zoom->GetYaxis()->SetTitleSize(0.035);
h_true_vs_reco_hitlevel_zoom->GetXaxis()->SetTitleOffset(1.1);
h_true_vs_reco_hitlevel_zoom->GetXaxis()->SetTitleSize(0.035);
h_true_vs_reco_hitlevel_zoom->GetYaxis()->SetTitle("Reco Energy [MeV]");
h_true_vs_reco_hitlevel_zoom->GetXaxis()->SetTitle("True Energy [MeV]");
h_true_vs_reco_hitlevel_zoom->Draw("colz");

line->SetLineColor(kRed);
line->SetLineWidth(2);
line->Draw("same");


TLegend *leg3 = new TLegend(0.15, 0.7, 0.3, 0.8);
leg3->AddEntry(line, "y = x", "L");
leg3->SetBorderSize(0);
leg3->Draw();

}







