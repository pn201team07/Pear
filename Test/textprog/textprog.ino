#include <WiFi.h>
char* ssid="meatblock";
char* password="yAMB/gn70A";
WiFiServer server(80);
void setup()
{
    delay(1000);
    Serial.begin(115200);
    pinMode(12, OUTPUT);      // set the LED pin mode
    pinMode(13, OUTPUT);
    pinMode(23, OUTPUT);
    delay(10);
 
    Serial.println();
    Serial.println();
    //Serial.print("SSID:");
   // Serial.print("Passward:");
    Serial.print("Connecting to ");
    Serial.println(ssid);
 
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.print("WiFi connected\n");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
     
    server.begin();
    digitalWrite(12, HIGH);
    delay(10);
    digitalWrite(12, LOW);
}

 
void loop(){
 WiFiClient client = server.available();
 digitalWrite(23, HIGH);
 
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
 
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<meta name='viewport' content='initial-scale=1.5'>");
            client.println("</head>");
            client.println("<body>");
            client.println("<form method='get'>");
            client.println("<font size='4'>ESP-WROOM-32<br>");
            client.println("Smart ALARM</font><br>");
            client.println("<br>");
            //client.println("<input type='text' name=time value='9999'maxlength='4'>");
            //client.println("<input type='submit' name=Switch value='ON' style='background-color:#88ff88; color:red;'>");
            //client.println("<input type='submit' name=Switch value='OFF' style='background-color:black; color:white;'>");
            
            client.println("</form>");
            client.println("</body>");
            client.println("</html>");
 
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
 
        if (currentLine.endsWith("Switch=ON")) {
          digitalWrite(13, HIGH);
          delay(10);
          digitalWrite(13, LOW);
          if(currentLine.indexOf("time=")){
            
          }
          Serial.println("beepON");
        }
        if (currentLine.endsWith("Switch=OFF")) {
          digitalWrite(12, HIGH);
          delay(10);
          digitalWrite(12, LOW);
          Serial.println("beepOFF");
        }
      }
    }
     
    client.stop();
    Serial.println("client disonnected");
  }
}
