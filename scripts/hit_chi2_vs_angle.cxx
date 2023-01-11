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

void hit_chi2_vs_angle(){

// get file
TFile *f        = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/root_files/hit_variables_1.root","read");

// get the trees
TTree *t_reco   = (TTree*)f->Get("TriggerResults/Reco_LS");
TTree *t_truth  = (TTree*)f->Get("TriggerResults/Truth_LS");

TH1D *h_chi2_90       = new TH1D("chi2_90","",50,0,1);
TH1D *h_chi2_70       = new TH1D("chi2_70","",50,0,1);


TH1D *h_peak_time_90    = new TH1D("peak_time_90","",50,0,2500);
TH1D *h_rms_90          = new TH1D("rms_90","",50,0,20);
TH1D *h_peak_amp_90     = new TH1D("peak_amp_90","",50,0,500);
TH1D *h_summed_adc_90   = new TH1D("summed_adc_90","",50,0,10000);
TH1D *h_integral_90     = new TH1D("integral_90","",50,0,10000);
TH1D *h_multiplicity_90 = new TH1D("multiplicity_90","",50,0,10);
TH1D *h_charge_90       = new TH1D("charge_90","",50,-10E3,600000);

TH1D *h_peak_time_70    = new TH1D("peak_time_70","",50,0,2500);
TH1D *h_rms_70          = new TH1D("rms_70","",50,0,20);
TH1D *h_peak_amp_70     = new TH1D("peak_amp_70","",50,0,500);
TH1D *h_summed_adc_70   = new TH1D("summed_adc_70","",50,0,10000);
TH1D *h_integral_70     = new TH1D("integral_70","",50,0,10000);
TH1D *h_multiplicity_70 = new TH1D("multiplicity_70","",50,0,10);
TH1D *h_charge_70       = new TH1D("charge_70","",50,-10E3,600000);

TH1D *h_charge_0        = new TH1D("charge_0","",50,0,150000);
TH1D *h_charge_30       = new TH1D("charge_30","",50,0,150000);
TH1D *h_charge_50       = new TH1D("charge_50","",50,0,150000);

TH2D *h_frac_res_vs_thetaXZ       = new TH2D("frac_res_vs_thetaXZ","",50,-180,180,20,-2,5);
TH2D *h_frac_res_vs_thetaYZ       = new TH2D("frac_res_vs_thetaYZ","",100,-180,180,50,-0.3,0.3);

TH2D *h_chi2_vs_energy       = new TH2D("chi2_vs_energy","",3,-2,0,20,0,60);

TProfile *p_frac_res_vs_thetaXZ       = new TProfile("profile_frac_res_vs_thetaXZ","",18,0,180,-2,200);
TProfile *p_frac_res_vs_thetaXZ_cut       = new TProfile("profile_frac_res_vs_thetaXZ_cut","",18,0,180,-2,200);

TH1D *h_res_50       = new TH1D("res50","",50,-0.5,0.5);
TH1D *h_res_70       = new TH1D("res70","",50,-0.5,0.5);
TH1D *h_res_90       = new TH1D("res90","",50,-0.5,0.5);


std::vector<double> *true_hit_energy_vec = 0;
std::vector<double> *reco_hit_energy_vec = 0;
std::vector<double> *hit_goodness_of_fit_vec = 0;
std::vector<double> *hit_peak_time_vec = 0;
std::vector<double> *hit_rms_vec = 0;
std::vector<double> *hit_peak_amp_vec = 0;
std::vector<double> *hit_summed_adc_vec = 0;
std::vector<double> *hit_integral_vec = 0;
std::vector<double> *hit_multiplicity_vec = 0;
std::vector<double> *hit_charge_vec = 0;

TBranch *btrue_hit_energy = 0;
TBranch *breco_hit_energy = 0;
TBranch *bhit_goodness_of_fit = 0;
TBranch *bhit_peak_time = 0;
TBranch *bhit_rms = 0;
TBranch *bhit_peak_amp = 0;
TBranch *bhit_summed_adc = 0;
TBranch *bhit_integral = 0;
TBranch *bhit_multiplicity = 0;
TBranch *bhit_charge = 0;
t_truth->SetBranchAddress("hit_energy",&true_hit_energy_vec,&btrue_hit_energy);
t_reco->SetBranchAddress("hit_energy",&reco_hit_energy_vec,&breco_hit_energy);
t_reco->SetBranchAddress("hit_goodness_of_fit",&hit_goodness_of_fit_vec,&bhit_goodness_of_fit);
t_reco->SetBranchAddress("hit_peak_time",&hit_peak_time_vec,&bhit_peak_time);
t_reco->SetBranchAddress("hit_rms",&hit_rms_vec,&bhit_rms);
t_reco->SetBranchAddress("hit_peak_amplitude",&hit_peak_amp_vec,&bhit_peak_amp);
t_reco->SetBranchAddress("hit_summed_adc",&hit_summed_adc_vec,&bhit_summed_adc);
t_reco->SetBranchAddress("hit_integral",&hit_integral_vec,&bhit_integral);
t_reco->SetBranchAddress("hit_multiplicity",&hit_multiplicity_vec,&bhit_multiplicity);
t_reco->SetBranchAddress("hit_charge",&hit_charge_vec,&bhit_charge);

int n = 1000;

double reco_90 = 0, reco_70 = 0, true_90 = 0, true_70 = 0;
//for(int i = 0; i < t_truth->GetEntries(); i++){
for(int i = 0; i < n; i++){
    t_truth->GetEntry(i);
    //get the variables we want
    double true_subrun = t_truth->GetLeaf("subrun")->GetValue();
    double true_event  = t_truth->GetLeaf("event")->GetValue();
    double true_hits   = t_truth->GetLeaf("numhits")->GetValue();
    double true_energy = t_truth->GetLeaf("energy")->GetValue();
    //double true_hit_energy{0};
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
        //double reco_hit_energy{0};
    
      
        if(true_subrun == reco_subrun && 
           true_event == reco_event) {

          double res_90 = 0;
          double res_70 = 0, res_50 = 0;
          reco_90 = 0, reco_70 = 0, true_90 = 0, true_70 = 0;
          for(auto k = 0; k < hit_goodness_of_fit_vec->size(); k++){
            // Only get hits with low chi2
            //if(hit_goodness_of_fit_vec->at(k) < 3 && hit_goodness_of_fit_vec->at(k) > 0){
            if(hit_goodness_of_fit_vec->at(k) == -1){

              if(true_thetaXZ > 0  && true_thetaXZ < 10){ h_charge_0->Fill(hit_charge_vec->at(k));}
              if(true_thetaXZ > 30 && true_thetaXZ < 40){ h_charge_30->Fill(hit_charge_vec->at(k));}
              if(true_thetaXZ > 50 && true_thetaXZ < 60){ h_charge_50->Fill(hit_charge_vec->at(k));}

              if(true_thetaXZ > 85 && true_thetaXZ < 95){
                res_90 = (reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k)) / true_hit_energy_vec->at(k);
                reco_90 += reco_hit_energy_vec->at(k);
                true_90 += true_hit_energy_vec->at(k);
                h_res_90->Fill(res_90);
              }

              if(true_thetaXZ > 65 && true_thetaXZ < 75){
                res_70 = (reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k)) / true_hit_energy_vec->at(k);
                reco_70 += reco_hit_energy_vec->at(k);
                true_70 += true_hit_energy_vec->at(k);
                h_res_70->Fill(res_70);
             }
             if(true_thetaXZ > 45 && true_thetaXZ < 55){
                res_50 = (reco_hit_energy_vec->at(k) - true_hit_energy_vec->at(k)) / true_hit_energy_vec->at(k);
                h_res_50->Fill(res_50);
             }

              if(true_thetaXZ > 65 && true_thetaXZ < 75){
                h_chi2_70->Fill(hit_goodness_of_fit_vec->at(k));
                h_peak_time_70->Fill(hit_peak_time_vec->at(k));
                h_rms_70->Fill(hit_rms_vec->at(k));
                h_peak_amp_70->Fill(hit_peak_amp_vec->at(k));
                h_summed_adc_70->Fill(hit_summed_adc_vec->at(k));
                h_integral_70->Fill(hit_integral_vec->at(k));
                h_multiplicity_70->Fill(hit_multiplicity_vec->at(k));
                h_charge_70->Fill(hit_charge_vec->at(k));
              }
              if(true_thetaXZ > 85 && true_thetaXZ < 95){
                h_chi2_90->Fill(hit_goodness_of_fit_vec->at(k));
                h_peak_time_90->Fill(hit_peak_time_vec->at(k));
                h_rms_90->Fill(hit_rms_vec->at(k));
                h_peak_amp_90->Fill(hit_peak_amp_vec->at(k));
                h_summed_adc_90->Fill(hit_summed_adc_vec->at(k));
                h_integral_90->Fill(hit_integral_vec->at(k));
                h_multiplicity_90->Fill(hit_multiplicity_vec->at(k));
                h_charge_90->Fill(hit_charge_vec->at(k));
                h_chi2_vs_energy->Fill(hit_goodness_of_fit_vec->at(k), reco_hit_energy_vec->at(k));
                if(hit_goodness_of_fit_vec->at(k) == -1){
                  std::cout << "true energy: " << true_hit_energy_vec->at(k) << "  reco energy: " << reco_hit_energy_vec->at(k) << std::endl;

                }
              }
              p_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (hit_goodness_of_fit_vec->at(k)));
              if(hit_goodness_of_fit_vec->at(k) < 0){continue;}
              h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (hit_goodness_of_fit_vec->at(k)));
              p_frac_res_vs_thetaXZ_cut->Fill(true_thetaXZ, (hit_goodness_of_fit_vec->at(k)));
              //h_frac_res_vs_thetaYZ->Fill(true_thetaYZ, (reco_hit_energy_vec->at(k)-true_hit_energy_vec->at(k))/true_hit_energy_vec->at(k));

           }

         }

          //h_frac_res_vs_thetaXZ->Fill(true_thetaXZ, (reco_energy-true_hit_energy)/true_hit_energy);
          //h_frac_res_vs_thetaYZ->Fill(true_thetaYZ, (reco_energy-true_hit_energy)/true_hit_energy);
                    
                  

          break;
        }
    }
    //h_res_90->Fill((reco_90 - true_90)/true_90);
    //h_res_70->Fill((reco_70 - true_70)/true_70);

}

