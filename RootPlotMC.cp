//
//RootPlotMCs.cpp
//
//want to compile this file usign g++
// g++ `root-config --cflags --glibs` RootPlotMC.cp -o RootPlotMC.exe
// ./RootPlotMC.exe

#include <stdio.h>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTreeReader.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include <TTree.h>


int main(){
    
    TString name[]={"CSIEt","GamClusCsiE","GamClusNumber", "KlongDeltaZ","KlongPt","Pi0Number","Pi0RecZ","Pi0Pt","Pi0Pt:Pi0RecZ"};
    TString GreekName[]={"CSIEt","GamClusCsiE","GamClusNumber", "K^{0}_{L}DeltaZ","K^{0}_{L}Pt","#pi^{0}Number","#pi^{0}RecZ","#pi^{0}Pt","#pi^{0}Pt:#pi^{0}RecZ"};
    std::vector<TCanvas*> c;
    
    std::vector<TH1F*> h;
    std::vector<TH1F*> mch;
    
    
    //open the file
    TFile *myFile = TFile::Open("~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root", "~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root");
    TFile *mcFile = TFile::Open("~/Desktop/Files_for_Koto/KL3pi0_160333.root", "~/Desktop/Files_for_Koto/KL3pi0_160333.root");
    TTree* myTree = (TTree*) myFile->Get("RecTree");
    TTree* mcTree = (TTree*) mcFile->Get("RecTree");
    
    Int_t  GamClusNumber, Pi0Number;
    Double_t CSIEt, GamClusCsiE[6][120], KlongDeltaZ[6], KlongPt[6],Pi0RecZ[6], Pi0Pt[6];
    
    Int_t  mcGamClusNumber, mcPi0Number;
    Double_t mcCSIEt, mcGamClusCsiE[6][120], mcKlongDeltaZ[6], mcKlongPt[6],mcPi0RecZ[6], mcPi0Pt[6], scale[9], mcscale[9];

    
    //linking local variables to the branches
    myTree->SetBranchAddress("CSIEt", &CSIEt); //h0
    myTree->SetBranchAddress("GamClusCsiE", GamClusCsiE); //h1
    myTree->SetBranchAddress("GamClusNumber", &GamClusNumber);//h2
    myTree->SetBranchAddress("KlongDeltaZ", KlongDeltaZ); //h3
    myTree->SetBranchAddress("KlongPt", KlongPt); //h4
    myTree->SetBranchAddress("Pi0Number", &Pi0Number); //h5
    myTree->SetBranchAddress("Pi0RecZ", Pi0RecZ); //h6
    myTree->SetBranchAddress("Pi0Pt", Pi0Pt); //h7
    
    //linking local variables to the montecarlo branches
    mcTree->SetBranchAddress("CSIEt", &mcCSIEt); //h0
    mcTree->SetBranchAddress("GamClusCsiE", mcGamClusCsiE); //h1
    mcTree->SetBranchAddress("GamClusNumber", &mcGamClusNumber);//h2
    mcTree->SetBranchAddress("KlongDeltaZ", mcKlongDeltaZ); //h3
    mcTree->SetBranchAddress("KlongPt", mcKlongPt); //h4
    mcTree->SetBranchAddress("Pi0Number", &mcPi0Number); //h5
    mcTree->SetBranchAddress("Pi0RecZ", mcPi0RecZ); //h6
    mcTree->SetBranchAddress("Pi0Pt", mcPi0Pt); //h7

    
    
   //creating the histograms
    h.push_back(new TH1F(GreekName[0],name[0],100,0,7000)); //CSIEt
    h.push_back(new TH1F(GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    h.push_back(new TH1F(GreekName[2],name[2],10,4,10)); //GamClusNumber
    h.push_back(new TH1F(GreekName[3],name[3],100,0,2500)); //KlongDeltaZ
    h.push_back(new TH1F(GreekName[4],name[4],10,0,140)); //KlongPt
    h.push_back(new TH1F(GreekName[5],name[5],10,2,10)); //Pi0Number
    h.push_back(new TH1F(GreekName[6],name[6],100,0,6000)); //Pi0RecZ
    h.push_back(new TH1F(GreekName[7],name[7],50,0,600)); //Pi0Pt
    TH2F *h8 = new TH2F(GreekName[8],name[8], 200,0,6100,200,0,600); //Pi0Pt:Pi0RecZ
    
    //creating the monte carlo histograms
    mch.push_back(new TH1F(GreekName[0],name[0],100,0,7000)); //CSIEt
    mch.push_back(new TH1F(GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    mch.push_back(new TH1F(GreekName[2],name[2],10,4,10)); //GamClusNumber
    mch.push_back(new TH1F(GreekName[3],name[3],100,0,2500)); //KlongDeltaZ
    mch.push_back(new TH1F(GreekName[4],name[4],10,0,140)); //KlongPt
    mch.push_back(new TH1F(GreekName[5],name[5],10,2,10)); //Pi0Number
    mch.push_back(new TH1F(GreekName[6],name[6],100,0,6000)); //Pi0RecZ
    mch.push_back(new TH1F(GreekName[7],name[7],50,0,600)); //Pi0Pt
    TH2F *mch8 = new TH2F(GreekName[8], "Monte Carlo", 200,0,6100,200,0,600); //Pi0Pt:Pi0RecZ

    int nEntries = myTree->GetEntries();
    for (int iEnt=0; iEnt < nEntries; iEnt++) {
        myTree->GetEntry(iEnt);
        h[0]->Fill(CSIEt);
        h[2]->Fill(GamClusNumber);
        h[5]->Fill(Pi0Number);
        for (int n=0; n<6; n++) {
            h[3]->Fill(KlongDeltaZ[n]);
            h[4]->Fill(KlongPt[n]);
            h[6]->Fill(Pi0RecZ[n]);
            h[7]->Fill(Pi0Pt[n]);
            h8->Fill(Pi0RecZ[n], Pi0Pt[n]);
            for (int j=0; j<120; j++) {
                h[1]->Fill(GamClusCsiE[n][j]);
            }
        }
    }
    nEntries = mcTree->GetEntries();
    for (int iEnt=0; iEnt < nEntries; iEnt++) {
        mcTree->GetEntry(iEnt);
        mch[0]->Fill(mcCSIEt);
        mch[2]->Fill(mcGamClusNumber);
        mch[5]->Fill(mcPi0Number);
        for (int n=0; n<6; n++) {
            mch[3]->Fill(mcKlongDeltaZ[n]);
            mch[4]->Fill(mcKlongPt[n]);
            mch[6]->Fill(mcPi0RecZ[n]);
            mch[7]->Fill(mcPi0Pt[n]);
            mch8->Fill(mcPi0RecZ[n], mcPi0Pt[n]);
            
            for (int j=0; j<120; j++) {
                mch[1]->Fill(mcGamClusCsiE[n][j]);
            }
        }
    }
    

    
    TString x[]={"Total Energy in CSI (MeV)","Energy in CSI gamma cluster (MeV)","Number of gamma clusters", "K^{0}_{L} distance travled in Z (mm)","K^{0}_{L} transverse momentum (MeV/#c)","Number of #pi^{0}s","#pi^{0} reconstructed Z poistion (mm)","#pi^{0} transverse momentum (MeV/#c)"};
    for (int i=0; i<9; i++){
        if (i==8){
            c.push_back(new TCanvas(Form("c%d",i),"",1250,600)); //creates the canvas
        }
        else{
            c.push_back(new TCanvas(Form("c%d",i),"",700,600)); //creates the canvas
        }
      c[i]->SetFillColor(0);
      c[i]->SetBorderMode(0);
      c[i]->SetBorderSize(2);
      c[i]->SetFrameBorderMode(0);
      c[i]->SetFrameBorderMode(0);
      c[i]->cd();
        if(i==8){
            mch8->GetXaxis()->SetTitle("Reconstructed Z position of #pi_{0}");
            mch8->GetYaxis()->SetTitle("Transverse momentum of #pi_{0}");
            mch8->GetYaxis()->SetTitleOffset(1.5);
            mch8->GetXaxis()->SetTitleOffset(1.4);
            h8->GetXaxis()->SetTitle("Reconstructed Z position of #pi_{0}");
            h8->GetYaxis()->SetTitle("Transverse momentum of #pi_{0}");
            h8->GetYaxis()->SetTitleOffset(1.5);
            h8->GetXaxis()->SetTitleOffset(1.4);
            c[i]->Divide(2);
            c[i]->cd(1);
            //normalization
            scale[i] = 1/h8->Integral();
            h8->Scale(scale[i]);
            mcscale[i] = 1/mch8->Integral();
            mch8->Scale(mcscale[i]);
            h8->Draw("scat");
            c[i]->cd(2);
            mch8->Draw("colz");
            gPad->Update();
            gStyle->SetOptStat(0);

        }
        else{
            gStyle->SetOptStat(0);
            mch[i]->GetXaxis()->SetTitle(x[i]);
            mch[i]->GetYaxis()->SetTitleOffset(1.5);
            mch[i]->GetXaxis()->SetTitleOffset(1.4);
            mch[i]->GetYaxis()->SetTitle("Arb. Units");
            mch[i]->GetYaxis()->SetTitleOffset(1.5);
            
            //normalization
            scale[i] = 1/h[i]->Integral();
            h[i]->Scale(scale[i]);
        
            //setting log plots for GamClusNumber and KlongPt plots
            if (i==1 or i==3 or i==4){
                c[i]->SetLogy();
            }
            mch[i]->SetLineColor(kRed);
            mch[i]->SetFillColor(kRed);
            mcscale[i] = 1/mch[i]->Integral();
            mch[i]->Scale(mcscale[i]);
            mch[i]->Draw("bar");
            h[i]->SetMarkerStyle(20);
            h[i]->Draw("E1 same");
        }
        c[i]->Update();
        c[i]->SaveAs(TString::Format("MCPlots/%s_3Pi0.eps",name[i].Data()));
   }
}

