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
	val, err := r.client.Cmd("GET", "core.routes.look").Str()
	if err != nil {
		panic(fmt.Sprintf("could not get string value from redis for key '%s'", key))
	}
	return val
}
func (r *redisClient) getInt(key string) int {
	val, err := r.client.Cmd("GET", "core.routes.look").Int()
	if err != nil {
		panic(fmt.Sprintf("could not get int value from redis for key '%s'", key))
	}
	return val
}
func (r *redisClient) getByte(key string) byte {
	return byte(r.getInt(key))
}

var (
	r *redisClient
	arduino1 byte
	arduino2 byte
	moveForward byte
	moveBack byte
	moveLeft, moveRight, moveStop byte
	lookCenter, lookLeft, lookRight, lookUp, lookDown byte
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
	
	r = newRedisClient(REDIS_HOST)
	loadConfigFromRedis(r)
	
	bus = embd.NewI2CBus(1)
	
	router = mux.NewRouter()
	router.HandleFunc(lookRoute, lookHandler).Methods("GET")
	router.HandleFunc(moveRoute, moveHandler).Methods("GET")
	http.Handle("/", router)
	
	host := hostname + ":" + port
	http.ListenAndServe(host, router)
}
