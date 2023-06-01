#include "testmethod.hpp"

//for test method API interfaces
#include "mapi.hpp"
using namespace std;
using namespace V93kLimits;

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class DPS_Meas: public testmethod::TestMethod {

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
	  //DPS Current measurement
	  DPS_TASK dpsIDD;
	  ON_FIRST_INVOCATION_BEGIN();
	  CONNECT();
	  FUNCTIONAL_TEST();
	  dpsIDD.pin("Vcc").min (0 uA).max(10 uA);
	  dpsIDD.execMode(TM::PVAL).trigMode(TM::INTERNAL).samples(4);
	  dpsIDD.execute();
	  ON_FIRST_INVOCATION_END();

	  double dps_result = 1E6*dpsIDD.getValue("Vcc");
	  TESTSET().cont(true).judgeAndLog_ParametricTest("Vcc","dps_param1",tmLimits, dps_result );

	 // LIMIT limit (TM::GT, 0, TM::LT ,10);
	 // limit.unit ("uA");
	  // TEST ("Vcc", "IDD", limit, 1E6*dpsIDD.getValue("VCC"),TRUE);

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
REGISTER_TESTMETHOD("DPS_Meas", DPS_Meas);
