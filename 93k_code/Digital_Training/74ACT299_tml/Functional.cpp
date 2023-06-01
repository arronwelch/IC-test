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
class Functional: public testmethod::TestMethod {

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
	  ON_FIRST_INVOCATION_BEGIN();
	  	  CONNECT();
	  	  Sequencer.reset();
	  	  cout << "\n Execute functional test on all sites \n" << endl;
	  	  FUNCTIONAL_TEST();
	  ON_FIRST_INVOCATION_END();

	  bool passfail_result = GET_FUNCTIONAL_RESULT();

	  TESTSET().cont(true).judgeAndLog_FunctionalTest("Functional", tmLimits, passfail_result);

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
REGISTER_TESTMETHOD("Functional", Functional);
