#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TAxis.h"

void bench()
{
  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
  c1->SetGrid();
  double yield[5]={50,100,5000,10000,50000};
  double re[5]={15.048,14.746,22.855,30.370,105.075};
  double user[5]={13.421,13.404,19.663,25.467,77.605};
  double sys[5]={1.357,1.308,3.149,4.868,19.097};
  //
  double re100[5]={27.692,26.596,34.237,42.607,147.128};
  double user100[5]={23.532,23.269,29.237,35.996,90.847};
  double sys100[5]={3.488,3.288,4.866,6.34,25.562};
  // rtx1 10
  double rertx[5]={13.159,12.16,15.033,17.567,53.557};
  double userrtx[5]={11.465,11.154,13.086,14.914,31.031};
  double sysrtx[5]={1.130,0.985,1.924,2.627,10.545};
  //
  //    normalize to 100 evts
  //

  for (int i=0;i<5;i++)
    {
      re[i]=re[i]*0.01;
      user[i]=user[i]*0.01+sys[i]*0.01;
      sys[i]=sys[i]*0.01;
      re100[i]=re100[i]*0.01;
      user100[i]=user100[i]*0.01+sys100[i]*0.01;
      sys100[i]=sys100[i]*0.01;
      rertx[i]=rertx[i]*0.01;
      userrtx[i]=userrtx[i]*0.01+sysrtx[i]*0.01;
      sysrtx[i]=sysrtx[i]*0.01;
    }

  TGraph *real_gr = new TGraph(5,yield,re);
  real_gr->SetMinimum(0.0);
  real_gr->SetMaximum(1.5);
  TGraph *user_gr = new TGraph(5,yield,user);
  TGraph *sys_gr = new TGraph(5,yield,sys);
  TGraph *real100_gr = new TGraph(5,yield,re100);
  TGraph *user100_gr = new TGraph(5,yield,user100);
  TGraph *sys100_gr = new TGraph(5,yield,sys100);
  TGraph *realrtx_gr = new TGraph(5,yield,rertx);
  TGraph *userrtx_gr = new TGraph(5,yield,userrtx);
  TGraph *sysrtx_gr = new TGraph(5,yield,sysrtx);
 
  real_gr->SetLineColor(2);
  real_gr->SetLineWidth(1);
  real_gr->SetMarkerColor(2);
  real_gr->SetMarkerStyle(21);
  user_gr->SetLineColor(2);
  user_gr->SetLineWidth(1);
  user_gr->SetMarkerColor(2);
  user_gr->SetMarkerStyle(22);
  sys_gr->SetLineColor(2);
  sys_gr->SetLineWidth(1);
  sys_gr->SetMarkerColor(2);
  sys_gr->SetMarkerStyle(20);
  real_gr->SetTitle("G4OpticksTest Benchmarking results");
  real_gr->GetXaxis()->SetTitle("Photons/MeV");
  real_gr->GetYaxis()->SetTitle("sec/evt");
  real_gr->Draw();
  user_gr->Draw("PL SAME");
  //  sys_gr->Draw("PL SAME");

  real100_gr->SetLineColor(3);
  real100_gr->SetLineWidth(1);
  real100_gr->SetMarkerColor(3);
  real100_gr->SetMarkerStyle(21);
  user100_gr->SetLineColor(3);
  user100_gr->SetLineWidth(1);
  user100_gr->SetMarkerColor(3);
  user100_gr->SetMarkerStyle(22);
  sys100_gr->SetLineColor(3);
  sys100_gr->SetLineWidth(1);
  sys100_gr->SetMarkerColor(3);
  sys100_gr->SetMarkerStyle(20);
  real100_gr->Draw("PL SAME");
  user100_gr->Draw("PL SAME");
  //  sys100_gr->Draw("PL SAME");

  realrtx_gr->SetLineColor(4);
  realrtx_gr->SetLineWidth(1);
  realrtx_gr->SetMarkerColor(4);
  realrtx_gr->SetMarkerStyle(21);
  userrtx_gr->SetLineColor(4);
  userrtx_gr->SetLineWidth(1);
  userrtx_gr->SetMarkerColor(4);
  userrtx_gr->SetMarkerStyle(22);
  sysrtx_gr->SetLineColor(4);
  sysrtx_gr->SetLineWidth(1);
  sysrtx_gr->SetMarkerColor(4);
  sysrtx_gr->SetMarkerStyle(20);
  realrtx_gr->Draw("PL SAME");
  userrtx_gr->Draw("PL SAME");

  TLegend *leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(real_gr , "real rng10", "lp" );
  leg->AddEntry(user_gr , "CPU  rng10", "lp" );
  // leg->AddEntry(sys_gr  , "CPU sys rng10", "lp" );
  leg->AddEntry(real100_gr , "real rng100", "lp" );
  leg->AddEntry(user100_gr , "CPU user rng100", "lp" );
  //leg->AddEntry(sys100_gr  , "CPU sys rng100", "lp" );
  leg->AddEntry(realrtx_gr , "real rng10 rtx", "lp" );
  leg->AddEntry(userrtx_gr , "CPU rng10 rtx", "lp" );

  leg->Draw();
  c1->Update();
  c1->GetFrame()->SetBorderSize(12);
  c1->Modified();
  c1->Print("bench.png");
}
