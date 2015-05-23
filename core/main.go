package main

import (
	"fmt"
	"github.com/gorilla/mux"
	"net/http"
)

func lookHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER pageHandler")

}

func moveHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER stubHandler")

}

func main() {
	
	// TODO:: load config from redis 
	
	r := mux.NewRouter()
	r.HandleFunc("/look/{direction}", lookHandler).Methods("GET")
	r.HandleFunc("/move/{direction}", moveHandler).Methods("GET")
	http.Handle("/", r)
	
	host := "0.0.0.0:8091"
	http.ListenAndServe(host, r)
}
