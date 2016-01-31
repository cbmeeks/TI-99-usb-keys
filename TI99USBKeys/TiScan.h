#ifndef _TI_SCAN_H
#define _TI_SCAN_H

//------------------------------------------------------
// TI Keyboard Column Scan Handling
//   The following functions are part of the interrupt
//   handlers triggered when the TI scans a keyboard
//   column.

void setOutputPin(int pin, int state) 
{
  digitalWrite(pin, state ? LOW : HIGH);
}

// Given a columns set of switches, set each output pin accordingly.
void setRowOutputs(int* rows)
{
  setOutputPin(ti_r0, rows[0]);
  setOutputPin(ti_r1, rows[1]);
  setOutputPin(ti_r2, rows[2]);
  setOutputPin(ti_r3, rows[3]);
  setOutputPin(ti_r4, rows[4]);
  setOutputPin(ti_r5, rows[5]);
  setOutputPin(ti_r6, rows[6]);
  setOutputPin(ti_r7, rows[7]);
}

void setAlphaLock()
{
  setOutputPin(ti_r4, *tk_Alpha);
}

void clearOutputs() {
  digitalWrite(ti_r0, HIGH);
  digitalWrite(ti_r1, HIGH);
  digitalWrite(ti_r2, HIGH);
  digitalWrite(ti_r3, HIGH);
  digitalWrite(ti_r4, HIGH);
  digitalWrite(ti_r5, HIGH);
  digitalWrite(ti_r6, HIGH);
  digitalWrite(ti_r7, HIGH);
}

void onTiColumnChange()
{
  // Stop interrupts so I don't get two with each column change.
  noInterrupts();
  if (digitalRead(ti_c0) == LOW) {
    setRowOutputs(c0rows);
  } else if (digitalRead(ti_c1) == LOW) {
    setRowOutputs(c1rows);
  } else if (digitalRead(ti_c2) == LOW) {
    setRowOutputs(c2rows);
  } else if (digitalRead(ti_c3) == LOW) {
    setRowOutputs(c3rows);
  } else if (digitalRead(ti_c4) == LOW) {
    setRowOutputs(c4rows);
  } else if (digitalRead(ti_c5) == LOW) {
    setRowOutputs(c5rows);
  } 

  if (digitalRead(ti_c6) == LOW) {
    setAlphaLock();
  }
  
  interrupts();
}

void setColumnInterrupts()
{
  int interruptMode = CHANGE;
  attachInterrupt(ti_c0, onTiColumnChange, interruptMode);
  attachInterrupt(ti_c1, onTiColumnChange, interruptMode);
  attachInterrupt(ti_c2, onTiColumnChange, interruptMode);
  attachInterrupt(ti_c3, onTiColumnChange, interruptMode);
  attachInterrupt(ti_c4, onTiColumnChange, interruptMode);
  attachInterrupt(ti_c5, onTiColumnChange, interruptMode);
  attachInterrupt(ti_c6, onTiColumnChange, interruptMode);
}


#endif

