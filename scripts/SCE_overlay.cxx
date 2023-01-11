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

void SCE_overlay(){

// get file
TFile *f_SCE_nocorr     = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cathode_SCE_corr_cheating_spacepoints.root","read");
TFile *f_SCE_corr       = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cathode_SCE_corr_cheating_spacepoints.root","read");
TFile *f_noSCE          = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_cathode_noSCE_cheating_spacepoints.root","read");

// get the trees
TTree *t_reco_SCE_nocorr   = (TTree*)f_SCE_nocorr->Get("TriggerResults/Reco_LS");
TTree *t_reco_SCE_corr     = (TTree*)f_SCE_corr->Get("TriggerResults/Reco_LS");
TTree *t_truth_SCE         = (TTree*)f_SCE_corr->Get("TriggerResults/Truth_LS");

TTree *t_reco_noSCE        = (TTree*)f_noSCE->Get("TriggerResults/Reco_LS");
TTree *t_truth_noSCE       = (TTree*)f_noSCE->Get("TriggerResults/Truth_LS");

TH1D *h_frac_res_nocorr = new TH1D("frac_res_nocorr","",50,-1,1);
TH1D *h_frac_res_corr   = new TH1D("frac_res_corr","",50,-1,1);
TH1D *h_frac_res        = new TH1D("frac_res","",50,-1,1);

std::vector<double> *true_hit_energy_vec      = 0;
std::vector<double> *reco_hit_energy_vec      = 0;
std::vector<double> *true_hit_energy_vec_SCE  = 0;
std::vector<double> *reco_hit_energy_vec_SCE  = 0;

TBranch *btrue_hit_energy     = 0;
TBranch *breco_hit_energy     = 0;
TBranch *btrue_hit_energy_SCE = 0;
TBranch *breco_hit_energy_SCE = 0;
t_truth_noSCE->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco_noSCE->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);
t_truth_SCE->SetBranchAddress("hit_energy",&true_hit_energy_vec_SCE,&btrue_hit_energy_SCE);
t_reco_SCE_corr->SetBranchAddress("hit_energy",&reco_hit_energy_vec_SCE,&breco_hit_energy_SCE);

int nevents = 2000;
int counter{0};
std::vector<int> good_events;
good_events.clear();

for(int i = 0; i < nevents; i++){
//for(int i = 0; i < t_truth_noSCE->GetEntries(); i++){
  t_truth_noSCE->GetEntry(i);
  for(int j = 0; j < nevents; j++){
  //for(int j = 0; j < t_truth_SCE->GetEntries(); j++){
    t_truth_SCE->GetEntry(j);

  double true_subrun = t_truth_noSCE->GetLeaf("subrun")->GetValue();
  double true_event  = t_truth_noSCE->GetLeaf("event")->GetValue();
  double true_hits   = t_truth_noSCE->GetLeaf("numhits")->GetValue();
  double true_subrun_SCE = t_truth_SCE->GetLeaf("subrun")->GetValue();
  double true_event_SCE  = t_truth_SCE->GetLeaf("event")->GetValue();
  double true_hits_SCE   = t_truth_SCE->GetLeaf("numhits")->GetValue();

  //std::cout << "subrun: " << true_subrun << "   " << true_subrun_SCE << std::endl;
  //std::cout << "events: " << true_event << "   " << true_event_SCE << std::endl;
  //std::cout << "hits: " << true_hits << "   " << true_hits_SCE << std::endl;

  if(true_subrun == true_subrun_SCE &&
     true_event  == true_event_SCE &&
     true_hits == true_hits_SCE){
  
    //std::cout << "subrun: " << true_subrun << "   " << true_subrun_SCE << std::endl;
    //std::cout << "events: " << true_event << "   " << true_event_SCE << std::endl;
    //std::cout << "hits: " << true_hits << "   " << true_hits_SCE << std::endl;
   
    std::cout << true_subrun << "    " << true_event << "   " << true_hits << std::endl;
    std::cout << i << "  " << j << std::endl;  

    counter++;
    good_events.push_back(i);
    break;
  }
  }
}
std::cout << "counter: "<< counter << std::endl;


