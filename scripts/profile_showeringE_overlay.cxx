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

void profile_showeringE_overlay(){

//ESTAR
   TCanvas *c1_n4 = new TCanvas("c1_n4", "",10,65,700,500);
   c1_n4->Range(-146.1538,-0.6246214,1238.462,0.001604726);
   c1_n4->SetFillColor(0);
   c1_n4->SetBorderMode(0);
   c1_n4->SetBorderSize(2);
   c1_n4->SetLeftMargin(0.12);
   c1_n4->SetFrameBorderMode(0);
   c1_n4->SetFrameBorderMode(0);
   
   TProfile *b = new TProfile("b","",25,20,1100,"s");
   b->SetBinEntries(0,89);
   b->SetBinEntries(1,235);
   b->SetBinEntries(2,234);
   b->SetBinEntries(3,233);
   b->SetBinEntries(4,488);
   b->SetBinEntries(5,477);
   b->SetBinEntries(6,462);
   b->SetBinEntries(7,439);
   b->SetBinEntries(8,432);
   b->SetBinEntries(9,464);
   b->SetBinEntries(10,421);
   b->SetBinEntries(11,411);
   b->SetBinEntries(12,419);
   b->SetBinEntries(13,410);
   b->SetBinEntries(14,391);
   b->SetBinEntries(15,334);
   b->SetBinEntries(16,357);
   b->SetBinEntries(17,346);
   b->SetBinEntries(18,263);
   b->SetBinEntries(19,247);
   b->SetBinEntries(20,244);
   b->SetBinEntries(21,264);
   b->SetBinEntries(22,237);
   b->SetBinEntries(23,261);
   b->SetBinEntries(24,205);
   b->SetBinEntries(25,171);
   b->SetBinEntries(26,1433);
   b->SetBinContent(0,-48.882);
   b->SetBinContent(1,-81.262);
   b->SetBinContent(2,-58.344);
   b->SetBinContent(3,-51.858);
   b->SetBinContent(4,-103.2);
   b->SetBinContent(5,-97.218);
   b->SetBinContent(6,-91.084);
   b->SetBinContent(7,-86.414);
   b->SetBinContent(8,-82.56);
   b->SetBinContent(9,-91.056);
   b->SetBinContent(10,-79.23);
   b->SetBinContent(11,-74.95);
   b->SetBinContent(12,-78.322);
   b->SetBinContent(13,-76.888);
   b->SetBinContent(14,-74.762);
   b->SetBinContent(15,-58.504);
   b->SetBinContent(16,-69.362);
   b->SetBinContent(17,-65.564);
   b->SetBinContent(18,-48.526);
   b->SetBinContent(19,-44.798);
   b->SetBinContent(20,-45.62);
   b->SetBinContent(21,-48.356);
   b->SetBinContent(22,-44.782);
   b->SetBinContent(23,-48.346);
   b->SetBinContent(24,-34.674);
   b->SetBinContent(25,-31.406);
   b->SetBinContent(26,-271.97);
   b->SetBinError(0,5.561661);
   b->SetBinError(1,6.074325);
   b->SetBinError(2,4.435537);
   b->SetBinError(3,3.921131);
   b->SetBinError(4,5.263055);
   b->SetBinError(5,5.062656);
   b->SetBinError(6,4.824337);
   b->SetBinError(7,4.692509);
   b->SetBinError(8,4.436723);
   b->SetBinError(9,4.795144);
   b->SetBinError(10,4.330715);
   b->SetBinError(11,4.015834);
   b->SetBinError(12,4.305525);
   b->SetBinError(13,4.247831);
   b->SetBinError(14,4.281244);
   b->SetBinError(15,3.473888);
   b->SetBinError(16,4.12471);
   b->SetBinError(17,3.919711);
   b->SetBinError(18,3.328994);
   b->SetBinError(19,3.187821);
   b->SetBinError(20,3.32756);
   b->SetBinError(21,3.293344);
   b->SetBinError(22,3.249938);
   b->SetBinError(23,3.290601);
   b->SetBinError(24,2.576016);
   b->SetBinError(25,2.659837);
   b->SetBinError(26,8.03158);
   b->SetEntries(8445);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.695,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("b");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 8445   ");
   ptstats_LaTex = ptstats->AddText("Mean  =  513.2");
   ptstats_LaTex = ptstats->AddText("Mean y = -0.1974");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  281.1");
   ptstats_LaTex = ptstats->AddText("Std Dev y =  0.107");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   b->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(b);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   b->SetLineColor(ci);
   b->SetLineWidth(2);
   b->GetXaxis()->SetTitle("Energy [MeV]");
   b->GetXaxis()->SetLabelFont(42);
   b->GetXaxis()->SetTitleOffset(1);
   b->GetXaxis()->SetTitleFont(42);
   b->GetYaxis()->SetTitle("#frac{Reco-True}{True} [Energy]");
   b->GetYaxis()->SetLabelFont(42);
   b->GetYaxis()->SetTitleFont(42);
   b->GetZaxis()->SetLabelFont(42);
   b->GetZaxis()->SetTitleOffset(1);
   b->GetZaxis()->SetTitleFont(42);
   b->Draw("");
   c1_n4->Modified();
   c1_n4->cd();
   c1_n4->SetSelected(c1_n4);

  b->SetLineWidth(3);
  b->SetLineColor(kBlue);
  b->GetYaxis()->SetRangeUser(-0.6, 0.1);

// OldMethod
   TProfile *b_oldmethod = new TProfile("b_oldmethod","",25,20,1100,"s");
   b_oldmethod->SetBinEntries(0,89);
   b_oldmethod->SetBinEntries(1,235);
   b_oldmethod->SetBinEntries(2,234);
   b_oldmethod->SetBinEntries(3,233);
   b_oldmethod->SetBinEntries(4,488);
   b_oldmethod->SetBinEntries(5,477);
   b_oldmethod->SetBinEntries(6,462);
   b_oldmethod->SetBinEntries(7,439);
   b_oldmethod->SetBinEntries(8,432);
   b_oldmethod->SetBinEntries(9,464);
   b_oldmethod->SetBinEntries(10,421);
   b_oldmethod->SetBinEntries(11,411);
   b_oldmethod->SetBinEntries(12,419);
   b_oldmethod->SetBinEntries(13,410);
   b_oldmethod->SetBinEntries(14,391);
   b_oldmethod->SetBinEntries(15,334);
   b_oldmethod->SetBinEntries(16,357);
   b_oldmethod->SetBinEntries(17,346);
   b_oldmethod->SetBinEntries(18,263);
   b_oldmethod->SetBinEntries(19,247);
   b_oldmethod->SetBinEntries(20,244);
   b_oldmethod->SetBinEntries(21,264);
   b_oldmethod->SetBinEntries(22,237);
   b_oldmethod->SetBinEntries(23,261);
   b_oldmethod->SetBinEntries(24,205);
   b_oldmethod->SetBinEntries(25,171);
   b_oldmethod->SetBinEntries(26,1433);
   b_oldmethod->SetBinContent(0,-44.514);
   b_oldmethod->SetBinContent(1,-64.518);
   b_oldmethod->SetBinContent(2,-38.376);
   b_oldmethod->SetBinContent(3,-31.058);
   b_oldmethod->SetBinContent(4,-60.144);
   b_oldmethod->SetBinContent(5,-55.306);
   b_oldmethod->SetBinContent(6,-49.068);
   b_oldmethod->SetBinContent(7,-46.426);
   b_oldmethod->SetBinContent(8,-42.78);
   b_oldmethod->SetBinContent(9,-48.156);
   b_oldmethod->SetBinContent(10,-40.126);
   b_oldmethod->SetBinContent(11,-35.586);
   b_oldmethod->SetBinContent(12,-38.802);
   b_oldmethod->SetBinContent(13,-38.46);
   b_oldmethod->SetBinContent(14,-38.258);
   b_oldmethod->SetBinContent(15,-26.836);
   b_oldmethod->SetBinContent(16,-36.29);
   b_oldmethod->SetBinContent(17,-33.376);
   b_oldmethod->SetBinContent(18,-24.19);
   b_oldmethod->SetBinContent(19,-21.034);
   b_oldmethod->SetBinContent(20,-23.156);
   b_oldmethod->SetBinContent(21,-23.604);
   b_oldmethod->SetBinContent(22,-22.682);
   b_oldmethod->SetBinContent(23,-23.594);
   b_oldmethod->SetBinContent(24,-15.174);
   b_oldmethod->SetBinContent(25,-15.234);
   b_oldmethod->SetBinContent(26,-138.798);
   b_oldmethod->SetBinError(0,5.228161);
   b_oldmethod->SetBinError(1,5.365049);
   b_oldmethod->SetBinError(2,3.570494);
   b_oldmethod->SetBinError(3,2.968788);
   b_oldmethod->SetBinError(4,3.82256);
   b_oldmethod->SetBinError(5,3.678694);
   b_oldmethod->SetBinError(6,3.458845);
   b_oldmethod->SetBinError(7,3.362931);
   b_oldmethod->SetBinError(8,3.011827);
   b_oldmethod->SetBinError(9,3.365453);
   b_oldmethod->SetBinError(10,2.950274);
   b_oldmethod->SetBinError(11,2.470254);
   b_oldmethod->SetBinError(12,2.900292);
   b_oldmethod->SetBinError(13,2.860485);
   b_oldmethod->SetBinError(14,2.996435);
   b_oldmethod->SetBinError(15,2.136373);
   b_oldmethod->SetBinError(16,2.854008);
   b_oldmethod->SetBinError(17,2.616748);
   b_oldmethod->SetBinError(18,2.227184);
   b_oldmethod->SetBinError(19,2.07433);
   b_oldmethod->SetBinError(20,2.343771);
   b_oldmethod->SetBinError(21,2.153732);
   b_oldmethod->SetBinError(22,2.213483);
   b_oldmethod->SetBinError(23,2.122954);
   b_oldmethod->SetBinError(24,1.466191);
   b_oldmethod->SetBinError(25,1.745572);
   b_oldmethod->SetBinError(26,5.464671);
   b_oldmethod->SetEntries(8445);

  b_oldmethod->SetLineWidth(3);
  b_oldmethod->SetLineColor(kRed);
  b_oldmethod->Draw("same");


// Make line at 0                                                                                                                                                                       
const int n_points = 2;                                                                                                                                                                 
int x[n_points] = {0, 2000};                                                                                                                                                            
int y[n_points] = {0, 0};                                                                                                                                                               
TGraph *line = new TGraph(n_points,x,y);                                                                                                                                                
                                                                                                                                                                                        
line->SetLineColor(kBlack);                                                                                                                                                             
line->SetLineWidth(3);                                                                                                                                                                  
line->Draw("same"); 


TLegend *l = new TLegend(0.6, 0.2, 0.8, 0.4);
l->SetBorderSize(0); 
l->AddEntry(b, "ESTAR", "L");
l->AddEntry(b_oldmethod, "OldMethod", "L");
l->Draw("same");

}
