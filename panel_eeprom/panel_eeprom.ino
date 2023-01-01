#include <ESP8266WebServer.h>
#include <EEPROM.h>
ESP8266WebServer server(80);
String usernames[5];
String passwords[5];
String mw;
int x;
int m;
int u_addr=0,p_addr=0;
void switch1On(){
 digitalWrite(2,HIGH);
 panel();
}
void switch1Off()
{
 digitalWrite(2,LOW);
 panel();
}
void switch2On()
{
 digitalWrite(5,HIGH);
 panel();
}
void switch2Off()
{
 digitalWrite(5,LOW);
 panel();
}
void switch3On()
{
 digitalWrite(14,HIGH);
 panel();
}
void switch3Off()
{
 digitalWrite(14,LOW);
 panel();
}
void switch4On()
{
 digitalWrite(16,HIGH);
 panel();
}
void switch4Off()
{
 digitalWrite(16,LOW);
 panel();
}
void login_check()
{
  Serial.println("q");
 //for(int j=0;j<64;j=+8)
 //{
 //Serial.print("username: ");
 //Serial.println(read(j));
 //}
// for(int j=100;j<164;j=+8)
// {
// Serial.print("password: ");
// Serial.println(read(j));
 //}
 

 if(server.hasArg("USERNAME") and server.hasArg ("PASSWORD"))
 {
  bool found=false;

 //for(int i=0;i<64;i=+8)
 //{       
 if(server.arg("USERNAME")==read(100) and server.arg("PASSWORD")==read(130))
 {
  found=true;
    mw="user login";
 server.sendHeader("Location", "/panel");
 server.sendHeader("Cache-Control","no-cache");
 server.sendHeader("Set-Cookie", "LOGIN=1");
 server.send(301);
 }
        //}
 
 if(found==false)
  mw="user login wrong";
 server.sendHeader("Location", "/");
 server.send(301);

      
 }
}
 void logout()
{
    mw="user logout";
 server.sendHeader("Location", "/");
 server.sendHeader("Cache-Control", "no-cache");
 server.sendHeader("Set-Cookie", "LOGIN=0");
 server.send(301); 
}
 void handleNotFound() {
String not_found = R"***(
<!DOCTYPE html> 
<head><meta name="viewport" content="width=device-width, initialscale=1.0">
<title>Controler</title>

 <style>
body{
 background: rgb(0,205,210);
background: radial-gradient(circle, rgba(0,205,210,1) 0%, rgba(10,89,232,1) 87%); 
}
p {
font-size: 1.2em;
color: #fff;
margin-bottom: 1%;
}
</style>
</head>
<body>
<p>the url you entered isn't exist</p>
</body>
</html>
)***";
server.send(200, "text/html", not_found);
}
void panel()
{
String panel ="<!DOCTYPE html> <head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Controler</title><style>html{min-height: 100%; background: rgb(0,205,210);background: radial-gradient(circle, rgba(0,205,210,1) 0%, rgba(10,89,232,1) 87%); }.logout{border: 1px solid red;backgroundcolor:transparent;padding:5px;color:#ff0000;borderradius:10px;font-size: 1em;text-decoration:none;}body{margin-top: 50px;}.button {text-decoration:none;display: inline-block;width: 80px;background-color:#1abc9c;border: none;color: white;padding: 13px 30px;textdecoration: none;font-size: 25px;margin: 0px auto 0px;cursor: pointer;border-radius: 10px;}.button-on {background-color: #1abc9c;}.button-on:active {background-color: #16a085;}.button-off {background-color: #34495e;text-decoration:none;}.button-off:active {text-decoration:none;background-color: #2c3e50;}p {font-size: 1.2em;color: #000;margin-bottom: 1%;}</style></head><body><p align ='center'>Switch 1 <a class='button button-on' href='/switch1On'>ON</a>&nbsp;<a class='button button-off' href='/switch1Off'>OFF</a></p><br><p align ='center'>Switch 2 <a class='button button-on' href='/switch2On'>ON</a>&nbsp;<a class='button button-off' href='/switch2Off'>OFF</a></p><br><p align ='center'>Switch 3 <a class='button button-on' href='/switch3On'>ON</a>&nbsp;<a class='button button-off' href='/switch3Off'>OFF</a></p><br><p align ='center'>Switch 4 <a class='button button-on' href='/switch4On'>ON</a>&nbsp;<a class='button button-off' href='/switch4Off'>OFF</a></p><br><a class='logout' href='/logout'>Log Out</a>";
 if (mw!="")
 {
 panel +="<script>alert('";
 panel +=mw;
  panel +="')</script>";
  mw="";
 }
 panel +="</body></html>";

if(server.hasHeader("Cookie") and 
server.header("Cookie").indexOf("LOGIN=1") != -1)
{
 server.send(200, "text/html", panel);
}
else
{
 server.sendHeader("Location", "/");
 server.send(301);
}
}
void home()
{

String home ="<!DOCTYPE html> <head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Controler</title><style>html{min-height: 100%; background: rgb(0,205,210);background: radial-gradient(circle, rgba(0,205,210,1) 0%, rgba(10,89,232,1) 87%); }.login {border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1em;text-decoration:none;}.login:hover {background-color:red;color:#fff;text-decoration:none;}</style></head><body>";
home +="<form action='/login_check' method='POST'><p align ='center' style='font-size:160%'><b> UserName: <input type='text' name='USERNAME' placeholder='user name' required></b></p><br><p align ='center' style='font-size:160%'><b>Password: <input type='password' name='PASSWORD' placeholder='password' required></b></p><br>";
home +="<p align ='center' style='font-size:160%'>     <input class='login' type='submit' name='submit' value='Log in'>   &nbsp;  <a class='login'  href='/scurity' >rigester</a> </p> ";
 if (mw!="")
 {
home +="<script>alert('";
home +=mw;
home +="')</script>";

mw="";
 }
home +="</form><br></body></html>";
server.send(200, "text/html", home);
Serial.println("s");
 for(int j=0;j<5;j++)
 {
 Serial.print(usernames[j]);
 Serial.println(passwords[j]);
 }
}

 void rigester(){

   String rigester ="<!DOCTYPE html> <head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Controler</title><style>html{min-height: 100%; background: rgb(0,205,210);background: radial-gradient(circle, rgba(0,205,210,1) 0%, rgba(10,89,232,1) 87%); }.login {border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1em;text-decoration:none;}.login:hover {background-color:red;color:#fff;text-decoration:none;} </style></head><body><form action='/rigester_1' method='POST'><p align ='center' style='font-size:160%'><b> UserName: <input type='text' name='USERNAME1' placeholder='user name' required></b></p><br><p align ='center' style='font-size:160%'><b>Password: <input type='password' name='PASSWORD1' placeholder='password' required></b></p><br><p align ='center' style='font-size:160%'><b>re_Password: <input type='password' name='re_PASSWORD' placeholder='re_password' required></b></p><br><p align ='center' style='font-size:160%'>   <input class='login' type='submit' name='submit' value='rigester'> &nbsp;       <a class='login'  href='/' > Log in </a></p>";
    if (mw!="")
 {
   rigester +="<script>alert('";
 rigester +=mw;
  rigester +="')</script>";
  mw="";
 }
rigester +="</form><br></body></html>";
 if(server.hasHeader("Cookie") and
server.header("Cookie").indexOf("sequrity=1") != -1)
{
server.send(200, "text/html", rigester);
}
else
{
server.sendHeader("Location", "/");
server.send(301);
}



  }
  void rigester_1(){
 if(server.hasArg("USERNAME1") and server.hasArg("PASSWORD1") and server.hasArg("re_PASSWORD") )
 {
 if( server.arg("PASSWORD1")==server.arg("re_PASSWORD") )
 {
    mw=" user rigestered ";
//   if(u_addr>62)
//   u_addr=0;
//   u_addr=u_addr+8;
//   if(p_addr>162)
//   u_addr=100;
//   u_addr=u_addr+8;
   
write(100,server.arg("USERNAME1"));
write(130,server.arg("PASSWORD1"));
 server.sendHeader("Location", "/panel");
 server.send(301);
 }
 else{
  mw="PASSWord or re wrong ";
 server.sendHeader("Location", "/rigester");
 server.send(301);
 }
 }
 }
  void scurity(){
 String scurity1 = "<!DOCTYPE html>";
 scurity1 +="<head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Controler</title>";
 scurity1 +="<style>html{min-height: 100%; background: rgb(0,205,210);background: radial-gradient(circle, rgba(0,205,210,1) 0%, rgba(10,89,232,1) 87%);}.login {border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1em;text-decoration:none;}.login:hover {background-color:red;color:#fff;text-decoration:none;}</style>";
 scurity1 +="</head><body><form action='/scurity_1' method='POST'><p align ='center' style='font-size:160%'><b> scuritykey: <input type='text' name='scurity_key' placeholder='scurity_key' required></b></p><br><p align ='center' style='font-size:160%'>";
 scurity1 +="<input class='login'  type='submit' name='scurity2' value='scurity_key'></p>";
 if (mw!="")
 {
 scurity1 +="<script>alert('";
 scurity1 +=mw;
 scurity1 +="')</script>";
 mw="";
 }
 scurity1 +="</form><br></body></html>";

  server.send(200, "text/html", scurity1);


    }
      void ssid(){
 String ssid = "<!DOCTYPE html>";
 ssid +="<head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Controler</title>";
 ssid +="<style>html{min-height: 100%; background: rgb(0,205,210);background: radial-gradient(circle, rgba(0,205,210,1) 0%, rgba(10,89,232,1) 87%);}.login {border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1em;text-decoration:none;}.login:hover {background-color:red;color:#fff;text-decoration:none;}</style>";
 ssid +="</head><body><form action='/ssid' method='POST'><p align ='center' style='font-size:160%'><b> username_ssid: <input type='text' name='user' placeholder='username' required></b></p><p align ='center' style='font-size:160%'><b> password_ssid: <input type='text' name='pass' placeholder='password' required></b></p><br><p align ='center' style='font-size:160%'>";
 ssid +="<input class='login'  type='submit' name='scurity2' value='enter'></p>";
 if (mw!="")
 {
 ssid +="<script>alert('";
 ssid +=mw;
 ssid +="')</script>";
 mw="";
 }
 ssid +="</form><br></body></html>";

  server.send(200, "text/html", ssid);


    }
      void scurity_1(){
        
 if(server.hasArg("scurity_key"))
 {

 if(server.arg("scurity_key")=="Tohidn1387" )
 {
  mw="scurity_key right";
 server.sendHeader("Location", "/rigester");
 server.sendHeader("Cache-Control","no-cache");
 server.sendHeader("Set-Cookie", "sequrity=1");
 server.send(301);
 }
 else{
  server.sendHeader("Location", "/");

 server.send(301);
  mw="scurity_key wrong";
 }
 }
 
 }
       void ssid_1(){
        
 if(server.hasArg("user") and server.hasArg("pass"))
 {

write(200,server.arg("user"));
write(220,server.arg("pass"));
  mw="ssid right";
 server.sendHeader("Location", "/rigester");
 server.sendHeader("Cache-Control","no-cache");
 server.sendHeader("Set-Cookie", "sequrity=1");
 server.send(301);


 }
 
 }
