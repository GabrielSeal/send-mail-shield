//Programa feito com base no topigo do LAGBDEGARAGEM
//http://labdegaragem.com/forum/topics/enviar-e-mail-de-alerta-com-et...

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#define time 1000

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
byte server[] = { 200, 147, 99, 132 }; // Colocar o ip do servidor SMTP

EthernetClient client;

void setup()
{
Ethernet.begin(mac, ip);
Serial.begin(9600);
delay(time);
Serial.println("Pronto. Envie 'e' para enviar o e-mail.");
}

void loop()
{
byte EntradaSerial;
EntradaSerial = Serial.read();
if(EntradaSerial == 'e')
{
envia();
}
}

void envia()
{
delay(time);
Serial.println("conectando...");
if (client.connect(server, 587)) // Porta de conexao do servidor do email.
{
Serial.println("conectado!");
Serial.println("enviando email...");
Serial.println();
client.println("EHLO localhost");
recebe();
delay(time);
client.println("AUTH LOGIN");
recebe();
delay(time);
client.println("xxxxxxxxxx"); // Email de login em base de 64: http://base64-encoder-online.waraxe.us/
recebe();
delay(time);
client.println("yyyyyyyyy"); // Senha do email em base de 64: http://base64-encoder-online.waraxe.us/
recebe();
delay(time);
client.println("mail from: <arduinosobral@bol.com.br>"); //Email remetente
recebe();
delay(time);
client.println("rcpt to: <mr.sobral@hotmail.com>"); // Email destinatário
recebe();
delay(time);
client.println("data");
recebe();
delay(time);
client.println("Subject: Teste BYTE IP de Email!"); // Assunto
recebe();
delay(time);
client.println("Testando email com arduino 2"); // Corpo
recebe();
delay(time);
client.println("."); // Indica fim do email.
recebe();
delay(time);
client.println();
recebe();
delay(time);
Serial.println("email enviado!");
delay(time);
if (client.connected()) // Desconecta pra deixar pronto para novo envio.
{
Serial.println();
Serial.println("desconectando...");
client.stop();
Serial.println();
Serial.println();
}
}
else
{
Serial.println("connection failed");
}
Serial.println("Ready. Press 'e' to connect.");
}


void recebe()
{
while (client.available())
{
char c = client.read();
Serial.print(c);
}
}
