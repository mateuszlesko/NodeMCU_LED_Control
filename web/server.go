package main

import (
	"fmt"
	"net/http"
	"strconv"
	"strings"
	"time"
)

var status int = 0

var l *File = NewFile("../logs.txt")

func setStatus(wr http.ResponseWriter, r *http.Request) {
	ls, err := strconv.Atoi(r.URL.Query().Get("led"))
	if err == nil {
		status = status ^ ls

		sb := strings.Builder{}
		sb.WriteString(time.Now().String())
		sb.WriteString(` set status' value:`)
		sb.WriteString(fmt.Sprint(status))
		l.WriteToFile(sb.String())
		wr.Write([]byte(fmt.Sprint(status)))

	} else {
		wr.Write([]byte("Error"))
	}

}

func checkStatus(wr http.ResponseWriter, r *http.Request) {
	wr.Write([]byte(fmt.Sprint(status)))
}

func main() {
	smux := http.NewServeMux()
	smux.HandleFunc("/led/checkstatus", checkStatus)
	smux.HandleFunc("/led/setstatus", setStatus)

	fmt.Println("Server is listening on port :5108")
	http.ListenAndServe(":5108", smux)

}
