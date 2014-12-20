#define SSID "KIKA"
#define PASS "sz123456"

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  delay(1000);
  
  Serial.begin(115200);
  Serial.setTimeout(5000);

  Serial.println("AT+RST");
  delay(100);

  if(Serial.find("ready")) {
    digitalWrite(13, HIGH);
  }
  
}


void loop() {
  delay(1000);
  digitalWrite(13, LOW);
  
  if(connectWiFi()) {
    digitalWrite(13, HIGH);
  }
  
  digitalWrite(13, LOW);
 
  delay(2000);
  String cmd = "AT+CIPSTART=\"TCP\",\"192.168.88.146\",5050";
  Serial.println(cmd);
  delay(500);
    
  while(1) {


    
  
    if(Serial.find("Error")) {
      digitalWrite(13, LOW);
      
    } else {
      digitalWrite(13, HIGH);
      cmd = "ZDRAVO!";

      Serial.print("AT+CIPSEND=");
      Serial.println(cmd.length()+1);
      delay(100);
      if(Serial.find(">")) {
	Serial.println(cmd);
      } else {
	Serial.println("AT+CIPCLOSE");
      }
    }
    
    // Close the TCP connection.
    //Serial.println("AT+CIPCLOSE");
    
  }

}


boolean connectWiFi() {
  Serial.println("AT+CWMODE=1");
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";

  Serial.println(cmd);
  delay(2000);

  if(Serial.find("OK")) {
    return true;
  } else {
    return false;
  }
}