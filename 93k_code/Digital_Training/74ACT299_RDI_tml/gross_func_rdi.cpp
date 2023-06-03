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
class gross_func_rdi: public testmethod::TestMethod {

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
	  rdi.burstId("My_Burst_1");
	  rdi.func("PF1").label("gross_func").execute();
	  rdi.func("PF2").label("gross_func_Fail").execute();
	  RDI_END();

	  DISCONNECT();
	  ON_FIRST_INVOCATION_END();

	  // retrieve the test result
	  bool PassFail1 = rdi.id("PF1").getPassFail();
	  bool PassFail2 = rdi.id("PF2").getPassFail();
	  int PassFailBurst = rdi.id("My_Burst_1").getPassFail();

	  // Datalog
	  cout << "PassFail1 : " << PassFail1 << endl;
	  cout << "PassFail2 : " << PassFail2 << endl;
	  cout << "PassFailBurst : " << PassFailBurst << endl;
	  TESTSET().cont(true).judgeAndLog_FunctionalTest(PassFail1, "funcTest1");
	  TESTSET().cont(true).judgeAndLog_FunctionalTest(PassFail2, "funcTest2");

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
REGISTER_TESTMETHOD("gross_func_rdi", gross_func_rdi);
