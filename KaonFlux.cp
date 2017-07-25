
//
//RootPlotMCcuts.cpp
//
// compile this file usign g++
// g++ `root-config --cflags --glibs` KaonFlux.cp -o KaonFlux.exe
// ./KaonFlux.exe

// g6 data from run 49C, 24kW
//https://justice.hep.sci.osaka-u.ac.jp/run40/html/runparam.php?runnumber=18929

#include <stdio.h>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTreeReader.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include <TTree.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <iostream>
#include <cmath>

int main(){
    
    enum triggers {
        trigger0 = 0x0001,
        trigger1 = 0x0002,
        trigger2 = 0x0004,
        trigger3 = 0x0008,
        trigger4 = 0x0010,
        trigger5 = 0x0020,
        trigger6 = 0x0,
    };

    //initializing cuts
    bool deltaVertexTimebool = true;
    Int_t g6deltaVertexTimevalue = 3;
    Int_t g4deltaVertexTimevalue = 3;
    Int_t g2deltaVertexTimevalue = 3;
    bool minFiducialXYbool = true;
    Int_t g6MinFiducialXYvalue = 150;
    Int_t g4MinFiducialXYvalue = 120;
    Int_t g2MinFiducialXYvalue = 120;
    bool maxFiducialRbool = true;
    Int_t g6MaxFiducialRvalue = 850;
    Int_t g4MaxFiducialRvalue = 850;
    Int_t g2MaxFiducialRvalue = 850;
    bool KlongChiSqZbool = true;
    Int_t g6KlongChiSqZvalue = 20;
    Int_t g4KlongChiSqZvalue = 5;
    Int_t g2KlongChiSqZvalue = 5;
    bool minGammaEbool = true;
    Int_t g6minGammaEnergy = 50;
    Int_t g4minGammaEnergy = 50;
    bool MinClusterDistancebool = true;
    Int_t g6MinClusterDistancevalue = 150;
    Int_t g4MinClusterDistancevalue = 150;
    bool MaxDeltaPi0Massbool = true;
    Int_t g6MaxDeltaPi0Massvalue = 10;
    Int_t g4MaxDeltaPi0Massvalue = 6;
    bool Pi0RecZmaxbool = true;
    Int_t g6Pi0RecZmaxvalue = 5400;
    Int_t g4Pi0RecZmaxvalue = 5400;
    Int_t g2Pi0RecZmaxvalue = 5000;
    bool Pi0RecZminbool = true;
    Int_t g6Pi0RecZminvalue = 2000;
    Int_t g4Pi0RecZminvalue = 2000;
    Int_t g2Pi0RecZminvalue = 2000;
    bool MinHalfEtbool=true;
    Int_t g6MinHalfEtvalue = 350;
    Int_t g4MinHalfEtvalue = 350;
    Int_t g2MinHalfEtvalue = 350;
    
    //initalizing prescaling
    Int_t prescaleTrig0 = 1;
    Int_t prescaleTrig1 = 30;
    Int_t prescaleTrig2 = 300;
    Int_t prescaleTrig3 = 10;
    Int_t prescaleTrig4 = 1;
    Int_t prescaleTrig5 = 1;
    Int_t prescaleTrig6 = 1;
    
    Int_t g6prescaleTrig0entries = 0;
    Int_t g6prescaleTrig1entries = 0;
    Int_t g6prescaleTrig2entries = 0;
    Int_t g6prescaleTrig3entries = 0;
    Int_t g6prescaleTrig4entries = 0;
    Int_t g6prescaleTrig5entries = 0;
    Int_t g6prescaleTrig6entries = 0;
    
    Int_t g4prescaleTrig0entries = 0;
    Int_t g4prescaleTrig1entries = 0;
    Int_t g4prescaleTrig2entries = 0;
    Int_t g4prescaleTrig3entries = 0;
    Int_t g4prescaleTrig4entries = 0;
    Int_t g4prescaleTrig5entries = 0;
    Int_t g4prescaleTrig6entries = 0;
    
    Int_t g2prescaleTrig0entries = 0;
    Int_t g2prescaleTrig1entries = 0;
    Int_t g2prescaleTrig2entries = 0;
    Int_t g2prescaleTrig3entries = 0;
    Int_t g2prescaleTrig4entries = 0;
    Int_t g2prescaleTrig5entries = 0;
    Int_t g2prescaleTrig6entries = 0;

    //initializing vectors of things
    TString name[]={"CSIEt","GamClusCsiE","GamClusNumber","Pi0Number","Pi0RecZ","Pi0Pt"};
    TString g6GreekName[]={"g6CSIEt","g6GamClusCsiE","g6GamClusNumber","g6#pi^{0}Number","g6#pi^{0}RecZ","g6#pi^{0}Pt"};
    TString g4GreekName[]={"g4CSIEt","g4GamClusCsiE","g4GamClusNumber","g4#pi^{0}Number","g4#pi^{0}RecZ","g4#pi^{0}Pt"};
    TString g2GreekName[]={"g2CSIEt","g2GamClusCsiE","g2GamClusNumber","g2#pi^{0}Number","g2#pi^{0}RecZ","g2#pi^{0}Pt"};
    std::vector<TCanvas*> c;
    
    std::vector<TH1F*> g6h;
    std::vector<TH1F*> g4h;
    std::vector<TH1F*> g2h;
    
    std::vector<double> lines = {1}; //for the line through the ratio plots at 1
    
    //open the file
    TFile *g6File = TFile::Open("~/Desktop/Files_for_Koto/g6ana18929_node32_file1.root", "~/Desktop/Files_for_Koto/g6ana18929_node32_file1.root");
    TTree* g6Tree = (TTree*) g6File->Get("RecTree");
    TFile *g4File = TFile::Open("~/Desktop/Files_for_Koto/g4ana18929_node32_file1.root", "~/Desktop/Files_for_Koto/g4ana18929_node32_file1.root");
    TTree* g4Tree = (TTree*) g4File->Get("RecTree");
    TFile *g2File = TFile::Open("~/Desktop/Files_for_Koto/g2ana18929_node32_file1.root", "~/Desktop/Files_for_Koto/g2ana18929_node32_file1.root");
    TTree* g2Tree = (TTree*) g2File->Get("RecTree");
    
    //g6 data
    Int_t  g6GamClusNumber, g6Pi0Number;
    UInt_t g6ScaledTrigBit;
    Double_t g6MinGammaE, g6MaxGammaE, g6MinFiducialXY, g6MaxFiducialR, g6DeltaVertexTime, g6TotalEt, g6KlongChiSqZ, g6MaxDeltaPi0Mass,g6MinClusterDistance, g6MinHalfEt;
    Double_t g6CSIEt, g6GamClusCsiE[6][120], g6KlongDeltaZ[6], g6Pi0RecZ[6], g6Pi0Pt[6], g6Pi0Mom[6][3];
    //g4 data
    Int_t  g4GamClusNumber, g4Pi0Number;
    UInt_t g4ScaledTrigBit;
    Double_t g4MinGammaE, g4MaxGammaE, g4MinFiducialXY, g4MaxFiducialR, g4DeltaVertexTime, g4TotalEt, g4KlongChiSqZ, g4MaxDeltaPi0Mass, g4MinClusterDistance, g4MinHalfEt;
    Double_t g4CSIEt, g4GamClusCsiE[6][120], g4KlongDeltaZ[6], g4Pi0RecZ[6], g4Pi0Pt[6], g4Pi0Mom[6][3];
    
    //g2 data
    Int_t  g2GamClusNumber, g2Pi0Number;
    UInt_t g2ScaledTrigBit;
    Double_t g2MinGammaE, g2MaxGammaE, g2MinFiducialXY, g2MaxFiducialR, g2DeltaVertexTime, g2KlongChiSqZ, g2MinHalfEt;
    Double_t g2CSIEt, g2GamClusCsiE[6][120], g2KlongPt[6], g2Pi0RecZ[6], g2Pi0Pt[6], g2Pi0Mom[6][3];
    
    //linking local variables to the branches
    g6Tree->SetBranchAddress("CSIEt", &g6CSIEt); //h0
    g6Tree->SetBranchAddress("GamClusCsiE", g6GamClusCsiE); //h1
    g6Tree->SetBranchAddress("GamClusNumber", &g6GamClusNumber);//h2
    g6Tree->SetBranchAddress("Pi0Number", &g6Pi0Number); //h3
    g6Tree->SetBranchAddress("Pi0RecZ", g6Pi0RecZ); //h4
    g6Tree->SetBranchAddress("Pi0Pt", g6Pi0Pt); //h5
    
    g6Tree->SetBranchAddress("ScaledTrigBit", &g6ScaledTrigBit); //for prescaling
    g6Tree->SetBranchAddress("MaxGammaE", &g6MaxGammaE);//for cuts
    g6Tree->SetBranchAddress("MinGammaE", &g6MinGammaE); //for cuts
    g6Tree->SetBranchAddress("MinFiducialXY", &g6MinFiducialXY); //for cuts
    g6Tree->SetBranchAddress("MaxFiducialR", &g6MaxFiducialR); //for cuts
    g6Tree->SetBranchAddress("DeltaVertexTime", &g6DeltaVertexTime); //for cuts
    g6Tree->SetBranchAddress("TotalEt", &g6TotalEt); //for cuts
    g6Tree->SetBranchAddress("KlongChisqZ", &g6KlongChiSqZ); //for cuts
    g6Tree->SetBranchAddress("MaxDeltaPi0Mass", &g6MaxDeltaPi0Mass); //for cuts
    g6Tree->SetBranchAddress("MinClusterDistance", &g6MinClusterDistance); //for cuts
    g6Tree->SetBranchAddress("KlongDeltaZ", g6KlongDeltaZ); //for cuts
    g6Tree->SetBranchAddress("MinHalfEt", &g6MinHalfEt); //for cuts


    
   //if we want range best for seeing cuts creating the histograms
    g6h.push_back(new TH1F(g6GreekName[0],name[0],80,500,5000)); //CSIEt
    g6h.push_back(new TH1F(g6GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    g6h.push_back(new TH1F(g6GreekName[2],name[2],10,0,8)); //GamClusNumber
    g6h.push_back(new TH1F(g6GreekName[5],name[5],10,0,10)); //Pi0Number
    g6h.push_back(new TH1F(g6GreekName[6],name[6],100,1500,5500)); //Pi0RecZ
    g6h.push_back(new TH1F(g6GreekName[7],name[7],40,0,400)); //Pi0Pt
    
 /////////////////////////////////////////////////////////
    
    //linking local variables to the branches
    g4Tree->SetBranchAddress("CSIEt", &g4CSIEt); //h0
    g4Tree->SetBranchAddress("GamClusCsiE", g4GamClusCsiE); //h1
    g4Tree->SetBranchAddress("GamClusNumber", &g4GamClusNumber);//h2
    g4Tree->SetBranchAddress("Pi0Number", &g4Pi0Number); //h3
    g4Tree->SetBranchAddress("Pi0RecZ", g4Pi0RecZ); //h4
    g4Tree->SetBranchAddress("Pi0Pt", g4Pi0Pt); //h5
    
    g4Tree->SetBranchAddress("MaxGammaE", &g4MaxGammaE);//for cuts
    g4Tree->SetBranchAddress("MinGammaE", &g4MinGammaE); //for cuts
    g4Tree->SetBranchAddress("MinFiducialXY", &g4MinFiducialXY); //for cuts
    g4Tree->SetBranchAddress("MaxFiducialR", &g4MaxFiducialR); //for cuts
    g4Tree->SetBranchAddress("DeltaVertexTime", &g4DeltaVertexTime); //for cuts
    g4Tree->SetBranchAddress("TotalEt", &g4TotalEt); //for cuts
    g4Tree->SetBranchAddress("KlongChisqZ", &g4KlongChiSqZ); //for cuts
    g4Tree->SetBranchAddress("MaxDeltaPi0Mass", &g4MaxDeltaPi0Mass); //for cuts
    g4Tree->SetBranchAddress("MinClusterDistance", &g4MinClusterDistance); //for cuts
    g4Tree->SetBranchAddress("KlongDeltaZ", g4KlongDeltaZ);  //for cuts
    g4Tree->SetBranchAddress("MinHalfEt", &g4MinHalfEt); //for cuts
    g4Tree->SetBranchAddress("ScaledTrigBit", &g4ScaledTrigBit); //for prescaling
    
    
    //if we want range best for seeing cuts creating the histograms
    g4h.push_back(new TH1F(g4GreekName[0],name[0],80,500,5000)); //CSIEt
    g4h.push_back(new TH1F(g4GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    g4h.push_back(new TH1F(g4GreekName[2],name[2],10,0,8)); //GamClusNumber
    g4h.push_back(new TH1F(g4GreekName[5],name[5],10,0,10)); //Pi0Number
    g4h.push_back(new TH1F(g4GreekName[6],name[6],100,1500,5500)); //Pi0RecZ
    g4h.push_back(new TH1F(g4GreekName[7],name[7],40,0,400)); //Pi0Pt
    
    /////////////////////////////////////////////////////////////////
    
    //linking local variables to the branches
    g2Tree->SetBranchAddress("CSIEt", &g2CSIEt); //h0
    g2Tree->SetBranchAddress("GamClusCsiE", g2GamClusCsiE); //h1
    g2Tree->SetBranchAddress("GamClusNumber", &g2GamClusNumber);//h2
    g2Tree->SetBranchAddress("Pi0Number", &g2Pi0Number); //h3
    g2Tree->SetBranchAddress("Pi0RecZ", g2Pi0RecZ); //h4
    g2Tree->SetBranchAddress("Pi0Pt", g2Pi0Pt); //h5
    
    g2Tree->SetBranchAddress("MaxGammaE", &g2MaxGammaE);//for cuts
    g2Tree->SetBranchAddress("MinGammaE", &g2MinGammaE); //for cuts
    g2Tree->SetBranchAddress("MinFiducialXY", &g2MinFiducialXY); //for cuts
    g2Tree->SetBranchAddress("MaxFiducialR", &g2MaxFiducialR); //for cuts
    g2Tree->SetBranchAddress("DeltaVertexTime", &g2DeltaVertexTime); //for cuts
    g2Tree->SetBranchAddress("MaxShapeChisq", &g2KlongChiSqZ); //for cuts
    g2Tree->SetBranchAddress("MinHalfEt", &g2MinHalfEt); //for cuts
    g2Tree->SetBranchAddress("ScaledTrigBit", &g2ScaledTrigBit); //for prescaling
    
    //if we want range best for seeing cuts creating the histograms
    g2h.push_back(new TH1F(g2GreekName[0],name[0],80,500,5000)); //CSIEt
    g2h.push_back(new TH1F(g2GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    g2h.push_back(new TH1F(g2GreekName[2],name[2],10,0,8)); //GamClusNumber
    g2h.push_back(new TH1F(g2GreekName[4],name[4],10,0,10)); //Pi0Number
    g2h.push_back(new TH1F(g2GreekName[5],name[5],100,1500,5500)); //Pi0RecZ
    g2h.push_back(new TH1F(g2GreekName[6],name[6],40,0,400)); //Pi0Pt
    
    int n6Entries = g6Tree->GetEntries();
    int g6sucessfulEntries = 0;
    for (int iEnt=0; iEnt < n6Entries; iEnt++) {
        g6Tree->GetEntry(iEnt);
       // std::cout<<"g6 iEnt: " <<iEnt<<"\n";
        
        //initialzing and applying cuts
        if (minGammaEbool) {
            if (g6MinGammaE < g6minGammaEnergy){
                //std::cout<<"g6MinGammaE: " << g6MinGammaE <<"\n";
                continue;
            }
        }
        if (minFiducialXYbool) {
            if (g6MinFiducialXY < g6MinFiducialXYvalue){
                continue;
            }
        }
        if (maxFiducialRbool) {
            if (g6MaxFiducialR > g6MaxFiducialRvalue){
                continue;
            }
        }
        if (deltaVertexTimebool) {
            if (g6DeltaVertexTime > g6deltaVertexTimevalue){
                continue;
            }
        }
        if (KlongChiSqZbool) {
            if (g6KlongChiSqZ > g6KlongChiSqZvalue){
                continue;
            }
        }
        if (MaxDeltaPi0Massbool) {
            if (g6MaxDeltaPi0Mass > g6MaxDeltaPi0Massvalue){
                continue;
            }
        }
        if (MinClusterDistancebool) {
            if (g6MinClusterDistance < g6MinClusterDistancevalue){
                continue;
            }
        }
        if (MinHalfEtbool) {
            if (g6MinHalfEt < g6MinHalfEtvalue){
                continue;
            }
        }
        if (Pi0RecZminbool) {
            for (int l=0; l<6; l++){
                if (g6Pi0RecZ[l] < g6Pi0RecZminvalue) {
                    goto g6increasing;
                }
            }
        }
        if (Pi0RecZmaxbool) {
            for (int l=0; l<6; l++){
                if (g6Pi0RecZ[l] > g6Pi0RecZmaxvalue) {
                    goto g6increasing;
                }
            }
        }
        if (g6ScaledTrigBit>0){
            // std::cout<<" g6ScaledTrigBit: " << g6ScaledTrigBit<<"\n";
            
            if (g6ScaledTrigBit & trigger0){
                g6prescaleTrig0entries++;
            }
            if ((g6ScaledTrigBit & trigger1)>>1){
                g6prescaleTrig1entries++;
            }
            if ((g6ScaledTrigBit & trigger2)>>2){
                g6prescaleTrig2entries++;
            }
            if ((g6ScaledTrigBit & trigger3)>>3){
                g6prescaleTrig3entries++;
            }
            if ((g6ScaledTrigBit & trigger4)>>4){
                g6prescaleTrig4entries++;
            }
            if ((g6ScaledTrigBit & trigger5)>>5){
                g6prescaleTrig5entries++;
            }
            if ((g6ScaledTrigBit & trigger6)>>6){
                g6prescaleTrig6entries++;
            }
            
        }

        //filling the histograms with the entries that have passed cutes
        g6sucessfulEntries++;
        g6h[0]->Fill(g6CSIEt);
        g6h[2]->Fill(g6GamClusNumber);
        g6h[3]->Fill(g6Pi0Number);
        for (int n=0; n<6; n++) {
            g6h[4]->Fill(g6Pi0RecZ[n]);
            g6h[5]->Fill(g6Pi0Pt[n]);
            for (int j=0; j<120; j++) {
                g6h[1]->Fill(g6GamClusCsiE[n][j]);
            }
        }
    g6increasing:;
    }
    
    int n4Entries = g4Tree->GetEntries();
    int g4sucessfulEntries = 0;
    for (int iEnt=0; iEnt < n4Entries; iEnt++) {
        g4Tree->GetEntry(iEnt);
        
        //std::cout<<"g4ScaledTrigBit: " << g4ScaledTrigBit<<"\n";

        //initialzing and applying cuts
        

        if (minFiducialXYbool) {
            if (g4MinFiducialXY < g4MinFiducialXYvalue){
                continue;
            }
        }
        if (maxFiducialRbool) {
            if (g4MaxFiducialR < g4MaxFiducialRvalue){
                continue;
            }
        }
        if (deltaVertexTimebool) {
            if (g4DeltaVertexTime > g4deltaVertexTimevalue){
                continue;
            }
        }
        if (KlongChiSqZbool) {
            if (g4KlongChiSqZ > g4KlongChiSqZvalue){
                continue;
            }
        }
        if (MaxDeltaPi0Massbool) {
            if (g4MaxDeltaPi0Mass > g4MaxDeltaPi0Massvalue){
                continue;
            }
        }
        if (MinClusterDistancebool) {
            if (g4MinClusterDistance < g4MinClusterDistancevalue){
                continue;
            }
        }
        if (MinHalfEtbool) {
            if (g4MinHalfEt < g4MinHalfEtvalue){
                continue;
            }
        }
        if (Pi0RecZmaxbool) {
            for (int l=0; l<4; l++){
                if (g4Pi0RecZ[l] > g4Pi0RecZmaxvalue) {
                    goto g4increasing;
                }
            }
        }
        if (Pi0RecZminbool) {
            for (int l=0; l<4; l++){
                if (g4Pi0RecZ[l] < g4Pi0RecZminvalue) {
                    goto g4increasing;
                }
            }
        }
        if (g4ScaledTrigBit>0){
            if (g4ScaledTrigBit & trigger0){
                g4prescaleTrig0entries++;
            }
            if ((g4ScaledTrigBit & trigger1)>>1){
                g4prescaleTrig1entries++;
            }
            if ((g4ScaledTrigBit & trigger2)>>2){
                g4prescaleTrig2entries++;
            }
            if ((g4ScaledTrigBit & trigger3)>>3){
                g4prescaleTrig3entries++;
            }
            if ((g4ScaledTrigBit & trigger4)>>4){
                g4prescaleTrig4entries++;
            }
            if ((g4ScaledTrigBit & trigger5)>>5){
                g4prescaleTrig5entries++;
            }
            if ((g4ScaledTrigBit & trigger6)>>6){
                g4prescaleTrig6entries++;
            }
        }

        
        //fillling the histograms with the entries that have passed cuts
        g4sucessfulEntries++;
        g4h[0]->Fill(g4CSIEt);
        //std::cout<<"CSIEt " << g4CSIEt <<"\n";
        g4h[2]->Fill(g4GamClusNumber);
        g4h[3]->Fill(g4Pi0Number);
        for (int n=0; n<4; n++) {
            g4h[4]->Fill(g4Pi0RecZ[n]);
            g4h[5]->Fill(g4Pi0Pt[n]);
            for (int j=0; j<120; j++) {
                g4h[1]->Fill(g4GamClusCsiE[n][j]);
            }
        }
    g4increasing:;
    }
    
    int n2Entries = g2Tree->GetEntries();
    int g2sucessfulEntries = 0;
    for (int iEnt=0; iEnt < n2Entries; iEnt++) {
        g2Tree->GetEntry(iEnt);
        //std::cout<<" g2 scaled trig bit int: " << g2ScaledTrigBit<<"\n";
        
        //initialzing and applying cuts
        if (minFiducialXYbool) {
            if (g2MinFiducialXY < g2MinFiducialXYvalue){
                continue;
            }
        }
        if (maxFiducialRbool) {
            if (g2MaxFiducialR < g2MaxFiducialRvalue){
                continue;
            }
        }
        if (deltaVertexTimebool) {
            if (g2DeltaVertexTime > g2deltaVertexTimevalue){
                continue;
            }
        }
        if (KlongChiSqZbool) {
            if (g2KlongChiSqZ > g2KlongChiSqZvalue){
                continue;
            }
        }
        if (MinHalfEtbool) {
            if (g2MinHalfEt < g2MinHalfEtvalue){
                continue;
            }
        }
        if (Pi0RecZminbool) {
            for (int l=0; l<1; l++){
                if (g2Pi0RecZ[l] < g2Pi0RecZminvalue) {
                    goto g2increasing;
                }
            }
        }
        if (Pi0RecZmaxbool) {
            for (int l=0; l<1; l++){
                if (g2Pi0RecZ[l] > g2Pi0RecZmaxvalue) {
                    goto g2increasing;
                }
            }
        }
        
        if (g2ScaledTrigBit & trigger0){
            g2prescaleTrig0entries++;
        }
        if ((g2ScaledTrigBit & trigger1)>>1){
            g2prescaleTrig1entries++;
        }
        if ((g2ScaledTrigBit & trigger2)>>2){
            g2prescaleTrig2entries++;
        }
        if ((g2ScaledTrigBit & trigger3)>>3){
            g2prescaleTrig3entries++;
        }
        if ((g2ScaledTrigBit & trigger4)>>4){
            g2prescaleTrig4entries++;
        }
        if ((g2ScaledTrigBit & trigger5)>>5){
            g2prescaleTrig5entries++;
        }
        if ((g2ScaledTrigBit & trigger6)>>6){
            g2prescaleTrig6entries++;
        }

        
        //fillling the histograms with the entries that have passed cuts
        g2sucessfulEntries++;
        g2h[0]->Fill(g2CSIEt);
        //std::cout<<"CSIEt " << g4CSIEt <<"\n";
        g2h[2]->Fill(g2GamClusNumber);
        g2h[3]->Fill(g2Pi0Number);
        for (int n=0; n<2; n++) {
            g2h[4]->Fill(g2Pi0RecZ[n]);
            g2h[5]->Fill(g2Pi0Pt[n]);
            for (int j=0; j<120; j++) {
                g2h[1]->Fill(g2GamClusCsiE[n][j]);
            }
        }
    g2increasing:;
    }
    
    TString x[]={"Total Energy in CSI (MeV)","Energy in CSI gamma cluster (MeV)","Number of gamma clusters","Number of #pi^{0}s","#pi^{0} reconstructed Z poistion (mm)","#pi^{0} transverse momentum (MeV/c)"};
   //print the number of entries, for calculating the klong flux for the g6 and g4 decays
    std::cout<<"Entries that passed the cut for g6: " << g6sucessfulEntries <<"\n";
    std::cout<<"Entries that passed the cut for g4: " << g4sucessfulEntries <<"\n";
    std::cout<<"Entries that passed the cut for g2: " << g2sucessfulEntries <<"\n";
    
    


    
    for (int i=0; i<6; i++){
        c.push_back(new TCanvas(Form("c%d",i),"",800,800)); //creates the canvas

      c[i]->SetFillColor(0);
      c[i]->SetBorderMode(0);
      c[i]->SetBorderSize(2);
      c[i]->SetFrameBorderMode(0);
      c[i]->SetFrameBorderMode(0);
      c[i]->cd();
        
        //comparing 2 2d histograms side by side rather than plotting on the same page
        gStyle->SetOptStat(0);
        g6h[i]->GetYaxis()->SetTitleOffset(1.5);
        g6h[i]->GetXaxis()->SetTitleOffset(1.4);
        g6h[i]->GetYaxis()->SetTitle("Arb. Units");
        g6h[i]->GetXaxis()->SetTitle(x[i]);
        g6h[i]->GetYaxis()->SetTitleOffset(1.6);
        TLegend *leg= new TLegend(0.8,0.84,0.89,0.89);
        leg->AddEntry(g6h[i],"3 #pi^{0} data");
        leg->AddEntry(g4h[i],"2 #pi^{0} data");
        leg->AddEntry(g2h[i],"2 #gamma data");
        leg->SetBorderSize(2);
        
        //sum of the weights for the error (Brian)
        g6h[i]->Sumw2();

        //setting log plots for GamClusNumber and Pi0RecZ and Pi0Pt plots
        if (i==1 or i==4 or i==5){
            c[i]->SetLogy();
        }
        
        g6h[i]->Draw();
        g4h[i]->SetLineColor(kRed);
        g4h[i]->Draw("same");
        g2h[i]->SetLineColor(kGreen);
        g2h[i]->Draw("same");
        leg->Draw();
        g6h[i]->GetYaxis()->SetTitleOffset(1.5);
        c[i]->Update();
        
        //save the histograms as pdfs
        c[i]->SaveAs(TString::Format("KaonFlux/%s_klongflux.eps",name[i].Data()));
        
   }
    ////////////////calculating kaon flux
    
    //prescale values from https://justice.hep.sci.osaka-u.ac.jp/run40/html/runparam.php?runnumber=24319
   
    
    Int_t g6prescaled = prescaleTrig0*g6prescaleTrig0entries + prescaleTrig1*g6prescaleTrig1entries + prescaleTrig2*g6prescaleTrig2entries + prescaleTrig3*g6prescaleTrig3entries + prescaleTrig4*g6prescaleTrig4entries + prescaleTrig5*g6prescaleTrig5entries + prescaleTrig6*g6prescaleTrig6entries;
    
    Int_t g4prescaled = prescaleTrig0*g4prescaleTrig0entries + prescaleTrig1*g4prescaleTrig1entries + prescaleTrig2*g4prescaleTrig2entries + prescaleTrig3*g4prescaleTrig3entries + prescaleTrig4*g4prescaleTrig4entries + prescaleTrig5*g4prescaleTrig5entries + prescaleTrig6*g4prescaleTrig6entries;
    
    Int_t g2prescaled = prescaleTrig0*g2prescaleTrig0entries + prescaleTrig1*g2prescaleTrig1entries + prescaleTrig2*g2prescaleTrig2entries + prescaleTrig3*g2prescaleTrig3entries + prescaleTrig4*g2prescaleTrig4entries + prescaleTrig5*g2prescaleTrig5entries + prescaleTrig6*g2prescaleTrig6entries;

    std::cout<<"prescaled g6trig0: " << g6prescaleTrig0entries <<"\n";
    std::cout<<"prescaled g6trig1: " << g6prescaleTrig1entries <<"\n";
    std::cout<<"prescaled g6trig2: " << g6prescaleTrig2entries <<"\n";
    std::cout<<"prescaled g6trig3: " << g6prescaleTrig3entries <<"\n";
    std::cout<<"prescaled g6trig4: " << g6prescaleTrig4entries <<"\n";
    std::cout<<"prescaled g6trig5: " << g6prescaleTrig5entries <<"\n";
    std::cout<<"prescaled g6trig6: " << g6prescaleTrig6entries <<"\n";
    
    std::cout<<"prescaled g4trig0: " << g4prescaleTrig0entries <<"\n";
    std::cout<<"prescaled g4trig1: " << g4prescaleTrig1entries <<"\n";
    std::cout<<"prescaled g4trig2: " << g4prescaleTrig2entries <<"\n";
    std::cout<<"prescaled g4trig3: " << g4prescaleTrig3entries <<"\n";
    std::cout<<"prescaled g4trig4: " << g4prescaleTrig4entries <<"\n";
    std::cout<<"prescaled g4trig5: " << g4prescaleTrig5entries <<"\n";
    std::cout<<"prescaled g4trig6: " << g4prescaleTrig6entries <<"\n";
    
    std::cout<<"prescaled g2trig0: " << g2prescaleTrig0entries <<"\n";
    std::cout<<"prescaled g2trig1: " << g2prescaleTrig1entries <<"\n";
    std::cout<<"prescaled g2trig2: " << g2prescaleTrig2entries <<"\n";
    std::cout<<"prescaled g2trig3: " << g2prescaleTrig3entries <<"\n";
    std::cout<<"prescaled g2trig4: " << g2prescaleTrig4entries <<"\n";
    std::cout<<"prescaled g2trig5: " << g2prescaleTrig5entries <<"\n";
    std::cout<<"prescaled g2trig6: " << g2prescaleTrig6entries <<"\n";

 

    
    Double_t g6BR = 0.1952; //plus minus 0.012
    Double_t g4BR = 0.000864; //plus minus 0.000006
    Double_t g2BR = 0.000547; //plus minus 0.000004
    
    Double_t g6klongFlux = g6prescaled/g6BR;
    Double_t g4klongFlux = g4prescaled/g4BR;
    Double_t g2klongFlux = g2prescaled/g2BR;
    
    std::cout<<"g6 Klong flux: " << g6klongFlux <<"\n";
    std::cout<<"g4 Klong flux: " << g4klongFlux <<"\n";
    std::cout<<"g2 Klong flux: " << g2klongFlux <<"\n";

}

