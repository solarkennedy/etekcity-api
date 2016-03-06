const char okHeader[] PROGMEM =
  "HTTP/1.0 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Pragma: no-cache\r\n"
  ;


static void page400(BufferFiller& buf, const char* data) {
  // TODO: Accept some sort of error hint
  Serial.println(PSTR("400! Data was: "));
  Serial.print(data);
  buf.emit_p(
    PSTR(
      "HTTP/1.0 400 Bad Request\r\n"
      "Content-Type: text/plain\r\n"
      "Pragma: no-cache\r\n"
      "\r\n"
      "400: Sorry no hints. Check serial output. Microcontroller web stacks are hard.\r\n"
    ));
}


static void homePage(BufferFiller& buf) {
  buf.emit_p(
    PSTR(
      "$F\r\n"
      "<a href='/help/'>Help</a>"
      " <a href='/code/'>Direct RF Code Input</a>"
      "<form>"
      "1414:<table border='1'>"
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
}


static void helpPage(BufferFiller& buf) {
  buf.emit_p(
    PSTR(
      "$F\r\n"
    ), okHeader
  );
  buf.emit_p(
    PSTR(
      "<a href='https://github.com/solarkennedy/etekcity-api'>Source Code</a><br>"
      "<a href='/code/'>Direct RF Code Input</a><br><br>"
      "API: <pre>"
      "# Turn a particular outlet NUM on or off:\n"
      "curl http://host/?NUM=(On|Off)\n"
      "\n"
      "# Send a direct RF code (see label on outlets)\n"
      "curl http://host/code/?code=123\n"
    ));
}


static void codeHomePage(BufferFiller& buf) {
  buf.emit_p(
    PSTR(
      "$F\r\n"
      "<form>"
    ), okHeader
  );
  buf.emit_p(
    PSTR(
      "code:<input type='text' name='code'><input type='submit' value='Submit'><br>"
      "</form>"
      "</html>"
    ));
}


static unsigned long getCodeArg(const char* data, const char* key, unsigned long value = -1) {
  // This magic number 10 comes from the possibility of having 9 digits in the RF code
  char code[10];
  // This magic number 10 comes from the offset of "GET /code/?"
  if (ether.findKeyVal(data + 10, code, sizeof code, key) > 0)
    //Serial.print("Found a k/v string in the url: "); Serial.println(code);
    //Serial.print("Debug: My code is: '"); Serial.print(code); Serial.println("'");
    value = atol(code);
  return value;
}


static void codePage(const char* data, BufferFiller& buf) {
  // Searches for the "code=" URL query param and returns the value
  unsigned long code = getCodeArg(data, "code", 0);
  Serial.print(PSTR("Code was: ")); Serial.println(code);

  if (code == -1 || code == 0) {
    Serial.println(PSTR("Couldn't find the code string in the URL?"));
    return page400(buf, data);
  }

  sendCode(code);
  buf.emit_p(
    PSTR(
      "$F\r\n"
      "<meta http-equiv='refresh' content='5;URL=/code/'>"
      "<title>Code Emit Request</title>"
      "Sending code: $L<br>Done."
    ), okHeader, code
  );
  buf.emit_p(
    PSTR(
      "</html>"
    ));
}


static void apiPage(const char* data, BufferFiller& buf) {
  int outlet_num = data[6] - 48;
  int desired_state_offset;

  char letter = data[9];
  Serial.println(letter);
  if (letter == 110) { // "n"
    Serial.println(PSTR("User asked to turn it ON"));
    desired_state_offset = 0;
  }
  else if (letter == 102) { // "f"
    Serial.println(PSTR("User asked to turn it OFF"));
    desired_state_offset = 9;
  }
  else {
    Serial.println(PSTR("Couldn't determine what the desired state was. 400'ing."));
    return page400(buf, data);
  }

  Serial.print(PSTR("Desired State offset:")); Serial.println(desired_state_offset);
  unsigned long code = calculateCode(outlet_num, desired_state_offset);
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

