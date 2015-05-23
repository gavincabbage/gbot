package main

import (
	"os"
	"fmt"
	"net/http"
	"github.com/gorilla/mux"
	"github.com/fzzy/radix/redis"
	"github.com/kidoman/embd"
	_ "github.com/kidoman/embd/host/rpi"
)

const REDIS_HOST string = "localhost:8090"

var (
	r redis.Client
	arduino1 byte
	arduino2 byte
	lookRoute string
	moveRoute string
	hostname string
	port string
	bus embd.I2CBus
	router *mux.Router
)

func lookHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER lookHandler")
	bus.WriteByte(arduino1, 0x0e)

}

func moveHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER moveHandler")
	bus.WriteByte(arduino1, 0x0a)
}

func loadConfigFromRedis(r *redis.Client) {
	a1, err := r.Cmd("GET", "core.i2c.addresses.arduino1").Int()
    arduino1 = byte(a1)
	a2, err := r.Cmd("GET", "core.i2c.addresses.arduino2").Int()
	arduino2 = byte(a2)
	lookRoute, err = r.Cmd("GET", "core.routes.look").Str()
	moveRoute, err = r.Cmd("GET", "core.routes.move").Str()
	hostname, err = r.Cmd("GET", "core.hostname").Str()
	port, err = r.Cmd("GET", "core.port").Str()
	if err != nil {
		panic(fmt.Sprintf("problem loading config from redis @ '%s'", REDIS_HOST))
	}
}

func errorHandler() {
	if r := recover(); r != nil {
		fmt.Println(r)
	}
	os.Exit(1)
}

func main() {
	
	defer errorHandler()
	
	r, err := redis.Dial("tcp", REDIS_HOST)
	if err != nil {
		panic(fmt.Sprintf("could not connect to redis @ '%s'", REDIS_HOST))
	}
	loadConfigFromRedis(r)
	
	bus = embd.NewI2CBus(1)
	
	router = mux.NewRouter()
	router.HandleFunc(lookRoute, lookHandler).Methods("GET")
	router.HandleFunc(moveRoute, moveHandler).Methods("GET")
	http.Handle("/", router)
	
	host := hostname + ":" + port
	http.ListenAndServe(host, router)
}
