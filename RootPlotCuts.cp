//
//RootPlotCuts.cpp
//
//want to compile this file usign g++
// g++ `root-config --cflags --glibs` RootPlotCuts.cp -o RootPlotCuts.exe
//./RootPlotCuts.exe

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
    bool cuts = true;
    bool both = true;
    
    TString name[]={"CSIEt","GamClusCsiE","GamClusNumber", "KlongDeltaZ","KlongPt","Pi0Number","Pi0RecZ","Pi0Pt","Pi0Pt:Pi0RecZ"};
    TString GreekName[]={"CSIEt","GamClusCsiE","GamClusNumber", "K^{0}_{L}DeltaZ","K^{0}_{L}Pt","#pi^{0}Number","#pi^{0}RecZ","#pi^{0}Pt","#pi^{0}Pt:#pi^{0}RecZ"};
    std::vector<TCanvas*> c;
    std::vector<TH1F*> h;
    std::vector<TH1F*> hcut;
    
    //open the file
    TFile *myFile = TFile::Open("~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root", "~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root");
    TTree* myTree = (TTree*) myFile->Get("RecTree");
    
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
    h.push_back(new TH1F(GreekName[0],name[0],100,0,7000)); //CSIEt
    h.push_back(new TH1F(GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    h.push_back(new TH1F(GreekName[2],name[2],10,4,10)); //GamClusNumber
    h.push_back(new TH1F(GreekName[3],name[3],100,0,2500)); //KlongDeltaZ
    h.push_back(new TH1F(GreekName[4],name[4],10,0,140)); //KlongPt
    h.push_back(new TH1F(GreekName[5],name[5],10,2,10)); //Pi0Number
    h.push_back(new TH1F(GreekName[6],name[6],100,0,6000)); //Pi0RecZ
    h.push_back(new TH1F(GreekName[7],name[7],50,0,600)); //Pi0Pt
    TH2F *h8 = new TH2F(GreekName[8],name[8], 100,0,6100,100,0,600); //Pi0Pt:Pi0RecZ
    
    //histograms for cuts to be plotted alongside original histogram
    hcut.push_back(new TH1F(GreekName[0],name[0],100,0,7000)); //CSIEt
    hcut.push_back(new TH1F(GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    hcut.push_back(new TH1F(GreekName[2],name[2],10,4,10)); //GamClusNumber
    hcut.push_back(new TH1F(GreekName[3],name[3],100,0,2500)); //KlongDeltaZ
    hcut.push_back(new TH1F(GreekName[4],name[4],10,0,140)); //KlongPt
    hcut.push_back(new TH1F(GreekName[5],name[5],10,2,10)); //Pi0Number
    hcut.push_back(new TH1F(GreekName[6],name[6],100,0,6000)); //Pi0RecZ
    hcut.push_back(new TH1F(GreekName[7],name[7],50,0,600)); //Pi0Pt
    TH2F *hcut8 = new TH2F(GreekName[8],name[8], 100,0,6100,100,0,600); //Pi0Pt:Pi0RecZ

    
    int nEntries = myTree->GetEntries();
    for (int iEnt=0; iEnt < nEntries; iEnt++) {
        if (both){
            myTree->GetEntry(iEnt);
            h[0]->Fill(CSIEt);
            hcut[0]->Fill(CSIEt);
            h[2]->Fill(GamClusNumber);
            hcut[2]->Fill(GamClusNumber);
            h[5]->Fill(Pi0Number);
            hcut[5]->Fill(Pi0Number);
            for (int n=0; n<6; n++) {
                h[3]->Fill(KlongDeltaZ[n]);
                h[4]->Fill(KlongPt[n]);
                h[6]->Fill(Pi0RecZ[n]);
                h[7]->Fill(Pi0Pt[n]);
                h8->Fill(Pi0RecZ[n], Pi0Pt[n]);
                for (int j=0; j<120; j++) {
                    h[1]->Fill(GamClusCsiE[n][j]);
                }
                if (Pi0RecZ[n]>3000 &&  Pi0RecZ[n]<4500  && Pi0Pt[n]>150 && Pi0Pt[n]<250){
                    // how to apply this cut on the events where we are not going into loops (look above!!)
                    hcut[3]->Fill(KlongDeltaZ[n]);
                    hcut[4]->Fill(KlongPt[n]);
                    hcut[6]->Fill(Pi0RecZ[n]);
                    hcut[7]->Fill(Pi0Pt[n]);
                    hcut8->Fill(Pi0RecZ[n], Pi0Pt[n]);
                    for (int j=0; j<120; j++) {
                        hcut[1]->Fill(GamClusCsiE[n][j]);
                    }
                }
            }

        }
        else {
            if (cuts){ //cuts on the data will change which things are plotted into the histograms
                myTree->GetEntry(iEnt);
                h[0]->Fill(CSIEt);
                h[2]->Fill(GamClusNumber);
                h[5]->Fill(Pi0Number);
                for (int n=0; n<6; n++) {
                    if (Pi0RecZ[n]>3000 &&  Pi0RecZ[n]<4500 ){ //&& Pi0Pt[n]>150 && Pi0Pt[n]<250){
                        // how to apply this cut on the events where we are not going into loops (look above!!)
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
            }
            else{
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
        }
    }
    
    TString x[]={"Total Energy in CSI (MeV)","Energy in CSI gamma cluster (MeV)","Number of gamma clusters", "Range of possible reconstructed positions of K^{0}_{L} (mm)","K^{0}_{L} transverse momentum (MeV/c)","Number of #pi^{0}s","#pi^{0} reconstructed Z poistion (mm)","#pi^{0} transverse momentum (MeV/c)"};
    for (int i=0; i<9; i++){
      c.push_back(new TCanvas(Form("c%d",i),"",550,600)); //creates the canvas
      c[i]->SetFillColor(0);
      c[i]->SetBorderMode(0);
      c[i]->SetBorderSize(2);
      c[i]->SetFrameBorderMode(0);
      c[i]->SetFrameBorderMode(0);
      c[i]->cd();
        if(i==8){
            h8->GetXaxis()->SetTitle("Reconstructed Z position of #pi_{0}");
            h8->GetYaxis()->SetTitle("Transverse momentum of #pi_{0}");
            h8->GetYaxis()->SetTitleOffset(1.5);
            h8->GetXaxis()->SetTitleOffset(1.4);
            if (both){
                c[i]->Divide(2);
                c[i]->cd(1);
                h8->Draw("colz");
                c[i]->cd(2);
                hcut8->Draw("colz");
                
            }
            else {
                h8->Draw("colz");
            }
            gPad->Update();
            TPaveStats *st = (TPaveStats*)h8->FindObject("stats");
            st->SetX1NDC(0.1459854); //new x start position
            st->SetX2NDC(0.3448905); //new x end position
            st->SetY1NDC(0.6143194); //new y start position
            st->SetY2NDC(0.8838475); //new y end position

        }
        else{
            gStyle->SetOptStat("nemrou");
            h[i]->GetXaxis()->SetTitle(x[i]);
            h[i]->GetYaxis()->SetTitleOffset(1.5);
            h[i]->GetXaxis()->SetTitleOffset(1.4);
            h[i]->GetYaxis()->SetTitle("Number of events");
        
            //setting log plots for GamClusNumber and KlongPt plots
            if (i==1 or i==3 or i==4){
                c[i]->SetLogy();
            }
            h[i]->Draw("colz");
            if (both){
                hcut[i]->SetLineColor(kRed);
                hcut[i]->Draw("same");
            }
        }
        c[i]->Update();
        if (both) {
            c[i]->SaveAs(TString::Format("CutPlots/both/%s_3Pi0.eps",name[i].Data()));
        }
        else{
            c[i]->SaveAs(TString::Format("CutPlots/%s_3Pi0.eps",name[i].Data()));
        }
   }
}

