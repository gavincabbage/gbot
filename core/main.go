package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"github.com/gorilla/mux"
	"html/template"
	"io/ioutil"
	"net/http"
	"os"
)

const (
	API_URI_BASE   string = "http://127.0.0.1:4242/run/"
	TITLE_TEXT     string = "KodeKata"
	ERR_TEMPLATE   string = "ERROR: Problem parsing template"
	ERR_REQUEST    string = "ERROR: Problem reading client request"
	ERR_API        string = "ERROR: Problem reaching code execution API"
	ERR_RESPONSE   string = "ERROR: Problem reading API response"
	ERR_JSON_MARSH string = "ERROR: Problem marshaling JSON"
)

var (
	ROOT_DIR string = os.Getenv("KODEKATA_ROOT_DIR")
	BASE_TEMPLATE string = ROOT_DIR + "/app/templates/base.html"
	STATIC_DIR string = ROOT_DIR + "/app/static/"
	STUB_DIR string = ROOT_DIR + "/app/stubs/"
	LANGUAGES = map[string]int{
					"python": 4,
					"ruby": 17,
					"java": 10,
					"javascript": 35,
					"go": 114,
				}
)

func buildStubList() (stubs map[string][]string, err error) {
	
	kataDirList, err := ioutil.ReadDir(STUB_DIR)
	if err != nil {
		fmt.Println("ERROR: Problem reading STUB_DIR")
	}
	
	for _, dir := range kataDirList {
		fmt.Println("dir.Name =", dir.Name())
		
		if dir.IsDir() {
			
			langDirList, err := ioutil.ReadDir(STUB_DIR + "/" + dir.Name())
			if err != nil {
				fmt.Println("ERROR: Problem reading STUB_DIR subdirectory")
			}
			
			for _, subdir := range langDirList {
				fmt.Println("subdir.Name =", subdir.Name())
			}
		}
	}
	
	return stubs, err
}

func pageHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER pageHandler")

	template, err := template.ParseFiles(BASE_TEMPLATE)
	if err != nil {
		fmt.Println(ERR_TEMPLATE)
		w.Write([]byte(ERR_TEMPLATE))
	}

	vals := structs.MainPageValues{MainTitleText: TITLE_TEXT}
	template.Execute(w, vals)
}

func stubHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER stubHandler")

	vars := mux.Vars(r)
	lang, kata := vars["language"], vars["kata"]

	responseData := structs.StubResponse{
		Code:  "You chose lang = " + lang,
		Tests: "You chose kata = " + kata,
	}

	response, err := json.Marshal(responseData)
	if err != nil {
		fmt.Println(ERR_JSON_MARSH)
	}

	w.Write([]byte(string(response)))
}

func runHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("ENTER runHandler")

	lang := mux.Vars(r)["language"]

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Println(ERR_REQUEST)
	}
	
	source := &structs.StubResponse{}
	err = json.Unmarshal(body, source)
	if err != nil {
		fmt.Println("ERROR: Problem unmarshaling run request")
	}
	src := source.Code + "\n\n" + source.Tests
	
	requestData := structs.RunRequest{
		Input:  src,
	}
	fmt.Println("requestData", requestData)
	
	response, err := json.Marshal(requestData)
	if err != nil {
		fmt.Println(ERR_JSON_MARSH)
	}

	resp, err := http.Post(API_URI_BASE+lang, "application/json", bytes.NewReader(response))
	if err != nil {
		fmt.Println(ERR_API)
	}
	defer resp.Body.Close()

	body, err = ioutil.ReadAll(resp.Body)
	if err != nil {
		fmt.Println(ERR_RESPONSE)
	}

	w.Write([]byte(body))
}

func main() {
	
	stubs, err := buildStubList()
	if err != nil {
		fmt.Println("FAILED")
	} else {
		fmt.Println("STUBS:", stubs)
	}
  	
	r := mux.NewRouter()
	r.HandleFunc("/", pageHandler).Methods("GET")
	r.HandleFunc("/kata/{kata}/lang/{language}", stubHandler).Methods("GET")
	r.HandleFunc("/run/{language}", runHandler).Methods("POST")

	fileServer := http.FileServer(http.Dir(STATIC_DIR))
	r.PathPrefix("/static/").
		Handler(http.StripPrefix("/static/", fileServer))

	http.Handle("/", r)
	host := os.Getenv("IP") + ":" + os.Getenv("PORT")
	http.ListenAndServe(host, r)
}
