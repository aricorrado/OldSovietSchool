#ifndef DISTGEN_H
#define DISTGEN_H

#include <TRandom3.h>
#include <TMath.h>
#include <TF1.h>

class DistGen : public TRandom3{
  
 public:
  
  DistGen();
  DistGen(double alpha, double xmin=0., double xmax=2*TMath::Pi(), unsigned int seed=65349); //default arguments ONLY in header file!!
  virtual ~DistGen();
  DistGen& operator=(const DistGen& source); //& prima di operator: non crea una
  
  double func(double xx);
  double invCumFunc(double xx);
  
  double inversion();
  double rejection();
  double importanceSampling(TF1 *funcPtr);
  

 private:
  
  double fParam;
  double fXmin;
  double fXmax;
  unsigned int fSeed;
  //TF1 func = TF1("func1", "1/(TMath::Sin(x)*TMath::Sin(x) + [0] * TMath::Cos(x)*TMath::Cos(x))", 0., 2*TMath::Pi());

  
  ClassDef(DistGen, 1)
    
    };


#endif
