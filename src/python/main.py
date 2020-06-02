import speech_recognition as sr
import socket

IP = ''
PORTA = 5000

def ouvir_microfone():
    frase= ''
    microfone = sr.Recognizer()
    with sr.Microphone() as source:
        microfone.adjust_for_ambient_noise(source)

        print("Diga alguma coisa: ")

        audio = microfone.listen(source)
    try:
        frase = microfone.recognize_google(audio,language='pt-BR')

        print("Você disse: " + frase)

        if ("vader" in frase.lower()):
            enviarComandoViaSocket(b'1')
        if ("luke" in frase.lower()):
            enviarComandoViaSocket(b'3')

        if ("yoda" in frase.lower()):
            enviarComandoViaSocket(b'2')

        if ("desligar" in frase.lower()):
            enviarComandoViaSocket(b'0')
    except Exception as e:
        print(e)
        print("Não entendi")
    return frase

def enviarComandoViaSocket(valor):
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    dest = (IP, PORTA)
    tcp.connect(dest)
    tcp.send(valor)
    print("OK")
    tcp.close()
while True:
    ouvir_microfone()
