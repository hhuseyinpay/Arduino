#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

const char* ssid     = "wemos"; // modemin ismi
const char* password = "";      // modemin parolasi

WiFiClient client;

IPAddress ip(192,168,2,170);//arduino ip


char* host  = "192.168.1.35"; // baglanilacak sunucunun ipsi
const int httpPort = 80; // kullanilacak port. Burada http uzerinden haberlesme yapilacak

unsigned long prevBeaconScan = 0; //son tarama zamanini tutuyor
unsigned long prevDataTime = 0; //son transfer zamanini tutuyor


void setup() {

 WiFi.begin(ssid, password); // wifi'ye baglanti
 Serial.begin(9600);
 delay(100);
 while (WiFi.status() != WL_CONNECTED) { //baglantinin saglanmasini garantiliyor
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  Serial.println("--------------");
}


void loop() {
  if (!client.connect(host, httpPort)) {// sunucu baglantisi
    Serial.println("connection failed");
    return;
  }
  delay(500);
  // Datanin gonderilecegi URL
  String url = "/AddAngle.aspx?Angle=";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  //servere gonderilecek data:
  client.println(String("GET ")+"/AddAngle.aspx?Angle="+"**Data**"+"&DeviceId=CD001"+
               " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(5000);

  // Sunucudan gelen cevabi serial ekranda yazdir.
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

}

bool control(String data){
  /*
   * Data transferi sirasinda bozulmalar olabiliyor. Araya NULL karakterler
   * girebiliyor.. 12 karakterlik ASCII data icin kontrol yapan fonksiyon:
   */
  char c;
  for(int i=0;i<12;i++){
    c=data[i];
    if(!isDigit(c) && !isAlpha(c))
    return false;
  }
  return true;
}
