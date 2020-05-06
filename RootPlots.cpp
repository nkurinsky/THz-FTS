//
//RootPlots.cpp
//
#include "TTree.h"
#include <stdio.h>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
void RootPlots(){ 
  TTree *tree[1];
  string name[9];
  std::vector<TCanvas*> c;
  TFile *file= new TFile("~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root", "~/Desktop/Files_for_Koto/g6ana18993_node19_file0.root");

  tree[0] = (TTree*)(file->Get("RecTree;1"));
  TH1F *hist[8];
  for (int i=0; i<9; i++){
    c.push_back(new TCanvas(Form("c%d",i),"",550,600));
    c[i]->SetFillColor(0);
    c[i]->SetBorderMode(0);
    c[i]->SetBorderSize(2);
    c[i]->SetFrameBorderMode(0);
    c[i]->SetFrameBorderMode(0);
    c[i]->cd();
    if (i==0){  
      name[i]="CSIEt";
      tree[0]->Draw("CSIEt");
    }
    if (i==1){
      name[i]="GamClusCsiE";
     (tree[0])->Draw("GamClusCsiE");
     c[i]->SetLogy();
    }
    if (i==2){
      name[i]="GamClusNumber";
      tree[0]->Draw("GamClusNumber");
    }
    if (i==3){
      name[i]="KlongDeltaZ";
      tree[0]->Draw("KlongDeltaZ");
    }
    if (i==4){
      name[i]="KlongPt";
      tree[0]->Draw("KlongPt");
      c[i]->SetLogy();
    }
    if (i==5){
      name[i]="Pi0Number";
      tree[0]->Draw("Pi0Number");
    }
    if (i==6){
      name[i]="Pi0Pt:Pi0RecZ";
      tree[0]->Draw("Pi0Pt:Pi0RecZ");
    }
    if (i==7){
      name[i]="Pi0RecZ";
      tree[0]->Draw("Pi0RecZ");
    }
    if(i==8){
      name[i]="Pi0Pt";
      tree[0]->Draw("Pi0Pt");
    }
    c[i]->SaveAs(TString::Format("plots/%s_3Pi0.eps",name[i].c_str()));
  }
}
