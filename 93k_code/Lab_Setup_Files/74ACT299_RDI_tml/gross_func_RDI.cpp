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
class gross_func_RDI: public testmethod::TestMethod {

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

	  //Retrieve the test result
	  bool PassFail1 = rdi.id("PF1").getPassFail();
	  bool PassFail2 = rdi.id("PF2").getPassFail();
	  int PassFailBurst = rdi.id("My_Burst_1").getPassFail();

	  //Datalog
	  cout << "PassFail1 : " << PassFail1 << endl;
	  cout << "PassFail2 : " << PassFail2 << endl;
	  cout << "PassFailBurst : " << PassFailBurst << endl;

	  TESTSET().judgeAndLog_FunctionalTest(PassFail1&&PassFail2);

//	  TESTSET().cont(true).judgeAndLog_FunctionalTest("funcTest1",tmLimits,PassFail1);
//	  TESTSET().cont(true).judgeAndLog_FunctionalTest("funcTest2",tmLimits,PassFail2);

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
REGISTER_TESTMETHOD("gross_func_RDI", gross_func_RDI);
