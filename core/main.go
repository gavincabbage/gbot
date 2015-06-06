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

const (
	REDIS_HOST string = "localhost:8090",
)

var moves map[string]int = map[string]int{
	"forward" : 10,
	"back" : 11,
	"left" : 12,
	"right" : 13,
	"stop" : 14,
}

var looks map[string]int = map[string]int{
	"center" : 20,
	"left" : 21,
	"right" : 22,
	"up" : 23,
	"down" : 24,
}

type redisClient struct {
	client *redis.Client
	host string
}
func newRedisClient(host string) *redisClient {
	client, err := redis.Dial("tcp", host)
	if err != nil {
		panic(fmt.Sprintf("could not reach redis @ '%s'", host))
	}
	return &redisClient{client, host}
}
func (r *redisClient) getString(key string) string {
	val, err := r.client.Cmd("GET", key).Str()
	if err != nil {
		panic(fmt.Sprintf("could not get string value from redis for key '%s'", key))
	}
	return val
}
func (r *redisClient) getInt(key string) int {
	val, err := r.client.Cmd("GET", key).Int()
	if err != nil {
		panic(fmt.Sprintf("could not get int value from redis for key '%s'", key))
	}
	return val
}
func (r *redisClient) getByte(key string) byte {
	return byte(r.getInt(key))
}

var (
	arduino1, arduino2 byte
	moveForward, moveBack, moveLeft, moveRight, moveStop byte
	lookCenter, lookLeft, lookRight, lookUp, lookDown byte
	lookRoute, moveRoute string
	hostname, port string
	rc *redisClient
	bus embd.I2CBus
	router *mux.Router
)

func lookHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER lookHandler")
	
	direction := mux.Vars(r)["direction"]
	switch direction {
	case "center":
		bus.WriteByte(arduino2, lookCenter)
	case "left":
		bus.WriteByte(arduino2, lookLeft)
	case "right":
		bus.WriteByte(arduino2, lookRight)
	case "up":
		bus.WriteByte(arduino2, lookUp)
	case "down":
		bus.WriteByte(arduino2, lookDown)
	}

	w.Write(nil)
}

func moveHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER moveHandler")

	direction := mux.Vars(r)["direction"]
	switch direction {
	case "stop":
		bus.WriteByte(arduino1, moveStop)
	case "left":
		bus.WriteByte(arduino1, moveLeft)
	case "right":
		bus.WriteByte(arduino1, moveRight)
	case "forward":
		bus.WriteByte(arduino1, moveForward)
	case "back":
		bus.WriteByte(arduino1, moveRight)
	}

	w.Write(nil)	
}

func getByteFromRedis(key string, r *redis.Client) (byte, error) {
	i, err := r.Cmd("GET", key).Int()
	return byte(i), err
}

func loadConfigFromRedis(r *redisClient) {
	arduino1 = r.getByte("core.i2c.addresses.arduino1")
	arduino2 = r.getByte("core.i2c.addresses.arduino2")
	lookRoute = r.getString("core.routes.look")
	moveRoute = r.getString("core.routes.move")
	hostname = r.getString("core.hostname")
	port = r.getString("core.port")
}

func errorHandler() {
	if r := recover(); r != nil {
		fmt.Println(r)
	}
	os.Exit(1)
}

func main() {
	
	defer errorHandler()
	
	rc = newRedisClient(REDIS_HOST)
	loadConfigFromRedis(rc)
	
	bus = embd.NewI2CBus(1)
	
	router = mux.NewRouter()
	router.HandleFunc(lookRoute, lookHandler).Methods("GET")
	router.HandleFunc(moveRoute, moveHandler).Methods("GET")
	http.Handle("/", router)
	
	host := hostname + ":" + port
	http.ListenAndServe(host, router)
}