//std::cout << "90 hits: " << nintyhits/nintydeg << std::endl;
//std::cout << "70 hits: " << seventyhits/seventydeg << std::endl;

// plot resolution as function of thetaXZ and thetaYZ

TCanvas *c_thetaXZ = new TCanvas("");  
h_frac_res_vs_thetaXZ->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");
h_frac_res_vs_thetaXZ->GetYaxis()->SetTitle("Hit Goodness of Fit");
h_frac_res_vs_thetaXZ->Draw("colz");

TCanvas *c_thetaYZ = new TCanvas("");  
h_frac_res_vs_thetaYZ->GetXaxis()->SetTitle("#theta_{YZ} [degrees]");
h_frac_res_vs_thetaYZ->GetYaxis()->SetTitle("#frac{reco-true}{true} [Energy]");
h_frac_res_vs_thetaYZ->Draw("colz");

TCanvas *c_thetaXZ_profile = new TCanvas("");  
p_frac_res_vs_thetaXZ->GetXaxis()->SetTitle("#theta_{XZ} [degrees]");
p_frac_res_vs_thetaXZ->GetYaxis()->SetTitle("Hit Goodness of Fit");
p_frac_res_vs_thetaXZ->Draw();
p_frac_res_vs_thetaXZ->SetLineColor(kRed);
p_frac_res_vs_thetaXZ->SetLineWidth(3);
p_frac_res_vs_thetaXZ_cut->Draw("same");
p_frac_res_vs_thetaXZ_cut->SetLineWidth(3);