void setup()
{
 pinMode(2, OUTPUT); 
 pinMode(5, OUTPUT); 
 pinMode(14, OUTPUT); 
 pinMode(16, OUTPUT); 
 WiFi.mode(WIFI_AP); 
 WiFi.softAP(read(200),read(220));
 server.on("/", home);
 server.on("/panel", panel);
 server.on("/login_check", login_check);
 server.on("/rigester", rigester); 
 server.on("/rigester_1", rigester_1);
 server.on("/switch1On", switch1On);
 server.on("/switch1Off", switch1Off);
 server.on("/switch2On", switch2On);
 server.on("/switch2Off", switch2Off);
 server.on("/switch3On", switch3On);
 server.on("/switch3Off", switch3Off);
 server.on("/switch4On", switch4On);
 server.on("/switch4Off", switch4Off);
 server.on("/logout", logout); 
 server.on("/scurity", scurity); 
 server.on("/scurity_1", scurity_1);
 EEPROM.begin(512);
 const char * headerkeys[] = {"User-Agent", "Cookie"} ;
 size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
 server.collectHeaders(headerkeys, headerkeyssize );
 server.onNotFound(handleNotFound);
 server.begin();
  Serial.begin(9600);
}
void write(int address, String data)
{
  int stringSize = data.length();
  for(int i=0;i<stringSize;i++)
  {
    EEPROM.write(address+i, data[i]);
  }
  EEPROM.write(address + stringSize,'\0');   //Add termination null character
 EEPROM.commit();
}
String read(int address)
{
  char data[100]; 
  int len=0;
  unsigned char k;
  k = EEPROM.read(address);
  while(k != '\0' && len < 100)   //Read until null character
  {
    k = EEPROM.read(address + len);
    data[len] = k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
void loop() {
 server.handleClient();

}



 

  


 
