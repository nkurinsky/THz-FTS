//
//RootPlotMCcuts.cpp
//
// compile this file usign g++
// g++ `root-config --cflags --glibs` RootPlotMCcutandUncut.cp -o RootPlotMCcutandUncut.exe
// ./RootPlotMCcutandUncut.exe

//montecarlo from run 63, 27kW
//data from run 62, 24kW

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
#include <TRatioPlot.h>
#include <TLegend.h>
#include <TLegendEntry.h>



int main(){
    
    //initializing cuts
    bool minGammaEbool = true;
    Int_t minGammaEnergy = 100;
    bool maxGammaEbool = true;
    Int_t maxGammaEnergy = 2000;
    bool minFiducialXYbool = true;
    Int_t MinFiducialXYvalue = 150;
    bool maxFiducialRbool = true;
    Int_t MaxFiducialRvalue = 850;
    bool KlongPtMaxbool = true;
    Int_t KlongPtMaxvalue = 50;
    bool deltaVertexTimebool = true;
    Int_t deltaVertexTimevalue = 3;
    bool totalEtbool = true;
    Int_t TotalEtvalue = 650;
    bool KlongChiSqZbool = true;
    Int_t KlongChiSqZvalue = 20;
    bool MaxDeltaPi0Massbool = true;
    Int_t MaxDeltaPi0Massvalue = 10;
    bool MinClusterDistancebool = true;
    Int_t MinClusterDistancevalue = 150;
    bool maxPi0RecZbool = true;
    Int_t maxPi0RecZvalue = 5000;
    bool minPi0RecZbool = true;
    Int_t minPi0RecZvalue = 3000;
   
    
    
    
    //initializing vectors of things
    TString name[]={"CSIEt","GamClusCsiE","GamClusNumber", "KlongDeltaZ","KlongPt","Pi0Number","Pi0RecZ","Pi0Pt","Pi0Pt:Pi0RecZ"};
    TString GreekName[]={"CSIEt","GamClusCsiE","GamClusNumber", "K^{0}_{L}DeltaZ","K^{0}_{L}Pt","#pi^{0}Number","#pi^{0}RecZ","#pi^{0}Pt","#pi^{0}Pt:#pi^{0}RecZ"};
    std::vector<TCanvas*> c;
    
    std::vector<TH1F*> h;
    std::vector<TH1F*> mch;
    std::vector<TH1F*> mchuncut;
    
    std::vector<double> lines = {1}; //for the line through the ratio plots at 1

    
    //open the file
    TFile *myFile = TFile::Open("~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root", "~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root");
    TFile *mcFile = TFile::Open("~/Desktop/Files_for_Koto/KL3pi0_160333.root", "~/Desktop/Files_for_Koto/KL3pi0_160333.root");
    TTree* myTree = (TTree*) myFile->Get("RecTree");
    TTree* mcTree = (TTree*) mcFile->Get("RecTree");
    
    //data
    Int_t  GamClusNumber, Pi0Number;
    Double_t MinGammaE, MaxGammaE, MinFiducialXY, MaxFiducialR, DeltaVertexTime, TotalEt, KlongChiSqZ, MaxDeltaPi0Mass, MinClusterDistance;
    Double_t CSIEt, GamClusCsiE[6][120], KlongDeltaZ[6], KlongPt[6],Pi0RecZ[6], Pi0Pt[6], Pi0Mom[6][3];
    
    //monte carlo
    Int_t  mcGamClusNumber, mcPi0Number;
    Double_t mcMinGammaE, mcMaxGammaE, mcMinFiducialXY, mcMaxFiducialR, mcDeltaVertexTime, mcTotalEt, mcKlongChiSqZ, mcMaxDeltaPi0Mass, mcMinClusterDistance;
    Double_t mcCSIEt, mcGamClusCsiE[6][120], mcKlongDeltaZ[6], mcKlongPt[6],mcPi0RecZ[6], mcPi0Pt[6], scale[9], mcscale[9], mchuncutscale[8],  mcPi0Mom[6][3];

    
    //linking local variables to the branches
    myTree->SetBranchAddress("CSIEt", &CSIEt); //h0
    myTree->SetBranchAddress("GamClusCsiE", GamClusCsiE); //h1
    myTree->SetBranchAddress("GamClusNumber", &GamClusNumber);//h2
    myTree->SetBranchAddress("KlongDeltaZ", KlongDeltaZ); //h3
    myTree->SetBranchAddress("KlongPt", KlongPt); //h4
    myTree->SetBranchAddress("Pi0Number", &Pi0Number); //h5
    myTree->SetBranchAddress("Pi0RecZ", Pi0RecZ); //h6
    myTree->SetBranchAddress("Pi0Pt", Pi0Pt); //h7
    
    myTree->SetBranchAddress("MaxGammaE", &MaxGammaE);//for cuts
    myTree->SetBranchAddress("MinGammaE", &MinGammaE); //for cuts
    myTree->SetBranchAddress("MinFiducialXY", &MinFiducialXY); //for cuts
    myTree->SetBranchAddress("MaxFiducialR", &MaxFiducialR); //for cuts
    myTree->SetBranchAddress("DeltaVertexTime", &DeltaVertexTime); //for cuts
    myTree->SetBranchAddress("TotalEt", &TotalEt); //for cuts
    myTree->SetBranchAddress("KlongChiSqZ", &KlongChiSqZ); //for cuts
    myTree->SetBranchAddress("MaxDeltaPi0Mass", &MaxDeltaPi0Mass); //for cuts
    myTree->SetBranchAddress("MinClusterDistance", &MinClusterDistance); //for cuts
    
    //linking local variables to the montecarlo branches
    mcTree->SetBranchAddress("CSIEt", &mcCSIEt); //h0
    mcTree->SetBranchAddress("GamClusCsiE", mcGamClusCsiE); //h1
    mcTree->SetBranchAddress("GamClusNumber", &mcGamClusNumber);//h2
    mcTree->SetBranchAddress("KlongDeltaZ", mcKlongDeltaZ); //h3
    mcTree->SetBranchAddress("KlongPt", mcKlongPt); //h4
    mcTree->SetBranchAddress("Pi0Number", &mcPi0Number); //h5
    mcTree->SetBranchAddress("Pi0RecZ", mcPi0RecZ); //h6
    mcTree->SetBranchAddress("Pi0Pt", mcPi0Pt); //h7
    
    mcTree->SetBranchAddress("MaxGammaE", &mcMaxGammaE);//for cuts
    mcTree->SetBranchAddress("MinGammaE", &mcMinGammaE); //for cuts
    mcTree->SetBranchAddress("MinFiducialXY", &mcMinFiducialXY); //for cuts
    mcTree->SetBranchAddress("MaxFiducialR", &mcMaxFiducialR); //for cuts
    mcTree->SetBranchAddress("DeltaVertexTime", &mcDeltaVertexTime); //for cuts
    mcTree->SetBranchAddress("TotalEt", &mcTotalEt); //for cuts
    mcTree->SetBranchAddress("KlongChiSqZ", &mcKlongChiSqZ); //for cuts
    mcTree->SetBranchAddress("MaxDeltaPi0Mass", &mcMaxDeltaPi0Mass); //for cuts
    mcTree->SetBranchAddress("MinClusterDistance", &mcMinClusterDistance); //for cuts
    
    
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
    mch.push_back(new TH1F(name[0],name[0],100, 0, 7000)); //CSIEt
    mch.push_back(new TH1F(name[1],name[1],75,0,1200)); //GamClusCsiE
    mch.push_back(new TH1F(name[2],name[2],10,4,10)); //GamClusNumber
    mch.push_back(new TH1F(name[3],name[3],100,0,2500)); //KlongDeltaZ
    mch.push_back(new TH1F(name[4],name[4],10,0,140)); //KlongPt
    mch.push_back(new TH1F(name[5],name[5],10,2,10)); //Pi0Number
    mch.push_back(new TH1F(name[6],name[6],100,0,6000)); //Pi0RecZ
    mch.push_back(new TH1F(name[7],name[7],50,0,600)); //Pi0Pt
    TH2F *mch8 = new TH2F(name[8], "Monte Carlo", 200,0,6100,200,0,600); //Pi0Pt:Pi0RecZ
    
    //creating the uncut monte carlo histograms
    mchuncut.push_back(new TH1F(name[0],name[0],100, 0, 7000)); //CSIEt
    mchuncut.push_back(new TH1F(name[1],name[1],75,0,1200)); //GamClusCsiE
    mchuncut.push_back(new TH1F(name[2],name[2],10,4,10)); //GamClusNumber
    mchuncut.push_back(new TH1F(name[3],name[3],100,0,2500)); //KlongDeltaZ
    mchuncut.push_back(new TH1F(name[4],name[4],10,0,140)); //KlongPt
    mchuncut.push_back(new TH1F(name[5],name[5],10,2,10)); //Pi0Number
    mchuncut.push_back(new TH1F(name[6],name[6],100,0,6000)); //Pi0RecZ
    mchuncut.push_back(new TH1F(name[7],name[7],50,0,600)); //Pi0Pt

    int nEntries = myTree->GetEntries();
    
    for (int iEnt=0; iEnt < nEntries; iEnt++) {
        myTree->GetEntry(iEnt);
        //std::cout<<"iEnt: " <<iEnt<<"\n";
        
        //initialzing and applying cuts
        if (minGammaEbool) {
            if (MinGammaE < minGammaEnergy){ //if actual energy is less than min energy cut,then skip the loop
                continue;
            }
        }
        if (maxGammaEbool) {
            if (MaxGammaE > maxGammaEnergy){ //if actual energy is greater than max energy cut,then skip the loop
                continue;
            }
        }
        if (minFiducialXYbool) {
            if (MinFiducialXY < MinFiducialXYvalue){
                continue;
            }
        }
        if (maxFiducialRbool) {
            if (MaxFiducialR > MaxFiducialRvalue){
                continue;
            }
        }
        if (KlongPtMaxbool){
            for (int l=0; l<6; l++){
                if (KlongPt[l] > KlongPtMaxvalue){
                    goto increasing;
                }
            }
        }
        if (deltaVertexTimebool) {
            if (DeltaVertexTime > deltaVertexTimevalue){
                continue;
            }
        }
        if (totalEtbool) {
            if (TotalEt < TotalEtvalue){
                continue;
            }
        }
        if (KlongChiSqZbool) {
            if (KlongChiSqZ > KlongChiSqZvalue){
                continue;
            }
        }
        if (MaxDeltaPi0Massbool) {
            if (MaxDeltaPi0Mass > MaxDeltaPi0Massvalue){
                continue;
            }
        }
        if (MinClusterDistancebool) {
            if (MinClusterDistance < MinClusterDistancevalue){
                continue;
            }
        }
        if (maxPi0RecZbool) {
            for (int l=0; l<6; l++){
                if (Pi0RecZ[l] > maxPi0RecZvalue){
                    goto increasing;
                }
            }
        }
        if (minPi0RecZbool) {
            for (int l=0; l<6; l++){
                if (Pi0RecZ[l] < minPi0RecZvalue){
                    goto increasing;
                }
            }
        }

        //fillling the histograms with the entries that have passed cutes
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
    increasing:; //this is how we are applying cuts from the array based branches.
    }
    
    nEntries = mcTree->GetEntries();
    for (int iEnt=0; iEnt < nEntries; iEnt++) {
        mcTree->GetEntry(iEnt);
        mchuncut[0]->Fill(mcCSIEt);
        mchuncut[2]->Fill(mcGamClusNumber);
        mchuncut[5]->Fill(mcPi0Number);
        for (int n=0; n<6; n++) {
            mchuncut[3]->Fill(mcKlongDeltaZ[n]);
            mchuncut[4]->Fill(mcKlongPt[n]);
            mchuncut[6]->Fill(mcPi0RecZ[n]);
            mchuncut[7]->Fill(mcPi0Pt[n]);
            
            for (int j=0; j<120; j++) {
                mchuncut[1]->Fill(mcGamClusCsiE[n][j]);
            }
        }

        
        //initializing and applying cuts
        if (minGammaEbool) {
            if (mcMinGammaE < minGammaEnergy){ //if actual energy is less than min energy cut,then skip the loop
                continue;
            }
        }
        if (maxGammaEbool) {
            if (mcMaxGammaE > maxGammaEnergy){ //if actual energy is greater than max energy cut,then skip the loop
                continue;
            }
        }
        if (minFiducialXYbool) { //if actual xy fiducial is less than min fiducial cut,then skip the loop
            if (mcMinFiducialXY < MinFiducialXYvalue){
                continue;
            }
        }
        if (maxFiducialRbool) { //if actual R fiducial is more than min fiducial cut,then skip the loop
            if (mcMaxFiducialR > MaxFiducialRvalue){
                continue;
            }
        }
        if (KlongPtMaxbool){
            for (int l=0; l<6; l++){
                if (mcKlongPt[l] > KlongPtMaxvalue){
                    goto increasingmc;
                }
            }
        }
        if (deltaVertexTimebool) {
            if (mcDeltaVertexTime > deltaVertexTimevalue){
                continue;
            }
        }
        if (totalEtbool) {
            if (mcTotalEt < TotalEtvalue){
                continue;
            }
        }
        if (KlongChiSqZbool) {
            if (mcKlongChiSqZ > KlongChiSqZvalue){
                continue;
            }
        }
        if (MaxDeltaPi0Massbool) {
            if (mcMaxDeltaPi0Mass > MaxDeltaPi0Massvalue){
                continue;
            }
        }
        if (MinClusterDistancebool) {
            if (mcMinClusterDistance < MinClusterDistancevalue){
                continue;
            }
        }
        if (maxPi0RecZbool) {
            for (int l=0; l<6; l++){
                if (mcPi0RecZ[l] > maxPi0RecZvalue){
                    goto increasingmc;
                }
            }
        }
        if (minPi0RecZbool) {
            for (int l=0; l<6; l++){
                if (mcPi0RecZ[l] < minPi0RecZvalue){
                    goto increasingmc;
                }
            }
        }
        

        //filling histograms with the entries that have passed all of our cuts
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
        increasingmc:; //this is how we are applying cuts from the array based branches.
    }
    
    TString x[]={"Total Energy in CSI (MeV)","Energy in CSI gamma cluster (MeV)","Number of gamma clusters", "Range of possible reconstructed positions of K^{0}_{L} (mm)","K^{0}_{L} transverse momentum (MeV/c)","Number of #pi^{0}s","#pi^{0} reconstructed Z poistion (mm)","#pi^{0} transverse momentum (MeV/c)"};

    
    //initializing the ratio plot
    std::vector<TRatioPlot*> rp;
    
    for (int i=0; i<9; i++){
        if (i==8){
            //no ratio plot for the 2d histogram
            c.push_back(new TCanvas(Form("c%d",i),"",1250,600)); //creates the canvas
        }
        else{
            c.push_back(new TCanvas(Form("c%d",i),"",800,800)); //creates the canvas
        }
      c[i]->SetFillColor(0);
      c[i]->SetBorderMode(0);
      c[i]->SetBorderSize(2);
      c[i]->SetFrameBorderMode(0);
      c[i]->SetFrameBorderMode(0);
      c[i]->cd();

        //histogram #8 is special bc it is 2d, so eerything is a bit different.
        //comparing 2 2d histograms side by side rather than plotting on the same page
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
            h[i]->GetYaxis()->SetTitleOffset(1.5);
            h[i]->GetXaxis()->SetTitleOffset(1.4);
            h[i]->GetYaxis()->SetTitle("Arb. Units");
            h[i]->GetXaxis()->SetTitle(x[i]);
            h[i]->GetYaxis()->SetTitleOffset(1.6);
            TLegend *leg= new TLegend(0.8,0.84,0.89,0.89);
            leg->AddEntry(h[i],"data");
            leg->AddEntry(mch[i],"monte carlo");
            leg->AddEntry(mchuncut[i],"uncut monte carlo");
            leg->SetBorderSize(2);
            
            
            //sum of the weights for the error (Brian)
            h[i]->Sumw2();
            mch[i]->Sumw2();

            
            //normalization
            scale[i] = 1/h[i]->Integral();
            h[i]->Scale(scale[i]);
            mcscale[i] = 1/mch[i]->Integral();
            mch[i]->Scale(mcscale[i]);
            mchuncutscale[i]=1/mchuncut[i]->Integral();
            mchuncut[i]->Scale(scale[i]);
            
            //coloring of histograms
            mch[i]->SetLineColor(kRed);


            
            rp.push_back(new TRatioPlot(h[i],mch[i])); //creates the ratio plots
            rp[i]->SetGridlines(lines);
            rp[i]->Draw();
            rp[i]->GetUpperPad()->cd();
            mchuncut[i]->Draw("same");
            //setting log plots for GamClusNumber and KlongPt and Pi0RecZ and Pi0Pt plots
            if (i==1 or i==3 or i==4 or i==6 or i==7){
                c[i]->SetLogy();
            }
            rp[i]->GetUpperRefYaxis()->SetRangeUser(0.,1.);
            
            
            mchuncut[i]->SetLineColor(1);


            leg->Draw();
            rp[i]->GetLowerRefGraph()->SetMinimum(-0.5);
            rp[i]->GetLowerRefGraph()->GetYaxis()->SetTitle("Data : MC Ratio");
            rp[i]->GetLowerRefGraph()->GetYaxis()->SetTitleOffset(1.5);
            rp[i]->GetLowerRefGraph()->SetMaximum(2);

        }
        c[i]->Update();
        
        //save the histograms as pdfs
        c[i]->SaveAs(TString::Format("MCPlotsCutnUncut/%s_3Pi0.eps",name[i].Data()));
   }
}

