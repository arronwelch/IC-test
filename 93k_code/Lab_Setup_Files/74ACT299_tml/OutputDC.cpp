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
class OutputDC: public testmethod::TestMethod {
protected:
//  testmethod::SpecValue CurrForce;
  string  mPin;
  string voh_out;
  double mCurrForce;
  testmethod::SpecValue  ForceVoltage;

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
                 &mPin,
                 testmethod::TM_PARAMETER_INPUT)
	  .setComment("Measure these pins");

    addParameter("Force Current (mA)",
				 "double",         // parameter type: "int","double","string"...
				 &mCurrForce)       //mVariableName should be declared as Class member variable
   	  .setDefault("-24")
	  .setOptions("-10:-20")
	  .setComment("Force current on to pin");

	  }

  /**
   *This test is invoked per site.
   */
  virtual void run()
  {
    //Add your test code here.


	   double dVout  = 0.0;
	   STRING strPin = "";

	   PPMU_SETTING pSetOutputDC;
	   PPMU_RELAY   pRelOutputDC, pRelRestore;
	   PPMU_MEASURE pMeaOutputDC;
	   PPMU_CLAMP   pClaOutputDC_ON, pClaOutputDC_OFF;
	   TASK_LIST    pTasOutputDC, pTasRestore;

	   strPin = mPin;

	   ON_FIRST_INVOCATION_BEGIN();

	     CONNECT();

	     cout << "\n Our own Output high level test at pin: " << mPin << endl;

	     pSetOutputDC.pin( mPin ).iForce( mCurrForce mA ).iRange( 30 mA ).min( 3500 mV ).max( 4600 mV );
	     pSetOutputDC.wait( 1 ms );

	     //apply voltage clamp to avoid hot switching during PPMU relay closure
	     pClaOutputDC_ON.pin( mPin ).status( "CLAMP_ON" ).high( 4.7 ).low( 0.0 );

	     pRelOutputDC.pin( mPin ).status( "PPMU_ON" );
	     pRelOutputDC.wait( 2 ms );

	     //remove clamps afterwards for improving measurement accuracy
	     pClaOutputDC_OFF.pin( mPin ).status( "CLAMP_OFF" );

	     pMeaOutputDC.pin( mPin ).execMode( TM::PVAL );

	     pRelRestore.pin( mPin ).status( "AC_ON" );
	     pRelRestore.wait( 0 ms );

	     FUNCTIONAL_TEST();

	     pTasOutputDC.add( pSetOutputDC )
	    		     .add( pClaOutputDC_ON )
	    		     .add( pRelOutputDC )
	    		     .add( pClaOutputDC_OFF )
	    		     .add( pMeaOutputDC ).execute();

	  //   pTasOutputDC.execute();
	     pTasRestore.add( pRelRestore ).execute();

	   ON_FIRST_INVOCATION_END();

	   cout << "My current force parameter = " << mCurrForce << endl;

	   STRING_VECTOR strPinList;
	   int iSizeOfPinList = 0;

	   //extract pin-group into string-array
	   strPinList = PinUtility.getDigitalPinNamesFromPinList( mPin, TM::IO_PIN, TRUE, TRUE );
	   iSizeOfPinList = strPinList.size();
	//   voh_out = "VOH";
	   //get Value and judge per pin
	   for( int iPinNameIndex = 0; iPinNameIndex < iSizeOfPinList; iPinNameIndex++ )
	   {
	     dVout = pMeaOutputDC.getValue( strPinList[iPinNameIndex] );
	     TESTSET().cont(true).judgeAndLog_ParametricTest( strPinList[iPinNameIndex], "Vout", tmLimits,  dVout);

	     cout << strPinList[iPinNameIndex] << " = " << dVout << " V" << endl;
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
