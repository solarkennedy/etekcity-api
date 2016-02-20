long calculateCode(int outlet_num, int desired_state) {

  int outlet_offset;
  switch (outlet_num) {
    case 1: outlet_offset = 0; break;
    case 2: outlet_offset = 144; break;
    case 3: outlet_offset = 464; break;
    case 4: outlet_offset = 2000; break;
    case 5: outlet_offset = 8144; break;
  }

  Serial.println("Code calculation:");
  Serial.print("Remote Offset: "); Serial.println(remote1_offset);
  Serial.print("Outlet: "); Serial.println(outlet_num);
  Serial.print("Outlet Offset: "); Serial.println(outlet_offset);
  Serial.print("Desired state offset: "); Serial.println(desired_state);
  return remote1_offset + outlet_offset + desired_state;
}

void sendCode(long code) {
  Serial.print("Sending code: "); Serial.println(code);
  mySwitch.send(code, 24);
}

