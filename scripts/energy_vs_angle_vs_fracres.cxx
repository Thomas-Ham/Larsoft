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

void energy_vs_angle_vs_fracres(){

// get file
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2.root","read");
//TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/hit_variables_1.root","read");
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/electron_vertex_bnblike_XZ_plane_cheating_plane2_oldmethod.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH2D *h_energy_vs_angle       = new TH2D("energy_vs_angle","",14,-70,70,12,0,1200);
h_energy_vs_angle->Sumw2();

//The mean value of z for each x-y bin.
TH2D *hMean = (TH2D*) h_energy_vs_angle->Clone("hMean");
hMean->Sumw2();
//hMean->SetTitle("Mean value of z");

TH1D *h_frac_res1       = new TH1D("frac_res1","",100,-0.1,0.1);
TH1D *h_frac_res2       = new TH1D("frac_res2","",100,-0.1,0.1);
TH1D *h_frac_res3       = new TH1D("frac_res3","",100,-0.1,0.1);


std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);

int n = 30;

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
            true_hit_energy += true_hit_energy_vec->at(k);   
            reco_hit_energy += reco_hit_energy_vec->at(k);   
           
            //h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));
            //profile_w->Fill(true_thetaXZ, ((reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k))*true_hit_energy_vec->at(k));
          
          }

          double frac_res = (reco_hit_energy - true_hit_energy)/true_hit_energy;
          h_energy_vs_angle->Fill(true_thetaXZ, reco_hit_energy);
          hMean->Fill(true_thetaXZ, reco_hit_energy, frac_res);

          if(true_thetaXZ > 20 && true_thetaXZ < 30 && reco_hit_energy > 200 && reco_hit_energy < 300){
            std::cout << "([20,30], [200,300]),  "<< "frac_res: " << frac_res << std::endl;
            h_frac_res1->Fill(frac_res);
          }

          if(true_thetaXZ > -40 && true_thetaXZ < -30 && reco_hit_energy > 200 && reco_hit_energy < 300){
            std::cout << "([-40,-30], [200,300]),  "<< "frac_res: " << frac_res << std::endl;
            h_frac_res2->Fill(frac_res);
          }
          
          if(true_thetaXZ > 40 && true_thetaXZ < 50 && reco_hit_energy > 800 && reco_hit_energy < 900){
            std::cout << "([40,50], [800,900]),  "<< "frac_res: " << frac_res << std::endl;
            h_frac_res3->Fill(frac_res);
          }

          break;
        }
    }
}

hMean->Divide(h_energy_vs_angle);

// plot resolution as function of thetaXZ and thetaYZ
TCanvas *c = new TCanvas("");  
c->SetRightMargin(0.25);
c->SetLeftMargin(0.15);
c->SetBottomMargin(0.15);
h_energy_vs_angle->GetXaxis()->SetTitle("#theta_{xz} [Degrees]");
h_energy_vs_angle->GetYaxis()->SetTitle("Reco Energy [MeV]");
h_energy_vs_angle->GetZaxis()->SetTitleOffset(1.5);
h_energy_vs_angle->GetXaxis()->SetTitleOffset(1.3);
h_energy_vs_angle->GetZaxis()->SetTitle("Number of Entries");
h_energy_vs_angle->DrawClone("COLZ");

TCanvas *cc = new TCanvas("");  
cc->SetRightMargin(0.25);
cc->SetLeftMargin(0.15);
cc->SetBottomMargin(0.15);
hMean->GetXaxis()->SetTitle("#theta_{xz} [Degrees]");
hMean->GetYaxis()->SetTitle("Reco Energy [MeV]");
hMean->GetZaxis()->SetTitleOffset(1.5);
hMean->GetXaxis()->SetTitleOffset(1.3);
hMean->GetZaxis()->SetTitle("(Reco-True)/True [Energy]");

hMean->DrawClone("COLZ");


int x, y, z;
h_energy_vs_angle->GetBinXYZ(h_energy_vs_angle->GetMaximumBin(),x,y,z);

std::cout << x << "   " << y << std::endl;
std::cout << h_energy_vs_angle->GetXaxis()->GetBinCenter(x) << std::endl;
std::cout << h_energy_vs_angle->GetYaxis()->GetBinCenter(y) << std::endl;

TCanvas *c1 = new TCanvas("");  
h_frac_res1->SetTitle("(angle, energy) = ([20,30],[200,300]");
h_frac_res1->GetXaxis()->SetTitle("Resolution");
h_frac_res1->Draw();

TCanvas *c2 = new TCanvas("");  
h_frac_res2->SetTitle("(angle, energy) = ([-40,-30],[200,300]");
h_frac_res2->GetXaxis()->SetTitle("Resolution");
h_frac_res2->Draw();

TCanvas *c3 = new TCanvas("");  
h_frac_res3->SetTitle("(angle, energy) = ([40,50],[800,900]");
h_frac_res3->GetXaxis()->SetTitle("Resolution");
h_frac_res3->Draw();

}







