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
class OutputDC: public testmethod::TestMethod {
protected:
  string  mPins;
  double  mCurrForce;

protected:
  /**
   *Initialize the parameter interface to the testflow.
   *This method is called just once after a testsuite is created.
   */
  virtual void initialize()
  {
    //Add your initialization code here
    //Note: Test Method API should not be used in this method!
    addParameter("Measure Pins",
                 "PinString",
                 &mPins,
                 testmethod::TM_PARAMETER_INPUT)
      .setComment("Measure there pins");
    addParameter("Current Force(mA)",
                 "double",
                 &mCurrForce,
                 testmethod::TM_PARAMETER_INPUT)
      .setDefault("-24")
      .setOptions("-24:-30")
      .setComment("Force Current on pins");
  }

  /**
   *This test is invoked per site.
   */
  virtual void run()
  {
    //Add your test code here.

	double dVout = 0.0;
	STRING strPin = "";

	PPMU_SETTING	pSetOutputDC;
	PPMU_RELAY		pRelOutputDC, pRelRestore;
	PPMU_MEASURE	pMeaOutputDC;
	PPMU_CLAMP		pClaOutputDC_ON, pClaOutputDC_OFF;
	TASK_LIST		pTasOutputDC, pTasRestore;

	strPin = mPins;

	ON_FIRST_INVOCATION_BEGIN();

		CONNECT();

		cout << "\n Our own Output high level test at pin: " << mPins << endl;

		pSetOutputDC.pin( mPins ).iForce( mCurrForce mA ).iRange( 30 mA ).min( 3500 mV ).max( 4600 mV );

		pSetOutputDC.wait( 1 ms );

		// apply voltage clamp to avoid hot switching during PPMU relay closure
		pClaOutputDC_ON.pin( mPins ).status( "CLAMP_ON" ).high( 4.7 ).low( 0.0 );

		pRelOutputDC.pin( mPins ).status( "PPMU_ON" );
		pRelOutputDC.wait( 2 ms );

		// remove clamps afterwards for improving measurement accuracy
		pClaOutputDC_OFF.pin( mPins ).status( "CLAMP_OFF" );

		pMeaOutputDC.pin( mPins ).execMode( TM::PVAL );

		pRelRestore.pin( mPins ).status( "AC_ON" );
		pRelRestore.wait( 0 ms );

		FUNCTIONAL_TEST();

		pTasOutputDC.add( pSetOutputDC ).add ( pClaOutputDC_ON ).add( pRelOutputDC ).add( pClaOutputDC_OFF ).add( pMeaOutputDC );
		pTasOutputDC.execute();
		pTasRestore.add( pRelRestore ).execute();

	ON_FIRST_INVOCATION_END();

	cout << "My current force parameter = " << mCurrForce << endl;

	STRING_VECTOR strPinList;
	int iSizeOfPinList = 0;

	// extract pin-group into string-array
	strPinList = PinUtility.getDigitalPinNamesFromPinList( mPins, TM::IO_PIN, TRUE, TRUE );
	iSizeOfPinList = strPinList.size();

	// get Value and judge per pin
	for ( int iPinNameIndex = 0; iPinNameIndex < iSizeOfPinList; iPinNameIndex++ )
	{
		dVout = pMeaOutputDC.getValue( strPinList[iPinNameIndex] );
		TESTSET().cont(true).judgeAndLog_ParametricTest( strPinList[iPinNameIndex], "Vout", tmLimits, dVout);
		cout << strPinList[iPinNameIndex] << "=" << dVout << " V" << endl;
	}

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
REGISTER_TESTMETHOD("OutputDC", OutputDC);
