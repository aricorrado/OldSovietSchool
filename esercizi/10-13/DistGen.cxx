#include <TH1F.h>
#include <TMath.h>
//#include <TRandom3.h>

#include "DistGen.h"


ClassImp(DistGen)


//DEFAULT CONSTRUCTOR
DistGen::DistGen():
TRandom3()
{
  fParam = 0.5;
  fXmin = 0.;
  fXmax = 2*TMath::Pi();
  fSeed = 65349;
}

//STANDARD CONSTRUCTOR
DistGen::DistGen(double alpha, double xmin, double xmax, unsigned int seed):
  TRandom3()
{
  fParam = alpha;
  fXmin = xmin;
  fXmax = xmax;
  fSeed = seed;

  this->SetName("DistGen"); //memb func di TRandom3
}

//DESTRUCTOR
DistGen::~DistGen(){}


//ASSIGNMENT OPERATOR
DistGen& DistGen::operator=(const DistGen& source){
  if(this != &source){
    TRandom3::operator=(source);
    fParam = source.fParam;
    fXmin = source.fXmin;
    fXmax = source.fXmax;
    fSeed = source.fSeed;
  }
  return *this;
}


//FUNCTION f(x)
double DistGen::funcAlpha(double xx){
  double theta = xx;
  double alpha = fParam; //posso accedere direttamente ai data member privati
                         //di DistGen perché ho specificato che la funzione
                         //è una member function della classe DistGen (DistGen::func)
  return 1/(TMath::Sin(theta)*TMath::Sin(theta) + alpha * TMath::Cos(theta)*TMath::Cos(theta));
}

//INVERSE of CUMULATIVE FUNCTION for f(x)
double DistGen::invCumFuncAlpha(double xx){
  double alpha = fParam;

  return TMath::ATan( TMath::Sqrt(alpha)*TMath::Tan(TMath::Pi()*xx - 0.5) );
}

//FUNCTION g(x)
double DistGen::funcSin(double xx){
  double theta = xx;
 
  return (TMath::Sin(theta)*TMath::Sin(theta)) / (theta*theta);
}

//SUPREMUM of g(x)
double DistGen::sinBig(double xx){
  if(abs(xx)<=2.6) return 1.;
  else if(abs(xx)>2.6) return 0.05;
}


//REJECTION TECHNIQUE
double DistGen::rejection(){
  //fXmin, fXmax
  
  double u1, u2, xT, yT;
  double yBig = fParam<1 ? 1/fParam : 1;
  
  do{
    u1 = gRandom->Rndm(fSeed);//anche this->Rndm(fSeed) oppure solo Rndm(fSeed)
    u2 = gRandom->Rndm(fSeed);
    //cout << u1 << " != " << u2 << endl;
    xT = fXmin+(fXmax-fXmin)*u1;
    yT = yBig*u2;
  }while(funcAlpha(xT)<yT);
  
  return xT;
}
//questo metodo funziona con qualunque funzione (e.g. basta passarla come parametro)


//INVERSION TECHNIQUE
double DistGen::inversion(){

  double u = gRandom->Rndm(fSeed);

  //risurltato in [-pi/2, pi/2]
  double x = invCumFuncAlpha(u);
  
  //traspongo in [0, 2pi]
  double w = gRandom -> Rndm(fSeed);
  if     (w<0.5)        x = x + TMath::Pi(); //II e III quadrante
  else if(w>0.5 && x<0) x = x + 2*TMath::Pi(); // IV quadrante
  else if(w>0.5 && x>0) x = x; //I quadrante (riga superflua)
  
  return x;
}
/*
//INVERSION TECHNIQUE
double DistGen::inversionsin(){

  double u = gRandom->Rndm(fSeed);

  double x;
  if(x<-2.6)
    x
  
  return x;
}

*/

//ROOT NUMERICAL INVERSION
double DistGen::rootInversion(TF1* funcPtr){

  //funcPtr.SetParameter(0, fParam);  
  return funcPtr->GetRandom();
}

//IMPORTANCE SAMPLING
double DistGen::importanceSampling(double xMin, double xMax){
  
  double u1, u2, xT, yT;
  
  do{
    u1 = gRandom->Rndm(fSeed);//anche this->Rndm(fSeed) oppure solo Rndm(fSeed)
    u2 = gRandom->Rndm(fSeed);
    //cout << u1 << " != " << u2 << endl;
    xT = xMin+(xMax-xMin)*u1;
    yT = sinBig(xT)*u2;
  }while(funcSin(xT)<yT);
  
  return xT;

}
