const char okHeader[] PROGMEM =
  "HTTP/1.0 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Pragma: no-cache\r\n"
  ;


static void homePage(BufferFiller& buf) {


  buf.emit_p(PSTR("$F\r\n"
                 
                  "<title>EtekCity Light Controller</title>"
                  "<h3>EtekCity Light Controller</h3>"
                  "<br>"), okHeader
            );


}