TCanvas *c_chi2 = new TCanvas("");
h_chi2_70->Scale(1/h_chi2_70->Integral());
h_chi2_70->Draw();
h_chi2_70->SetLineColor(kRed);
h_chi2_70->SetLineWidth(3);
h_chi2_70->GetXaxis()->SetTitle("Goodness of Fit");
h_chi2_70->GetYaxis()->SetTitle("Normalised Events");

h_chi2_90->Scale(1/h_chi2_90->Integral());
h_chi2_90->Draw("same");
h_chi2_90->SetLineWidth(3);

TLegend *chi2_leg = new TLegend();
chi2_leg->SetFillStyle(0);
chi2_leg->SetBorderSize(0);
chi2_leg->AddEntry(h_chi2_70, "70 Deg", "L");
chi2_leg->AddEntry(h_chi2_90, "90 Deg", "L");
chi2_leg->Draw();


TCanvas *c_peak_time = new TCanvas("");
h_peak_time_70->Scale(1/h_peak_time_70->Integral());
h_peak_time_70->Draw();
h_peak_time_70->SetLineColor(kRed);
h_peak_time_70->SetLineWidth(3);
h_peak_time_70->GetXaxis()->SetTitle("Hit Peak Time");
h_peak_time_70->GetYaxis()->SetTitle("Normalised Events");

h_peak_time_90->Scale(1/h_peak_time_90->Integral());
h_peak_time_90->Draw("same");
h_peak_time_90->SetLineWidth(3);


TCanvas *c_rms = new TCanvas("");
h_rms_70->Scale(1/h_rms_70->Integral());
h_rms_70->Draw();
h_rms_70->SetLineColor(kRed);
h_rms_70->SetLineWidth(3);
h_rms_70->GetXaxis()->SetTitle("Hit RMS");
h_rms_70->GetYaxis()->SetTitle("Normalised Events");

h_rms_90->Scale(1/h_rms_90->Integral());
h_rms_90->Draw("same");
h_rms_90->SetLineWidth(3);

