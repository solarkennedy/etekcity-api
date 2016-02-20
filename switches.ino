long calculateCode(int outlet_num, int desired_state){
  return remote1_offset + (outlet_spacing * (outlet_num - 1)) + desired_state;
}

