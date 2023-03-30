// PPMU Value Measurement(0) demo code:

// API            Option        Notes
// iForce(double)               Force current
// vForce(double)               Force voltage
RDI_BEGIN();
	rdi.dc().pin("pinA").iForce(10 mA).execute(); // current force
	rdi.dc().pin("pinB").vForce(1.0 V).execute(); // voltage force
RDI_END();

// PPMU Value Measurement(1) demo code:
// API            Option        Notes
// iMeas()                      Current measurement
// vMeas()                      Voltage measurement
// measWait(double)             Wait before measurement
// average(int)                 Number of samples for averaging
// getValue(string)             retrieve measurement result

RDI_BEGIN();
	rdi.dc("id1").pin("pinA").iForce(10 mA).vMeas().measWait(5 ms).execute();
	// IFVM with wait time before measurement
	rdi.dc("id2").pin("pinB").vForce(1.0 V).iMeas().measWait(10 ms).average(16).execute();
	// VFIM with wait time and average setting
RDI_END();

double vA = rdi.id("id1").getValue();
double vB = rdi.id("id2").getValue();

// PPMU Value Measurement(2) demo code:
// PS1600/9G hardware has two modes for the PPMU to get analog value results

// Syntax: valueMode(TA::VALUE_MODE type)
// Board ADC:                TA::BADC(Default)
// Successive-Approximation: TA::SA

RDI_BEGIN();
	rdi.dc("id1").pin("pinA").vForce(1.2).iMeas().execute(); // default BADC mode
	rdi.dc("id2").pin("pinB").vForce(1.2).iMeas().valueMode(TA::SA).execute();
	rdi.dc("id3").pin("pinC").vForce(1.2).iMeas().valueMode(TA::BADC).execute();
RDI_END();

// PPMU Value Measurement(3) demo code:
// - With valueMode(TA::BADC) the AMUX will be switched in the pattern, a measWait()
//   might be required to ensure the setting time.
// - Having one BADC for a group of 16 channels, there can be a need of a serial
//   measurement. This serialization is done by SmartRDI automatically.
// - The mode(TA::SA) works in parallel for any pin and site combination
// - The accuracy of the BADC is better than SA.
// - For a single pin measurement the BADC option is much faster.
//   - SA value mode : 300 us
//   - BADC value mode : 25us + 4us * Average

// PPMU PASS/FAIL Measurement
// - The PPMU limit() command supports the pattern based execution in "pass/fail mode".
// - The pass/fail decision is done per burst.

RDI_BEGIN();
	rdi.dc().pin("PinA").vMeas().limit(0.1, 1.2).execute();
RDI_END();

bool result = rdi.getBurstPassFail("PinA"); // pass/fail result of burst

// PPMU Current Range
// The PPMU has different current ranges which can be set by the
// iRange(double) command.
rdi.dc().pin("pinA").vForce(3 V).iMeas().iRange(10 mA).execute();
// Note: Default current range is the MAX range.

// PPMU Relay Options
// Syntax: relay(TA::PPMU_RELAY rly_before, TA::PPMU_RELAY rly_after)
//         relay(TA::PPMU_RELAY rly_before)
rdi.dc().pin(A).vForce(1.0).iMeas().relay(TA::ppmuRly_NO).execute();
// Option: ppmuRly_onPPMU_offACDC        ppmuRly_onPPMU  (keep others)
//         ppmuRly_onAC_offDCPPMU        ppmuRly_onAC    (keep others)
//         ppmuRly_onDC_offACPPMU        ppmuRly_onDC    (keep others)
//         ppmuRly_onACPPMU_offDC        ppmuRly_onALL
//         ppmuRly_onACDC_offPPMU        ppmuRly_offALL
//         ppmuRly_onDCPPMU_offAC        ppmuRly_NO
// Default: rly_before: TA::ppmuRly_onPPMU_offACDC
//          rly_after : TA::ppmuRly_NO              // means: "NO change"
// Note:    PPMU default relay behavior can be changed with RDI_Configure option
//          PPMU_DEFAULT_RELAY (TDC Topic 146692)

// PPMU Voltage Clamp
// - PPMU has a voltage clamp circuit, which is mainly used to  avoid spikes or over-voltage
//   in force current / measure voltage(IFVM) mode
// clamp(double lowClamp, double highClamp)
rdi.dc().pin("pinA").iForce(1 mA).vMeas().clamp(0, 3).execute();

// Note:
// When clamp(low, high) is used with relay() function in same execute(), it will be
// disabled after the relay() action.

// Pure BADC: API Usage
// API              Option               Notes
// vMeas()                               Voltage measurement
// measWait(double)                      Wait between relay/mux and measurement
// average(int)                          Averaging to provide better result
// relay(enum)      2 options            Relay control

// - Pure-BADC can only make voltage measurement.
// - The AMUX + BADC relays are switched automatically.
// - relay() option
//   TA::badcRly_onDC_MEAS_offDC (Default) : Switch on DC relay before measurement and
// switch off DC relay after measurement
//   TA::badcRly_NO : No relay action
RDI_BEGIN();
	rdi.dc().pin("pinA", TA::BADC).vMeas().average(4).measWait(1 ms).execute();
RDI_END();

