const char okHeader[] PROGMEM =
  "HTTP/1.0 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Pragma: no-cache\r\n"
  ;


static void page400(BufferFiller& buf, const char* data) {
  Serial.println("400");
  Serial.println("Data was: ");
  Serial.print(data);
  buf.emit_p(
    PSTR(
      "HTTP/1.0 400 Fail\r\n"
      "Content-Type: text/plain\r\n"
      "Pragma: no-cache\r\n"
      "400"
    ));

}

static void homePage(BufferFiller& buf) {
  buf.emit_p(
    PSTR(
      "$F\r\n"
      "<form>"
      "<table border='1'><caption>Remote 1414</caption>"
    ), okHeader
  );
  for (byte i = 1; i <= 5; ++i) {
    buf.emit_p(
      PSTR(
        "<tr>"
        "<td><input type='submit' name='$D' value='On'></td>"
        "<td>$D</td>    "
        "<td><input type='submit' name='$D' value='Off'></td>"
        "</tr>"
      ), i, i, i);
  }
  buf.emit_p(
    PSTR(
      "<br><a href='code'>Direct code input</a>"
      "</table>"
      "</form>"
      "</html>"
    ));
}


static void apiPage(const char* data, BufferFiller& buf) {
  int outlet_num = data[6] - 48;
  int desired_state_offset;

  char letter = data[9];
  Serial.println(letter);
  if (letter == 110) { // "n"
    Serial.println("User asked to turn it ON");
    desired_state_offset = 0;
  }
  else if (letter == 102) { // "f"
    Serial.println("User asked to turn it OFF");
    desired_state_offset = 9;
  }
  else
    return page400(buf, data);

  Serial.print("Desired State offset:"); Serial.println(desired_state_offset);
  long code = calculateCode(outlet_num, desired_state_offset);
  sendCode(code);

  buf.emit_p(
    PSTR(
      "$F\r\n"
      "<meta http-equiv='refresh' content='5;URL=/'>"
      "<title>API Request</title>"
      "Requested outlet: $D <br>"
      "Sending code: $L<br>"
    ), okHeader, outlet_num, code
  );

  buf.emit_p(
    PSTR(
      "</html>"
    ));
}

