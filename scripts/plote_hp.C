#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include <math.h>
void plote()
{
  auto c1 = new TCanvas("c1","Energy response",200,10,700,500);
  c1->SetGrid();
  c1->GetFrame()->SetBorderSize(12);
  auto mg = new TMultiGraph();
  auto sigmg = new TMultiGraph();
  auto sqrtmg = new TMultiGraph();
  TLegend *leg = new TLegend(0.45, 0.6, 0.9, 0.89);
  const Int_t n = 7;
  const Int_t n_hp = 6;
  const Int_t n_k = 5;
  Double_t Ekin[n]={1.,2.,5.,10.,20.,50.,100.};
  Double_t sqrtEkin[n];
  const Double_t mpi=139.57039*0.001;
  const Double_t mk=493.677*0.001;
  const Double_t mp=938.2720813*0.001;
  Double_t e[n]={0.,0.,0.,0.,0.,0.,0.};
  Double_t e_hp[n]={0.,0.,0.,0.,0.,0.};
  Double_t Ekin_hp[n_hp]  = {1.,2.,5.,10.,20.,50.};
  Double_t sqrtEkin_hp[n_hp];
  Double_t Ekin_k[n_k]  = {1.,2.,5.,10.,20.};
  Double_t FTFP_BERT_63_ele_Edep[n]={
				     0.001*9.99280e+02,
				     0.001*1.99924e+03,
				     0.001*5.01375e+03,
				     0.001*9.99910e+03,
				     0.001*1.99962e+04,
				     0.001*4.99450e+04,
				     0.001*9.99607e+04};
  Double_t FTFP_BERT_63_Edep[n]={1.02018,1.90333,4.61387,9.25967,18.5262,46.5616,93.5625};
  Double_t FTFP_BERT_63_proton_Edep[n]={
					0.001*9.00318e+02,
					0.001*1.77825e+03,
					0.001*4.43880e+03,
					0.001*8.98919e+03,
					0.001*1.81788e+04,
					0.001*4.60178e+04,
					0.001*9.28141e+04};
  Double_t FTFP_INCLXX_71_Edep[n]=
    {
     0.001*1.03469e+03,
     0.001*1.95632e+03,
     0.001*4.70481e+03,
     0.001*9.34823e+03,
     0.001*1.87213e+04,
     0.001*4.69596e+04,
     0.001*9.43384e+04
    };
    Double_t FTFP_INCLXX_71_sigEdep[n]=
    {
      0.001*6.47540e+01,
      0.001*9.82373e+01,
      0.001*1.92601e+02,
      0.001*3.34808e+02,
      0.001*5.09347e+02,
      0.001*9.92788e+02,
      0.001*1.67243e+03
    };
  Double_t QGSP_BERT_71_Edep[n]=
    {
     0.001*1.01905e+03,
     0.001*1.90445e+03,
     0.001*4.60803e+03,
     0.001*9.26017e+03,
     0.001*1.86275e+04,
     0.001*4.69717e+04,
     0.001*9.42756e+04
    };
   Double_t QGSP_BERT_71_sigEdep[n]=
    {
     0.001*5.58096e+01,
     0.001*8.80630e+01,
     0.001*1.86253e+02,
     0.001*2.85823e+02,
     0.001*5.05698e+02,
     0.001*1.11447e+03,
     0.001*1.91837e+03
    };
 Double_t FTFP_BERT_71_Edep[n]=
    {
     0.001*1.02018e+03,
     0.001*1.90333e+03,
     0.001*4.61387e+03,
     0.001*9.25967e+03,
     0.001*1.85262e+04,
     0.001*4.65616e+04,
     0.001*9.35625e+04

    };
   Double_t FTFP_BERT_71_sigEdep[n]=
    {
     0.001*5.61740e+01,
     0.001*8.87100e+01,
     0.001*1.86142e+02,
     0.001*2.84127e+02,
     0.001*4.72885e+02,
     0.001*9.54156e+02,
     0.001*1.68432e+03
    };
   
  for (int i=0;i<n;i++)
    {
      sqrtEkin[i]=1./sqrt(Ekin[i]);
      //
      FTFP_BERT_63_ele_Edep[i]=100.*(FTFP_BERT_63_ele_Edep[i]-Ekin[i])/Ekin[i];
      FTFP_BERT_63_Edep[i]=100.* (FTFP_BERT_63_Edep[i]-Ekin[i]-mpi)/(Ekin[i]+mpi);
      FTFP_BERT_63_proton_Edep[i]=100.*(FTFP_BERT_63_proton_Edep[i]-Ekin[i])/Ekin[i];
      //
      FTFP_BERT_71_Edep[i]=100.*(FTFP_BERT_71_Edep[i]-Ekin[i]-mpi)/(Ekin[i]+mpi);
      FTFP_INCLXX_71_Edep[i]=100.*(FTFP_INCLXX_71_Edep[i]-Ekin[i]-mpi)/(Ekin[i]+mpi);
      QGSP_BERT_71_Edep[i]=100.*(QGSP_BERT_71_Edep[i]-Ekin[i]-mpi)/(Ekin[i]+mpi);
      //
      FTFP_BERT_71_sigEdep[i]=100.*(FTFP_BERT_71_sigEdep[i])/(Ekin[i]+mpi);
      FTFP_INCLXX_71_sigEdep[i]=100.*(FTFP_INCLXX_71_sigEdep[i])/(Ekin[i]+mpi);
      QGSP_BERT_71_sigEdep[i]=100.*(QGSP_BERT_71_sigEdep[i])/(Ekin[i]+mpi);	
    }
  
  Double_t FTFP_BERT_63_kaonplus_Edep[n_k]={
					    0.001*1.25344e+03,
					    0.001*2.14198e+03,
					    0.001*4.84037e+03,
					    0.001*9.45913e+03,
					    0.001*1.87000e+04					  
  };
  
  
  Double_t FTFP_BERT_63_pbar_Edep[n_k]={
					0.001*2.60363e+03,
					0.001*3.49754e+03,
					0.001*6.20162e+03,
					0.001*1.07891e+04,
					0.001*2.00174e+04
  };
  for (int i=0;i<n_k;i++)
    {
      FTFP_BERT_63_kaonplus_Edep[i]= 100.*(FTFP_BERT_63_kaonplus_Edep[i]-Ekin[i]-mk)/(Ekin[i]+mk);
      FTFP_BERT_63_pbar_Edep[i]=     100.*(FTFP_BERT_63_pbar_Edep[i]	-(Ekin[i]+2*mp))/(Ekin[i]+2*mp);
    }
  
  
  Double_t FTFP_BERT_HP_71_Edep[n_hp]={1.36259,2.57037,6.08753,11.8140,23.2571,57.1341};
  Double_t FTFP_BERT_HP_71_sigEdep[n_hp]={0.172422,
					  0.242114,
					  0.420143,
					  0.634273,
					  1.00070,
					  1.94795
};
  for (int i=0;i<n_hp;i++)
    {
      
      sqrtEkin_hp[i] = 1./sqrt(Ekin_hp[i]);
      FTFP_BERT_HP_71_Edep[i]=  100.*( FTFP_BERT_HP_71_Edep[i]	-Ekin[i]-mpi)/(Ekin_hp[i]+mpi);
      FTFP_BERT_HP_71_sigEdep[i]=  100.*( FTFP_BERT_HP_71_sigEdep[i])/(Ekin_hp[i]+mpi);
    }
  //
  auto  FTFP_BERT_63_ele_Edep_gr = new TGraph(n,Ekin, FTFP_BERT_63_ele_Edep);
  FTFP_BERT_63_ele_Edep_gr->SetMarkerColor(kCyan);
  FTFP_BERT_63_ele_Edep_gr->SetLineColor(kCyan);
  FTFP_BERT_63_ele_Edep_gr->SetMarkerStyle(20);
  mg->Add( FTFP_BERT_63_ele_Edep_gr);
  leg->AddEntry( FTFP_BERT_63_ele_Edep_gr,"e^{-} FTFP_BERT Gent4.10.6.p03");
  
  auto  FTFP_BERT_63_kaonplus_Edep_gr = new TGraph(n_k,Ekin_k, FTFP_BERT_63_kaonplus_Edep);
  FTFP_BERT_63_kaonplus_Edep_gr->SetMarkerColor(kOrange);
  FTFP_BERT_63_kaonplus_Edep_gr->SetLineColor(kOrange);
  FTFP_BERT_63_kaonplus_Edep_gr->SetMarkerStyle(20);
  mg->Add( FTFP_BERT_63_kaonplus_Edep_gr);
  leg->AddEntry( FTFP_BERT_63_kaonplus_Edep_gr,"K^{+} FTFP_BERT Gent4.10.6.p03");
  
  auto  FTFP_BERT_63_proton_Edep_gr = new TGraph(n,Ekin, FTFP_BERT_63_proton_Edep);
  FTFP_BERT_63_proton_Edep_gr->SetMarkerColor(kBlack);
  FTFP_BERT_63_proton_Edep_gr->SetLineColor(kBlack);
  FTFP_BERT_63_proton_Edep_gr->SetMarkerStyle(20);
  mg->Add( FTFP_BERT_63_proton_Edep_gr);
  leg->AddEntry( FTFP_BERT_63_proton_Edep_gr,"proton FTFP_BERT Gent4.10.6.p03");  
  
  auto  FTFP_BERT_63_pbar_Edep_gr = new TGraph(n_k,Ekin_k, FTFP_BERT_63_pbar_Edep);
  FTFP_BERT_63_pbar_Edep_gr->SetMarkerColor(kViolet);
  FTFP_BERT_63_pbar_Edep_gr->SetLineColor(kViolet);
  FTFP_BERT_63_pbar_Edep_gr->SetMarkerStyle(20);
  mg->Add( FTFP_BERT_63_pbar_Edep_gr);
  leg->AddEntry( FTFP_BERT_63_pbar_Edep_gr,"anti proton FTFP_BERT Gent4.10.6.p03");
  
  auto FTFP_BERT_63_Edep_gr = new TGraph(n,Ekin,FTFP_BERT_63_Edep);
  FTFP_BERT_63_Edep_gr->SetMarkerColor(kRed);
  FTFP_BERT_63_Edep_gr->SetLineColor(kRed);
  FTFP_BERT_63_Edep_gr->SetMarkerStyle(21);
  mg->Add(FTFP_BERT_63_Edep_gr);
  leg->AddEntry(FTFP_BERT_63_Edep_gr,"#pi^{+} FTFP_BERT Gent4.10.6.p03");
  auto FTFP_INCLXX_71_Edep_gr = new TGraph(n,Ekin,FTFP_INCLXX_71_Edep);
  FTFP_INCLXX_71_Edep_gr->SetMarkerColor(kBlue);
  FTFP_INCLXX_71_Edep_gr->SetLineColor(kBlue);
  FTFP_INCLXX_71_Edep_gr->SetMarkerStyle(24);
  mg->Add(FTFP_INCLXX_71_Edep_gr);
  leg->AddEntry(FTFP_INCLXX_71_Edep_gr,"#pi^{+} FTFP_INCLXX Geant4.10.7.p01");
  //
  auto QGSP_BERT_71_Edep_gr = new TGraph(n,Ekin,QGSP_BERT_71_Edep);
  QGSP_BERT_71_Edep_gr->SetMarkerColor(kGreen);
  QGSP_BERT_71_Edep_gr->SetLineColor(kGreen);
  QGSP_BERT_71_Edep_gr->SetMarkerStyle(25);
  mg->Add(QGSP_BERT_71_Edep_gr);
  leg->AddEntry(QGSP_BERT_71_Edep_gr,"#pi^{+} QGSP_BERT Geant4.10.7.p01");
  //
  auto FTFP_BERT_HP_71_Edep_gr = new TGraph(n_hp,Ekin_hp,FTFP_BERT_HP_71_Edep);
  FTFP_BERT_HP_71_Edep_gr->SetMarkerColor(kMagenta);
  FTFP_BERT_HP_71_Edep_gr->SetLineColor(kMagenta);
  FTFP_BERT_HP_71_Edep_gr->SetMarkerStyle(23);
  mg->Add( FTFP_BERT_HP_71_Edep_gr);
  leg->AddEntry(FTFP_BERT_HP_71_Edep_gr,"#pi^{+} FTFP_BERT_HP Geant4.10.7.p01");
  //
  auto FTFP_BERT_71_Edep_gr = new TGraph(n,Ekin,FTFP_BERT_71_Edep);
  FTFP_BERT_71_Edep_gr->SetMarkerColor(kMagenta);
  FTFP_BERT_71_Edep_gr->SetLineColor(kMagenta);
  FTFP_BERT_71_Edep_gr->SetMarkerStyle(24);
  mg->Add( FTFP_BERT_71_Edep_gr);
  leg->AddEntry(FTFP_BERT_71_Edep_gr,"#pi^{+} FTFP_BERT Geant4.10.7.p01");
  //
  mg->GetXaxis()->SetTitle("Ekin [GeV]");
  mg->GetYaxis()->SetTitle("relative difference (Edep-Eavail/Eavail) [%]");
  mg->SetMinimum(-20.);
  mg->SetMaximum(40.);
  mg->Draw("lap");
  leg->Draw();
  c1->Update();

  auto c2 = new TCanvas("c2","sigma Energy",200,10,700,500);
  TLegend *sigleg = new TLegend(0.45, 0.6, 0.9, 0.89);
  c2->SetGrid();
  c2->GetFrame()->SetBorderSize(12);
  auto FTFP_INCLXX_71_sigEdep_gr = new TGraph(n,Ekin,FTFP_INCLXX_71_sigEdep);
  FTFP_INCLXX_71_sigEdep_gr->SetMarkerColor(kBlue);
  FTFP_INCLXX_71_sigEdep_gr->SetLineColor(kBlue);
  FTFP_INCLXX_71_sigEdep_gr->SetMarkerStyle(24);
  sigmg->Add(FTFP_INCLXX_71_sigEdep_gr);
  sigleg->AddEntry(FTFP_INCLXX_71_sigEdep_gr,"#pi^{+} FTFP_INCLXX Geant4.10.7.p01");
  //
  auto QGSP_BERT_71_sigEdep_gr = new TGraph(n,Ekin,QGSP_BERT_71_sigEdep);
  QGSP_BERT_71_sigEdep_gr->SetMarkerColor(kGreen);
  QGSP_BERT_71_sigEdep_gr->SetLineColor(kGreen);
  QGSP_BERT_71_sigEdep_gr->SetMarkerStyle(25);
  sigmg->Add(QGSP_BERT_71_sigEdep_gr);
  sigleg->AddEntry(QGSP_BERT_71_sigEdep_gr,"#pi^{+} QGSP_BERT Geant4.10.7.p01");
  //
  auto FTFP_BERT_HP_71_sigEdep_gr = new TGraph(n_hp,Ekin_hp,FTFP_BERT_HP_71_sigEdep);
  FTFP_BERT_HP_71_sigEdep_gr->SetMarkerColor(kMagenta);
  FTFP_BERT_HP_71_sigEdep_gr->SetLineColor(kMagenta);
  FTFP_BERT_HP_71_sigEdep_gr->SetMarkerStyle(23);
  sigmg->Add( FTFP_BERT_HP_71_sigEdep_gr);
  sigleg->AddEntry(FTFP_BERT_HP_71_sigEdep_gr,"#pi^{+} FTFP_BERT_HP Geant4.10.7.p01");
  //
  auto FTFP_BERT_71_sigEdep_gr = new TGraph(n,Ekin,FTFP_BERT_71_sigEdep);
  FTFP_BERT_71_sigEdep_gr->SetMarkerColor(kMagenta);
  FTFP_BERT_71_sigEdep_gr->SetLineColor(kMagenta);
  FTFP_BERT_71_sigEdep_gr->SetMarkerStyle(24);
  sigmg->Add( FTFP_BERT_71_sigEdep_gr);
  sigleg->AddEntry(FTFP_BERT_71_sigEdep_gr,"#pi^{+} FTFP_BERT Geant4.10.7.p01");
  //
  sigmg->GetXaxis()->SetTitle("Ekin [GeV]");
  sigmg->GetYaxis()->SetTitle("sigma of energy response (sigEdep/Eavail) [%]");
  sigmg->SetMinimum(0.);
  sigmg->SetMaximum(20.);
  sigmg->Draw("lap");
  sigleg->Draw();
  c2->Update();
  //
  auto c3 = new TCanvas("c3","sigma Energy",200,10,700,500);
  TLegend *sqrtleg = new TLegend(0.15, 0.6, 0.5, 0.89);
  c3->SetGrid();
  c3->GetFrame()->SetBorderSize(12);
  auto FTFP_INCLXX_71_sqrtEdep_gr = new TGraph(n,sqrtEkin,FTFP_INCLXX_71_sigEdep);
  FTFP_INCLXX_71_sqrtEdep_gr->SetMarkerColor(kBlue);
  FTFP_INCLXX_71_sqrtEdep_gr->SetLineColor(kBlue);
  FTFP_INCLXX_71_sqrtEdep_gr->SetMarkerStyle(24);
  //FTFP_INCLXX_71_sqrtEdep_gr->Fit("pol1");
  sqrtmg->Add(FTFP_INCLXX_71_sqrtEdep_gr);
  sqrtleg->AddEntry(FTFP_INCLXX_71_sqrtEdep_gr,"#pi^{+} FTFP_INCLXX Geant4.10.7.p01");
  //
  auto QGSP_BERT_71_sqrtEdep_gr = new TGraph(n,sqrtEkin,QGSP_BERT_71_sigEdep);
  QGSP_BERT_71_sqrtEdep_gr->SetMarkerColor(kGreen);
  QGSP_BERT_71_sqrtEdep_gr->SetLineColor(kGreen);
  QGSP_BERT_71_sqrtEdep_gr->SetMarkerStyle(25);
  //QGSP_BERT_71_sqrtEdep_gr->Fit("pol1");
  sqrtmg->Add(QGSP_BERT_71_sqrtEdep_gr);
  sqrtleg->AddEntry(QGSP_BERT_71_sqrtEdep_gr,"#pi^{+} QGSP_BERT Geant4.10.7.p01");
  //
  auto FTFP_BERT_HP_71_sqrtEdep_gr = new TGraph(n_hp,sqrtEkin_hp,FTFP_BERT_HP_71_sigEdep);
  FTFP_BERT_HP_71_sqrtEdep_gr->SetMarkerColor(kMagenta);
  FTFP_BERT_HP_71_sqrtEdep_gr->SetLineColor(kMagenta);
  FTFP_BERT_HP_71_sqrtEdep_gr->SetMarkerStyle(23);
  //FTFP_BERT_HP_71_sqrtEdep_gr->Fit("pol1");
  sqrtmg->Add( FTFP_BERT_HP_71_sqrtEdep_gr);
  sqrtleg->AddEntry(FTFP_BERT_HP_71_sqrtEdep_gr,"#pi^{+} FTFP_BERT_HP Geant4.10.7.p01");
  //
  auto FTFP_BERT_71_sqrtEdep_gr = new TGraph(n,sqrtEkin,FTFP_BERT_71_sigEdep);
  FTFP_BERT_71_sqrtEdep_gr->SetMarkerColor(kMagenta);
  FTFP_BERT_71_sqrtEdep_gr->SetLineColor(kMagenta);
  FTFP_BERT_71_sqrtEdep_gr->SetMarkerStyle(24);
  //  FTFP_BERT_71_sqrtEdep_gr->Fit("pol1");
  sqrtmg->Add( FTFP_BERT_71_sqrtEdep_gr);
  sqrtleg->AddEntry(FTFP_BERT_71_sqrtEdep_gr,"#pi^{+} FTFP_BERT Geant4.10.7.p01");
  //
  sqrtmg->GetXaxis()->SetTitle("1/#sqrt{Ekin} ");
  sqrtmg->GetYaxis()->SetTitle("sigma of energy response (sigEdep/Eavail) [%]");
  sqrtmg->SetMinimum(0.);
  sqrtmg->SetMaximum(20.);
  sqrtmg->Draw("lap");
  sqrtleg->Draw();
  c3->Update();
  
  
}
