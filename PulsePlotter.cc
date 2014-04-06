{

  gROOT->Reset();
  TCanvas* C = new TCanvas("C", "C	", 400, 500);
  C->cd();
  
  TFile* list = new TFile("/Users/cmorgoth/Software/git/TimingAnalysis/tof_2216_run_65_ana.root");
  TTree* tree = (TTree*)list->Get("tree");

  
  float t1gausroot, t2gausroot, t3gausroot, t4gausroot, ch1Amp, ch2Amp, ch3Amp, ch4Amp;
  unsigned int ch1QualityBit, ch2QualityBit, ch3QualityBit, ch4QualityBit;
  unsigned int event;

  tree->SetBranchStatus("*",0);
  
  tree->SetBranchStatus("event",1);

  tree->SetBranchStatus("ch1Amp",1);
  tree->SetBranchStatus("ch2Amp",1);
  tree->SetBranchStatus("ch3Amp",1);
  tree->SetBranchStatus("ch4Amp",1);
  tree->SetBranchStatus("t1gausroot",1);
  tree->SetBranchStatus("t2gausroot",1);
  tree->SetBranchStatus("t3gausroot",1);
  tree->SetBranchStatus("t4gausroot",1);
  tree->SetBranchStatus("ch1QualityBit",1);
  tree->SetBranchStatus("ch2QualityBit",1);
  tree->SetBranchStatus("ch3QualityBit",1);
  tree->SetBranchStatus("ch4QualityBit",1);

  tree->SetBranchAddress("event", &event);
  tree->SetBranchAddress("ch1Amp", &ch1Amp);
  tree->SetBranchAddress("ch2Amp", &ch2Amp);
  tree->SetBranchAddress("ch3Amp", &ch3Amp);
  tree->SetBranchAddress("ch4Amp", &ch4Amp);
  tree->SetBranchAddress("t1gausroot", &t1gausroot);
  tree->SetBranchAddress("t2gausroot", &t2gausroot);
  tree->SetBranchAddress("t3gausroot", &t3gausroot);
  tree->SetBranchAddress("t4gausroot", &t4gausroot);
  tree->SetBranchAddress("ch1QualityBit", &ch1QualityBit);
  tree->SetBranchAddress("ch2QualityBit", &ch2QualityBit);
  tree->SetBranchAddress("ch3QualityBit", &ch3QualityBit);
  tree->SetBranchAddress("ch4QualityBit", &ch4QualityBit);
  
  int listPulse[3000];
  int npulses = 0;
  
  for(int iEntry = 0; iEntry < tree->GetEntries();iEntry++){
    tree->GetEntry(iEntry);
    if(ch2QualityBit==0 && ch1QualityBit==0 && ch3QualityBit==0 && t2gausroot>t1gausroot){
      listPulse[npulses] = iEntry;
      npulses++;
    }
  }



  TFile* f = new TFile("~/DRS4Data/tof_2216_run_65.root");
  TTree* t = (TTree*)f->Get("T");

  int evt;
  float c1[1024];
  float c2[1024];
  float c3[1024];
  float c4[1024];  
  int t1[1024];
  
  t->SetBranchAddress("event", &evt);
  t->SetBranchAddress("c1", c1);
  t->SetBranchAddress("c2", c2);
  t->SetBranchAddress("c3", c3);
  t->SetBranchAddress("c4", c4);
  t->SetBranchAddress("t1", t1);
  
  //int entry = 82;
  
  //t->GetEntry(entry);
  

  std::cout << "npulses: " << npulses << std::endl;
  float sf = 0.20;//samples to ns
  
  TH1F* ch1;// = new TH1F("ch1", "ch1", 1024, .0*sf, 1023.0*sf);
  TH1F* ch2;// = new TH1F("ch2", "ch2", 1024, .0*sf, 1023.0*sf);
  TH1F* ch3;// = new TH1F("ch3", "ch3", 1024, .0*sf, 1023.0*sf);
  TH1F* ch4;// = new TH1F("ch4", "ch4", 1024, .0*sf, 1023.0*sf);
  

  TString sn;
  for(int ipulse; ipulse < npulses; ipulse++){
    t->GetEntry(listPulse[ipulse]);
    ch1 = new TH1F("ch1", "ch1", 1024, .0*sf, 1023.0*sf);
    ch2 = new TH1F("ch2", "ch2", 1024, .0*sf, 1023.0*sf);
    ch3 = new TH1F("ch3", "ch3", 1024, .0*sf, 1023.0*sf);
    ch4 = new TH1F("ch4", "ch4", 1024, .0*sf, 1023.0*sf);
    for(int i = 0; i < 1024; i++){
      ch1->Fill(i*sf, c1[i]);
      ch2->Fill(i*sf, c2[i]);
      ch3->Fill(i*sf, c3[i]);
      ch4->Fill(i*sf, c4[i]);
    }
    
    sn = TString(Form("Long_8GeV_Ele/tof_evt%d",listPulse[ipulse]));
    
    
    ch1->SetXTitle("Time [ns]");
    ch1->SetYTitle("Amp [Volts]");
    ch1->SetLineColor(kRed);
    ch1->Draw("");
    
    ch2->SetLineColor(kBlue);
    ch2->Draw("Same");
    ch3->SetLineColor(8);
    ch3->Draw("same");
    C->SaveAs(sn+".png");
    C->SaveAs(sn+".pdf");
    C->SaveAs(sn+".C");
    C->SaveAs(sn+".root");
    delete ch1;
    delete ch2;
    delete ch3;
    delete ch4;
  }
  
  /*
    ch4->SetLineColor(8);
    //ch4->Draw("");
    ch1->SetXTitle("Time [ns]");
    ch1->SetYTitle("Amp [Volts]");
    ch1->SetLineColor(kRed);
    ch1->Draw("same");
    
    ch2->SetLineColor(kBlue);
    ch2->Draw("Same");
  */
}
