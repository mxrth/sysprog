package main

import (
    "fmt"
    "net/http"
    "io"
    "os"
)

func do_request(method string, url string, filename string) {

    client := http.Client{}

    req, err := http.NewRequest(method, url, nil)
    if err != nil {
	fmt.Println("Could not create request")
	return
    }

    req.Header.Add("User-Agent", "My SysProg Client")
    resp,err := client.Do(req)
    if err != nil {
	fmt.Printf("Could not send request, %v\n", err)
	return
    }
    if resp.StatusCode != 200 {
	fmt.Println("Error: Got status %s %d", resp.Status , resp.StatusCode)
	return
    }
    file, err := os.Create(filename)
    if err != nil {
	fmt.Println("Could not create file response.html")
	return
    }
    io.Copy(file, resp.Body)
}

func main() {
    do_request("GET", "http://localhost:1234/test.html", "response_get.html")
    do_request("POST", "http://localhost:1234/test.html", "response_post.html")
}
