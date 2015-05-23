package main

import (
	"fmt"
	"net/http"
	"github.com/gorilla/mux"
	"github.com/kidoman/embd"
	_ "github.com/kidoman/embd/host/rpi"
)

var bus embd.I2CBus

func lookHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER lookHandler")
	bus.WriteByte(0x04, 0x0d)

}

func moveHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER moveHandler")

}

func main() {
	
	// TODO:: load config from redis 
	
	bus = embd.NewI2CBus(1)
	bus.WriteByte(0x04, 0x0a)
	
	r := mux.NewRouter()
	r.HandleFunc("/look/{direction}", lookHandler).Methods("GET")
	r.HandleFunc("/move/{direction}", moveHandler).Methods("GET")
	http.Handle("/", r)
	
	host := "0.0.0.0:8091"
	http.ListenAndServe(host, r)
}
