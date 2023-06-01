#include "testmethod.hpp"

//for test method API interfaces (any other include should be added above this line)
//for MTP test method API interfaces
#include "MtpTest.hpp"
#include "solution_tools.h"
#include "mapi.hpp"
using namespace std;

using namespace V93kLimits; // Add this line

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class DPS_Meas_Task_Gen: public testmethod::TestMethod {

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

	  //DPS Current Measurement
	  DPS_TASK dpsTask;
	  ON_FIRST_INVOCATION_BEGIN();
	    dpsTask.pin("Vcc").min(0 A).max(0.00001 A).measurementMode(TM::MEASURE_CURRENT);
	    dpsTask.wait(0 ms).samples(4).execMode(TM::PVAL);
	    dpsTask.execute();
	  ON_FIRST_INVOCATION_END();

	  double measuredValue = dpsTask.getValue("Vcc");

	  TESTSET().cont(true).judgeAndLog_ParametricTest("Vcc", "static_icc_gen_dps" , tmLimits, measuredValue*1E6);



	  //DC Profiling Current Measurement
	  DC_RESULT_ACCESSOR profileResult;
	  ON_FIRST_INVOCATION_BEGIN();
	    DC_PROFILING_ON("Vcc", TM::CURRENT, 0.2 A, 0.1 ms, 1, TM::RESTORE_RANGE);
	    FUNCTIONAL_TEST();
	    DC_PROFILING_OFF("Vcc");
	    profileResult.uploadResult("Vcc", TM::RESULT_INDEX);
	  ON_FIRST_INVOCATION_END();

	  ARRAY_D results = profileResult.getValues("Vcc");

	  TESTSET().cont(true).judgeAndLog_ParametricTest("Vcc", "static_icc_gen_profile" , tmLimits, results*1E6);

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
REGISTER_TESTMETHOD("DPS_Meas_Task_Gen", DPS_Meas_Task_Gen);
