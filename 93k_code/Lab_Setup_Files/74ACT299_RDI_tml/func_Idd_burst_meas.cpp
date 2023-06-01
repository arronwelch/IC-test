#include "testmethod.hpp"

//for test method API interfaces
#include "mapi.hpp"
#include "rdi.hpp"
using namespace std;
using namespace V93kLimits;

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
	  RDI_INIT();
		  ON_FIRST_INVOCATION_BEGIN();
		  CONNECT();
		  RDI_BEGIN();
		  //Add your test code here.
		  rdi.func().label("gross_func").execute();
		  rdi.dc("idd1").pin("Vcc").iMeasRange(1 mA).measWait(3 ms).average(128).iMeas().execute();
		  RDI_END();

		  DISCONNECT();
		  ON_FIRST_INVOCATION_END();

		  //Retrieve the test result
		  double idd1 = rdi.id("idd1").getValue("Vcc");

		  //Datalog
		  cout << "idd1 = " << idd1 << endl;

			// This method uses the LIMIT API which allows you to program the Limits
			// directly in the TM.
			// LIMIT limit(TM::GT,0, TM::LT,30);
			// TESTSET().cont(true).judgeAndLog_ParametricTest("Vcc","dps_param",limit, idd1 );

			// This is the standard TESTSET API that uses tmLimits which in turn uses the
	        // the test table to set the limits.
	         TESTSET().cont(true).judgeAndLog_ParametricTest("Vcc","dps_param",tmLimits, idd1);


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
