//
//RootPlotsNew3.cpp
//
#include <stdio.h>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include <TTree.h>


void RootPlotsNew3(){
    
    TString name[]={"CSIEt","GamClusCsiE","GamClusNumber", "KlongDeltaZ","KlongPt","Pi0Number","Pi0RecZ","Pi0Pt","Pi0Pt:Pi0RecZ"};
    std::vector<TCanvas*> c;
    std::vector<TH1F*> h;
    
    //open the file
    TFile myFile("~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root", "~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root");
    TTree* myTree = (TTree*) myFile.Get("RecTree");
    
    Int_t  GamClusNumber, Pi0Number;
    Double_t CSIEt, GamClusCsiE[6][120], KlongDeltaZ[6], KlongPt[6],Pi0RecZ[6], Pi0Pt[6];
    
    //linking local variables to the branches
    myTree->SetBranchAddress("CSIEt", &CSIEt); //h0
    myTree->SetBranchAddress("GamClusCsiE", GamClusCsiE); //h1
    myTree->SetBranchAddress("GamClusNumber", &GamClusNumber);//h2
    myTree->SetBranchAddress("KlongDeltaZ", KlongDeltaZ); //h3
    myTree->SetBranchAddress("KlongPt", KlongPt); //h4
    myTree->SetBranchAddress("Pi0Number", &Pi0Number); //h5
    myTree->SetBranchAddress("Pi0RecZ", Pi0RecZ); //h6
    myTree->SetBranchAddress("Pi0Pt", Pi0Pt); //h7
    
    
   //creating the histograms
    h.push_back(new TH1F("h0",name[0],100,0,7000)); //CSIEt
    h.push_back(new TH1F("h1",name[1],75,0,1200)); //GamClusCsiE
    h.push_back(new TH1F("h2",name[2],10,4,10)); //GamClusNumber
    h.push_back(new TH1F("h3",name[3],100,0,2500)); //KlongDeltaZ
    h.push_back(new TH1F("h4",name[4],10,0,140)); //KlongPt
    h.push_back(new TH1F("h5",name[5],10,2,10)); //Pi0Number
    h.push_back(new TH1F("h6",name[6],100,0,6000)); //Pi0RecZ
    h.push_back(new TH1F("h7",name[7],50,0,600)); //Pi0Pt
    
    TH2F *h8 = new TH2F("h8",name[8], 10,0,6000,10,0,600); //Pi0Pt:Pi0RecZ
    
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

    for (int i=0; i<9; i++){
      c.push_back(new TCanvas(Form("c%d",i),"",550,600)); //creates the canvas
      c[i]->SetFillColor(0);
      c[i]->SetBorderMode(0);
      c[i]->SetBorderSize(2);
      c[i]->SetFrameBorderMode(0);
      c[i]->SetFrameBorderMode(0);
      c[i]->cd();
        if(i==8){
            h8->GetYaxis()->SetTitle(name[i]);
            h8->SetMarkerStyle(7);
            h8->Draw();
        }
        else{
            h[i]->GetYaxis()->SetTitle(name[i]);
        
            //setting log plots for GamClusNumber and KlongPt plots
            if (i==1 or i==3 or i==4){
                c[i]->SetLogy();
            }
            h[i]->Draw();
        }
        c[i]->SaveAs(TString::Format("FancyPlots/%s_3Pi0.eps",name[i].Data()));
        c[i]->Close();
   }
}