// sample without SCE
//for(int i = 0; i < t_truth_noSCE->GetEntries(); i++){
for(auto i = good_events.begin(); i != good_events.end(); i++){
//for(int i = 0; i < nevents; i++){
    t_truth_noSCE->GetEntry(*i);
    //t_truth_noSCE->GetEntry(*i);
    //get the variables we want
    double true_subrun = t_truth_noSCE->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth_noSCE->GetLeaf("event")->GetValue();
    double true_hits   = t_truth_noSCE->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth_noSCE->GetLeaf("energy")->GetValue();

    double true_hit_energy{0};

    //for(int j = 0; j < t_reco_noSCE->GetEntries(); j++){
    //for(int j = 0; j < nevents; j++){
    for(auto j = good_events.begin(); j != good_events.end(); j++){
        t_reco_noSCE->GetEntry(*j);
        //get the variables we want
        double reco_subrun = t_reco_noSCE->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco_noSCE->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco_noSCE->GetLeaf("numhits")->GetValue();
        double reco_energy = t_reco_noSCE->GetLeaf("energy")->GetValue();
        double reco_hit_energy{0};

       
        if(true_subrun == reco_subrun && 
           true_event == reco_event){
 
          for(auto k = 0; k < true_hit_energy_vec->size(); k++){
            true_hit_energy   += true_hit_energy_vec->at(k);
            reco_hit_energy   += reco_hit_energy_vec->at(k);

          }
 
          h_frac_res->Fill((reco_hit_energy - true_hit_energy)/true_hit_energy);

          //std::cout << "true hits: " << true_hits << std::endl;
          //std::cout << "true E: " << true_hit_energy << " reco E: " << reco_energy << std::endl;

          break;
        }
    }
}
// sample with SCE
//for(int i = 0; i < t_truth_SCE->GetEntries(); i++){
//for(int i = 0; i < nevents; i++){
for(auto i = good_events.begin(); i != good_events.end(); i++){
    t_truth_SCE->GetEntry(*i);
    //get the variables we want
    double true_subrun = t_truth_SCE->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth_SCE->GetLeaf("event")->GetValue();
    double true_hits   = t_truth_SCE->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth_SCE->GetLeaf("energy")->GetValue();

    double true_hit_energy{0};

    //for(int j = 0; j < t_reco_SCE_nocorr->GetEntries(); j++){
    //for(int j = 0; j < nevents; j++){
    for(auto j = good_events.begin(); j != good_events.end(); j++){
        t_reco_SCE_nocorr->GetEntry(*j);
        t_reco_SCE_corr->GetEntry(*j);
        //get the variables we want
        double reco_subrun = t_reco_SCE_nocorr->GetLeaf("subrun")->GetValue();
        double reco_event  = t_reco_SCE_nocorr->GetLeaf("event")->GetValue();
        double reco_hits   = t_reco_SCE_nocorr->GetLeaf("numhits")->GetValue();
        double reco_energy_nocorr = t_reco_SCE_nocorr->GetLeaf("energy")->GetValue();
        double reco_energy_corr   = t_reco_SCE_corr->GetLeaf("energy")->GetValue();
        double reco_hit_energy{0};


        if(true_subrun == reco_subrun && 
           true_event == reco_event){
  
          for(auto k = 0; k < true_hit_energy_vec_SCE->size(); k++){
            true_hit_energy   += true_hit_energy_vec_SCE->at(k);
            reco_hit_energy   += reco_hit_energy_vec_SCE->at(k);
          }
 
          h_frac_res_nocorr->Fill((reco_energy_nocorr - true_hit_energy)/true_hit_energy);
          h_frac_res_corr->Fill((reco_hit_energy - true_hit_energy)/true_hit_energy);

          //std::cout << "true hits: " << true_hits << std::endl;
          //std::cout << "true E: " << true_hit_energy << " reco E: " << reco_energy_nocorr << " reco E corr: " << reco_energy_corr  << std::endl;

          break;
        }
    }
}




