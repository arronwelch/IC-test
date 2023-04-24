/*
 * Using SmartRDI for DC with DC-SCALE
 * DC-Scale Pin modes: DPS & SIG
 * DPS Mode                           SIG Mode
 * Takes part in CONNECT() and        Does NOT take part in CONNECT() and
 * DISCONNECT()                       DISCONNECT()
 * Basic Setup (force, clamp, force   Basic Setup (force, clamp, force range)
 * range) activated by Level          activated by static commands
 * Equation set
 * Supports Test Events in Pattern    Supports Test Events in Pattern
 * => RDI pattern based command       => RDI pattern based command
 */

/*
 * Connect and Disconnect: Static Only {excluded RDI_BEGIN()/RDI_END()}
 * For DPS pins, connect() and disconnect()
 */
rdi.dc().pin("A").connect().execute();
rdi.dc().pin("A").disconnect().execute();
/*
 * For SIG pins
 * - No "connect()" command available, connection is included into iForce() / vForce()
 */
rdi.dc().pin("B").vForce(3.0 V).execute();
/*
 * - Disconnect available: disconnect()
 */
rdi.dc().pin("B").disconnect().execute();

/*
 * Current and Voltage Force Range - Static ( code-based )
 * For DPS pins:
 * Force ranges are set in the Level Equation Set
 * For SIG pins:
 * iForceRange(double) / vForceRange(double)
 * Note: iForceRange() / vForceRange() should be issued together with iForce() / vForce().
 */
