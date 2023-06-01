#include "testmethod.hpp"

//for test method API interfaces
#include "mapi.hpp"
#include "rdi.hpp"
using namespace std;
using namespace V93kLimits;
/**
 *
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class   PMU_Meas    : public testmethod::TestMethod {

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
		  RDI_BEGIN();
		  rdi.func().label("gross_func").execute();
		  rdi.dc("Vid1").pin("I/O1").iForce(-24 mA).vMeas().clamp(0.0,4.25).valueMode(TA::BADC).relay(TA::ppmuRly_onPPMU_offACDC, TA::ppmuRly_NO).execute();
		  rdi.dc("Vid2").pin("I/O3").iForce(-24 mA).vMeas().clamp(0.0,4.25).valueMode(TA::BADC).relay(TA::ppmuRly_onPPMU_offACDC,  TA::ppmuRly_NO).execute();
		  rdi.hwRelay().pin("I/O1,I/O3").setOff("PPMU").execute();
		  RDI_END();
		  DISCONNECT();
		  ON_FIRST_INVOCATION_END();

		  //Retrieve the test result
		  double vout1 = rdi.id("Vid1").getValue();
		  double vout2 = rdi.id("Vid2").getValue();

		  //Datalog
		  cout << "vout_I/01 : " << vout1 << endl;
		  cout << "vout_I/O3 : " << vout2 << endl;

		// TESTSET().cont(true).judgeAndLog_ParametricTest("I/O1","V_I/O1",tmLimits, vout1 );
		// TESTSET().cont(true).judgeAndLog_ParametricTest("I/O3","V_I/O3",tmLimits, vout2 );

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
