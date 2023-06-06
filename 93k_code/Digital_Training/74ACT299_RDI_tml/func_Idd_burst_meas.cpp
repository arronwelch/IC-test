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
class func_Idd_burst_meas: public testmethod::TestMethod {

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
	  rdi.func().label("gross_func").execute(); // functional test
	  rdi.dc("idd1").pin("Vcc").iMeasRange(1 mA).measWait(3 ms).iMeas().execute();
	  RDI_END();
	  DISCONNECT();
	  ON_FIRST_INVOCATION_END();

	  // retrieve the test result
	  double Idd = rdi.id("idd1").getValue("Vcc");

	  // judge and send the result to Datalog same as usual API
	  LIMIT limit(TM::GT, 0, TM::LT, 30);

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
REGISTER_TESTMETHOD("func_Idd_burst_meas", func_Idd_burst_meas);
