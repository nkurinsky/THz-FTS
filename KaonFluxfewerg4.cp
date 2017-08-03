
//
//RootPlotMCcuts.cpp
//
// compile this file usign g++
// g++ `root-config --cflags --glibs` KaonFluxfewerg4.cp -o KaonFluxfewerg4.exe
// ./KaonFluxfewerg4.exe

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
    bool DeltaKlongMassbool = true;
    Double_t g6MaxDeltaKlongMassvalue = 497.6 + 15;
    Double_t g4MaxDeltaKlongMassvalue = 497.6 + 15;
    Double_t g6MinDeltaKlongMassvalue = 497.6 - 15;
    Double_t g4MinDeltaKlongMassvalue = 497.6 - 15;
    bool Pi0RecZbool = true;
    Int_t g6Pi0RecZmaxvalue = 5400;
    Int_t g4Pi0RecZmaxvalue = 5400;
    Int_t g2Pi0RecZmaxvalue = 5000;
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
    
    Int_t g6prescaleTrig0entries1 = 0;
    Int_t g6prescaleTrig1entries1 = 0;
    Int_t g6prescaleTrig2entries1 = 0;
    Int_t g6prescaleTrig3entries1 = 0;
    Int_t g6prescaleTrig4entries1 = 0;
    Int_t g6prescaleTrig5entries1 = 0;
    Int_t g6prescaleTrig6entries1 = 0;
    Int_t g6prescaleTrig0entries2 = 0;
    Int_t g6prescaleTrig1entries2 = 0;
    Int_t g6prescaleTrig2entries2 = 0;
    Int_t g6prescaleTrig3entries2 = 0;
    Int_t g6prescaleTrig4entries2 = 0;
    Int_t g6prescaleTrig5entries2 = 0;
    Int_t g6prescaleTrig6entries2 = 0;
    Int_t g6prescaleTrig0entries3 = 0;
    Int_t g6prescaleTrig1entries3 = 0;
    Int_t g6prescaleTrig2entries3 = 0;
    Int_t g6prescaleTrig3entries3 = 0;
    Int_t g6prescaleTrig4entries3 = 0;
    Int_t g6prescaleTrig5entries3 = 0;
    Int_t g6prescaleTrig6entries3 = 0;
    
    Int_t g4prescaleTrig0entries1 = 0;
    Int_t g4prescaleTrig1entries1 = 0;
    Int_t g4prescaleTrig2entries1 = 0;
    Int_t g4prescaleTrig3entries1 = 0;
    Int_t g4prescaleTrig4entries1 = 0;
    Int_t g4prescaleTrig5entries1 = 0;
    Int_t g4prescaleTrig6entries1 = 0;
    Int_t g4prescaleTrig0entries2 = 0;
    Int_t g4prescaleTrig1entries2 = 0;
    Int_t g4prescaleTrig2entries2 = 0;
    Int_t g4prescaleTrig3entries2 = 0;
    Int_t g4prescaleTrig4entries2 = 0;
    Int_t g4prescaleTrig5entries2 = 0;
    Int_t g4prescaleTrig6entries2 = 0;
    Int_t g4prescaleTrig0entries3 = 0;
    Int_t g4prescaleTrig1entries3 = 0;
    Int_t g4prescaleTrig2entries3 = 0;
    Int_t g4prescaleTrig3entries3 = 0;
    Int_t g4prescaleTrig4entries3 = 0;
    Int_t g4prescaleTrig5entries3 = 0;
    Int_t g4prescaleTrig6entries3 = 0;
    
    Int_t g2prescaleTrig0entries1 = 0;
    Int_t g2prescaleTrig1entries1 = 0;
    Int_t g2prescaleTrig2entries1 = 0;
    Int_t g2prescaleTrig3entries1 = 0;
    Int_t g2prescaleTrig4entries1 = 0;
    Int_t g2prescaleTrig5entries1 = 0;
    Int_t g2prescaleTrig6entries1 = 0;
    Int_t g2prescaleTrig0entries2 = 0;
    Int_t g2prescaleTrig1entries2 = 0;
    Int_t g2prescaleTrig2entries2 = 0;
    Int_t g2prescaleTrig3entries2 = 0;
    Int_t g2prescaleTrig4entries2 = 0;
    Int_t g2prescaleTrig5entries2 = 0;
    Int_t g2prescaleTrig6entries2 = 0;
    Int_t g2prescaleTrig0entries3 = 0;
    Int_t g2prescaleTrig1entries3 = 0;
    Int_t g2prescaleTrig2entries3 = 0;
    Int_t g2prescaleTrig3entries3 = 0;
    Int_t g2prescaleTrig4entries3 = 0;
    Int_t g2prescaleTrig5entries3 = 0;
    Int_t g2prescaleTrig6entries3 = 0;
    
    
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
    // TFile *g6File = TFile::Open("~/Desktop/Files_for_Koto/g6ana18929_node32_file0.root", "~/Desktop/Files_for_Koto/g6ana18929_node32_file0.root");
    TFile *g6File = TFile::Open("~/Desktop/Files_for_Koto/g6ana18929_node32_file0.root", "~/Desktop/Files_for_Koto/g6ana18929_node32_file0.root");
    TFile *g6File2 = TFile::Open("~/Desktop/Files_for_Koto/g6ana19070_node30_file0.root", "~/Desktop/Files_for_Koto/g6ana19070_node30_file0.root");
    TFile *g6File3 = TFile::Open("~/Desktop/Files_for_Koto/g6ana19023_node30_file0.root", "~/Desktop/Files_for_Koto/g6ana19023_node30_file0.root");
    TTree* g6Tree = (TTree*) g6File->Get("RecTree");
    TTree* g6Tree2 = (TTree*) g6File2->Get("RecTree");
    TTree* g6Tree3 = (TTree*) g6File3->Get("RecTree");
    TFile *g4File = TFile::Open("~/Desktop/Files_for_Koto/g4ana18929_node32_file0.root", "~/Desktop/Files_for_Koto/g4ana18929_node32_file0.root");
    TFile *g4File2 = TFile::Open("~/Desktop/Files_for_Koto/g4ana19070_node30_file0.root", "~/Desktop/Files_for_Koto/g4ana19070_node30_file0.root");
    TFile *g4File3 = TFile::Open("~/Desktop/Files_for_Koto/g4ana19023_node30_file0.root", "~/Desktop/Files_for_Koto/g4ana19023_node30_file0.root");
    TTree* g4Tree = (TTree*) g4File->Get("RecTree");
    TTree* g4Tree2 = (TTree*) g4File2->Get("RecTree");
    TTree* g4Tree3 = (TTree*) g4File3->Get("RecTree");
    TFile *g2File = TFile::Open("~/Desktop/Files_for_Koto/g2anaKL18929_node32_file0.root", "~/Desktop/Files_for_Koto/g2anaKL18929_node32_file0.root");
    TFile *g2File2 = TFile::Open("~/Desktop/Files_for_Koto/g2anaKL19070_node30_file0.root", "~/Desktop/Files_for_Koto/g2anaKL19070_node30_file0.root");
    TFile *g2File3 = TFile::Open("~/Desktop/Files_for_Koto/g2anaKL19023_node30_file0.root", "~/Desktop/Files_for_Koto/g2anaKL19023_node30_file0.root");
    TTree* g2Tree = (TTree*) g2File->Get("RecTree");
    TTree* g2Tree2 = (TTree*) g2File2->Get("RecTree");
    TTree* g2Tree3 = (TTree*) g2File3->Get("RecTree");
    
    //g6 data
    Int_t  g6GamClusNumber, g6Pi0Number;
    UInt_t g6ScaledTrigBit;
    Double_t g6MinGammaE, g6MaxGammaE, g6MinFiducialXY, g6MaxFiducialR, g6DeltaVertexTime, g6TotalEt, g6KlongChiSqZ, g6MaxDeltaPi0Mass,g6MinClusterDistance, g6MinHalfEt;
    Double_t g6CSIEt, g6GamClusCsiE[6][120], g6KlongDeltaZ[6], g6Pi0RecZ[6], g6Pi0Pt[6], g6Pi0Mom[6][3], g6KlongMass[6];
    
    //g6 data2
    Int_t  g6GamClusNumber2, g6Pi0Number2;
    UInt_t g6ScaledTrigBit2;
    Double_t g6MinGammaE2, g6MaxGammaE2, g6MinFiducialXY2, g6MaxFiducialR2, g6DeltaVertexTime2, g6TotalEt2, g6KlongChiSqZ2, g6MaxDeltaPi0Mass2,g6MinClusterDistance2, g6MinHalfEt2;
    Double_t g6CSIEt2, g6GamClusCsiE2[6][120], g6KlongDeltaZ2[6], g6Pi0RecZ2[6], g6Pi0Pt2[6], g6Pi0Mom2[6][3], g6KlongMass2[6];
    
    //g6 data3
    Int_t  g6GamClusNumber3, g6Pi0Number3;
    UInt_t g6ScaledTrigBit3;
    Double_t g6MinGammaE3, g6MaxGammaE3, g6MinFiducialXY3, g6MaxFiducialR3, g6DeltaVertexTime3, g6TotalEt3, g6KlongChiSqZ3, g6MaxDeltaPi0Mass3,g6MinClusterDistance3, g6MinHalfEt3;
    Double_t g6CSIEt3, g6GamClusCsiE3[6][120], g6KlongDeltaZ3[6], g6Pi0RecZ3[6], g6Pi0Pt3[6], g6Pi0Mom3[6][3], g6KlongMass3[6];
    
    //g4 data
    Int_t  g4GamClusNumber, g4Pi0Number;
    UInt_t g4ScaledTrigBit;
    Double_t g4MinGammaE, g4MaxGammaE, g4MinFiducialXY, g4MaxFiducialR, g4DeltaVertexTime, g4TotalEt, g4KlongChiSqZ, g4MaxDeltaPi0Mass, g4MinClusterDistance, g4MinHalfEt;
    Double_t g4CSIEt, g4GamClusCsiE[6][120], g4KlongDeltaZ[6], g4Pi0RecZ[6], g4Pi0Pt[6], g4Pi0Mom[6][3], g4KlongMass[6];
    
    //g4 data2
    Int_t  g4GamClusNumber2, g4Pi0Number2;
    UInt_t g4ScaledTrigBit2;
    Double_t g4MinGammaE2, g4MaxGammaE2, g4MinFiducialXY2, g4MaxFiducialR2, g4DeltaVertexTime2, g4TotalEt2, g4KlongChiSqZ2, g4MaxDeltaPi0Mass2, g4MinClusterDistance2, g4MinHalfEt2;
    Double_t g4CSIEt2, g4GamClusCsiE2[6][120], g4KlongDeltaZ2[6], g4Pi0RecZ2[6], g4Pi0Pt2[6], g4Pi0Mom2[6][3], g4KlongMass2[6];
    
    //g4 data3
    Int_t  g4GamClusNumber3, g4Pi0Number3;
    UInt_t g4ScaledTrigBit3;
    Double_t g4MinGammaE3, g4MaxGammaE3, g4MinFiducialXY3, g4MaxFiducialR3, g4DeltaVertexTime3, g4TotalEt3, g4KlongChiSqZ3, g4MaxDeltaPi0Mass3, g4MinClusterDistance3, g4MinHalfEt3;
    Double_t g4CSIEt3, g4GamClusCsiE3[6][120], g4KlongDeltaZ3[6], g4Pi0RecZ3[6], g4Pi0Pt3[6], g4Pi0Mom3[6][3], g4KlongMass3[6];
    
    //g2 data
    Int_t  g2GamClusNumber, g2Pi0Number;
    UInt_t g2ScaledTrigBit;
    Double_t g2MinGammaE, g2MaxGammaE, g2MinFiducialXY, g2MaxFiducialR, g2DeltaVertexTime, g2KlongChiSqZ, g2MinHalfEt;
    Double_t g2CSIEt, g2GamClusCsiE[6][120], g2KlongPt[6], g2Pi0RecZ[6], g2Pi0Pt[6], g2Pi0Mom[6][3];
    
    //g2 data2
    Int_t  g2GamClusNumber2, g2Pi0Number2;
    UInt_t g2ScaledTrigBit2;
    Double_t g2MinGammaE2, g2MaxGammaE2, g2MinFiducialXY2, g2MaxFiducialR2, g2DeltaVertexTime2, g2KlongChiSqZ2, g2MinHalfEt2;
    Double_t g2CSIEt2, g2GamClusCsiE2[6][120], g2KlongPt2[6], g2Pi0RecZ2[6], g2Pi0Pt2[6], g2Pi0Mom2[6][3];
    //g2 data3
    Int_t  g2GamClusNumber3, g2Pi0Number3;
    UInt_t g2ScaledTrigBit3;
    Double_t g2MinGammaE3, g2MaxGammaE3, g2MinFiducialXY3, g2MaxFiducialR3, g2DeltaVertexTime3, g2KlongChiSqZ3, g2MinHalfEt3;
    Double_t g2CSIEt3, g2GamClusCsiE3[6][120], g2KlongPt3[6], g2Pi0RecZ3[6], g2Pi0Pt3[6], g2Pi0Mom3[6][3];
    
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
    g6Tree->SetBranchAddress("KlongMass", g6KlongMass); //for cuts
    
    
    
    //linking local variables to the branches
    g6Tree3->SetBranchAddress("CSIEt", &g6CSIEt3); //h0
    g6Tree3->SetBranchAddress("GamClusCsiE", g6GamClusCsiE3); //h1
    g6Tree3->SetBranchAddress("GamClusNumber", &g6GamClusNumber3);//h2
    g6Tree3->SetBranchAddress("Pi0Number", &g6Pi0Number3); //h3
    g6Tree3->SetBranchAddress("Pi0RecZ", g6Pi0RecZ3); //h4
    g6Tree3->SetBranchAddress("Pi0Pt", g6Pi0Pt3); //h5
    
    g6Tree3->SetBranchAddress("MaxGammaE", &g6MaxGammaE3);//for cuts
    g6Tree3->SetBranchAddress("MinGammaE", &g6MinGammaE3); //for cuts
    g6Tree3->SetBranchAddress("MinFiducialXY", &g6MinFiducialXY3); //for cuts
    g6Tree3->SetBranchAddress("MaxFiducialR", &g6MaxFiducialR3); //for cuts
    g6Tree3->SetBranchAddress("DeltaVertexTime", &g6DeltaVertexTime3); //for cuts
    g6Tree3->SetBranchAddress("MaxShapeChisq", &g6KlongChiSqZ3); //for cuts
    g6Tree3->SetBranchAddress("MinHalfEt", &g6MinHalfEt3); //for cuts
    g6Tree3->SetBranchAddress("ScaledTrigBit", &g6ScaledTrigBit3); //for prescaling
    g6Tree3->SetBranchAddress("KlongMass", g6KlongMass3); //for cuts
    
    //linking local variables to the branches
    g6Tree2->SetBranchAddress("CSIEt", &g6CSIEt2); //h0
    g6Tree2->SetBranchAddress("GamClusCsiE", g6GamClusCsiE2); //h1
    g6Tree2->SetBranchAddress("GamClusNumber", &g6GamClusNumber2);//h2
    g6Tree2->SetBranchAddress("Pi0Number", &g6Pi0Number2); //h3
    g6Tree2->SetBranchAddress("Pi0RecZ", g6Pi0RecZ2); //h4
    g6Tree2->SetBranchAddress("Pi0Pt", g6Pi0Pt2); //h5
    
    g6Tree2->SetBranchAddress("MaxGammaE", &g6MaxGammaE2);//for cuts
    g6Tree2->SetBranchAddress("MinGammaE", &g6MinGammaE2); //for cuts
    g6Tree2->SetBranchAddress("MinFiducialXY", &g6MinFiducialXY2); //for cuts
    g6Tree2->SetBranchAddress("MaxFiducialR", &g6MaxFiducialR2); //for cuts
    g6Tree2->SetBranchAddress("DeltaVertexTime", &g6DeltaVertexTime2); //for cuts
    g6Tree2->SetBranchAddress("MaxShapeChisq", &g6KlongChiSqZ2); //for cuts
    g6Tree2->SetBranchAddress("MinHalfEt", &g6MinHalfEt2); //for cuts
    g6Tree2->SetBranchAddress("ScaledTrigBit", &g6ScaledTrigBit2); //for prescaling
    g6Tree2->SetBranchAddress("KlongMass", g6KlongMass2); //for cuts
    
    
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
    g4Tree->SetBranchAddress("KlongMass", g4KlongMass); //for cuts
    
    
    
    //linking local variables to the branches
    g4Tree3->SetBranchAddress("CSIEt", &g4CSIEt3); //h0
    g4Tree3->SetBranchAddress("GamClusCsiE", g4GamClusCsiE3); //h1
    g4Tree3->SetBranchAddress("GamClusNumber", &g4GamClusNumber3);//h2
    g4Tree3->SetBranchAddress("Pi0Number", &g4Pi0Number3); //h3
    g4Tree3->SetBranchAddress("Pi0RecZ", g4Pi0RecZ3); //h4
    g4Tree3->SetBranchAddress("Pi0Pt", g4Pi0Pt3); //h5
    
    g4Tree3->SetBranchAddress("MaxGammaE", &g4MaxGammaE3);//for cuts
    g4Tree3->SetBranchAddress("MinGammaE", &g4MinGammaE3); //for cuts
    g4Tree3->SetBranchAddress("MinFiducialXY", &g4MinFiducialXY3); //for cuts
    g4Tree3->SetBranchAddress("MaxFiducialR", &g4MaxFiducialR3); //for cuts
    g4Tree3->SetBranchAddress("DeltaVertexTime", &g4DeltaVertexTime3); //for cuts
    g4Tree3->SetBranchAddress("MaxShapeChisq", &g4KlongChiSqZ3); //for cuts
    g4Tree3->SetBranchAddress("MinHalfEt", &g4MinHalfEt3); //for cuts
    g4Tree3->SetBranchAddress("ScaledTrigBit", &g4ScaledTrigBit3); //for prescaling
    g4Tree3->SetBranchAddress("KlongMass", g4KlongMass3); //for cuts
    
    //linking local variables to the branches
    g4Tree2->SetBranchAddress("CSIEt", &g4CSIEt2); //h0
    g4Tree2->SetBranchAddress("GamClusCsiE", g4GamClusCsiE2); //h1
    g4Tree2->SetBranchAddress("GamClusNumber", &g4GamClusNumber2);//h2
    g4Tree2->SetBranchAddress("Pi0Number", &g4Pi0Number2); //h3
    g4Tree2->SetBranchAddress("Pi0RecZ", g4Pi0RecZ2); //h4
    g4Tree2->SetBranchAddress("Pi0Pt", g4Pi0Pt2); //h5
    
    g4Tree2->SetBranchAddress("MaxGammaE", &g4MaxGammaE2);//for cuts
    g4Tree2->SetBranchAddress("MinGammaE", &g4MinGammaE2); //for cuts
    g4Tree2->SetBranchAddress("MinFiducialXY", &g4MinFiducialXY2); //for cuts
    g4Tree2->SetBranchAddress("MaxFiducialR", &g4MaxFiducialR2); //for cuts
    g4Tree2->SetBranchAddress("DeltaVertexTime", &g4DeltaVertexTime2); //for cuts
    g4Tree2->SetBranchAddress("MaxShapeChisq", &g4KlongChiSqZ2); //for cuts
    g4Tree2->SetBranchAddress("MinHalfEt", &g4MinHalfEt2); //for cuts
    g4Tree2->SetBranchAddress("ScaledTrigBit", &g4ScaledTrigBit2); //for prescaling
    g4Tree2->SetBranchAddress("KlongMass", g4KlongMass2); //for cuts
    
    
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
    
    //linking local variables to the branches
    g2Tree3->SetBranchAddress("CSIEt", &g2CSIEt3); //h0
    g2Tree3->SetBranchAddress("GamClusCsiE", g2GamClusCsiE3); //h1
    g2Tree3->SetBranchAddress("GamClusNumber", &g2GamClusNumber3);//h2
    g2Tree3->SetBranchAddress("Pi0Number", &g2Pi0Number3); //h3
    g2Tree3->SetBranchAddress("Pi0RecZ", g2Pi0RecZ3); //h4
    g2Tree3->SetBranchAddress("Pi0Pt", g2Pi0Pt3); //h5
    
    g2Tree3->SetBranchAddress("MaxGammaE", &g2MaxGammaE3);//for cuts
    g2Tree3->SetBranchAddress("MinGammaE", &g2MinGammaE3); //for cuts
    g2Tree3->SetBranchAddress("MinFiducialXY", &g2MinFiducialXY3); //for cuts
    g2Tree3->SetBranchAddress("MaxFiducialR", &g2MaxFiducialR3); //for cuts
    g2Tree3->SetBranchAddress("DeltaVertexTime", &g2DeltaVertexTime3); //for cuts
    g2Tree3->SetBranchAddress("MaxShapeChisq", &g2KlongChiSqZ3); //for cuts
    g2Tree3->SetBranchAddress("MinHalfEt", &g2MinHalfEt3); //for cuts
    g2Tree3->SetBranchAddress("ScaledTrigBit", &g2ScaledTrigBit3); //for prescaling
    
    //linking local variables to the branches
    g2Tree2->SetBranchAddress("CSIEt", &g2CSIEt2); //h0
    g2Tree2->SetBranchAddress("GamClusCsiE", g2GamClusCsiE2); //h1
    g2Tree2->SetBranchAddress("GamClusNumber", &g2GamClusNumber2);//h2
    g2Tree2->SetBranchAddress("Pi0Number", &g2Pi0Number2); //h3
    g2Tree2->SetBranchAddress("Pi0RecZ", g2Pi0RecZ2); //h4
    g2Tree2->SetBranchAddress("Pi0Pt", g2Pi0Pt2); //h5
    
    g2Tree2->SetBranchAddress("MaxGammaE", &g2MaxGammaE2);//for cuts
    g2Tree2->SetBranchAddress("MinGammaE", &g2MinGammaE2); //for cuts
    g2Tree2->SetBranchAddress("MinFiducialXY", &g2MinFiducialXY2); //for cuts
    g2Tree2->SetBranchAddress("MaxFiducialR", &g2MaxFiducialR2); //for cuts
    g2Tree2->SetBranchAddress("DeltaVertexTime", &g2DeltaVertexTime2); //for cuts
    g2Tree2->SetBranchAddress("MaxShapeChisq", &g2KlongChiSqZ2); //for cuts
    g2Tree2->SetBranchAddress("MinHalfEt", &g2MinHalfEt2); //for cuts
    g2Tree2->SetBranchAddress("ScaledTrigBit", &g2ScaledTrigBit2); //for prescaling
    
    
    //if we want range best for seeing cuts creating the histograms
    g2h.push_back(new TH1F(g2GreekName[0],name[0],80,500,5000)); //CSIEt
    g2h.push_back(new TH1F(g2GreekName[1],name[1],75,0,1200)); //GamClusCsiE
    g2h.push_back(new TH1F(g2GreekName[2],name[2],10,0,8)); //GamClusNumber
    g2h.push_back(new TH1F(g2GreekName[4],name[4],10,0,10)); //Pi0Number
    g2h.push_back(new TH1F(g2GreekName[5],name[5],100,1500,5500)); //Pi0RecZ
    g2h.push_back(new TH1F(g2GreekName[6],name[6],40,0,400)); //Pi0Pt
    
    
    ////////////// going throgh data files and filling histograms
    
    ///////////////////g6 #1
    int n6Entries = g6Tree->GetEntries();
    int g6sucessfulEntries = 0;
    
    
    for (int iEnt=0; iEnt < n6Entries; iEnt++) {
        g6Tree->GetEntry(iEnt);
        bool mingammae, minfiducialxy, maxfiducialr, deltavertextime, klongchisqz,  maxdeltapi0mass, minclusterdistance, pi0recz, deltaklongmass = false;
        
        if (minGammaEbool && g6MinGammaE > g6minGammaEnergy) mingammae = true;
        if (minFiducialXYbool && g6MinFiducialXY > g6MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g6MaxFiducialR < g6MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g6DeltaVertexTime < g6deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g6KlongChiSqZ < g6KlongChiSqZvalue) klongchisqz = true;
        if (MaxDeltaPi0Massbool && g6MaxDeltaPi0Mass < g6MaxDeltaPi0Massvalue) maxdeltapi0mass = true;
        if (MinClusterDistancebool && g6MinClusterDistance < g6MinClusterDistancevalue) minclusterdistance = true;
        if (Pi0RecZbool) {
            for (int l=0; l<6; l++){
                if (g6Pi0RecZ[l] < g6Pi0RecZminvalue || g6Pi0RecZ[l] > g6Pi0RecZmaxvalue) {
                    goto g6increasing;
                }
                pi0recz = true;
            }
        }
        if (DeltaKlongMassbool) {
            for (int l=0; l<2; l++){
                if (g6KlongMass[l] < g6MaxDeltaKlongMassvalue && g6KlongMass[l] > g6MinDeltaKlongMassvalue) {
                    deltaklongmass = true;
                }
            }
        }
        
        
        //filling the histograms with the entries that have passed cuts
        if (minGammaEbool==mingammae && minFiducialXYbool==minfiducialxy && maxFiducialRbool==maxfiducialr && deltaVertexTimebool==deltavertextime && KlongChiSqZbool==klongchisqz && MaxDeltaPi0Massbool==maxdeltapi0mass && MinClusterDistancebool==minclusterdistance && Pi0RecZbool==pi0recz && DeltaKlongMassbool==deltaklongmass) {
            // std::cout<<" true stuff \n";
            
            // checking trigger bits
            if (g6ScaledTrigBit & trigger0) g6prescaleTrig0entries1++;
            if ((g6ScaledTrigBit & trigger1)>>1) g6prescaleTrig1entries1++;
            if ((g6ScaledTrigBit & trigger2)>>2) g6prescaleTrig2entries1++;
            if ((g6ScaledTrigBit & trigger3)>>3) g6prescaleTrig3entries1++;
            if ((g6ScaledTrigBit & trigger4)>>4) g6prescaleTrig4entries1++;
            if ((g6ScaledTrigBit & trigger5)>>5) g6prescaleTrig5entries1++;
            if ((g6ScaledTrigBit & trigger6)>>6) g6prescaleTrig6entries1++;
            
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
        }
    g6increasing:;
    }
    std::cout<<"g6sucessfulEntries " << g6sucessfulEntries<<"\n";
    
    
    ////////////////g6 #2
    int n6Entries2 = g6Tree2->GetEntries();
    
    for (int iEnt=0; iEnt < n6Entries2; iEnt++) {
        g6Tree2->GetEntry(iEnt);
        
        //std::cout<<" g6 scaled trig bit int: " << g2ScaledTrigBit<<"\n";
        bool mingammae, minfiducialxy, maxfiducialr, deltavertextime, klongchisqz,  maxdeltapi0mass, minclusterdistance, pi0recz, deltaklongmass, csivetoenergy = false;
        
        if (minGammaEbool && g6MinGammaE2 > g6minGammaEnergy) mingammae = true;
        if (minFiducialXYbool && g6MinFiducialXY2 > g6MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g6MaxFiducialR2 < g6MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g6DeltaVertexTime2 < g6deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g6KlongChiSqZ2 < g6KlongChiSqZvalue) klongchisqz = true;
        if (MaxDeltaPi0Massbool && g6MaxDeltaPi0Mass2 < g6MaxDeltaPi0Massvalue) maxdeltapi0mass = true;
        if (MinClusterDistancebool && g6MinClusterDistance2 < g6MinClusterDistancevalue) minclusterdistance = true;
        if (Pi0RecZbool) {
            for (int l=0; l<6; l++){
                if (g6Pi0RecZ2[l] < g6Pi0RecZminvalue || g6Pi0RecZ2[l] > g6Pi0RecZmaxvalue) {
                    goto g6increasing2;
                }
                pi0recz = true;
            }
        }
        if (DeltaKlongMassbool) {
            for (int l=0; l<2; l++){
                if (g6KlongMass2[l] < g6MaxDeltaKlongMassvalue && g6KlongMass2[l] > g6MinDeltaKlongMassvalue) {
                    deltaklongmass = true;
                }
            }
        }
        
        
        //filling the histograms with the entries that have passed cuts
        if (minGammaEbool==mingammae && minFiducialXYbool==minfiducialxy && maxFiducialRbool==maxfiducialr && deltaVertexTimebool==deltavertextime && KlongChiSqZbool==klongchisqz && MaxDeltaPi0Massbool==maxdeltapi0mass && MinClusterDistancebool==minclusterdistance && Pi0RecZbool==pi0recz && DeltaKlongMassbool==deltaklongmass ) {
            
            // checking trigger bits
            if (g6ScaledTrigBit2 & trigger0) g6prescaleTrig0entries2++;
            if ((g6ScaledTrigBit2 & trigger1)>>1) g6prescaleTrig1entries2++;
            if ((g6ScaledTrigBit2 & trigger2)>>2) g6prescaleTrig2entries2++;
            if ((g6ScaledTrigBit2 & trigger3)>>3) g6prescaleTrig3entries2++;
            if ((g6ScaledTrigBit2 & trigger4)>>4) g6prescaleTrig4entries2++;
            if ((g6ScaledTrigBit2 & trigger5)>>5) g6prescaleTrig5entries2++;
            if ((g6ScaledTrigBit2 & trigger6)>>6) g6prescaleTrig6entries2++;
            
            g6sucessfulEntries++;
            g6h[0]->Fill(g6CSIEt2);
            g6h[2]->Fill(g6GamClusNumber2);
            g6h[3]->Fill(g6Pi0Number2);
            for (int n=0; n<6; n++) {
                g6h[4]->Fill(g6Pi0RecZ2[n]);
                g6h[5]->Fill(g6Pi0Pt2[n]);
                for (int j=0; j<120; j++) {
                    g6h[1]->Fill(g6GamClusCsiE2[n][j]);
                }
            }
        }
    g6increasing2:;
    }
    std::cout<<"g6sucessfulEntries " << g6sucessfulEntries<<"\n";
    
    
    //////////////// g6 #3
    int n6Entries3 = g6Tree3->GetEntries();
    for (int iEnt=0; iEnt < n6Entries3; iEnt++) {
        g6Tree3->GetEntry(iEnt);
        //std::cout<<" g6 scaled trig bit int: " << g6ScaledTrigBit<<"\n";
        
        bool mingammae, minfiducialxy, maxfiducialr, deltavertextime, klongchisqz,  maxdeltapi0mass, minclusterdistance, pi0recz, deltaklongmass = false;
        
        if (minGammaEbool && g6MinGammaE3 > g6minGammaEnergy ) mingammae = true;
        if (minFiducialXYbool && g6MinFiducialXY3 > g6MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g6MaxFiducialR3 < g6MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g6DeltaVertexTime3 < g6deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g6KlongChiSqZ3 < g6KlongChiSqZvalue) klongchisqz = true;
        if (MaxDeltaPi0Massbool && g6MaxDeltaPi0Mass3 < g6MaxDeltaPi0Massvalue) maxdeltapi0mass = true;
        if (MinClusterDistancebool && g6MinClusterDistance3 < g6MinClusterDistancevalue) minclusterdistance = true;
        if (Pi0RecZbool) {
            for (int l=0; l<6; l++){
                if (g6Pi0RecZ3[l] < g6Pi0RecZminvalue || g6Pi0RecZ3[l] > g6Pi0RecZmaxvalue) {
                    goto g6increasing3;
                }
                pi0recz = true;
            }
        }
        if (DeltaKlongMassbool) {
            for (int l=0; l<2; l++){
                if (g6KlongMass3[l] < g6MaxDeltaKlongMassvalue && g6KlongMass3[l] > g6MinDeltaKlongMassvalue) {
                    deltaklongmass = true;
                }
            }
        }
        
        //filling the histograms with the entries that have passed cuts
        if ((minGammaEbool==mingammae) && (minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MaxDeltaPi0Massbool==maxdeltapi0mass) && (MinClusterDistancebool==minclusterdistance) && (Pi0RecZbool==pi0recz) && (DeltaKlongMassbool==deltaklongmass)) {
            
            // checking trigger bits
            if (g6ScaledTrigBit3 & trigger0) g6prescaleTrig0entries1++;
            if ((g6ScaledTrigBit3 & trigger1)>>1) g6prescaleTrig1entries3++;
            if ((g6ScaledTrigBit3 & trigger2)>>2) g6prescaleTrig2entries3++;
            if ((g6ScaledTrigBit3 & trigger3)>>3) g6prescaleTrig3entries3++;
            if ((g6ScaledTrigBit3 & trigger4)>>4) g6prescaleTrig4entries3++;
            if ((g6ScaledTrigBit3 & trigger5)>>5) g6prescaleTrig5entries3++;
            if ((g6ScaledTrigBit3 & trigger6)>>6) g6prescaleTrig6entries3++;
            
            
            g6sucessfulEntries++;
            g6h[0]->Fill(g6CSIEt3);
            g6h[2]->Fill(g6GamClusNumber3);
            g6h[3]->Fill(g6Pi0Number3);
            for (int n=0; n<6; n++) {
                g6h[4]->Fill(g6Pi0RecZ3[n]);
                g6h[5]->Fill(g6Pi0Pt3[n]);
                for (int j=0; j<120; j++) {
                    g6h[1]->Fill(g6GamClusCsiE3[n][j]);
                }
            }
        }
    g6increasing3:;
    }
    std::cout<<"g6sucessfulEntries " << g6sucessfulEntries<<"\n";
    
    /////////////////g4 #1
    int n4Entries = g4Tree->GetEntries();
    int g4sucessfulEntries = 0;
    for (int iEnt=0; iEnt < n4Entries; iEnt++) {
        g4Tree->GetEntry(iEnt);
        
        //initialzing and applying cuts
        bool mingammae, minfiducialxy, maxfiducialr, deltavertextime, klongchisqz,  maxdeltapi0mass, minclusterdistance, pi0recz, deltaklongmass = false;
        
        if (minGammaEbool && g4MinGammaE > g4minGammaEnergy ) mingammae = true;
        if (minFiducialXYbool && g4MinFiducialXY > g4MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g4MaxFiducialR < g4MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g4DeltaVertexTime < g4deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g4KlongChiSqZ < g4KlongChiSqZvalue) klongchisqz = true;
        if (MaxDeltaPi0Massbool && g4MaxDeltaPi0Mass < g4MaxDeltaPi0Massvalue) maxdeltapi0mass = true;
        if (MinClusterDistancebool && g4MinClusterDistance < g4MinClusterDistancevalue) minclusterdistance = true;
        if (Pi0RecZbool) {
            for (int l=0; l<2; l++){
                if (g4Pi0RecZ[l] < g4Pi0RecZminvalue || g4Pi0RecZ[l] > g4Pi0RecZmaxvalue) {
                    goto g4increasing;
                }
                pi0recz = true;
            }
        }
        if (DeltaKlongMassbool) {
            for (int l=0; l<2; l++){
                if (g4KlongMass[l] < g4MaxDeltaKlongMassvalue && g4KlongMass[l] > g4MinDeltaKlongMassvalue) {
                    deltaklongmass = true;
                }
            }
        }
        //filling the histograms with the entries that have passed cuts
        if ((minGammaEbool==mingammae) && (minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MaxDeltaPi0Massbool==maxdeltapi0mass) && (MinClusterDistancebool==minclusterdistance) && (Pi0RecZbool==pi0recz) && (DeltaKlongMassbool==deltaklongmass)) {
            
            // checking trigger bits
            if (g4ScaledTrigBit & trigger0) g4prescaleTrig0entries1++;
            if ((g4ScaledTrigBit & trigger1)>>1) g4prescaleTrig1entries1++;
            if ((g4ScaledTrigBit & trigger2)>>2) g4prescaleTrig2entries1++;
            if ((g4ScaledTrigBit & trigger3)>>3) g4prescaleTrig3entries1++;
            if ((g4ScaledTrigBit & trigger4)>>4) g4prescaleTrig4entries1++;
            if ((g4ScaledTrigBit & trigger5)>>5) g4prescaleTrig5entries1++;
            if ((g4ScaledTrigBit & trigger6)>>6) g4prescaleTrig6entries1++;
            
            g4sucessfulEntries++;
            g4h[0]->Fill(g4CSIEt);
            g4h[2]->Fill(g4GamClusNumber);
            g4h[3]->Fill(g4Pi0Number);
            for (int n=0; n<2; n++) {
                g4h[4]->Fill(g4Pi0RecZ[n]);
                g4h[5]->Fill(g4Pi0Pt[n]);
                for (int j=0; j<120; j++) {
                    g4h[1]->Fill(g4GamClusCsiE[n][j]);
                }
            }
        }
    g4increasing:;
    }
    std::cout<<"g4sucessfulEntries " << g4sucessfulEntries<<"\n";
    
    /////////////g4 #2
    int n4Entries2 = g4Tree2->GetEntries();
    for (int iEnt=0; iEnt < n4Entries2; iEnt++) {
        g4Tree2->GetEntry(iEnt);
        //std::cout<<" g4 scaled trig bit int: " << g4ScaledTrigBit<<"\n";
        // std::cout<<"g4 data 2: "  <<"\n";
        //initialzing and applying cuts
        bool mingammae, minfiducialxy, maxfiducialr, deltavertextime, klongchisqz,  maxdeltapi0mass, minclusterdistance, pi0recz, deltaklongmass = false;
        
        if (minGammaEbool && g4MinGammaE2 > g4minGammaEnergy ) mingammae = true;
        if (minFiducialXYbool && g4MinFiducialXY2 > g4MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g4MaxFiducialR2 < g4MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g4DeltaVertexTime2 < g4deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g4KlongChiSqZ2 <g4KlongChiSqZvalue) klongchisqz = true;
        if (MaxDeltaPi0Massbool && g4MaxDeltaPi0Mass2 < g4MaxDeltaPi0Massvalue) maxdeltapi0mass = true;
        if (MinClusterDistancebool && g4MinClusterDistance2 < g4MinClusterDistancevalue) minclusterdistance = true;
        if (Pi0RecZbool) {
            for (int l=0; l<2; l++){
                if (g4Pi0RecZ2[l] < g4Pi0RecZminvalue || g4Pi0RecZ2[l] > g4Pi0RecZmaxvalue) {
                    goto g4increasing2;
                }
                pi0recz = true;
            }
        }
        if (DeltaKlongMassbool) {
            for (int l=0; l<2; l++){
                if (g4KlongMass2[l] < g4MaxDeltaKlongMassvalue && g4KlongMass2[l] > g4MinDeltaKlongMassvalue) {
                    deltaklongmass = true;
                }
            }
        }
        
        //filling the histograms with the entries that have passed cuts
        if ((minGammaEbool==mingammae) && (minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MaxDeltaPi0Massbool==maxdeltapi0mass) && (MinClusterDistancebool==minclusterdistance) && (Pi0RecZbool==pi0recz) && (DeltaKlongMassbool==deltaklongmass)) {
            
            // std::cout << "g4 2 iEnt " << iEnt << "\n";
            
            // checking trigger bits
            if (g4ScaledTrigBit2 & trigger0) g4prescaleTrig0entries2++;
            if ((g4ScaledTrigBit2 & trigger1)>>1) g4prescaleTrig1entries2++;
            if ((g4ScaledTrigBit2 & trigger2)>>2) g4prescaleTrig2entries2++;
            if ((g4ScaledTrigBit2 & trigger3)>>3) g4prescaleTrig3entries2++;
            if ((g4ScaledTrigBit2 & trigger4)>>4) g4prescaleTrig4entries2++;
            if ((g4ScaledTrigBit2 & trigger5)>>5) g4prescaleTrig5entries2++;
            if ((g4ScaledTrigBit2 & trigger6)>>6) g4prescaleTrig6entries2++;
            
            
            g4sucessfulEntries++;
            g4h[0]->Fill(g4CSIEt2);
            g4h[2]->Fill(g4GamClusNumber2);
            g4h[3]->Fill(g4Pi0Number2);
            for (int n=0; n<2; n++) {
                g4h[4]->Fill(g4Pi0RecZ2[n]);
                g4h[5]->Fill(g4Pi0Pt2[n]);
                for (int j=0; j<120; j++) {
                    g4h[1]->Fill(g4GamClusCsiE2[n][j]);
                }
            }
        }
    g4increasing2:;
    }
    
    std::cout<<"g4sucessfulEntries " << g4sucessfulEntries<<"\n";
    
    //////////////g4 #3
    int n4Entries3 = g4Tree3->GetEntries();
    for (int iEnt=0; iEnt < n4Entries3; iEnt++) {
        g4Tree3->GetEntry(iEnt);
        //std::cout<<" g2 scaled trig bit int: " << g2ScaledTrigBit<<"\n";
        
        //initialzing and applying cuts
        bool mingammae, minfiducialxy, maxfiducialr, deltavertextime, klongchisqz,  maxdeltapi0mass, minclusterdistance, pi0recz, deltaklongmass = false;
        
        if (minGammaEbool && g4MinGammaE3 > g4minGammaEnergy ) mingammae = true;
        if (minFiducialXYbool && g4MinFiducialXY3 > g4MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g4MaxFiducialR3 < g4MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g4DeltaVertexTime3 < g4deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g4KlongChiSqZ3 < g4KlongChiSqZvalue) klongchisqz = true;
        if (MaxDeltaPi0Massbool && g4MaxDeltaPi0Mass3 < g4MaxDeltaPi0Massvalue) maxdeltapi0mass = true;
        if (MinClusterDistancebool && g4MinClusterDistance3 < g4MinClusterDistancevalue) minclusterdistance = true;
        if (Pi0RecZbool) {
            for (int l=0; l<2; l++){
                if (g4Pi0RecZ3[l] < g4Pi0RecZminvalue || g4Pi0RecZ3[l] > g4Pi0RecZmaxvalue) {
                    goto g4increasing3;
                }
                pi0recz = true;
            }
        }
        if (DeltaKlongMassbool) {
            for (int l=0; l<2; l++){
                if (g4KlongMass3[l] < g4MaxDeltaKlongMassvalue && g4KlongMass3[l] > g4MinDeltaKlongMassvalue) {
                    deltaklongmass = true;
                }
            }
        }
        
        
        //filling the histograms with the entries that have passed cuts
        if ((minGammaEbool==mingammae) && (minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MaxDeltaPi0Massbool==maxdeltapi0mass) && (MinClusterDistancebool==minclusterdistance) && (Pi0RecZbool==pi0recz) && (DeltaKlongMassbool==deltaklongmass)) {
            
            //std::cout << "g4 3 iEnt " << iEnt << "\n";
            
            // checking trigger bits
            if (g4ScaledTrigBit3 & trigger0) g4prescaleTrig0entries3++;
            if ((g4ScaledTrigBit3 & trigger1)>>1) g4prescaleTrig1entries3++;
            if ((g4ScaledTrigBit3 & trigger2)>>2) g4prescaleTrig2entries3++;
            if ((g4ScaledTrigBit3 & trigger3)>>3) g4prescaleTrig3entries3++;
            if ((g4ScaledTrigBit3 & trigger4)>>4) g4prescaleTrig4entries3++;
            if ((g4ScaledTrigBit3 & trigger5)>>5) g4prescaleTrig5entries3++;
            if ((g4ScaledTrigBit3 & trigger6)>>6) g4prescaleTrig6entries3++;
            
            g4sucessfulEntries++;
            g4h[0]->Fill(g4CSIEt3);
            g4h[2]->Fill(g4GamClusNumber3);
            g4h[3]->Fill(g4Pi0Number3);
            for (int n=0; n<2; n++) {
                g4h[4]->Fill(g4Pi0RecZ3[n]);
                g4h[5]->Fill(g4Pi0Pt3[n]);
                for (int j=0; j<120; j++) {
                    g4h[1]->Fill(g4GamClusCsiE3[n][j]);
                }
            }
        }
    g4increasing3:;
    }
    std::cout<<"g4sucessfulEntries " << g4sucessfulEntries<<"\n";
    
    ///////////g2 #1
    int n2Entries = g2Tree->GetEntries();
    int g2sucessfulEntries = 0;
    for (int iEnt=0; iEnt < n2Entries; iEnt++) {
        g2Tree->GetEntry(iEnt);
        //std::cout<<" g2 scaled trig bit int: " << g2ScaledTrigBit<<"\n";
        
        bool minfiducialxy, maxfiducialr,  deltavertextime, klongchisqz,  minhalfet, pi0recz, deltaklongmass = false;
        
        //initialzing and applying cuts
        if (minFiducialXYbool && g2MinFiducialXY > g2MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g2MaxFiducialR < g2MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g2DeltaVertexTime < g2deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g2KlongChiSqZ < g2KlongChiSqZvalue) klongchisqz = true;
        if (MinHalfEtbool && g2MinHalfEt > g2MinHalfEtvalue) minhalfet =true;
        if (Pi0RecZbool) {
            for (int l=0; l<1; l++){
                if (g2Pi0RecZ[l] < g2Pi0RecZminvalue || g2Pi0RecZ[l] > g2Pi0RecZmaxvalue) {
                    goto g2increasing;
                }
                pi0recz = true;
            }
        }
        
        if ((minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MinHalfEtbool==minhalfet) && (Pi0RecZbool==pi0recz) ) {
            
            if (g2ScaledTrigBit & trigger0) g2prescaleTrig0entries1++;
            if ((g2ScaledTrigBit & trigger1)>>1) g2prescaleTrig1entries1++;
            if ((g2ScaledTrigBit & trigger2)>>2) g2prescaleTrig2entries1++;
            if ((g2ScaledTrigBit & trigger3)>>3) g2prescaleTrig3entries1++;
            if ((g2ScaledTrigBit & trigger4)>>4) g2prescaleTrig4entries1++;
            if ((g2ScaledTrigBit & trigger5)>>5) g2prescaleTrig5entries1++;
            if ((g2ScaledTrigBit & trigger6)>>6) g2prescaleTrig6entries1++;
            
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
        }
    g2increasing:;
    }
    std::cout<<"g2sucessfulEntries " << g2sucessfulEntries<<"\n";
    
    ///////////////g2 #2
    int n2Entries2 = g2Tree2->GetEntries();
    for (int iEnt=0; iEnt < n2Entries2; iEnt++) {
        g2Tree2->GetEntry(iEnt);
        //std::cout<<" g2 scaled trig bit int: " << g2ScaledTrigBit<<"\n";
        bool minfiducialxy, maxfiducialr,  deltavertextime, klongchisqz,  minhalfet, pi0recz, deltaklongmass = false;
        
        //initialzing and applying cuts
        if (minFiducialXYbool && g2MinFiducialXY2 > g2MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g2MaxFiducialR2 < g2MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g2DeltaVertexTime2 < g2deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g2KlongChiSqZ2 < g2KlongChiSqZvalue) klongchisqz = true;
        if (MinHalfEtbool && g2MinHalfEt2 > g2MinHalfEtvalue) minhalfet =true;
        if (Pi0RecZbool) {
            for (int l=0; l<1; l++){
                if (g2Pi0RecZ2[l] < g2Pi0RecZminvalue || g2Pi0RecZ2[l] > g2Pi0RecZmaxvalue) {
                    goto g2increasing2;
                }
                pi0recz = true;
            }
        }
        
        if ((minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MinHalfEtbool==minhalfet) && (Pi0RecZbool==pi0recz) ) {
            
            if (g2ScaledTrigBit2 & trigger0) g2prescaleTrig0entries2++;
            if ((g2ScaledTrigBit2 & trigger1)>>1) g2prescaleTrig1entries2++;
            if ((g2ScaledTrigBit2 & trigger2)>>2) g2prescaleTrig2entries2++;
            if ((g2ScaledTrigBit2 & trigger3)>>3) g2prescaleTrig3entries2++;
            if ((g2ScaledTrigBit2 & trigger4)>>4) g2prescaleTrig4entries2++;
            if ((g2ScaledTrigBit2 & trigger5)>>5) g2prescaleTrig5entries2++;
            if ((g2ScaledTrigBit2 & trigger6)>>6) g2prescaleTrig6entries2++;
            
            //fillling the histograms with the entries that have passed cuts
            g2sucessfulEntries++;
            g2h[0]->Fill(g2CSIEt2);
            //std::cout<<"CSIEt " << g4CSIEt <<"\n";
            g2h[2]->Fill(g2GamClusNumber2);
            g2h[3]->Fill(g2Pi0Number2);
            for (int n=0; n<2; n++) {
                g2h[4]->Fill(g2Pi0RecZ2[n]);
                g2h[5]->Fill(g2Pi0Pt2[n]);
                for (int j=0; j<120; j++) {
                    g2h[1]->Fill(g2GamClusCsiE2[n][j]);
                }
            }
        }
    g2increasing2:;
    }
    std::cout<<"g2sucessfulEntries " << g2sucessfulEntries<<"\n";
    
    
    /////////////g2 #3
    int n2Entries3 = g2Tree3->GetEntries();
    for (int iEnt=0; iEnt < n2Entries3; iEnt++) {
        g2Tree3->GetEntry(iEnt);
        //std::cout<<" g2 scaled trig bit int: " << g2ScaledTrigBit<<"\n";
        bool minfiducialxy, maxfiducialr,  deltavertextime, klongchisqz,  minhalfet, pi0recz, deltaklongmass = false;
        
        //initialzing and applying cuts
        if (minFiducialXYbool && g2MinFiducialXY3 > g2MinFiducialXYvalue) minfiducialxy = true;
        if (maxFiducialRbool && g2MaxFiducialR3 < g2MaxFiducialRvalue) maxfiducialr = true;
        if (deltaVertexTimebool && g2DeltaVertexTime3 < g2deltaVertexTimevalue) deltavertextime = true;
        if (KlongChiSqZbool && g2KlongChiSqZ3 < g2KlongChiSqZvalue) klongchisqz = true;
        if (MinHalfEtbool && g2MinHalfEt3 > g2MinHalfEtvalue) minhalfet =true;
        if (Pi0RecZbool) {
            for (int l=0; l<1; l++){
                if (g2Pi0RecZ3[l] < g2Pi0RecZminvalue || g2Pi0RecZ3[l] > g2Pi0RecZmaxvalue) {
                    goto g2increasing3;
                }
                pi0recz = true;
            }
        }
        
        if ((minFiducialXYbool==minfiducialxy) && (maxFiducialRbool==maxfiducialr) && (deltaVertexTimebool==deltavertextime) && (KlongChiSqZbool==klongchisqz) && (MinHalfEtbool==minhalfet) && (Pi0RecZbool==pi0recz) ) {
            
            if (g2ScaledTrigBit3 & trigger0) g2prescaleTrig0entries3++;
            if ((g2ScaledTrigBit3 & trigger1)>>1) g2prescaleTrig1entries3++;
            if ((g2ScaledTrigBit3 & trigger2)>>2) g2prescaleTrig2entries3++;
            if ((g2ScaledTrigBit3 & trigger3)>>3) g2prescaleTrig3entries3++;
            if ((g2ScaledTrigBit3 & trigger4)>>4) g2prescaleTrig4entries3++;
            if ((g2ScaledTrigBit3 & trigger5)>>5) g2prescaleTrig5entries3++;
            if ((g2ScaledTrigBit3 & trigger6)>>6) g2prescaleTrig6entries3++;
            
            //fillling the histograms with the entries that have passed cuts
            g2sucessfulEntries++;
            g2h[0]->Fill(g2CSIEt3);
            //std::cout<<"CSIEt " << g4CSIEt <<"\n";
            g2h[2]->Fill(g2GamClusNumber);
            g2h[3]->Fill(g2Pi0Number);
            for (int n=0; n<2; n++) {
                g2h[4]->Fill(g2Pi0RecZ3[n]);
                g2h[5]->Fill(g2Pi0Pt3[n]);
                for (int j=0; j<120; j++) {
                    g2h[1]->Fill(g2GamClusCsiE3[n][j]);
                }
            }
        }
    g2increasing3:;
    }
    
    std::cout<<"g2sucessfulEntries " << g2sucessfulEntries<<"\n";
    
    TString x[]={"Total Energy in CSI (MeV)","Energy in CSI gamma cluster (MeV)","Number of gamma clusters","Number of #pi^{0}s","#pi^{0} reconstructed Z poistion (mm)","#pi^{0} transverse momentum (MeV/c)"};
    //print the number of entries, for calculating the klong flux for the g6 and g4 decays
    std::cout<<"Entries that passed the cut for g6: " << g6sucessfulEntries <<"\n";
    std::cout<<"Entries that passed the cut for g4: " << g4sucessfulEntries <<"\n";
    std::cout<<"Entries that passed the cut for g2: " << g2sucessfulEntries <<"\n";
    
    
    
    
    for (int i=0; i<6; i++){
        std::cout<<"for loop \n";
        c.push_back(new TCanvas(Form("c%d",i),"",800,800)); //creates the canvas
        
        c[i]->SetFillColor(0);
        c[i]->SetBorderMode(0);
        c[i]->SetBorderSize(2);
        c[i]->SetFrameBorderMode(0);
        c[i]->SetFrameBorderMode(0);
        c[i]->cd();
        
        TLegend *leg= new TLegend(0.8,0.84,0.89,0.89);
        leg->AddEntry(g6h[i],"3 #pi^{0} data");
        leg->AddEntry(g4h[i],"2 #pi^{0} data");
        leg->AddEntry(g2h[i],"2 #gamma data");
        leg->SetBorderSize(2);
        
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
    
    
    Int_t g6prescaleTrig0entries = g6prescaleTrig0entries1 + g6prescaleTrig0entries2 + g6prescaleTrig0entries3;
    Int_t g6prescaleTrig1entries = g6prescaleTrig1entries1 + g6prescaleTrig1entries2 + g6prescaleTrig1entries3;
    Int_t g6prescaleTrig2entries = g6prescaleTrig2entries1 + g6prescaleTrig2entries2 + g6prescaleTrig2entries3;
    Int_t g6prescaleTrig3entries = g6prescaleTrig3entries1 + g6prescaleTrig3entries2 + g6prescaleTrig3entries3;
    Int_t g6prescaleTrig4entries = g6prescaleTrig4entries1 + g6prescaleTrig4entries2 + g6prescaleTrig4entries3;
    Int_t g6prescaleTrig5entries = g6prescaleTrig5entries1 + g6prescaleTrig5entries2 + g6prescaleTrig5entries3;
    Int_t g6prescaleTrig6entries = g6prescaleTrig6entries1 + g6prescaleTrig6entries2 + g6prescaleTrig6entries3;
    
    Int_t g6prescaled = prescaleTrig0*g6prescaleTrig0entries + prescaleTrig1*g6prescaleTrig1entries + prescaleTrig2*g6prescaleTrig2entries + prescaleTrig3*g6prescaleTrig3entries + prescaleTrig4*g6prescaleTrig4entries + prescaleTrig5*g6prescaleTrig5entries + prescaleTrig6*g6prescaleTrig6entries;
    
    Int_t g4prescaleTrig0entries = g4prescaleTrig0entries1 + g4prescaleTrig0entries2 + g4prescaleTrig0entries3;
    Int_t g4prescaleTrig1entries = g4prescaleTrig1entries1 + g4prescaleTrig1entries2 + g4prescaleTrig1entries3;
    Int_t g4prescaleTrig2entries = g4prescaleTrig2entries1 + g4prescaleTrig2entries2 + g4prescaleTrig2entries3;
    Int_t g4prescaleTrig3entries = g4prescaleTrig3entries1 + g4prescaleTrig3entries2 + g4prescaleTrig3entries3;
    Int_t g4prescaleTrig4entries = g4prescaleTrig4entries1 + g4prescaleTrig4entries2 + g4prescaleTrig4entries3;
    Int_t g4prescaleTrig5entries = g4prescaleTrig5entries1 + g4prescaleTrig5entries2 + g4prescaleTrig5entries3;
    Int_t g4prescaleTrig6entries = g4prescaleTrig6entries1 + g4prescaleTrig6entries2 + g4prescaleTrig6entries3;
    
    Int_t g4prescaled = prescaleTrig0*g4prescaleTrig0entries + prescaleTrig1*g4prescaleTrig1entries + prescaleTrig2*g4prescaleTrig2entries + prescaleTrig3*g4prescaleTrig3entries + prescaleTrig4*g4prescaleTrig4entries + prescaleTrig5*g4prescaleTrig5entries + prescaleTrig6*g4prescaleTrig6entries;
    
    Int_t g2prescaleTrig0entries = g2prescaleTrig0entries1 + g2prescaleTrig0entries2 + g2prescaleTrig0entries3;
    Int_t g2prescaleTrig1entries = g2prescaleTrig1entries1 + g2prescaleTrig1entries2 + g2prescaleTrig1entries3;
    Int_t g2prescaleTrig2entries = g2prescaleTrig2entries1 + g2prescaleTrig2entries2 + g2prescaleTrig2entries3;
    Int_t g2prescaleTrig3entries = g2prescaleTrig3entries1 + g2prescaleTrig3entries2 + g2prescaleTrig3entries3;
    Int_t g2prescaleTrig4entries = g2prescaleTrig4entries1 + g2prescaleTrig4entries2 + g2prescaleTrig4entries3;
    Int_t g2prescaleTrig5entries = g2prescaleTrig5entries1 + g2prescaleTrig5entries2 + g2prescaleTrig5entries3;
    Int_t g2prescaleTrig6entries = g2prescaleTrig6entries1 + g2prescaleTrig6entries2 + g2prescaleTrig6entries3;
    
    Int_t g2prescaled = prescaleTrig0*g2prescaleTrig0entries + prescaleTrig1*g2prescaleTrig1entries + prescaleTrig2*g2prescaleTrig2entries + prescaleTrig3*g2prescaleTrig3entries + prescaleTrig4*g2prescaleTrig4entries + prescaleTrig5*g2prescaleTrig5entries + prescaleTrig6*g2prescaleTrig6entries;
    /*
     std::cout<<"prescaled g6trig0-1: " << g6prescaleTrig0entries1 <<"\n";
     std::cout<<"prescaled g6trig1-1: " << g6prescaleTrig1entries1 <<"\n";
     std::cout<<"prescaled g6trig2-1: " << g6prescaleTrig2entries1 <<"\n";
     std::cout<<"prescaled g6trig3-1: " << g6prescaleTrig3entries1 <<"\n";
     std::cout<<"prescaled g6trig4-1: " << g6prescaleTrig4entries1 <<"\n";
     std::cout<<"prescaled g6trig5-1: " << g6prescaleTrig5entries1 <<"\n";
     std::cout<<"prescaled g6trig6-1: " << g6prescaleTrig6entries1 <<"\n";
     
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
     
     std::cout<<"prescaled g2trig0-2: " << g2prescaleTrig0entries2 <<"\n";
     std::cout<<"prescaled g2trig1-2: " << g2prescaleTrig1entries2 <<"\n";
     std::cout<<"prescaled g2trig2-2: " << g2prescaleTrig2entries2 <<"\n";
     std::cout<<"prescaled g2trig3-2: " << g2prescaleTrig3entries2 <<"\n";
     std::cout<<"prescaled g2trig4-2: " << g2prescaleTrig4entries2 <<"\n";
     std::cout<<"prescaled g2trig5-2: " << g2prescaleTrig5entries2 <<"\n";
     std::cout<<"prescaled g2trig6-2: " << g2prescaleTrig6entries2 <<"\n";
     
     std::cout<<"prescaled g2trig0-3: " << g2prescaleTrig0entries3 <<"\n";
     std::cout<<"prescaled g2trig1-3: " << g2prescaleTrig1entries3 <<"\n";
     std::cout<<"prescaled g2trig2-3: " << g2prescaleTrig2entries3 <<"\n";
     std::cout<<"prescaled g2trig3-3: " << g2prescaleTrig3entries3 <<"\n";
     std::cout<<"prescaled g2trig4-3: " << g2prescaleTrig4entries3 <<"\n";
     std::cout<<"prescaled g2trig5-3: " << g2prescaleTrig5entries3 <<"\n";
     std::cout<<"prescaled g2trig6-3: " << g2prescaleTrig6entries3 <<"\n";
     
     */
    
    
    //definitions of the branching ratios for the various background decays
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

