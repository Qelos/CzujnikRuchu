package main

import (
	"io/ioutil"
	"log"
	"strconv"
	"strings"
    "net"
    "fmt"
    "os"
)

var ip string = "192.168.45.147" //Adres ESP
var port int = 1234 //port ESP

const (
	message       = "Ping"    //wiadomość budząca if'a ESP
	StopCharacter = "\r\n\r\n"
)

func SocketClient(ip string, port int) {
	addr := strings.Join([]string{ip, strconv.Itoa(port)}, ":")
	conn, err := net.Dial("tcp", addr)

	defer conn.Close()

	if err != nil {
		log.Fatalln(err)
	}
    
	conn.Write([]byte(message))
	conn.Write([]byte(StopCharacter)) //obudź if'a w ESP

	signal := make([]byte, 16)
	n, _ := conn.Read(signal)
	log.Printf("Receive: %s", signal[:n])              //do usunięcia
    data, _ := strconv.Atoi(string(signal[:n]))        //byte to string
    
    
        f, err := os.Open("signal.txt")     //otwiera 'BD'
        if err != nil {
        fmt.Println(err)
        return
    }
    
    if data == 1{
            /*
        message := []byte("1")
	err := ioutil.WriteFile("signal.txt", message, 0644)
    if err != nil {
		log.Fatal(err)
        */
        message := []byte("1")
       err := ioutil.WriteFile("signal.txt",message,0644) //zapisz w pliku 1 
    if err != nil {
        fmt.Println(err)
        f.Close()
        return
    }
    }else {
    /*
            message := []byte("0")
	err := ioutil.WriteFile("signal.txt", message, 0644)
    if err != nil {
		log.Fatal(err)
        */
        message := []byte("0")
         err := ioutil.WriteFile("signal.txt",message,0644) //zapisz w pliku 0
        if err != nil {
        fmt.Println(err)
        f.Close()
        return
	}
    }
}

func main(){
    for(true){
    SocketClient(ip,port) //chodzi w pętli żeby aktualizować na bierząco. w bocie async?
    }
}