#ifndef Vertex_h
#define Vertex_h

#include "Point.h"
#include "TString.h"
#include "TH1F.h"


/**
 * Vertex class. Used to initialise a Vertex along the beam line. Vertex' data members are a Point in the 3-dimentional space and a multiplicity, i.e. the number of particles produced in the Vertex.
 */
class Vertex : public Point {

 public:

  /**
   * Default constructor.
   * Coordinates are extracted following a gaussian distribution around (0., 0., 0.)cm, center of symmetry of the barrel detector, with sigmas (0.01, 0.01, 5.3)cm.
   * Multiplicity: fixed at default value of 20.
   */
  Vertex();

  /**
   * Standard constructor.
   * Coordinates are extracted following a gaussian distribution around (0., 0., zVert)cm, with sigmas (0.01, 0.01, 5.3)cm.
   * Multiplicity follows a distribution that requires only one parameter.
   * @param multOpt option for specifying the generation distribution for the multiplicity (it can only be "fixed", for now)
   * @param mult fixed value for the multiplicity
   * @param zVert mean value for the Gaussian distribution of the z coordinate
   */
  Vertex(TString multOpt, UInt_t mult, Double_t zVert);

  /**
   * Standard constructor.
   * Coordinates are extracted following a gaussian distribution around (0., 0., zVert)cm, with sigmas (0.01, 0.01, 5.3)cm.
   * Multiplicity follows a distribution that requires two parameters.
   * @param multOpt option for specifying the generation distribution for the multiplicity (it can be "uniform" or "gaus")
   * @param par1 mean (if gaus), lowest multiplicity (if uniform)
   * @param par2 sigma (if gaus), higest multiplicity (if uniform)
   * @param zVert mean value for the Gaussian distribution of the z coordinate
   */
  Vertex(TString multOpt, Double_t par1, Double_t par2, Double_t zVert);

  /**
   * Standard constructor.
   * Coordinates are extracted following a Gaussian distribution around (0., 0., zVert)cm, with sigmas (0.01, 0.01, 5.3)cm.
   * Multiplicity follows a distribution which is passed through an input histogram (hmul, stored in kinem.root)
   * @param multOpt option for specifying the generation distribution for the multiplicity (here it can only be "hist")
   * @param histMult input histogram with multiplicity distribution
   * @param zVert mean value for the Gaussian distribution of the z coordinate
   */
  Vertex(TString multOpt, TH1F* histMult, Double_t zVert);
  
  virtual ~Vertex(); ///< Default destructor.


  //multiplicity generation

  /**
   * Extracts uniform multiplicity
   * The function extracts an integer value for the multiplicity and assigns it to fMult (data member).
   * The multiplicity is extracted following a uniform distribution in [minMult, maxMult] (passed as arguments).
   */
  void genUniformMult(Double_t minMult = 0., Double_t maxMult = 50.);

  /**
   * Extracts gaussian multiplicity
   * The function extracts an integer value for the multiplicity and assigns it to fMult (data member).
   * The multiplicity is extracted following a Gaussian distribution with mean = mult and sigma = sMult, passed as arguments.
   */
  void genGausMult(Double_t mult = 20., Double_t sMult = 5.);

  /**
   * Extracts fixed multiplicity
   * The function extracts an integer value for the multiplicity and assigns it to fMult (data member).
   * The value of the multiplicity is fixed to mult, passed as argument.
   */
  void genFixedMult(UInt_t mult = 20);

  /**
   * Extracts multiplicity following an input distribution
   * The function extracts an integer value for the multiplicity and assigns it to fMult (data member).
   * The value of the multiplicity follows the distribution stored in the input histogram histMult.
   */
  void genHistMult(TH1F* histMult);
    
  
  //getter functions
  Point getPoint() const {return fVertex;}  ///< Returns fPoint
  UInt_t getMult() const {return fMult;}    ///< Returns fMult
  


 private:

  Point fVertex;  ///< Point indicating the 3-dimensional position of the Vertex
  UInt_t fMult;   ///< Multiplicity (i.e. the number of particles produced in the Vertex)

  
  ClassDef(Vertex, 1)
  
};

#endif
