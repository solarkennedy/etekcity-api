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
      "<title>EtekCity Light Controller</title>"
      "<h3>EtekCity Light Controller</h3>"
      "<br>"
      "<form>"
      "<table border='1'><caption>Remote 1414</caption>"
    ), okHeader
  );
  for (byte i = 1; i <= 5; ++i) {
    buf.emit_p(
      PSTR(
        "  <tr>"
        "    <td><input type='submit' name='$D' value='On'></td>"
        "    <td>$D</td>    "
        "    <td><input type='submit' name='$D' value='Off'></td>"
        "  </tr>"
      ), i, i, i);
  }
  buf.emit_p(
    PSTR(
      "</table>"
      "</form>"
      "</html>"
    ));
}


static void apiPage(const char* data, BufferFiller& buf) {
  int outlet_num = data[6] - 48;
  bool desired_state;

  char letter = data[9];
  Serial.println(letter);
  if (letter == 110) // "n"
    desired_state = OFF;
  else if (letter == 102) // "f"
    desired_state == ON;
  else
    return page400(buf, data);

  long code = calculateCode(outlet_num, desired_state);
  Serial.print("Sending code: "); Serial.print(code);

  buf.emit_p(
    PSTR(
      "$F\r\n"
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



