package main

import (
	//"net/http"
	"log"
	"io/ioutil"
    //"strconv"
)

func main() {
	MakeRequest()
}

func MakeRequest() {
	/*
    resp, err := http.Get("http://localhost:1234/view/signal")
	if err != nil {
		log.Fatalln(err)
	}

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalln(err)
	}
    */
    
    b, err := ioutil.ReadFile("signal.txt") //czytaj plik
    if err != nil {
        log.Print(err)
    }
    str := string(b)                //wczytana dana: byte to string
    log.Println(str)                 //można usunąć
    
    
    
	//log.Println(string(body))
	//signal, _ := strconv.Atoi(string(body))

    if (str == "1"){//sprawza czytana daną
        log.Println("Ktoś gra")
    }else{
        log.Println("Nikt nie gra")
    }
}