TCanvas *c_peak_amp = new TCanvas("");
h_peak_amp_70->Scale(1/h_peak_amp_70->Integral());
h_peak_amp_70->Draw();
h_peak_amp_70->SetLineColor(kRed);
h_peak_amp_70->SetLineWidth(3);
h_peak_amp_70->GetXaxis()->SetTitle("Hit Peak Amplitude");
h_peak_amp_70->GetYaxis()->SetTitle("Normalised Events");

h_peak_amp_90->Scale(1/h_peak_amp_90->Integral());
h_peak_amp_90->Draw("same");
h_peak_amp_90->SetLineWidth(3);

TCanvas *c_summed_adc = new TCanvas("");
h_summed_adc_70->Scale(1/h_summed_adc_70->Integral());
h_summed_adc_70->Draw();
h_summed_adc_70->SetLineColor(kRed);
h_summed_adc_70->SetLineWidth(3);
h_summed_adc_70->GetXaxis()->SetTitle("Hit Summed ADC");
h_summed_adc_70->GetYaxis()->SetTitle("Normalised Events");

h_summed_adc_90->Scale(1/h_summed_adc_90->Integral());
h_summed_adc_90->Draw("same");
h_summed_adc_90->SetLineWidth(3);

TCanvas *c_integral = new TCanvas("");
h_integral_70->Scale(1/h_integral_70->Integral());
h_integral_70->Draw();
h_integral_70->SetLineColor(kRed);
h_integral_70->SetLineWidth(3);
h_integral_70->GetXaxis()->SetTitle("Hit Integral");
h_integral_70->GetYaxis()->SetTitle("Normalised Events");

h_integral_90->Scale(1/h_integral_90->Integral());
h_integral_90->Draw("same");
h_integral_90->SetLineWidth(3);

TCanvas *c_multiplicity = new TCanvas("");
h_multiplicity_70->Scale(1/h_multiplicity_70->Integral());
h_multiplicity_70->Draw();
h_multiplicity_70->SetLineColor(kRed);
h_multiplicity_70->SetLineWidth(3);
h_multiplicity_70->GetXaxis()->SetTitle("Hit Multiplicity");
h_multiplicity_70->GetYaxis()->SetTitle("Normalised Events");

h_multiplicity_90->Scale(1/h_multiplicity_90->Integral());
h_multiplicity_90->Draw("same");
h_multiplicity_90->SetLineWidth(3);

TCanvas *c_charge = new TCanvas("");
h_charge_70->Scale(1/h_charge_70->Integral());
h_charge_70->SetLineColor(kRed);
h_charge_70->SetLineWidth(3);
h_charge_70->GetXaxis()->SetTitle("Hit Charge");
h_charge_70->GetYaxis()->SetTitle("Normalised Events");
h_charge_70->Draw("Hist C");

/*
h_charge_0->Scale(1/h_charge_0->Integral());
h_charge_0->Draw("same, Hist C");
h_charge_0->SetLineWidth(3);
h_charge_0->SetLineColor(kMagenta);

h_charge_30->Scale(1/h_charge_30->Integral());
h_charge_30->Draw("same, Hist C");
h_charge_30->SetLineWidth(3);
h_charge_30->SetLineColor(kOrange+1);

h_charge_50->Scale(1/h_charge_50->Integral());
h_charge_50->Draw("same, Hist C");
h_charge_50->SetLineWidth(3);
h_charge_50->SetLineColor(kCyan);
*/
h_charge_90->Scale(1/h_charge_90->Integral());
h_charge_90->Draw("same, Hist C");
h_charge_90->SetLineWidth(3);


TLegend *l_charge = new TLegend();
l_charge->AddEntry(h_charge_0, "0-10 Deg", "L");
l_charge->AddEntry(h_charge_30, "30-40 Deg", "L");
l_charge->AddEntry(h_charge_50, "50-60 Deg", "L");
l_charge->AddEntry(h_charge_70, "65-75 Deg", "L");
l_charge->AddEntry(h_charge_90, "85-95 Deg", "L");
l_charge->Draw();



TCanvas *c_res = new TCanvas("");
h_res_90->Scale(1/h_res_90->Integral());
h_res_90->Draw("hist");
h_res_90->GetXaxis()->SetTitle("(reco - true)/true");
h_res_90->SetLineColor(kRed);
h_res_90->SetLineWidth(3);


h_res_70->Scale(1/h_res_70->Integral());
h_res_70->SetLineWidth(3);
h_res_70->Draw("hist, same");

h_res_50->Scale(1/h_res_50->Integral());
h_res_50->SetLineWidth(3);
h_res_50->SetLineColor(kGreen);
h_res_50->Draw("hist, same");


TCanvas *c_chi2_vs_energy = new TCanvas("");
h_chi2_vs_energy->Draw("colz");
h_chi2_vs_energy->GetXaxis()->SetTitle("Goodness of fit");
h_chi2_vs_energy->GetYaxis()->SetTitle("HitEnergy [MeV]");




}