TCanvas *c = new TCanvas("");  
std::cout << h_frac_res_nocorr->Integral() << std::endl;
h_frac_res_nocorr->Scale(1/h_frac_res_nocorr->Integral());
h_frac_res_corr  ->Scale(1/h_frac_res_corr->Integral());
h_frac_res       ->Scale(1/h_frac_res->Integral());
h_frac_res_nocorr->SetLineWidth(3);
h_frac_res_corr  ->SetLineWidth(3);
h_frac_res       ->SetLineWidth(3);
h_frac_res_nocorr->GetYaxis()->SetTitleSize(0.035);
h_frac_res_nocorr->GetXaxis()->SetTitleOffset(1.75);
h_frac_res_nocorr->GetXaxis()->SetTitleSize(0.025);
h_frac_res_nocorr->GetYaxis()->SetTitle("Normalised Events");
h_frac_res_nocorr->GetXaxis()->SetTitle("#frac{Reco - True}{True} [Hit Energy]");
h_frac_res_nocorr->SetLineColor(kRed);
h_frac_res_nocorr->Draw("histE");
h_frac_res_corr->SetLineColor(kBlue);
h_frac_res_corr->Draw("histE,same");
h_frac_res->SetLineColor(kBlack);
h_frac_res->Draw("histE,same");


TLegend *leg = new TLegend();
//leg->SetHeader("True Hit Energy", "C");
leg->SetBorderSize(0);
leg->AddEntry(h_frac_res_nocorr, "SCE sample no correction", "L");
leg->AddEntry(h_frac_res_corr, "SCE sample with correction", "L");
leg->AddEntry(h_frac_res, "Sample with no SCE", "L");
leg->Draw();



TCanvas *c2 = new TCanvas();
c2->Draw();    
 
auto rp_nocorr = new TRatioPlot(h_frac_res_nocorr, h_frac_res); 
auto rp_corr = new TRatioPlot(h_frac_res_corr, h_frac_res); 

rp_nocorr->SetH1DrawOpt("HistE");      // Drawing options for histograms in top pad    
rp_nocorr->SetH2DrawOpt("HistE");      // Drawing options for histograms in top pad    
rp_corr->SetH1DrawOpt("HistE");      // Drawing options for histograms in top pad    
rp_corr->SetH2DrawOpt("HistE");      // Drawing options for histograms in top pad    

rp_corr->Draw();
rp_nocorr->Draw();
 
rp_nocorr->GetLowerRefGraph()->SetLineColor(kRed);                                                                                                                                      
rp_nocorr->GetLowerRefGraph()->SetLineWidth(3);  
rp_nocorr->GetLowerRefGraph()->SetMinimum(0.7);                                                                                                                                      
rp_nocorr->GetLowerRefGraph()->SetMaximum(1.3);  
rp_nocorr->GetLowerRefGraph()->GetYaxis()->SetTitle("SCE/no_SCE"); 

TGraph *g_rp_corr_lower = rp_corr->GetLowerRefGraph();  

rp_nocorr->GetUpperPad()->cd();
h_frac_res_corr->Draw("same,HistE");

rp_nocorr->GetLowerPad()->cd();
g_rp_corr_lower->SetLineColor(kBlue);
g_rp_corr_lower->SetLineWidth(3);                                                                                                                                      
g_rp_corr_lower->Draw("Psame");

// Draw Legend                                                                                                                                                                        
TLegend *leg2 = rp_nocorr->GetUpperPad()->BuildLegend(0.15,0.7,0.35,0.9);                                                                                                 
leg2->SetFillStyle(0);                                                                                                                                                     
leg2->SetBorderSize(0);   


}







