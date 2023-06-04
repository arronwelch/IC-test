#include "testmethod.hpp"

#include "rdi.hpp" // Add this line.

//for test method API interfaces (any other include should be added above this line)
//for MTP test method API interfaces
#include "MtpTest.hpp"
#include "solution_tools.h"
#include "mapi.hpp"
using namespace std;

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class PMU_Meas: public testmethod::TestMethod {

protected:
  /**
   *Initialize the parameter interface to the testflow.
   *This method is called just once after a testsuite is created.
   */
  virtual void initialize()
  {
    //Add your initialization code here
    //Note: Test Method API should not be used in this method!
  }

  /**
   *This test is invoked per site.
   */
  virtual void run()
  {
    //Add your test code here.
	  RDI_INIT();
	  ON_FIRST_INVOCATION_BEGIN();
	  CONNECT();
	  RDI_BEGIN(TA::BURST);
	  rdi.func().label("gross_func").execute();
	  rdi.dc("Vid1").pin("Q0").clamp(0.0, 4.25).iForce(-20 uA).vMeas().valueMode(TA::BADC)
			  .relay(TA::ppmuRly_onPPMU_offACDC, TA::ppmuRly_NO).execute();
	  rdi.dc("Vid2").pin("Q7").clamp(0.0, 4.25).iForce(-20 uA).vMeas().valueMode(TA::BADC)
			  .relay(TA::ppmuRly_onPPMU_offACDC, TA::ppmuRly_NO).execute();
	  rdi.hwRelay().pin("Q0,Q7").setOff("PPMU").execute();
	  RDI_END();
	  DISCONNECT();
	  ON_FIRST_INVOCATION_END();

	  double vout1 = rdi.id("Vid1").getValue();
	  double vout2 = rdi.id("Vid2").getValue();
	  cout << vout1 << endl;
	  cout << vout2 << endl;

    return;
  }

  /**
   *This function will be invoked once the specified parameter's value is changed.
   *@param parameterIdentifier
   */
  virtual void postParameterChange(const string& parameterIdentifier)
  {
    //Add your code
    //Note: Test Method API should not be used in this method!
    return;
  }

  /**
   *This function will be invoked once the Select Test Method Dialog is opened.
   */
  virtual const string getComment() const 
  {
    string comment = " please add your comment for this method.";
    return comment;
  }
};
REGISTER_TESTMETHOD("PMU_Meas", PMU_Meas);
