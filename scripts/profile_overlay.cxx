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

void profile_overlay(){

//TFile *f  = new TFile("/sbnd/app/users/tham/larsoft_energy_tech_note/images/something.root","read"); 

//f->Draw();

//TProfile * prof = gROOT->ProcessLine(".x /sbnd/app/users/tham/larsoft_energy_tech_note/images/frac_res_vs_energy_cheating_2.C");

//ESTAR  
TCanvas *c1_n2 = new TCanvas("c1_n2", "",10,65,700,500);
   c1_n2->Range(-146.1538,-0.05627317,1238.462,0.07441429);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetLeftMargin(0.12);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   TProfile *a = new TProfile("a","",25,20,1100,"s");
   a->SetBinEntries(0,168);
   a->SetBinEntries(1,294);
   a->SetBinEntries(2,315);
   a->SetBinEntries(3,525);
   a->SetBinEntries(4,594);
   a->SetBinEntries(5,573);
   a->SetBinEntries(6,542);
   a->SetBinEntries(7,519);
   a->SetBinEntries(8,557);
   a->SetBinEntries(9,504);
   a->SetBinEntries(10,501);
   a->SetBinEntries(11,493);
   a->SetBinEntries(12,445);
   a->SetBinEntries(13,423);
   a->SetBinEntries(14,380);
   a->SetBinEntries(15,321);
   a->SetBinEntries(16,304);
   a->SetBinEntries(17,287);
   a->SetBinEntries(18,280);
   a->SetBinEntries(19,275);
   a->SetBinEntries(20,259);
   a->SetBinEntries(21,231);
   a->SetBinEntries(22,192);
   a->SetBinEntries(23,191);
   a->SetBinEntries(24,158);
   a->SetBinEntries(25,154);
   a->SetBinEntries(26,480);
   a->SetBinContent(0,-3.432);
   a->SetBinContent(1,1.824);
   a->SetBinContent(2,1.512);
   a->SetBinContent(3,7.68);
   a->SetBinContent(4,8.088);
   a->SetBinContent(5,6.816);
   a->SetBinContent(6,8.496);
   a->SetBinContent(7,6.336);
   a->SetBinContent(8,8.616);
   a->SetBinContent(9,7.944);
   a->SetBinContent(10,8.496);
   a->SetBinContent(11,7.752);
   a->SetBinContent(12,8.448);
   a->SetBinContent(13,7.128);
   a->SetBinContent(14,6.672);
   a->SetBinContent(15,5.832);
   a->SetBinContent(16,6.672);
   a->SetBinContent(17,5.208);
   a->SetBinContent(18,5.472);
   a->SetBinContent(19,4.104);
   a->SetBinContent(20,3.912);
   a->SetBinContent(21,4.248);
   a->SetBinContent(22,4.008);
   a->SetBinContent(23,3.96);
   a->SetBinContent(24,3.096);
   a->SetBinContent(25,3.144);
   a->SetBinContent(26,6.144);
   a->SetBinError(0,0.8576433);
   a->SetBinError(1,0.7732322);
   a->SetBinError(2,0.7139748);
   a->SetBinError(3,0.912);
   a->SetBinError(4,0.9608996);
   a->SetBinError(5,0.9056622);
   a->SetBinError(6,0.8876756);
   a->SetBinError(7,0.8673269);
   a->SetBinError(8,0.9656832);
   a->SetBinError(9,0.8623317);
   a->SetBinError(10,0.8492067);
   a->SetBinError(11,0.8461489);
   a->SetBinError(12,0.8410279);
   a->SetBinError(13,0.7330812);
   a->SetBinError(14,0.7319016);
   a->SetBinError(15,0.6620695);
   a->SetBinError(16,0.6702835);
   a->SetBinError(17,0.63995);
   a->SetBinError(18,0.5946966);
   a->SetBinError(19,0.5602856);
   a->SetBinError(20,0.5932419);
   a->SetBinError(21,0.5834518);
   a->SetBinError(22,0.5208608);
   a->SetBinError(23,0.5285452);
   a->SetBinError(24,0.5130614);
   a->SetBinError(25,0.5130614);
   a->SetBinError(26,0.6702835);
   a->SetEntries(9317);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.695,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("a");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 9317   ");
   ptstats_LaTex = ptstats->AddText("Mean  =  468.2");
   ptstats_LaTex = ptstats->AddText("Mean y = 0.01561");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  275.6");
   ptstats_LaTex = ptstats->AddText("Std Dev y = 0.03525");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   a->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(a);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   a->SetLineColor(ci);
   a->SetLineWidth(2);
   a->GetXaxis()->SetTitle("Energy [MeV]");
   a->GetXaxis()->SetLabelFont(42);
   a->GetXaxis()->SetTitleOffset(1);
   a->GetXaxis()->SetTitleFont(42);
   a->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
   a->GetYaxis()->SetLabelFont(42);
   a->GetYaxis()->SetTitleFont(42);
   a->GetZaxis()->SetLabelFont(42);
   a->GetZaxis()->SetTitleOffset(1);
   a->GetZaxis()->SetTitleFont(42);
   a->Draw("");
   c1_n2->Modified();
   c1_n2->cd();
   c1_n2->SetSelected(c1_n2);


  a->SetLineWidth(3);
  a->SetLineColor(kBlue);
  a->GetYaxis()->SetRangeUser(-0.2, 0.5);

// Old method
   TProfile *a_oldmethod = new TProfile("a_oldmethod","",25,20,1100,"s");
   a_oldmethod->SetBinEntries(0,167);
   a_oldmethod->SetBinEntries(1,294);
   a_oldmethod->SetBinEntries(2,315);
   a_oldmethod->SetBinEntries(3,525);
   a_oldmethod->SetBinEntries(4,594);
   a_oldmethod->SetBinEntries(5,573);
   a_oldmethod->SetBinEntries(6,542);
   a_oldmethod->SetBinEntries(7,519);
   a_oldmethod->SetBinEntries(8,557);
   a_oldmethod->SetBinEntries(9,505);
   a_oldmethod->SetBinEntries(10,501);
   a_oldmethod->SetBinEntries(11,494);
   a_oldmethod->SetBinEntries(12,445);
   a_oldmethod->SetBinEntries(13,423);
   a_oldmethod->SetBinEntries(14,380);
   a_oldmethod->SetBinEntries(15,321);
   a_oldmethod->SetBinEntries(16,304);
   a_oldmethod->SetBinEntries(17,287);
   a_oldmethod->SetBinEntries(18,280);
   a_oldmethod->SetBinEntries(19,275);
   a_oldmethod->SetBinEntries(20,259);
   a_oldmethod->SetBinEntries(21,231);
   a_oldmethod->SetBinEntries(22,192);
   a_oldmethod->SetBinEntries(23,191);
   a_oldmethod->SetBinEntries(24,158);
   a_oldmethod->SetBinEntries(25,154);
   a_oldmethod->SetBinEntries(26,480);
   a_oldmethod->SetBinContent(0,14.376);
   a_oldmethod->SetBinContent(1,35.04);
   a_oldmethod->SetBinContent(2,37.2);
   a_oldmethod->SetBinContent(3,68.016);
   a_oldmethod->SetBinContent(4,76.44);
   a_oldmethod->SetBinContent(5,72.72);
   a_oldmethod->SetBinContent(6,70.8);
   a_oldmethod->SetBinContent(7,64.968);
   a_oldmethod->SetBinContent(8,73.008);
   a_oldmethod->SetBinContent(9,65.88);
   a_oldmethod->SetBinContent(10,66.6);
   a_oldmethod->SetBinContent(11,64.08);
   a_oldmethod->SetBinContent(12,59.64);
   a_oldmethod->SetBinContent(13,55.824);
   a_oldmethod->SetBinContent(14,50.592);
   a_oldmethod->SetBinContent(15,42.864);
   a_oldmethod->SetBinContent(16,41.976);
   a_oldmethod->SetBinContent(17,38.544);
   a_oldmethod->SetBinContent(18,37.824);
   a_oldmethod->SetBinContent(19,35.496);
   a_oldmethod->SetBinContent(20,33.84);
   a_oldmethod->SetBinContent(21,30.888);
   a_oldmethod->SetBinContent(22,26.544);
   a_oldmethod->SetBinContent(23,26.016);
   a_oldmethod->SetBinContent(24,21.408);
   a_oldmethod->SetBinContent(25,21);
   a_oldmethod->SetBinContent(26,61.392);
   a_oldmethod->SetBinError(0,1.495529);
   a_oldmethod->SetBinError(1,2.216072);
   a_oldmethod->SetBinError(2,2.242941);
   a_oldmethod->SetBinError(3,3.119446);
   a_oldmethod->SetBinError(4,3.291677);
   a_oldmethod->SetBinError(5,3.183779);
   a_oldmethod->SetBinError(6,3.173631);
   a_oldmethod->SetBinError(7,3);
   a_oldmethod->SetBinError(8,3.248256);
   a_oldmethod->SetBinError(9,3.083136);
   a_oldmethod->SetBinError(10,3.094325);
   a_oldmethod->SetBinError(11,3.032939);
   a_oldmethod->SetBinError(12,2.952585);
   a_oldmethod->SetBinError(13,2.809128);
   a_oldmethod->SetBinError(14,2.693352);
   a_oldmethod->SetBinError(15,2.480722);
   a_oldmethod->SetBinError(16,2.489646);
   a_oldmethod->SetBinError(17,2.358359);
   a_oldmethod->SetBinError(18,2.331338);
   a_oldmethod->SetBinError(19,2.216202);
   a_oldmethod->SetBinError(20,2.191241);
   a_oldmethod->SetBinError(21,2.110227);
   a_oldmethod->SetBinError(22,1.97472);
   a_oldmethod->SetBinError(23,1.945925);
   a_oldmethod->SetBinError(24,1.776973);
   a_oldmethod->SetBinError(25,1.760527);
   a_oldmethod->SetBinError(26,2.881999);
   a_oldmethod->SetEntries(9319);

   a_oldmethod->SetLineWidth(3);
   a_oldmethod->SetLineColor(kRed);
   a_oldmethod->Draw("same");


// Make line at 0
const int n_points = 2;
int x[n_points] = {0, 2000};
int y[n_points] = {0, 0};
TGraph *line = new TGraph(n_points,x,y);

line->SetLineColor(kBlack);
line->SetLineWidth(3);
line->Draw("same");

TLegend *l = new TLegend(0.2, 0.6, 0.4, 0.8);
l->SetBorderSize(0); 
l->AddEntry(a, "ESTAR", "L");
l->AddEntry(a_oldmethod, "OldMethod", "L");
l->Draw("same");
}







